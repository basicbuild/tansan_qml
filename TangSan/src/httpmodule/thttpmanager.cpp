#include "THttpManager.h"

#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QtCore>
#include <QUrlQuery>

#include "TLogging.h"
#include "TStrUtils.h"
#include "TNetworkReplyTimeout.h"

#define THREAD_COUNT 1
#define MAX_HTTP_TASK_COUNT 4
#define LOG_TAG "THttpManager"

QString map2Str(const QMap<QString, QMap<QString, QString>> &group)
{
    QString sTemp = "";
    for (auto itr = group.begin(); itr != group.end(); ++itr) {
        sTemp.append("::");
        sTemp.append(itr.key());
        sTemp.append(itr.value().keys().join("::"));
        sTemp.append(itr.value().values().join("::"));
    }

    return sTemp;
}

class THttpManagerPrivate{
    class HttpTask{
    public:
        HttpTask(){}
        HttpTask(THttpManager::HttpTaskType taskType,
                 qulonglong taskId,
                 const QString& url,
                 const QMap<QString, QMap<QString, QString>>& group,
                 const QByteArray &data,
                 const QVariant& cookie,
                 int timeout)
            : taskType(taskType),
              taskId(taskId),
              url(url),
              group(group),
              data(data),
              cookie(cookie),
              timeout(timeout)
        {
        }

    public:
        THttpManager::HttpTaskType taskType; // 任务类型
        qulonglong taskId; // 任务Id
        QString url; // 请求url
        QMap<QString, QMap<QString, QString>> group; // 请求参数、请求头等
        QByteArray data; // 发送请求的数据
        QVariant cookie; // cookie
        int timeout; // 超时时间
    };

public:
    explicit THttpManagerPrivate();
    ~THttpManagerPrivate();

    bool isValidUrl(const QString& url);

    // 设置ssl支持
    void setSslConfig(const QString &url, QNetworkRequest &req);
    // 添加请求头
    void fillRequestHeader(QNetworkRequest &request, const QMap<QString, QString> &headers);
    // 添加cookie
    void fillRequestCookie(QNetworkRequest &request, const QVariant &cookie);
    // 添加请求参数
    void fillQueryParams(QUrlQuery &query, const QMap<QString, QString> &params);
    void translateError(QString &errCode, QString &errMsg);
    // 处理请求返回数据
    bool handleReplyResponse(qulonglong taskId, const QByteArray &replyData, QJsonValue &replyJsonVal, QString &errCode, QString &errMsg);

    // 添加HttpTask到队列
    void pushTask(THttpManager::HttpPriority priority, THttpManagerPrivate::HttpTask &&task);
    // 从队列删除HttpTask
    int popTask(THttpManagerPrivate::HttpTask &task);
    // 获取某个类型的任务数量
    int taskCnt(THttpManager::HttpPriority priority);

public:
    friend class THttpManager;

private:
    QSet<QString> m_runningRequests;  //
    QHash<QString, QString> m_errMsg; // 异常信息
    QQueue<HttpTask> m_tasks[THttpManager::HttpPriorityCount]; // HttpTask队列, 创建了3个队列
    mutable QMutex m_mutexTask; // http task 锁
    mutable QMutex m_mutexOps; //
    mutable QMutex m_mutexThread; // 线程统计 锁

    int m_threadCount = 0;
};

THttpManagerPrivate::THttpManagerPrivate(){}

THttpManagerPrivate::~THttpManagerPrivate(){}

bool THttpManagerPrivate::isValidUrl(const QString& url){
    if(url.isEmpty())
        return false;

    return QUrl::fromUserInput(url).isValid();
}

void THttpManagerPrivate::setSslConfig(const QString &url, QNetworkRequest &req)
{
    if (url.toLower().startsWith("https:")) {
        //        QSslConfiguration oSslConfig;
        //        oSslConfig.setProtocol(QSsl::TlsV1_0);
        //        req.setSslConfiguration(oSslConfig);
    }
}

void THttpManagerPrivate::fillRequestHeader(QNetworkRequest &request, const QMap<QString, QString> &headers)
{
    for (auto itr = headers.begin(); itr != headers.end(); ++itr) {
        request.setRawHeader(itr.key().toUtf8(), itr.value().toUtf8());
    }
}

void THttpManagerPrivate::fillRequestCookie(QNetworkRequest &request, const QVariant &cookie)
{
    if (!cookie.isNull()) {
        request.setHeader(QNetworkRequest::CookieHeader, cookie);
    }
}

void THttpManagerPrivate::fillQueryParams(QUrlQuery &query, const QMap<QString, QString> &params)
{
    for (auto itr = params.begin(); itr != params.end(); ++itr) {
        query.addQueryItem(itr.key(), itr.value());
    }
}

void THttpManagerPrivate::translateError(QString &errCode, QString &errMsg)
{
    if (!errMsg.isEmpty()) {
        return;
    }
    else if (m_errMsg.contains(errCode)) {
        errMsg = m_errMsg.value(errCode);
    }
    else {
        errCode = "1001";
        errMsg = m_errMsg.value(errCode);
    }
}

bool THttpManagerPrivate::handleReplyResponse(qulonglong taskId, const QByteArray &replyData, QJsonValue &replyJsonVal,
                                              QString &errCode, QString &errMsg)
{
    QJsonDocument oDoc = QJsonDocument::fromJson(replyData);
    if (oDoc.isEmpty() || oDoc.isNull()) {
        return false;
    }
    if (oDoc.isObject()) {
        QJsonObject oJson = oDoc.object();
        if (oJson.contains("code")) {
            // 服务端返回code=0也代表请求成功
            if (200 == oJson.value("code").toInt() || 0 == oJson.value("code").toInt()) {
              //  YLOGD(LOG_TAG) << __FUNCTION__ << " reply success";
                if (oJson.contains("data")) {
                    replyJsonVal = oJson.value("data");
                }
                else {
                    replyJsonVal = oJson;
                }
            }
            else {
                errCode = QString::number(oJson.value("code").toInt());
                translateError(errCode, errMsg);
               // LOGE(LOG_TAG, "@@@@ %s: task %lld reply fail code = %d; msg = %s", __FUNCTION__, taskId,
                  //   oJson.value("code").toInt(), oJson.value("msg").toString().toStdString().c_str());
                return false;
            }
        }
    }
    else if (oDoc.isArray()) {
        replyJsonVal = oDoc.array();
    }
    //LOGD(LOG_TAG, "@@@@ %s finish", __FUNCTION__);
    return true;
}

void THttpManagerPrivate::pushTask(THttpManager::HttpPriority priority, THttpManagerPrivate::HttpTask &&task)
{
    QMutexLocker locker(&m_mutexTask);
    m_tasks[priority].enqueue(task);

    QString log = "pushTask taskId:" + QString::number(task.taskId)
            + ", url:" + task.url
            + ", m_threadCount" + QString::number(m_threadCount);
    LOGT(LOG_TAG, log)
}

int THttpManagerPrivate::popTask(THttpManagerPrivate::HttpTask &task)
{
    QMutexLocker locker(&m_mutexTask);
    if(m_tasks[THttpManager::HttpPriorityDirectly].size()){
        task = m_tasks[THttpManager::HttpPriorityDirectly].dequeue();
        QString log = "pop Priority Directly taskId:" + QString::number(task.taskId)+ ", url:" + task.url;
        LOGT(LOG_TAG, log)
                return 1;
    }
    if(m_tasks[THttpManager::HttpPriorityHigh].size()){
        task = m_tasks[THttpManager::HttpPriorityHigh].dequeue();
        QString log = "pop Priority High taskId:" + QString::number(task.taskId)+ ", url:" + task.url;
        LOGT(LOG_TAG, log)
                return 1;
    }
    if(m_tasks[THttpManager::HttpPriorityNormal].size()){
        task = m_tasks[THttpManager::HttpPriorityNormal].dequeue();
        QString log = "pop Priority Normal taskId:" + QString::number(task.taskId)+ ", url:" + task.url;
        LOGT(LOG_TAG, log)
                return 1;
    }
    return 0;
}

int THttpManagerPrivate::taskCnt(THttpManager::HttpPriority priority)
{
    QMutexLocker locker(&m_mutexTask);
    if(priority == THttpManager::HttpPriorityCount){
        return m_tasks[THttpManager::HttpPriorityDirectly].size() +
                m_tasks[THttpManager::HttpPriorityHigh].size() +
                m_tasks[THttpManager::HttpPriorityNormal].size();
    }else{
        return m_tasks[priority].size();
    }
}

//////////////////////////////////////////////////////////////////////////////
THttpManager::THttpManager(QObject* parent)
    : QObject(parent)
    , p(new THttpManagerPrivate) {

}

THttpManager::~THttpManager(){}

bool THttpManager::sendGet(qulonglong taskId,
                           const QString& url,
                           const QMap<QString, QMap<QString, QString>>& group,
                           const QVariant& cookie,
                           int timeout,
                           HttpPriority priority)
{
    Q_UNUSED(taskId)
    //Q_UNUSED(url)
    Q_UNUSED(group)
    Q_UNUSED(cookie)
    Q_UNUSED(timeout)
    Q_UNUSED(priority)
    // 检查url是否可用
    if(!p->isValidUrl(url)){
        QString logge =  "url: " + url + " is not valid.";
        LOGT(LOG_TAG, logge)
                return false;
    }

    // 当前请求加入 HttpTask队列
    p->pushTask(priority, THttpManagerPrivate::HttpTask(THttpManager::HttpTaskGet, taskId, url, group, QByteArray(),
                                                        cookie, timeout));

    // 创建新的请求
    if(p->m_threadCount < THREAD_COUNT){

    }

    return true;
}

void THttpManager::newTask()
{
    increaseThread();
    // 创建线程，异步处理请求过程
    std::thread t([=]{
        QNetworkAccessManager *accessMgr = new QNetworkAccessManager();

        QEventLoop loop;
        QMap<qulonglong, THttpManagerPrivate::HttpTask> tasks;

        std::unique_ptr<QMetaObject::Connection> pconn{new QMetaObject::Connection};
        QMetaObject::Connection &conn = *pconn;
        conn = QObject::connect(this, &THttpManager::requestFinished, QThread::currentThread(),
                                [this, &tasks, &loop, &conn, &accessMgr]
                                (qulonglong taskId,
                                int method,
                                bool isSuccess,
                                const QJsonValue &jsonResponse,
                                const QString &errCode,
                                const QString &errMsg){
            Q_UNUSED(method);
            Q_UNUSED(isSuccess);
            Q_UNUSED(jsonResponse);
            Q_UNUSED(errCode);
            Q_UNUSED(errMsg);
            if(tasks.contains(taskId)){
                tasks.remove(taskId);

                if(tasks.isEmpty())
                    loop.exit();
            }
        }); // connect

        // 请求超时定时器
        QTimer timerHttpTimeout;
        timerHttpTimeout.setInterval(HTTP_REQUEST_TIMEOUT * 2);
        connect(&timerHttpTimeout, &QTimer::timeout, this, [this, &loop]{
            LOGT(LOG_TAG, "http task event loop timeout")
            loop.exit();
        }); // connect

        // 开始请求
        THttpManagerPrivate::HttpTask task;
        bool shouldStop = false;
        while(!shouldStop){
            while (p->popTask(task)) {
                tasks.insert(task.taskId, task);
                // 网路请求
                handleHttpTask(accessMgr, task.taskType, task.taskId, task.url, task.group, task.data, task.cookie,task.timeout);
                if(tasks.count() >= MAX_HTTP_TASK_COUNT)
                    break;
            } // while

            timerHttpTimeout.start();
            loop.exec();
            timerHttpTimeout.stop();
            if(!p->taskCnt(THttpManager::HttpPriorityCount)){
                shouldStop = true;
                break;
            }
        } // while

        timerHttpTimeout.stop();
        tasks.clear();
        accessMgr->clearAccessCache();
        accessMgr->clearConnectionCache();
        accessMgr->deleteLater();
        accessMgr = nullptr;
        decreaseThread();
    }); // std::thread

    t.detach();
}

void THttpManager::increaseThread()
{
    p->m_threadCount++;
}

void THttpManager::decreaseThread()
{
    QMutexLocker locker(&p->m_mutexThread);
    if(p->m_threadCount > 0){
        p->m_threadCount--;
    }
}

void THttpManager::handleHttpTask(QNetworkAccessManager *accessMgr, HttpTaskType type, qulonglong taskId,
                    const QString &url, const QMap<QString, QMap<QString, QString>> &group,
                    const QByteArray &data, const QVariant &cookie, int timeout)
{
    QMutexLocker locker(&p->m_mutexOps);
    switch (type) {
    case HttpTaskGet:
        handleHttpGetTask(accessMgr, taskId, url, group, cookie, timeout);
        break;
    case HttpTaskPost:
        break;
    case HttpTaskPostData:
        break;
    case HttpTaskPostFile:
        break;
    case HttpTaskGetRawHeader:
        break;
    }
}

void THttpManager::handleHttpGetTask(QNetworkAccessManager *accessMgr, qulonglong taskId, const QString &url,
                       const QMap<QString, QMap<QString, QString>> &group, const QVariant &cookie, int timeout)
{
    QString sTemp = QString("%1::%2%3").arg(__FUNCTION__).arg(url).arg(map2Str(group));
    QString sFinger = StrUtils::getMD5(sTemp.toUtf8());

    if(p->m_runningRequests.contains(sFinger)){
        emit requestFinished(taskId, _REQUEST_HTTP_SENDPOST, false, QJsonValue(), QString(), QString("repeat request, canncelled"));
        return;
    }

   p->m_runningRequests.insert(sFinger);
   // 添加查询参数
   QUrlQuery _query;
   _query.addQueryItem("client", DEVICE_TYPE);
   p->fillQueryParams(_query, group.value("params"));

   QUrl _url = QUrl::fromUserInput(url);
   _url.setQuery(_query);

   // 设置请求头、cookie和ssl
   QNetworkRequest _request;
   p->fillRequestHeader(_request, group.value("headers"));
   p->fillRequestCookie(_request, cookie);
   p->setSslConfig(url, _request);
   _request.setUrl(_url);

   QNetworkReply *_reply = accessMgr->get(_request);
   _reply->setProperty("finger", sFinger);
   _reply->setProperty("url", url);

   QReplyTimeout *_replyTimeout = new QReplyTimeout(_reply, timeout);

   connect(_reply, &QNetworkReply::finished, [this, taskId, _reply, sFinger, _replyTimeout](){
       if (QNetworkReply::NoError == _reply->error()) {
           QByteArray oReplyData = _reply->readAll();
           QJsonValue jsonResponse;
           QString errCode, errMsg;
           bool bSuccess = p->handleReplyResponse(taskId, oReplyData, jsonResponse, errCode, errMsg);
           //LOGD(LOG_TAG, "@@@@ %s taskId %lld success = %d", __FUNCTION__, taskId, bSuccess);
           if (!bSuccess) {
               //YLOGE(LOG_TAG) << "error url " << reply->url().toString().toStdString();
           }
           emit requestFinished(taskId, _REQUEST_HTTP_SENDGET, bSuccess, jsonResponse, errCode, errMsg);
       }
       else {
          // YLOGE(LOG_TAG) << "@@@@ %s reply fail code = " << reply->error()
                         // << "; msg = " << reply->errorString().toStdString();
           //YLOGE(LOG_TAG) << "error url " << reply->url().toString().toStdString();
           emit requestFinished(taskId, _REQUEST_HTTP_SENDGET, false, QJsonValue(), QString::number(_reply->error()),
                                _reply->errorString());
       }
       p->m_runningRequests.remove(sFinger);
       _reply->deleteLater();
       _replyTimeout->deleteLater();
   });

   connect(_reply,
           static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),
           [this, taskId, _reply, sFinger, _replyTimeout](QNetworkReply::NetworkError err) {
               QString errCode = QString::number(err);
               QString errMsg = _reply->errorString();
               //LOGE(LOG_TAG, "@@@@ %s reply fail code = %s; msg = %s", __FUNCTION__, errCode.toStdString().c_str(),
                  //  errMsg.toStdString().c_str());

               p->translateError(errCode, errMsg);
               p->m_runningRequests.remove(_reply->property("finger").toString());
               //YLOGE(LOG_TAG) << "error url " << reply->url().toString().toStdString();
               emit requestFinished(taskId, _REQUEST_HTTP_SENDGET, false, QJsonValue(), errCode, errMsg);
               _reply->deleteLater();
               _replyTimeout->deleteLater();
           });

   if (_reply && QNetworkReply::NoError != _reply->error()) {
       QString errCode = QString::number(_reply->error());
       QString errMsg = _reply->errorString();
       //YLOGE(LOG_TAG) << "error url " << reply->url().toString().toStdString();
       emit requestFinished(taskId, _REQUEST_HTTP_SENDGET, false, QJsonValue(), errCode, errMsg);
       _reply->deleteLater();
       _replyTimeout->deleteLater();
   }
}














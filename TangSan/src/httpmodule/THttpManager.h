#ifndef THTTPMANAGER_H
#define THTTPMANAGER_H

#include <QObject>
#include <QVariant>

#include "THttpDefine.h"

class QNetworkReply;
class QNetworkAccessManager;
class THttpManagerPrivate;
class THttpManager : public QObject {
    Q_OBJECT
  public:
    enum HttpPriority {
        HttpPriorityDirectly,
        HttpPriorityHigh,
        HttpPriorityNormal,
        HttpPriorityCount  // do not use
    };
    enum HttpTaskType { HttpTaskGet, HttpTaskPost, HttpTaskPostData, HttpTaskGetRawHeader, HttpTaskPostFile };
    explicit THttpManager(QObject* parent = nullptr);
    virtual ~THttpManager();

    /**
     * @brief 异步发送get请求
     * @param {qulonglong} taskid - 请求的任务id
     * @param {QString} url - 请求url
     * @param {QMap<QString, QMap<QString, QString>>} group - 请求参数、请求头等
     * @param {QVariant} cookie - 请求cookie
     * @param {int} timeout - 超时时间
     *
     * @return true or false
     */
    bool sendGet(qulonglong taskId,
                 const QString& url,
                 const QMap<QString, QMap<QString, QString>>& group,
                 const QVariant& cookie = QVariant(),
                 int timeout = HTTP_REQUEST_TIMEOUT,
                 HttpPriority priority = HttpPriorityNormal);

signals:
    void requestFinished(qulonglong taskId,
                         int method,
                         bool isSuccess,
                         const QJsonValue &jsonResponse,
                         const QString &errCode,
                         const QString &errMsg);

private:
    void handleHttpGetTask(QNetworkAccessManager *accessMgr,
                           qulonglong taskId,
                           const QString &url,
                           const QMap<QString, QMap<QString, QString>> &group,
                           const QVariant &cookie,
                           int timeout);

    void handleHttpTask(QNetworkAccessManager *accessMgr,
                        HttpTaskType type,
                        qulonglong taskId,
                        const QString &url,
                        const QMap<QString, QMap<QString, QString>> &group,
                        const QByteArray &data,
                        const QVariant &cookie,
                        int timeout);

    void newTask();
    void increaseThread();
    void decreaseThread();
private:
    THttpManagerPrivate *p;
};

#define HTTPMANAGER CSingleton<THttpManager>::instance()

#endif  // THTTPMANAGER_H

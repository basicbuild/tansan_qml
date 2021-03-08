#include "TGuiApplication.h"

#include <QQmlEngine>
#include <QQuickView>
#include <QtQml>

#include "TSystemBase.h"
#include "TEnumWrapper.h"

class TGuiApplicationPrivate {
  public:
    explicit TGuiApplicationPrivate();
    ~TGuiApplicationPrivate();

    /**
     * @brief view展示及基类exec调用
     *
     * @return
     */
    int exec();

    /**
     * @brief 用于初始化业务类
     *
     * @return
     */
    void initClass();

    /**
     * @brief 用于初始化UI
     *
     * @return
     */
    void initUi();

  private:
    /**
     * @brief 用于初始化业务类
     *
     * @return
     */
    void initClassPrivate(QQuickView* needClassView);

  private:
    QQuickView* m_pView = new QQuickView();
};

TGuiApplicationPrivate::TGuiApplicationPrivate() {
    QCoreApplication::setOrganizationName(QStringLiteral("CSDN"));
    QCoreApplication::setOrganizationDomain(
        QStringLiteral("https://blog.csdn.net/qq_27096221?spm=1001.2101.3001.5343"));
    QCoreApplication::setApplicationName(QStringLiteral("TangSan"));

    QTextCodec::setCodecForLocale(QTextCodec::codecForName(QByteArrayLiteral("UTF-8")));

    /*
     * qmlRegisterUncreatableType()将c++类(派生自QObject)注册到QML系统(注册为非实例化类型)。
     * 但是我们不能在qml文件中为类创建对象，我们需要在qml文件中使用属性枚举方式来调用。
     * 若QML要访问类里的枚举值必须使用以下宏将其提供给QML系统，否则无法访问
     * Q_ENUMS(enumType)
     *  qmlRegisterUncreatableType("ModuleName/uri", MajorVersion, MinorVersion, "QmlName", "message");
   */
    qmlRegisterUncreatableType<TEnumWrapper>("tangsan.github", 1, 0, "TEnum", "Not creatable as it is an enum type.");

    initClass();
    initUi();
}

TGuiApplicationPrivate::~TGuiApplicationPrivate() {
    if (m_pView) {
        m_pView->deleteLater();
        m_pView = nullptr;
    }
}

int TGuiApplicationPrivate::exec() {
    m_pView->show();

    return QGuiApplication::exec();
}

void TGuiApplicationPrivate::initClass() { initClassPrivate(m_pView); }

void TGuiApplicationPrivate::initUi() {
    m_pView->setSource(QUrl(QStringLiteral("qrc:/main.qml")));

    m_pView->setResizeMode(QQuickView::SizeViewToRootObject);
    // m_pView->setFlags(Qt::FramelessWindowHint);
}

void TGuiApplicationPrivate::initClassPrivate(QQuickView* needClassView) {
    Q_ASSERT(nullptr != needClassView);
    m_pView->rootContext()->setContextProperty("systemBase", SYSTEMBASE);
}

TGuiApplication::TGuiApplication(int& argc, char** argv) :
    QGuiApplication(argc, argv), p(new TGuiApplicationPrivate()) {}

TGuiApplication::~TGuiApplication() {
    if (p) {
        delete p;
        p = nullptr;
    }
}

int TGuiApplication::exec() { return p->exec(); }

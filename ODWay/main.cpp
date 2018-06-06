
#include <QDir>
#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlFileSelector>
#include <QQuickView> //Not using QQmlApplicationEngine because many examples don't have a Window{}

#include <ODWayM/ODWayM.h>

#include <ODWayV/ODVTime.h>

int main(int argc, char* argv[])
{
    /**
     * Init Model layer.
     */
    // get home path.
    std::string dir = QDir::homePath().toStdString();
#ifdef Q_OS_IOS
    dir += "/Documents/list.db";
#else
    dir += "/brick/List/list.db";
#endif
    ODWayM::Instance(dir)->ReadDB();

    /**
     * Init View layer.
     */
    qmlRegisterType<ODVTime>("ODVTime", 1, 0, "ODVTimeList");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc,argv);
    app.setOrganizationName("QtProject");
    app.setOrganizationDomain("qt-project.org");
    app.setApplicationName(QFileInfo(app.applicationFilePath()).baseName());
    QQuickView view;
    if (qgetenv("QT_QUICK_CORE_PROFILE").toInt()) {
        QSurfaceFormat f = view.format();
        f.setProfile(QSurfaceFormat::CoreProfile);
        f.setVersion(4, 4);
        view.setFormat(f);
    }
    if (qgetenv("QT_QUICK_MULTISAMPLE").toInt()) {
        QSurfaceFormat f = view.format();
        f.setSamples(4);
        view.setFormat(f);
    }
    view.connect(view.engine(), &QQmlEngine::quit, &app, &QCoreApplication::quit);
    new QQmlFileSelector(view.engine(), &view);
    view.setSource(QUrl("qrc:///main.qml"));
    if (view.status() == QQuickView::Error)
        return -1;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();
    return app.exec();
}

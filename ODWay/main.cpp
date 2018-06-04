#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDir>

#include <ODWayM/ODWayM.h>

int main(int argc, char *argv[])
{
    /**
     * Init Model layer.
     */
    // get home path.
    std::string dir = QDir::homePath().toStdString() + "/test.db";
    ODWayM::Instance(dir)->ReadDB();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

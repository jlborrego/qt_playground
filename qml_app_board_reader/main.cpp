#include <QGuiApplication>
#include <QQmlApplicationEngine>
//#include "controller.h"



//int sys_network_boot(char *parameter)
//{
//    slot_init("", __MMC_SERVICE_IP_PORT, 0);
//    mmc_channel_boot();
//    mmc_channel_configure(parameter);
//    return 0;
//}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

//    Controller controller;

//    engine.rootContext()->setContextProperty("Controller", &controller);

    const QUrl url(u"qrc:/AppTarj/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

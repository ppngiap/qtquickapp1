#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "material.h"
#include "colormap.h"
#include "materiallistmodel.h"


void testMaterialTheme()
{
    Material m;
    m.read("input/daynav.xml");
    m.print();
    m.update("yellow-clr", "00ff22ff");
    m.write("output/outnav.xml");
}

void testMaterialMap()
{
    ColorMap cm;
    cm.read("input/colormap.xml");
    cm.print();
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<MaterialListModel>("com.comtechtel", 1, 0, "MaterialListModel");

    QQmlApplicationEngine engine;
    //engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    engine.load(QUrl(QLatin1String("qrc:/ThemeSelectorTest.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    testMaterialMap();

    return app.exec();
}

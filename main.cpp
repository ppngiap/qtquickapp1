#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "colortheme.h"
#include "colormap.h"
#include "materiallistmodel.h"


void testColorTheme()
{
    ColorTheme ct;
    ct.read("input/daynav.xml");
    ct.print();
    ct.update("yellow-clr", "00ff22ff");
    ct.write("output/outnav.xml");
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

    qmlRegisterType<Material>("com.comtechtel.maptool", 1, 0, "Material");
    qmlRegisterType<MaterialListModel>("com.comtechtel.maptool", 1, 0, "MaterialListModel");

    QQmlApplicationEngine engine;
    //engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    engine.load(QUrl(QLatin1String("qrc:/ThemeSelectorTest.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    testMaterialMap();
    testColorTheme();

    return app.exec();
}

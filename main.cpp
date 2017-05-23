#include <QApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QQmlContext>

#include "iconsimageprovider.h"
#include "iconthemeimageprovider.h"

#include "qmldownloader.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Unvanquished Development");
    QCoreApplication::setOrganizationDomain("unvanquished.net");
    QCoreApplication::setApplicationName("Unvanquished Updater");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    int fontId = QFontDatabase::addApplicationFont(":resources/Roboto-Regular.ttf");
    if (fontId != -1) {
        QFont font("Roboto-Regular");
        font.setPointSize(10);
        app.setFont(font);
    }
    QQmlApplicationEngine engine;
    engine.addImportPath(QLatin1String("qrc:/"));
    engine.addImageProvider(QLatin1String("fluidicons"), new IconsImageProvider());
    engine.addImageProvider(QLatin1String("fluidicontheme"), new IconThemeImageProvider());
    auto* context = engine.rootContext();
    Settings settings;
    QmlDownloader downloader;
    context->setContextProperty("updaterSettings", &settings);
    context->setContextProperty("downloader", &downloader);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    return app.exec();
}

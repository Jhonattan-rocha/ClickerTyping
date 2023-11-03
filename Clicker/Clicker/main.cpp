#include "mainWindowInstance.h"

MainWindow* w;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Clicker_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    w = new MainWindow; // Crie uma instância dinamicamente
//    w->initialize();
//    w->updateClikSaves();
    w->show();
    int result = a.exec();

    // Certifique-se de liberar a memória da instância de MainWindow
    delete w;
    return result;
}

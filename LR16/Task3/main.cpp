#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    
    app.setApplicationName("Data Structures Demo");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("University Lab");
    
    MainWindow window;
    window.resize(900, 700);
    window.show();

    return app.exec();
}
#include <QApplication>

#include <cstdlib>
#include <ctime>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    std::srand(std::time(nullptr));
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return QApplication::exec();
}
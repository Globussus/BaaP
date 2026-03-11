#include "mainwindow.h"
#include "tools.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    auto *centralWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(centralWidget);

    labelStats = new QLabel("Выберите папку для анализа", this);
    buttonSelect = new QPushButton("Выбрать папку", this);
    buttonOpenFile = new QPushButton("Открыть файл", this);

    layout->addWidget(labelStats);
    layout->addWidget(buttonSelect);
    layout->addWidget(buttonOpenFile);

    setCentralWidget(centralWidget);

    connect(buttonSelect, &QPushButton::clicked, this, &MainWindow::showDirectoryInfo);
    connect(buttonOpenFile, &QPushButton::clicked, this, &MainWindow::openFile);
}

void MainWindow::showDirectoryInfo() {
    QString path = QFileDialog::getExistingDirectory(this, "Выберите папку");
    if (!path.isEmpty()) {
        Stats stats = {0, 0};
        countFilesAndDirectories(path, stats);
        labelStats->setText(QString("Папок: %1, Файлов: %2").arg(stats.directories).arg(stats.files));
    }
}

void MainWindow::openFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл для открытия");
    if (!filePath.isEmpty()) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    }
}

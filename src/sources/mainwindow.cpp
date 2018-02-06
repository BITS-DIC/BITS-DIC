#include "src/headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(WINDOW_TITLE);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::information(this, "About", "Developed by\nDigital Image Correlation Lab\nVersion 0.1");
}

void MainWindow::on_actionContribute_triggered() {
    QDesktopServices::openUrl(QUrl("https://github.com/BITS-DIC/BITS-DIC", QUrl::TolerantMode));
}


void MainWindow::on_actionExit_triggered() {
    exit(0);
}

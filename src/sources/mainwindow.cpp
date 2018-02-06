#include "src/headers/mainwindow.h"
#include "ui_mainwindow.h"

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

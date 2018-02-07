#include "src/headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QStatusBar>
#include <QFileDialog>

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

void MainWindow::on_actionLoad_Reference_Image_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                     tr("Select Reference Image File"),
                                                     "",
                                                     "Images (*.png *.jpg *.jpeg *.tif *.tiff);;All Files (*)"
                                                     );
    QString status = tr("");
    if (fileName.length() == 0) status = tr("No File Selected");
    else status = tr("Selected ") + fileName;
    statusBar()->showMessage(status, 2000);
}

void MainWindow::on_actionLoad_Current_Image_s_triggered()
{
    QStringList files = QFileDialog::getOpenFileNames(this,
                                                      tr("Select Current Image(s)"),
                                                      "",
                                                      "Images (*.png *.jpg *.jpeg *.tif *.tiff);;All Files (*)"
                                                      );
    QString status;
    switch (files.length()) {
        case 0: {
            status = tr("No File Selected");
        } break;

        case 1: {
            status = tr("Selected file ") + files.at(0);
        } break;

        default: {
            status = tr("Selected ") + tr(std::to_string(files.length()).c_str()) + tr(" Files : ")
                    + files.first() + " ... " + files.last();
        } break;
    }
    statusBar()->showMessage(status, 2000);
}

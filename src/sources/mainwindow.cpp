#include "src/headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QStatusBar>
#include <QFileDialog>
#include <QDesktopWidget>
#include <opencv2/opencv.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(WINDOW_TITLE);
    this->showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Method to convert a cv::Mat object to QImage object.
 * @param cv::Mat object.
 * @return Non null QImage object.
 */
QImage matToQImage(const cv::Mat& mat) {
    if(mat.type() == CV_8UC1) {
        // 8-bits unsigned, NO. OF CHANNELS=1
        //Example would be grayscale images

        // Set the color table (used to translate colour indexes to qRgb values)
        QVector<QRgb> colorTable;
        for (int i=0; i<256; i++)
            colorTable.push_back(qRgb(i,i,i));
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*) mat.data;
        // Create QImage with same dimensions as input Mat
        QImage qimg(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
        qimg.setColorTable(colorTable);
        return qimg;
    } else {
        return QImage();
    }
}

void MainWindow::on_actionLoad_Reference_Image_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                     tr("Select Reference Image File"),
                                                     "",
                                                     "Images (*.png *.jpg *.jpeg *.tif *.tiff);;All Files (*)"
                                                     );
    QString status = tr("");
    if (fileName.length() == 0) status = tr("No File Selected");
    else {
        status = tr("Selected ") + fileName;
        statusBar()->showMessage(status, 2000);
        cv::Mat refImage = cv::imread(fileName.toStdString(), cv::IMREAD_GRAYSCALE);
        QImage convertedImage = matToQImage(refImage);

        //reducing image width and height
        int width = convertedImage.width();
        int height = convertedImage.height();
        if (width > height && width > 512) {
            height = (height * 512) / width;
            width = 512;
        } else if(height > width && height > 512) {
            width = (width * 512) / height;
            height = 512;
        }

        ui->label->setPixmap(QPixmap::fromImage(convertedImage.scaled(width, height, Qt::KeepAspectRatio)));
    }
}

void MainWindow::on_actionLoad_Current_Image_s_triggered() {
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

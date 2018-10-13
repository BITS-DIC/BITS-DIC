#include "setroi.h"
#include "ui_setroi.h"
#include "utils.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>

SetROI::SetROI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetROI)
{
    ui->setupUi(this);
    roiImageMat = cv::Mat::zeros(0, 0, CV_8UC1);
}

SetROI::~SetROI()
{
    delete ui;
    roiImageMat.release();
}

void SetROI::on_setRoiLoadFromFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Select Reference Image File"),
            QDir::homePath(),
            "Images (*.png *.jpg *.jpeg *.tif *.tiff);;All Files (*)",
            nullptr,
            QFileDialog::DontUseNativeDialog
        );
    QString status = tr("");
    if (fileName.length() == 0) qDebug() << "No File Selected";
    else {
        //TODO check for data consistency if images are larger/smaller than roi we can have issue

        //Display ROI data
        roiImageMat = cv::imread(fileName.toStdString(), cv::IMREAD_GRAYSCALE);
        QImage roiImageQImg = Utils::matToQImage(roiImageMat);
        Utils::loadImage(roiImageQImg, ui->setRoiImageDisplay);

        qDebug() << "Success in loading file " + fileName;
    }
}

void SetROI::on_setRoiButtonBox_accepted()
{
    //Send ROI data
    //No checking is done here for validity of data as ref and curr images may not have been set up
    qDebug() << "Sending roi mat data";
    emit onRoiSet(roiImageMat.clone());
}


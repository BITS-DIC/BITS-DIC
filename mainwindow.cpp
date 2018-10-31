#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setroi.h"
#include "utils.h"
#include <QFile>
#include <QDir>
#include <QStatusBar>
#include <QFileDialog>
#include <QDesktopWidget>
#include <cstdlib>
#include <QDebug>
#include <utility>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(WINDOW_TITLE);
    this->showMaximized();
    dic = new Dic();
    setRoiDialog = new SetROI(this);
    currImgIndex = -1;
    /*std::vector<float> distanceF{0, 1, 2, 3, 4, 5, 6, 7}; // this is the type of the vector
    std::vector<cv::Complex<float> > ff;
    cv::dft(distanceF, ff, cv::DFT_ROWS|cv::DFT_COMPLEX_OUTPUT);
    for (int i = 0; i < ff.size(); i++) {
        qDebug("%f + %f i\t", ff[i].re, ff[i].im);
    }*/
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dic;
    delete setRoiDialog;
}


void MainWindow::setCurrentImageIndex(int i) {
    currImgIndex = i;
    QImage qim = Utils::matToQImage(dic->getCurrentImage(i));
    Utils::loadImage(qim, ui->currImage, 512);
    ui->currentImageIndex->setText(tr(std::to_string(i + 1).c_str()));
    ui->prevImage->setEnabled(i > 0);
    ui->nextImage->setEnabled(i < dic->getCurrentImagesCount() - 1);
    ui->currentImageIndex->setEnabled(true);
}

void MainWindow::on_actionLoad_Reference_Image_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Select Reference Image File"),
            QDir::homePath(),
            "Images (*.png *.jpg *.jpeg *.tif *.tiff);;All Files (*)",
            nullptr,
            QFileDialog::DontUseNativeDialog
        );
    QString status = tr("");
    if (fileName.length() == 0) status = tr("No File Selected");
    else {
        status = tr("Selected ") + fileName;
        statusBar()->showMessage(status, 2000);
        cv::Mat refImage = cv::imread(fileName.toStdString(), cv::IMREAD_GRAYSCALE);
        dic->setReferenceImage(refImage);
        QImage convertedImage = Utils::matToQImage(refImage);
        Utils::loadImage(convertedImage, ui->refImage, 512);
        ui->refImgChk->setChecked(true);
        ui->refImgChk->setText(tr("Reference \n Image Loaded"));
    }
}

QStringList files;
void MainWindow::on_actionLoad_Current_Image_s_triggered() {
    files = QFileDialog::getOpenFileNames(this,
            tr("Select Current Image(s)"),
            QDir::homePath(),
            "Images (*.png *.jpg *.jpeg *.tif *.tiff);;All Files (*)",
            0, QFileDialog::DontUseNativeDialog
        );
    if (files.length() == 0) {
        statusBar()->showMessage(tr("No File Selected"), 2000);
        return;
    }

    cv::Mat *imagesList = (cv::Mat *) calloc(files.length(), sizeof(cv::Mat));
    for (int i = 0; i < files.length(); i++) {
        imagesList[i] = cv::imread(files[i].toStdString(), cv::IMREAD_GRAYSCALE);
    }
    dic->setCurrentImages(files.length(), imagesList);
    setCurrentImageIndex(0);

    QString status;
    if (files.length() == 1) {
        status = tr("Selected file ") + files.at(0);
        ui->currImgChk->setText("Loaded 1 \ncurrent image");
    } else {
        status = tr("Selected ") + tr(std::to_string(files.length()).c_str()) + tr(" Files : ")
                + files.first() + " ... " + files.last();
        ui->currImgChk->setText(tr("Loaded ") + tr(std::to_string(files.length()).c_str()) + tr(" \ncurrent images"));
    }
    ui->currImgChk->setChecked(true);

    statusBar()->showMessage(status, 2000);
}

void MainWindow::on_prevImage_clicked()
{
    setCurrentImageIndex(currImgIndex - 1);
}

void MainWindow::on_nextImage_clicked()
{
    setCurrentImageIndex(currImgIndex + 1);
}

void MainWindow::on_actionSet_Region_of_Interest_ROI_triggered()
{
    qDebug() << "Loading SetROI";
    setRoiDialog->open();

    qDebug() << "Setting up signal/slot connection for ROI";
    connect(setRoiDialog, SIGNAL(onRoiSet(cv::Mat)), this, SLOT(onRoiSet(cv::Mat)), Qt::UniqueConnection);
}

/**
 * @brief MainWindow::onRoiSet When SetROI gives a signal that user has decided on ROI data.
 * @param roiImage cv::Mat image data. //TODO make sure it is either 0/255 data.
 */
void MainWindow::onRoiSet(cv::Mat roiImage) {
    dic->setROI(roiImage);

    ui->roiChk->setChecked(true);
    ui->roiChk->setText(tr("ROI set"));

    // Show preview of ROI (to be removed later)
    //NOTE If this fails, high-gui may be not have been implemented in opencv build
    //cv::namedWindow("ROI preview", cv::WINDOW_NORMAL);
    //cv::imshow("ROI preview", roiImage);
    //cv::waitKey(0);

    //TODO what happens in case SetROI window gets closed. Maybe unique connection will prevent extra connects.
    qDebug() << "Disconnecting signal/slot connection for ROI";
    disconnect(setRoiDialog, SIGNAL(onRoiSet(cv::Mat)), this, SLOT(onRoiSet(cv::Mat)));
}

void MainWindow::on_actionPerform_DIC_Analysis_triggered()
{
    dic->performDicAnalysis();
}

void MainWindow::on_actionSet_DIC_Parameters_triggered()
{
    //TODO open gui and get parameters from user
    Params fakeParams;
    int seedX = dic->getReferenceImage().cols / 2;
    int seedY = dic->getReferenceImage().rows / 8;
    fakeParams.subsetSize = 10;
    fakeParams.subsetSpacing = 0;
    fakeParams.seedPoint = std::make_pair(seedX, seedY);
    dic->setParams(fakeParams);
    qDebug( "seed location is {%d, %d}", seedX, seedY);
    ui->paramsChk->setText(tr("Fake Parameters set"));
    ui->paramsChk->setChecked(true);
}

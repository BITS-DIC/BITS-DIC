#include "mainwindow.h"
#include "setroi.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QDir>
#include <QElapsedTimer>
#include <QFile>
#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QStatusBar>
#include <QThread>
#include <cstdlib>
#include <utility>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle(WINDOW_TITLE);
    this->showMaximized();
    dic = new Dic();
    currImgIndex = -1;
}

MainWindow::~MainWindow() {
    delete ui;
    delete dic;
    delete setRoiDialog;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    //BUG
    if (event->key() == Qt::Key_Left) {
        on_prevImage_clicked();
    } else if (event->key() == Qt::Key_Right) {
        on_nextImage_clicked();
    }
}

void MainWindow::setCurrentImageIndex(std::size_t i) {
    if (dic->cimgs.size() == 0 || i >= dic->cimgs.size())
        return;
    currImgIndex = i;
    QImage qim = Utils::dicImagetoQImage(dic->cimgs[currImgIndex]);
    Utils::loadImage(qim, ui->currImage, 512);
    ui->currentImageIndex->setNum(static_cast<int>(currImgIndex + 1));
    ui->prevImage->setEnabled(currImgIndex > 0);
    ui->nextImage->setEnabled(currImgIndex < dic->cimgs.size() - 1);
    ui->currentImageIndex->setEnabled(true);
}

void MainWindow::on_actionLoad_Reference_Image_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Select Reference Image File"),
                                                    QDir::homePath(),
                                                    "Images (*.png *.jpg *.jpeg *.tif *.tiff);;All Files (*)",
                                                    nullptr,
                                                    QFileDialog::DontUseNativeDialog);
    QString status = tr("");
    if (fileName.length() == 0)
        status = tr("No File Selected");
    else {
        status = tr("Selected ") + fileName;
        statusBar()->showMessage(status, 2000);
        cv::Mat refImage = cv::imread(fileName.toStdString(), cv::IMREAD_GRAYSCALE);
        dic->rimg = class_img(refImage, fileName.toStdString());
        QImage convertedImage = Utils::dicImagetoQImage(dic->rimg);
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
                                          nullptr, QFileDialog::DontUseNativeDialog);
    if (files.length() == 0) {
        statusBar()->showMessage(tr("No File Selected"), 2000);
        return;
    }
    QMessageBox::information(this, "Threads", QString("Count is %1").arg(QThread::idealThreadCount()));
    std::vector<class_img> imagesList(files.length());
    for (int i = 0; i < files.length(); i++) {
        imagesList[i] = class_img(cv::imread(files[i].toStdString(), cv::IMREAD_GRAYSCALE), files[i].toStdString());
    }
    dic->cimgs = imagesList;
    setCurrentImageIndex(0);

    QString status;
    if (files.length() == 1) {
        status = tr("Selected file ") + files.at(0);
        ui->currImgChk->setText("Loaded 1 \ncurrent image");
    } else {
        status = tr("Selected ") + tr(std::to_string(files.length()).c_str()) + tr(" Files : ") + files.first() + " ... " + files.last();
        ui->currImgChk->setText(tr("Loaded ") + tr(std::to_string(files.length()).c_str()) + tr(" \ncurrent images"));
    }
    ui->currImgChk->setChecked(true);

    statusBar()->showMessage(status, 2000);
}

void MainWindow::on_prevImage_clicked() {
    setCurrentImageIndex(currImgIndex - 1);
}

void MainWindow::on_nextImage_clicked() {
    setCurrentImageIndex(currImgIndex + 1);
}

void MainWindow::on_actionPerform_DIC_Analysis_triggered() {
    double start = clock();
    dic->performDicAnalysis();
    double end = clock() - start;
    end /= CLOCKS_PER_SEC;
    std::ofstream of("./time.txt");
    of << end << "\n";
    QMessageBox::information(this, "DIC", QString("Analysis over! %1").arg(end));
}

void MainWindow::on_actionSet_Region_of_Interest_ROI_triggered() {
    setRoiDialog = new SetROI(this, this->dic);
    setRoiDialog->open();
    connect(setRoiDialog, SIGNAL(onRoiSet(class_roi)), this, SLOT(onRoiSet(class_roi)), Qt::UniqueConnection);
}

void MainWindow::on_actionSet_DIC_Parameters_triggered() {
    setDicParams = new SetDicParams(this);
    setDicParams->show();
    connect(setDicParams, SIGNAL(onParamsSet(Params, bool)), this, SLOT(onParamsSet(Params, bool)), Qt::UniqueConnection);
}

void MainWindow::on_actionShow_Displacements_triggered() {
    //TODO Preconditions is completion of DIC Analysis.
    displWindow = new DisplWindow(this, this->dic);
    displWindow->show();
}

//Callbacks
//
//
//
//
/**
 * @brief MainWindow::onRoiSet When SetROI gives a signal that user has decided on ROI data.
 * @param roiImage class_roi image data.
 */
void MainWindow::onRoiSet(class_roi roiImage) {
    dic->roi = roiImage;

    ui->roiChk->setChecked(true);
    ui->roiChk->setText(tr("ROI set"));

    //TODO show ROI preview in mainwindow
    //TODO what happens in case SetROI window gets closed. Maybe unique connection will prevent extra connects.
    disconnect(setRoiDialog, SIGNAL(onRoiSet(class_roi)), this, SLOT(onRoiSet(class_roi)));
    setRoiDialog = nullptr;
}

void MainWindow::onParamsSet(Params params, bool success) {
    if (success) {
        dic->params = params;
        ui->paramsChk->setText("Parameters set");
        ui->paramsChk->setChecked(true);
    }
    disconnect(setDicParams, SIGNAL(onParamsSet(Params, bool)), this, SLOT(onParamsSet(Params, bool)));
    setDicParams = nullptr;
}

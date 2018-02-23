#include "src/headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QStatusBar>
#include <QFileDialog>
#include <QDesktopWidget>
#include <opencv2/opencv.hpp>
#include <cstdlib>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->setWindowTitle(WINDOW_TITLE);
	this->showMaximized();
	dic = new Dic();
	currImgIndex = -1;
}

MainWindow::~MainWindow()
{
	delete ui;
	delete dic;
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
		for (int i=0; i<256; i++) {
			colorTable.push_back(qRgb(i,i,i));
		}

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

void MainWindow::setCurrentImageIndex(int i) {
	currImgIndex = i;
	QImage qim = matToQImage(dic->getcurrimg_i(i));
	loadImage(&qim, ui->currImage, 512);
	ui->currentImageIndex->setText(tr(std::to_string(i + 1).c_str()));
	ui->prevImage->setEnabled(i > 0);
	ui->nextImage->setEnabled(i < dic->getcurrimgcount() - 1);
	ui->currentImageIndex->setEnabled(true);
}

void MainWindow::loadImage(QImage *image, QLabel *frame, int maxDim = 512) {
	//reducing image width and height
	int width = image->width();
	int height = image->height();
	if (width > height && width > maxDim) {
		height = (height * maxDim) / width;
		width = maxDim;
	} else if(height > width && height > maxDim) {
		width = (width * maxDim) / height;
		height = maxDim;
	}
	frame->setPixmap(QPixmap::fromImage(image->scaled(width, height, Qt::KeepAspectRatio)));
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
		dic->setrefimg(refImage);
		QImage convertedImage = matToQImage(refImage);
		loadImage(&convertedImage, ui->refImage, 512);
		ui->refImgChk->setChecked(true);
		ui->refImgChk->setText(tr("Reference \n Image Loaded"));
	}
}

void MainWindow::on_actionLoad_Current_Image_s_triggered() {
	QStringList files = QFileDialog::getOpenFileNames(this,
			tr("Select Current Image(s)"),
			"",
			"Images (*.png *.jpg *.jpeg *.tif *.tiff);;All Files (*)"
		);
	if (files.length() == 0) {
		statusBar()->showMessage(tr("No File Selected"), 2000);
		return;
	}

	cv::Mat *list = (cv::Mat *) calloc(files.length(), sizeof(cv::Mat));
	for (int i = 0; i < files.length(); i++) {
		list[i] = cv::imread(files[i].toStdString(), cv::IMREAD_GRAYSCALE);
	}
	dic->setcurrimg(files.length(), list);
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

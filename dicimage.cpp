#include "dicimage.h"
#include <vector>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <ostream>
#include <stdexcept>

DicImage::DicImage() {
    this->image = cv::Mat::zeros(1,1, CV_32FC1);
}

DicImage::DicImage(cv::Mat input) {
    //Assumed that image is grayscale
    this->image = input;
    //getBcoef();
}


int DicImage::getHeight() {
    return this->image.rows;
}

int DicImage::getWidth() {
    return this->image.cols;
}

double DicImage::getValue(int row, int col) {
    if(row < 0 || col < 0 || row >= getHeight() || col >= getWidth()) {
        throw std::out_of_range("Index out of range");
    }
    return this->image.at<uchar>(row, col);
}

int DicImage::getBcoefBorder() {
    return this->border_bcoef;
}

cv::Mat DicImage::getBcoef() {
    if(this->bcoef.empty()) {
        formBcoef();
    }
    return this->bcoef;
}

void DicImage::formBcoef() {
    //bcoeff range from 0 to 1
    cv::Mat temp;
    image.convertTo(temp, CV_32FC1, 1/255.0);
    cv::copyMakeBorder(temp, bcoef, border_bcoef, border_bcoef, border_bcoef, border_bcoef, cv::BORDER_REPLICATE);

    // Form kernel vector
    std::vector<float> kernel_b;
    std::vector<std::complex<float> > kernel_x; /* stores result of fourier on ker_x */
    kernel_b.push_back(11.0f / 20.0f);
    kernel_b.push_back(13.0f / 60.0f);
    kernel_b.push_back(1.0f / 120.0f);
    for (int i = 3; i < bcoef.cols - 2; i++) {
        kernel_b.push_back(0.0f);
    }
    kernel_b.push_back(1.0f / 120.0f);
    kernel_b.push_back(13.0f / 60.0f);
    //FFT across kernel
    cv::dft(kernel_b, kernel_x, cv::DFT_ROWS | cv::DFT_COMPLEX_OUTPUT);

    std::vector<std::complex<float> > row_fft;
    for (int row = 0; row < bcoef.rows; row++) {
        cv::dft(bcoef.row(row), row_fft, cv::DFT_ROWS | cv::DFT_COMPLEX_OUTPUT);
        for (int col = 0; col < bcoef.cols; col++) {
            row_fft[col] /= kernel_x[col];
        }
        cv::dft(row_fft, bcoef.row(row), cv::DFT_INVERSE | cv::DFT_ROWS | cv::DFT_SCALE | cv::DFT_REAL_OUTPUT);
    }

    row_fft.clear();
    kernel_x.clear();
    kernel_b.clear();

    cv::Mat bcoef_t = bcoef.t();

    kernel_b.push_back(11.0f / 20.0f);
    kernel_b.push_back(13.0f / 60.0f);
    kernel_b.push_back(1.0f / 120.0f);
    for (int i = 3; i < bcoef_t.cols - 2; i++) {
        kernel_b.push_back(0.0f);
    }
    kernel_b.push_back(1.0f / 120.0f);
    kernel_b.push_back(13.0f / 60.0f);
    cv::dft(kernel_b, kernel_x, cv::DFT_ROWS | cv::DFT_COMPLEX_OUTPUT);

    for (int row = 0; row < bcoef_t.rows; row++) {
        cv::dft(bcoef_t.row(row), row_fft, cv::DFT_ROWS | cv::DFT_COMPLEX_OUTPUT);
        for (int col = 0; col < bcoef_t.cols; col++) {
            row_fft[col] /= kernel_x[col];
        }
        cv::dft(row_fft, bcoef_t.row(row), cv::DFT_INVERSE | cv::DFT_ROWS | cv::DFT_SCALE | cv::DFT_REAL_OUTPUT);
    }

    row_fft.clear();
    kernel_x.clear();
    kernel_b.clear();

    bcoef = bcoef_t.t();

    //Save output
    /*std::ostringstream oss;
    oss << "M = " << endl << " " << bcoef << endl;

    QFile dumpbcoeff("/tmp/dicdump-bcoeff.txt");
    if (dumpbcoeff.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream outbCoeff(&dumpbcoeff);
        outbCoeff << QString(oss.str().c_str());;
    }
    dumpbcoeff.close();*/
}


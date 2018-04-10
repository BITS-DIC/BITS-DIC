#include "src/headers/dic.h"
#include <QFile>
#include <QDebug>
#include <vector>

Dic::Dic()
{
    currentImagesCount = 0;
}

void Dic::setReferenceImage(const cv::Mat matrix)
{
    referenceImage = matrix;
}

void Dic::setROI(cv::Mat matrix)
{
    roi = matrix;
}

void Dic::performDicAnalysis()
{
    preCompute();
}

void Dic::preCompute()
{
    refImgBcoeff = cv::Mat::zeros(referenceImage.rows + 10,
            referenceImage.cols + 10, CV_32FC1);
    refImgGradX = cv::Mat::zeros(referenceImage.rows,
            referenceImage.cols, referenceImage.type());
    refImgGradY = cv::Mat::zeros(referenceImage.rows,
            referenceImage.cols, referenceImage.type());
    computeBcoefGrad(referenceImage,
            refImgBcoeff, refImgGradX, refImgGradY);
}

void Dic::setCurrentImages(int n, cv::Mat *list)
{
    currentImagesCount = n;
    currentImages = list;
}

void Dic::computeBcoefGrad(cv::Mat img, cv::Mat bcoeff, 
        cv::Mat gradX, cv::Mat gradY)
{
    int b_cols;	/* number of columns of b coeff matrix */
    int b_rows;	/* number of rows of b coeff matrix */
    int ri_cols;	/* number of columns of reference image */
    int ri_rows;	/* number of rows of reference image */
    int i;
    int j;
    int k;
    std::vector<float> ker_x;
    std::vector<std::complex<float> > ker_x_fft; /* stores result of fourier on ker_x */
    std::vector<std::complex<float> > row_fft; /* stores resulf of fourier on a row */
    qDebug() << "Starting";
    cv::Mat bcoeff_t;	/* transpose of b coeff matrix */
    int bt_cols;	/* number of columns of b coeff transpose matrix*/
    int bt_rows;

    ri_cols = img.cols;
    ri_rows = img.rows;
    b_rows = ri_rows + 10;	/* padding is 5 pixel on each side */
    b_cols = ri_cols + 10;
    qDebug("%d %d %d %d\n", ri_cols, ri_rows, b_rows, b_cols);
    /*corners*/
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            bcoeff.at<float>(i, j) = (float) img.at<uchar>(0, 0);
            bcoeff.at<float>(i, b_cols - 1 - j) = (float) img.at<uchar>(0, ri_cols - 1);
            bcoeff.at<float>(b_rows - 1 - i, j) = (float) img.at<uchar>(ri_rows - 1, 0);
            bcoeff.at<float>(b_rows - 1 - i, b_rows - 1 - j) = (float) img.at<uchar>(ri_rows - 1, ri_cols - 1);
        }
    }

    /*sides*/
    for (k = 0; k < 5; k++) {
        /* horizontal sides*/
        for (j = 5; j < b_cols - 5; j++) {
            bcoeff.at<float>(k, j) = (float) img.at<uchar>(0, j - 5);
            bcoeff.at<float>(b_rows - 1 - k, j) = (float) img.at<uchar>(ri_rows - 1, j - 5);
        }

        /* vertical sides */
        for (i = 5; i < b_rows - 5; i++) {
            bcoeff.at<float>(i, k) = (float) img.at<uchar>(i - 5, 0);
            bcoeff.at<float>(i, b_cols - 1 - k) = (float) img.at<uchar>(i - 5, ri_cols - 1);
        }
    }

    for (i = 5; i < b_rows - 5; i++) {
        for (j = 5; j < b_cols; j++) {
            bcoeff.at<float>(i, j) = (float) img.at<uchar>(i - 5, j - 5);
        }
    }

    ker_x.push_back(11.0f / 20.0f);
    ker_x.push_back(13.0f / 60.0f);
    ker_x.push_back(1.0f / 120.0f);
    for (i = 3; i < b_cols - 2; i++) {
        ker_x.push_back(0.0f);
    }
    ker_x.push_back(1.0f / 120.0f);
    ker_x.push_back(13.0f / 60.0f);

    cv::dft(ker_x, ker_x_fft, cv::DFT_ROWS|cv::DFT_COMPLEX_OUTPUT);
    for (i = 0; i < b_rows; i++) {
        cv::dft(bcoeff.row(i), row_fft, cv::DFT_ROWS|cv::DFT_COMPLEX_OUTPUT);
        for (j = 0; j < b_cols; j++) {
            row_fft[j] /= ker_x_fft[j];
        }
        cv::dft(row_fft, bcoeff.row(i), cv::DFT_INVERSE|cv::DFT_ROWS|cv::DFT_REAL_OUTPUT);
    }

    ker_x.clear();
    ker_x_fft.clear();
    row_fft.clear();
    cv::transpose(bcoeff, bcoeff_t);
    bt_cols = b_rows;
    bt_rows = b_cols;

    ker_x.push_back(11.0f / 20.0f);
    ker_x.push_back(13.0f / 60.0f);
    ker_x.push_back(1.0f / 120.0f);
    for (i = 3; i < bt_cols - 2; i++) {
        ker_x.push_back(0.0f);
    }
    ker_x.push_back(1.0f / 120.0f);
    ker_x.push_back(13.0f / 60.0f);
    cv::dft(ker_x, ker_x_fft, cv::DFT_ROWS|cv::DFT_COMPLEX_OUTPUT);
    for (i = 0; i < bt_rows; i++) {
        cv::dft(bcoeff_t.row(i), row_fft, cv::DFT_ROWS|cv::DFT_COMPLEX_OUTPUT);
        for (j = 0; j < bt_cols; j++) {
            row_fft[j] /= ker_x_fft[j];
        }
        cv::dft(row_fft, bcoeff_t.row(i), cv::DFT_INVERSE|cv::DFT_ROWS|cv::DFT_REAL_OUTPUT);
    }
    cv::transpose(bcoeff_t, bcoeff);
    /*======== Done B coefficients =======================================*/
    gradX = cv::Mat::zeros(ri_rows, ri_cols, img.type());
    gradY = cv::Mat::zeros(ri_rows, ri_cols, img.type());
    for (i = 2; i < b_cols - 8; i++) {
        for (j = 2; j < b_rows - 8; j++) {
            float b0 = bcoeff.at<float>(j,i);
            float b1 = bcoeff.at<float>(j,i);
            float b2 = bcoeff.at<float>(j+1,i);
            float b3 = bcoeff.at<float>(j+2,i);
            float b4 = bcoeff.at<float>(j+3,i);
            float b5 = bcoeff.at<float>(j+4,i);
            float b6 = bcoeff.at<float>(j,i+1);
            float b7 = bcoeff.at<float>(j,i+1);
            float b8 = bcoeff.at<float>(j+1,i+1);
            float b9 = bcoeff.at<float>(j+2,i+1);
            float b11 = bcoeff.at<float>(j+3,i+1);
            float b10 = bcoeff.at<float>(j+4,i+1);
            float b12 = bcoeff.at<float>(j,i+2);
            float b13 = bcoeff.at<float>(j,i+2);
            float b14 = bcoeff.at<float>(j+1,i+2);
            float b15 = bcoeff.at<float>(j+2,i+2);
            float b16 = bcoeff.at<float>(j+3,i+2);
            float b17 = bcoeff.at<float>(j+4,i+2);
            float b18 = bcoeff.at<float>(j,i+3);
            float b19 = bcoeff.at<float>(j,i+3);
            float b20 = bcoeff.at<float>(j+1,i+3);
            float b21 = bcoeff.at<float>(j+2,i+3);
            float b22 = bcoeff.at<float>(j+3,i+3);
            float b23 = bcoeff.at<float>(j+4,i+3);
            float b24 = bcoeff.at<float>(j,i+4);
            float b25 = bcoeff.at<float>(j,i+4);
            float b26 = bcoeff.at<float>(j+1,i+4);
            float b27 = bcoeff.at<float>(j+2,i+4);
            float b28 = bcoeff.at<float>(j+3,i+4);
            float b29 = bcoeff.at<float>(j+4,i+4);
            float b30 = bcoeff.at<float>(j,i+5);
            float b31 = bcoeff.at<float>(j,i+5);
            float b32 = bcoeff.at<float>(j+1,i+5);
            float b33 = bcoeff.at<float>(j+2,i+5);
            float b34 = bcoeff.at<float>(j+3,i+5);
            float b35 = bcoeff.at<float>(j+4,i+5);

            gradX.at<uchar>(j - 2, i - 2) = (uchar) (0.003472222222222222*b18-0.009027777777777778*b1-0.003472222222222222*b10-0.0003472222222222222*b0+0.09027777777777778*b19-0.02291666666666667*b2+0.2291666666666667*b20+0.09027777777777778*b21+0.003472222222222222*b22+0.0003472222222222222*b24+0.009027777777777778*b25+0.02291666666666667*b26+0.009027777777777778*b27+0.0003472222222222222*b28-0.009027777777777778*b3-0.0003472222222222222*b4-0.003472222222222222*b6-0.09027777777777778*b7-0.2291666666666667*b8-0.09027777777777778*b9);
            gradY.at<uchar>(j - 2, i - 2) =(uchar) (0.009027777777777778*b10-0.003472222222222222*b1-0.0003472222222222222*b0-0.02291666666666667*b12-0.2291666666666667*b13+0.2291666666666667*b15+0.02291666666666667*b16-0.009027777777777778*b18-0.09027777777777778*b19+0.09027777777777778*b21+0.009027777777777778*b22-0.0003472222222222222*b24-0.003472222222222222*b25+0.003472222222222222*b27+0.0003472222222222222*b28+0.003472222222222222*b3+0.0003472222222222222*b4-0.009027777777777778*b6-0.09027777777777778*b7+0.09027777777777778*b9);
        }
    }

    QFile dumpbcoeff("/tmp/dicdump-bcoeff.txt");
    if (!dumpbcoeff.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug("bcoeff returning");
        return;
    }

    QTextStream outbCoeff(&dumpbcoeff);
    for (i = 0; i < b_rows; i++) {
        for (j = 0; j < b_cols; j++) {
            outbCoeff << bcoeff.at<float>(i, j) << "\t";
        }
        outbCoeff << "\n";
    }
    dumpbcoeff.close();

    QFile dumpGradX("/tmp/dicdump-gradX");
    if (!dumpGradX.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug("gradx returning");
        return;
    }

    QTextStream outGradX(&dumpGradX);
    for (i = 0; i < ri_rows; i++) {
        for (j = 0; j < ri_cols; j++) {
            outGradX << gradX.at<float>(i, j) << "\t";
        }
        outGradX << "\n";
    }
    dumpGradX.close();


    QFile dumpGradY("/tmp/dicdump-gradY");
    if (!dumpGradY.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug("grady returning");
        return;
    }

    QTextStream outGradY(&dumpGradY);
    for (i = 0; i < ri_rows; i++) {
        for (j = 0; j < ri_cols; j++) {
            outGradY << gradY.at<float>(i, j) << "\t";
        }
        outGradY << "\n";
    }
    dumpGradY.close();

    cv::namedWindow("gradientX", cv::WINDOW_NORMAL);	/* Create a window for display. */
    cv::imshow("gradientX", refImgGradX);	/* Show our image inside it. */
    cv::namedWindow("gradientY", cv::WINDOW_NORMAL);	/* Create a window for display. */
    cv::imshow("gradientY", refImgGradY);	/* Show our image inside it. */
    cv::waitKey(0);
}

cv::Mat Dic::getReferenceImage()
{
    return referenceImage;
}

cv::Mat Dic::getImgGradX()
{
    return refImgGradX;
}

cv::Mat Dic::getImgGradY()
{
    return refImgGradY;
}

int Dic::getCurrentImagesCount()
{
    return currentImagesCount;
}

cv::Mat Dic::getCurrentImage(int i)
{
    return currentImages[i];
}


Dic::~Dic()
{
    referenceImage.release();
    if (currentImages != NULL) {
        for (int i = 0; i < currentImagesCount; i++) {
            currentImages[i].release();
        }
        currentImages = NULL;
    }
}

#include "dic.h"
#include "utils.h"
#include <QFile>
#include <QDebug>
#include "dicimage.h"

Dic::Dic()
{
    currentImagesCount = 0;
}

void Dic::setReferenceImage(const DicImage refImage)
{
    referenceImage = refImage;
}

void Dic::setROI(cv::Mat matrix)
{
    roi = matrix;
}

void Dic::performDicAnalysis()
{
    preCompute();
    for (int i = 0; i < currentImagesCount; i++) {
        matchSeed(i);
    }
}

void Dic::preCompute() {
    refImgGradX = cv::Mat::zeros(referenceImage.getHeight(),
            referenceImage.getWidth(), CV_8UC1);
    refImgGradY = cv::Mat::zeros(referenceImage.getHeight(),
            referenceImage.getWidth(), CV_8UC1);
    computeGrad(referenceImage, refImgGradX, refImgGradY);
}

void Dic::setCurrentImages(int n, std::vector<DicImage> list)
{
    this->currentImagesCount = n;
    this->currentImages = list;
}

void Dic::computeGrad(DicImage img, cv::Mat gradX, cv::Mat gradY)
{
    int b_cols;	/* number of columns of b coeff matrix */
    int b_rows;	/* number of rows of b coeff matrix */
    int ri_cols;	/* number of columns of reference image */
    int ri_rows;	/* number of rows of reference image */
    int i;
    int j;
    int k;
    cv::Mat bcoeff = img.getBcoef();
    gradX = cv::Mat::zeros(ri_rows, ri_cols, CV_8UC1);
    gradY = cv::Mat::zeros(ri_rows, ri_cols, CV_8UC1);
    //error here probably.not verified
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

DicImage Dic::getReferenceImage()
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

DicImage Dic::getCurrentImage(int i)
{
    return currentImages[i];
}

void Dic::setParams(Params params)
{
    this->params = params;
}

void Dic::matchSeed(int currentIndex)
{
    double maxCorrelation = 0.0, correlation;
    std::pair<int, int> match, candidate;
    std::vector<double> serialSeed = serializeSubset(referenceImage, params.seedPoint);
    for (int i = 0; i < currentImages[currentIndex].getHeight(); i++) {
        for (int j = 0; j < currentImages[currentIndex].getWidth(); j++) {
            candidate = std::make_pair(i, j);
            correlation = Utils::ncc(serialSeed,
                                     serializeSubset(currentImages[currentIndex], candidate));
            if (correlation > maxCorrelation) {
                match = candidate;
                maxCorrelation = correlation;
            }
        }
    }
    qDebug("for %d th current image, found match at {%d, %d} with correlation = %lf",
           currentIndex, match.first, match.second, maxCorrelation);
}

std::vector<double> Dic::serializeSubset(DicImage &image,
                                    std::pair<int, int> center)
{
    unsigned long xMin = 0;
    unsigned long xMax = static_cast<unsigned long>(image.getWidth()) - 1;
    unsigned long yMin = 0;
    unsigned long yMax = static_cast<unsigned long>(image.getHeight()) - 1;
    unsigned long side = static_cast<unsigned long>(params.subsetSize);
    unsigned long xStart = static_cast<unsigned long>(center.first) - side / 2;
    unsigned long yStart = static_cast<unsigned long>(center.second) - side / 2;
    unsigned long x;
    unsigned long y;
    std::vector<double> res(static_cast<size_t>(side * side), 0.0);


    if (xStart < xMin or yStart < yMin or
            xStart + side - 1 > xMax or yStart + side - 1 > yMax) {
        std::vector<double> empty;
        return empty;
    }
    x = xStart;
    for (size_t i = 0; i < side; i++, x++) {
        y = yStart;
        for (size_t j = 0; j < side; j++, y++) {
            res[i * side + j] = static_cast<double>(image.getValue(static_cast<int>(x),
                                                                         static_cast<int>(y)));
        }
    }
    return res;
}

Dic::~Dic()
{
    currentImages.clear();
}

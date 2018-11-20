#include "utils.h"
#include <algorithm>
#include <cstdio>
#include <QErrorMessage>
#include <cmath>

/**
 * @brief Method to convert a cv::Mat object to QImage object.
 * @param cv::Mat object.
 * @return Non null QImage object.
 */
const QImage Utils::matToQImage(const cv::Mat &mat) {
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

/**
 * @brief Method to convert a cv::Mat object to QImage object.
 * @param cv::Mat object.
 * @return Non null QImage object.
 */
QImage Utils::dicImagetoQImage(DicImage mat) {
    // Set the color table (used to translate colour indexes to qRgb values)
    QVector<QRgb> colorTable;
    for (int i=0; i<256; i++) {
        colorTable.push_back(qRgb(i,i,i));
    }

    // Create QImage with same dimensions as input Mat
    QImage qimg(mat.getWidth(), mat.getHeight(), QImage::Format_Indexed8);
    qimg.setColorTable(colorTable);
    for(int i = 0; i < mat.getWidth(); i++) {
        for(int j = 0; j < mat.getHeight(); j++) {
            qimg.setPixel(i, j, mat.getValue(j, i));
        }
    }
    return qimg;
}

/**
 * @brief Loads a QImage reference into a QLabel.
 * @param image Reference to QImage object to load.
 * @param frame Pointer to QLabel object to use for showing image.
 * @param maxDim default at 512.
 */
void Utils::loadImage(const QImage& image, QLabel *frame, int maxDim) {
    //Reducing image width and height
    int width = image.width();
    int height = image.height();
    if (width > height && width > maxDim) {
        height = (height * maxDim) / width;
        width = maxDim;
    } else if(height > width && height > maxDim) {
        width = (width * maxDim) / height;
        height = maxDim;
    }
    frame->setPixmap(QPixmap::fromImage(image.scaled(width, height, Qt::KeepAspectRatio)));
}

double Utils::ncc(const std::vector<double> &f, const std::vector<double> &g)
{
    if (f.size() == 0 or g.size() == 0) return 0.0;
    double fm = std::accumulate(f.begin(), f.end(), 0.0) / f.size();
    double gm = std::accumulate(g.begin(), g.end(), 0.0) / g.size();
    return ncc(f, g, fm, gm);
}

double Utils::ncc(const std::vector<double> &f,
		  const std::vector<double> &g,
		  double fm,
		  double gm)
{
    // size of subset
    unsigned long n;
    // sum((f(i) - fm)(g(i) - gm))
    double sum_cross_prod = 0.0;
    // sum((f(i) - fm) ^ 2)
    double sum_sq_f = 0.0;
    // sum((g(i) - gm) ^ 2)
    double sum_sq_g = 0.0;

    n = f.size();
    if (n != g.size() or n == 0) {
        return 0.0;
    }

    for (unsigned long i = 0; i < n; i++) {
        sum_cross_prod += (f[i] - fm) * (g[i] - gm);
	sum_sq_f += (f[i] - fm) * (f[i] - fm);
	sum_sq_g += (g[i] - gm) * (g[i] - gm);
    }

    return sum_cross_prod / (std::sqrt(sum_sq_f * sum_sq_g));
}

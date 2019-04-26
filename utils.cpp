#include "utils.h"
#include <QErrorMessage>
#include <algorithm>
#include <cmath>
#include <cstdio>
/**
 * @brief Method to convert a cv::Mat object to QImage object.
 * @param cv::Mat object.
 * @return Non null QImage object.
 */
const QImage Utils::matToQImage(const cv::Mat &mat) {
    if (mat.type() == CV_8UC1) {
        // 8-bits unsigned, NO. OF CHANNELS=1
        //Example would be grayscale images

        // Set the color table (used to translate colour indexes to qRgb values)
        QVector<QRgb> colorTable;
        for (int i = 0; i < 256; i++) {
            colorTable.push_back(qRgb(i, i, i));
        }

        // Copy input Mat
        const uchar *qImageBuffer = (const uchar *)mat.data;
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
 * @param class_img object.
 * @return Non null QImage object.
 */
QImage Utils::dicImagetoQImage(class_img mat) {
    // Set the color table (used to translate colour indexes to qRgb values)
    QVector<QRgb> colorTable;
    for (int i = 0; i < 256; i++) {
        colorTable.push_back(qRgb(i, i, i));
    }

    // Create QImage with same dimensions as input Mat
    QImage qimg(mat.gs.width, mat.gs.height, QImage::Format_Indexed8);
    qimg.setColorTable(colorTable);
    for (int y = 0; y < mat.gs.height; y++) {
        for (int x = 0; x < mat.gs.width; x++) {
            //check this TODO
            qimg.setPixel(x, y, static_cast<uchar>(mat.gs.value[y + x * mat.gs.height] * 255.0));
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
void Utils::loadImage(const QImage &image, QLabel *frame, int maxDim, int sf) {
    //Reducing image width and height
    int width = image.width();
    int height = image.height();
    if (width > height && width > maxDim) {
        height = (height * maxDim) / width;
        width = maxDim;
    } else if (height > width && height > maxDim) {
        width = (width * maxDim) / height;
        height = maxDim;
    }
    frame->setPixmap(QPixmap::fromImage(image.scaled(sf * width, sf * height, Qt::KeepAspectRatio)));
}

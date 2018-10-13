#include "utils.h"

/**
 * @brief Method to convert a cv::Mat object to QImage object.
 * @param cv::Mat object.
 * @return Non null QImage object.
 */
const QImage Utils::matToQImage(const cv::Mat& mat) {
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

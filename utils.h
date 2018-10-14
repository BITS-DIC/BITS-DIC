#ifndef UTILS_H
#define UTILS_H
#include <opencv2/opencv.hpp>
#include <QImage>
#include <QLabel>

class Utils
{
public:
    Utils();
    ~Utils();
    static const QImage matToQImage(const cv::Mat& mat);
    static void loadImage(const QImage&, QLabel*, int = 512);
};

#endif // UTILS_H

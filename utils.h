#ifndef UTILS_H
#define UTILS_H
#include <opencv2/opencv.hpp>
#include <QImage>
#include <QLabel>
#include <vector>
#include <dicimage.h>

class Utils
{
public:
    Utils();
    ~Utils();
    static const QImage matToQImage(const cv::Mat&);
    static QImage dicImagetoQImage(DicImage);
    static void loadImage(const QImage&, QLabel*, int = 512);
    static double ncc(const std::vector<double> &f,
		      const std::vector<double> &g);
    static double ncc(const std::vector<double> &f,
		      const std::vector<double> &g,
		      double fm,
		      double gm);
};

#endif // UTILS_H

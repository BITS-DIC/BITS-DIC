#ifndef UTILS_H
#define UTILS_H
#include "class_logical_array.h"
#include "class_region.h"
#include "vec_struct_region.h"
#include <QLabel>
#include <QImage>
#include <opencv2/opencv.hpp>
#include "class_img.h"
#define LAMBDA 0.0000000001  // Cutoff for values approximately zero
#define FILTERITERATIONS 50  // Number of average filters applied when extrapolating data

class Utils {
  public:
    Utils();
    ~Utils();
    static const QImage matToQImage(const cv::Mat &);
    static QImage dicImagetoQImage(class_img);
    static void loadImage(const QImage &, QLabel *, int = 512, int sf = 1);
};

#endif // UTILS_H

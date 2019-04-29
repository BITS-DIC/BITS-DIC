#ifndef CLASS_IMG_H
#define CLASS_IMG_H
#include <string>
#include "class_double_array.h"
#include "opencv2/core.hpp"

// This is for an ncorr_class_img input ---------------------------------//
class class_img {
public:
    // Constructor
    class_img();    // THREADSAFE
    class_img(cv::Mat,std::string);
    class_img(const class_img &img2);
    // Properties
    std::string name;
    class_double_array gs;
    double max_gs;
    class_double_array bcoef;
    int border_bcoef;
};

#endif // CLASS_IMG_H

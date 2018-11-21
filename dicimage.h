#ifndef DICIMAGE_H
#define DICIMAGE_H
#include <string>
#include "opencv2/core.hpp"

class DicImage {
    public:
        DicImage();
        DicImage(cv::Mat);
        int getHeight();
        int getWidth();
        double getValue(int row, int col);
        int getBcoefBorder();
        cv::Mat getBcoef();
    private:
        int border_bcoef = 20;
        cv::Mat bcoef;
        cv::Mat image;
        void formBcoef();
};

#endif // DICIMAGE_H

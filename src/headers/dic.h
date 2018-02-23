#ifndef DIC_H
#define DIC_H
#include <opencv2/opencv.hpp>

class Dic
{
    public:
        Dic();
        ~Dic();
        void setReferenceImage(cv::Mat);
        void setROI(cv::Mat);
        void setCurrentImages(int /* Number of images */, cv::Mat * /* Pointer to array of images */);
        int getCurrentImagesCount();
        cv::Mat getCurrentImage(int);
        cv::Mat getReferenceImage();
    private:
        cv::Mat referenceImage;
        cv::Mat *currentImages;
        cv::Mat roi;	/* Region of Interest */
        int currentImagesCount;    /* Number of current images */
};

#endif // DIC_H

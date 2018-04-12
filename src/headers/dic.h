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
        void setCurrentImages(int /* Number of images */,
                cv::Mat * /* Pointer to array of images */);
        int getCurrentImagesCount();
        cv::Mat getCurrentImage(int);
        cv::Mat getReferenceImage();
        cv::Mat getImgGradX();
        cv::Mat getImgGradY();
        void performDicAnalysis();
    private:
        cv::Mat referenceImage;
        cv::Mat *currentImages;
        cv::Mat roi;	/* Region of Interest */
        cv::Mat refImgBcoeff;
        cv::Mat refImgGradX;	/* (d/dx) (f) */
        cv::Mat refImgGradY;	/* (d/dy) (f) */
        int currentImagesCount;	/* Number of current images */
        cv::Mat *currImgsBcoeff;
        cv::Mat *currImgsGradX;
        cv::Mat *currImgsGradY;
        void preCompute();

        /* Given image `img`, calculates and saves its- 
         * b coefficient matrix in `bcoeff`
         * D/Dx gradient in `gradX`
         * D/Dy gradient in `gradY`
         */
        void computeBcoefGrad(cv::Mat img,
                cv::Mat bcoeff, 
                cv::Mat gradX, 
                cv::Mat gradY);
};

#endif // DIC_H

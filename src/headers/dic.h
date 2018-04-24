#ifndef DIC_H
#define DIC_H
#include <opencv2/opencv.hpp>
#include <utility>
#include <vector>

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
        double normDiff(cv::Mat A, cv::Mat B);	/* ||A - B|| */
    private:
        cv::Mat referenceImage;
        cv::Mat *currentImages;
        // Region of Interest : boolean array
        cv::Mat roi;
        cv::Mat refImgBcoeff;
        cv::Mat refImgGradX;	// (d/dx) (f)
        cv::Mat refImgGradY;	// (d/dy) (f)
        unsigned int currentImagesCount;	// Number of current images
        cv::Mat *currImgsBcoeff;
        cv::Mat *currImgsGradX;
        cv::Mat *currImgsGradY;
        double *refQK_B_QKT;
        // norm difference threshold for terminating iterations
        double threshold;
        // maximum number of iterations
        unsigned int maxIter;
        unsigned int subsetRadius;
        // distance between two subset centres
        unsigned int subsetSpacing;
        void preCompute();
        std::vector<std::pair<double, double> > subsetCentres;
        std::vector<double *> params;
        /* Given image `img`, calculates and saves its- 
         * b coefficient matrix in `bcoeff`
         * D/Dx gradient in `gradX`
         * D/Dy gradient in `gradY`
         */
        cv::Mat hessian;
        void calcHessian();
        void computeBcoefGrad(cv::Mat img,
                cv::Mat bcoeff, 
                cv::Mat gradX, 
                cv::Mat gradY);
        void computeQK_B_QKT(cv::Mat img, cv::Mat bcoef, double *dest);
        void populateSubsetCentres();
        void calcParam(int x, int y, double * p, cv::Mat curr);
};

#endif // DIC_H

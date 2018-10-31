#ifndef DIC_H
#define DIC_H
#include <opencv2/opencv.hpp>
#include <vector>
#include "disp.h"
#include "params.h"

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
        void setParams(Params);
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

        Disp plot_u;
        Disp plot_v;
        Disp plot_corrcoef;

        /* Given image `img`, calculates and saves its- 
         * b coefficient matrix in `bcoeff`
         * D/Dx gradient in `gradX`
         * D/Dy gradient in `gradY`
         */
        void computeBcoefGrad(cv::Mat img,
                cv::Mat bcoeff, 
                cv::Mat gradX, 
                cv::Mat gradY);

        Params params;
	// temporary, we will replace this by deformation vector
	std::vector<std::pair<int, int>> initMatches;
	// find subset in each current image, similar to seed subset
	void matchSeed(int currentIndex);
    // serialize pixel intensities of a subset into a vector
    std::vector<double> serializeSubset(const cv::Mat &image,
                                        std::pair<int, int> center);
};

#endif // DIC_H

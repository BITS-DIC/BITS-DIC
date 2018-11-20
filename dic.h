#ifndef DIC_H
#define DIC_H
#include <opencv2/opencv.hpp>
#include <vector>
#include "params.h"
#include "array2d.h"
#include "dicimage.h"

class Dic
{
    public:
        Dic();
        ~Dic();
        void setReferenceImage(DicImage);
        void setROI(cv::Mat);
        void setCurrentImages(int, std::vector<DicImage>);
        int getCurrentImagesCount();
        DicImage getCurrentImage(int);
        DicImage getReferenceImage();
        cv::Mat getImgGradX();
        cv::Mat getImgGradY();
        void performDicAnalysis();
        void setParams(Params);
    private:
        DicImage referenceImage;
        std::vector<DicImage> currentImages;
        cv::Mat roi;	/* Region of Interest */
        cv::Mat refImgGradX;	/* (d/dx) (f) */
        cv::Mat refImgGradY;	/* (d/dy) (f) */
        int currentImagesCount;	/* Number of current images */
        cv::Mat *currImgsGradX;
        cv::Mat *currImgsGradY;
        void preCompute();

        Array2D<double> plot_u;
        Array2D<double> plot_v;
        Array2D<double> plot_corrcoef;

        /* Given image `img`, calculates and saves its- 
         * D/Dx gradient in `gradX`
         * D/Dy gradient in `gradY`
         */
        void computeGrad(DicImage img, cv::Mat gradX, cv::Mat gradY);

        Params params;
        // temporary, we will replace this by deformation vector
        std::vector<std::pair<int, int>> initMatches;
        // find subset in each current image, similar to seed subset
        void matchSeed(int currentIndex);
        // serialize pixel intensities of a subset into a vector
        std::vector<double> serializeSubset(DicImage &image,
                                        std::pair<int, int> center);
};

#endif // DIC_H

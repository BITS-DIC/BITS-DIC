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
        void setCurrentImages(std::size_t, std::vector<DicImage>);
        void setROI(cv::Mat);
        std::size_t getCurrentImagesCount();
        DicImage getCurrentImage(std::size_t);
        DicImage getReferenceImage();
        void performDicAnalysis();
        void setParams(Params);
    private:
        DicImage referenceImage;
        std::vector<DicImage> currentImages;
        cv::Mat roi;	/* Region of Interest */
        std::vector<double> refImgGradX;	/* (d/dx) (f) */
        std::vector<double> refImgGradY;	/* (d/dy) (f) */
        std::vector<double> QK_B_QKT;
        std::size_t currentImagesCount;	/* Number of current images */
        void preCompute(std::size_t currentImage);

        Array2D<double> plot_u;
        Array2D<double> plot_v;
        Array2D<double> plot_corrcoef;

        Params params;
        // temporary, we will replace this by deformation vector
        std::vector<std::pair<int, int>> initMatches;
        // find subset in each current image, similar to seed subset
        void matchSeed(std::size_t currentIndex);
        // serialize pixel intensities of a subset into a vector
        std::vector<double> serializeSubset(DicImage &image,
                                        std::pair<int, int> center);
};

#endif // DIC_H

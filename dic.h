#ifndef DIC_H
#define DIC_H
#include "array2d.h"
#include "class_double_array.h"
#include "class_img.h"
#include "class_logical_array.h"
#include "class_roi.h"
#include "dicimage.h"
#include "params.h"
#include <opencv2/core.hpp>
#include <vector>
#include "utils.h"
#include <fstream>

#define LAMBDA 0.0000000001

struct comp_queue {
    bool operator()(std::vector<double> const &a, std::vector<double> const &b) const {
        // Eighth element is the correlation coefficient
        return a[8] > b[8];
    }
};

typedef std::priority_queue<std::vector<double>, std::vector<std::vector<double>>, comp_queue> heap;

class Dic {
  public:
    Dic();
    ~Dic();
    void performDicAnalysis();
    void setParams(Params);
    class_roi roi;
    class_img rimg;
    std::vector<class_img> cimgs;
    Params params;

    //outputs
    std::vector<class_double_array> plot_u;
    std::vector<class_double_array> plot_v;
    std::vector<class_double_array> plot_corrcoef;
    std::vector<class_logical_array> plot_validpoints;

  private:
    int oHeight = 0;
    int oWidth = 0;

    //reference image vectors
    std::vector<double> df_dx_buffer; /* (d/dx) (f) */
    std::vector<double> df_dy_buffer; /* (d/dy) (f) */

    //per current image vectors
    std::vector<double> g_buffer;
    std::vector<double> df_dp_buffer;
    std::vector<double> x_vec_buffer;
    std::vector<double> y_vec_buffer;
    std::vector<double> gradient_buffer;
    std::vector<double> hessian_gn_buffer;
    std::vector<double> QK_B_QKT_buffer;
    std::vector<std::vector<double>> seed_info;

    //output vector of cv Mat
    class_logical_array plot_calcpoints;

    void preCompute(std::ofstream&, std::size_t currentImage);
    void analysis(std::ofstream&, std::size_t currentImage);
    void analyzepoint(std::ofstream&, std::size_t currentImage, heap &queue, const int &x, const int &y, const std::vector<double> &paramvector_init, const int &num_region);
    bool calcpoint(std::ofstream&, std::size_t currentImage, std::vector<double> &paramvector,const int &x,const int &y, const std::vector<double> &paramvector_init, const int &num_region);
    bool iterativesearch(std::ofstream&, std::size_t currImg,std::vector<double> &defvector, double &corrcoef, const std::vector<double> &defvector_init);
    bool newton(std::ofstream&, std::size_t currImg,std::vector<double> &defvector, double &corrcoef, double &diffnorm, const std::vector<double> &defvector_init, const double &fm, const double &deltaf_inv);

    // temporary, we will replace this by deformation vector
    std::vector<std::pair<int, int>> initMatches;
    // find subset in each current image, similar to seed subset
    void matchSeed(std::size_t currentIndex);
    // serialize pixel intensities of a subset into a vector
    std::vector<double> serializeSubset(class_img &image, std::pair<int, int> center);
};

#endif // DIC_H

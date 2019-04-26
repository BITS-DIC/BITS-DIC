#ifndef DICUTILS_H
#define DICUTILS_H
#include "class_logical_array.h"
#include "class_region.h"
#include "vec_struct_region.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include "class_double_array.h"
#include "class_inverseregion.h"
#include "class_img.h"
#define LAMBDA 0.0000000001  // Cutoff for values approximately zero
#define FILTERITERATIONS 50  // Number of average filters applied when extrapolating data

class dicutils {
public:
    static double ncc(const std::vector<double> &f, const std::vector<double> &g);
    static double ncc(const std::vector<double> &f, const std::vector<double> &g, double fm, double gm);
    static int mod_pos(const int &i, const int &n);                                                                                                               // THREADSAFE
    static void form_boundary(std::vector<std::vector<int>> &vec_boundary, const std::vector<int> &point_topleft, const class_logical_array &mask, int &direc);   // THREADSAFE
    static void form_regions(std::vector<vec_struct_region> &region, bool &removed, const class_logical_array &mask, const int &cutoff, const bool &preservelength);     // THREADSAFE
    static void form_union(std::vector<vec_struct_region> &region_union, const std::vector<class_region> &region, const class_logical_array &mask, const bool &inplace); // THREADSAFE
    static double ncorr_round(const double &r);                                                                                                                   // THREADSAFE
    static int sign(const double &r);

    static void cholesky(std::vector<double> &mat,bool &positivedef,const int &size_mat);    // THREADSAFE
    static void forwardsub(std::vector<double> &vec,const std::vector<double> &mat,const int &size_mat);        // THREADSAFE
    static void backwardsub(std::vector<double> &vec,const std::vector<double> &mat,const int &size_mat);       // THREADSAFE
    static bool interp_qbs(double &interp,const double &x_tilda,const double &y_tilda,const class_double_array &plot_interp,const class_logical_array &mask,const int &offset_x,const int &offset_y,const int &border_bcoef); // NOT THREADSAFE
    static void expand_filt(class_double_array &plot_extrap,const class_inverseregion &inverseregion);    // THREADSAFE
};

#endif // DICUTILS_H

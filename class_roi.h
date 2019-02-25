#ifndef DICROI_H
#define DICROI_H
#include "class_logical_array.h"
#include "class_region.h"
#include "struct_cirroi.h"
#include "struct_info_cirroi.h"
#include <vector>
#include "utils.h"

class class_roi {
  public:
    // Constructor
    class_roi(); // THREADSAFE

    // Properties
    class_logical_array mask;
    std::vector<class_region> region;
    struct_cirroi cirroi;

    // Methods
    void set_cirroi(const int &radius_i);                                                          // NOT THREADSAFE
    void update_cirroi(const int &num_region);                                                       // THREADSAFE
    void get_cirroi(const int &x_i, const int &y_i, const int &num_region, const bool &subsettrunc); // THREADSAFE
    bool withinregion(const int &x_i, const int &y_i, const int &num_region);                                               // THREADSAFE

  private:
    // Properties
    struct_info_cirroi info_cirroi;
};

#endif // DICROI_H

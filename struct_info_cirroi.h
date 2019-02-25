#ifndef STRUCT_INFO_CIRROI_H
#define STRUCT_INFO_CIRROI_H
#include "class_logical_array.h"
#include "class_integer_array.h"
#include "class_region.h"
#include <vector>

struct struct_info_cirroi {
    // Constructor
    struct_info_cirroi();    // THREADSAFE

    // Main properties
    class_region region;
    class_logical_array mask;
    int radius;
    int x;
    int y;

    // Additional Properties
    class_logical_array mask_buffer; // Used as additional storage so you dont have to overwrite original mask
    class_integer_array circletemplate;
    class_integer_array queue_buffer;
    std::vector<int> queue_nodelist;
    std::vector<int> queue_nodeindex;
    std::vector<int> activelines;
};

#endif // STRUCT_INFO_CIRROI_H

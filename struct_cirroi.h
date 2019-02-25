#ifndef STRUCT_CIRROI_H
#define STRUCT_CIRROI_H
#include "class_region.h"
#include "class_logical_array.h"

struct struct_cirroi {
    // Constructor
    struct_cirroi();         // THREADSAFE

    // Properties
    class_region region;
    class_logical_array mask;
    int radius;
    int x;
    int y;
};

#endif // STRUCT_CIRROI_H

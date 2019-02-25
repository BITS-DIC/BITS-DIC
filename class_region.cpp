#include "class_region.h"
#include <limits>

class_region::class_region() {
    upperbound = std::numeric_limits<int>::max();
    lowerbound = std::numeric_limits<int>::min();
    leftbound = std::numeric_limits<int>::max();
    rightbound = std::numeric_limits<int>::min();
    totalpoints = 0;
}

// NOT THREADSAFE
void class_region::alloc(const int &h,const int &w) {
    // Allocate space for nodelist and noderange
    nodelist.alloc(h,w);
    noderange.alloc(h,1);
}

// NOT THREADSAFE
void class_region::free() {
    // Free nodelist and noderange
    nodelist.free();
    noderange.free();
}

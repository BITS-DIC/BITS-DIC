#ifndef CLASS_REGION_H
#define CLASS_REGION_H
#include "class_integer_array.h"

class class_region {
public:
    // Constructor
    class_region();    // THREADSAFE

    // Properties
    class_integer_array nodelist;
    class_integer_array noderange;
    int upperbound;
    int lowerbound;
    int leftbound;
    int rightbound;
    int totalpoints;

    // Methods
    void alloc(const int &h,const int &w);    // NOT THREADSAFE
    void free();                              // NOT THREADSAFE
};

#endif // CLASS_REGION_H

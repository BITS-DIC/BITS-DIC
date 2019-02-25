#ifndef VEC_STRUCT_REGION_H
#define VEC_STRUCT_REGION_H
#include <vector>

struct vec_struct_region {
public:
    // Constructor
    vec_struct_region(); // THREADSAFE

    // Properties
    std::vector<int> nodelist;
    std::vector<int> noderange;
    int height_nodelist;
    int width_nodelist;
    int upperbound;
    int lowerbound;
    int leftbound;
    int rightbound;
    int totalpoints;
};
#endif // VEC_STRUCT_REGION_H

#include "class_double_array.h"
#include <cstdlib>

class_double_array::class_double_array() {
    width = 0;
    height = 0;
    value = nullptr;
}

//First row filled from left to right..and so on for other rows
void class_double_array::reset() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            value[j + i * height] = 0.0;
        }
    }
}

void class_double_array::alloc(const int &h, const int &w) {
    width = w;
    height = h;
    value = (double *)calloc(h * w, sizeof(double));
}

void class_double_array::free() {
    width = 0;
    height = 0;
    ::free(value);
    value = nullptr;
}

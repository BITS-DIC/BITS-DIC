#include "class_double_array.h"
#include <cstdlib>

class_double_array::class_double_array() {
    width = 0;
    height = 0;
    value = nullptr;
}

class_double_array::class_double_array(const class_double_array &cda2) {
    width = cda2.width;
    height = cda2.height;
    value = nullptr;
    if(cda2.value != nullptr) {
        value = (double*) calloc(height * width, sizeof(double));
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                value[j + i * height] = cda2.value[j + i * height];
            }
        }
    }
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
    value = (double *) calloc(h * w, sizeof(double));
}

void class_double_array::free() {
    width = 0;
    height = 0;
    ::free(value);
    value = nullptr;
}

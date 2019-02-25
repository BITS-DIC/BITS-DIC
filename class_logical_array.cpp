#include "class_logical_array.h"
#include <cstdlib>

class_logical_array::class_logical_array() {
    width = 0;
    height = 0;
    value = nullptr;
}

// THREAD SAFE
void class_logical_array::reset() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            value[j + i * height] = false;
        }
    }
}

// NOT THREAD SAFE
void class_logical_array::alloc(const int &h, const int &w) {
    width = w;
    height = h;
    value = (bool *)calloc(h * w, sizeof(bool));
}

// NOT THREAD SAFE
void class_logical_array::free() {
    width = 0;
    height = 0;
    ::free(value);
    value = NULL;
}

#include "class_integer_array.h"
#include <cstdlib>

// THREAD SAFE
class_integer_array::class_integer_array() {
    width = 0;
    height = 0;
    value = nullptr;
}

// THREAD SAFE
void class_integer_array::reset() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            value[j + i * height] = 0;
        }
    }
}

// NOT THREAD SAFE
void class_integer_array::alloc(const int &h, const int &w) {

    width = w;
    height = h;
    value = (int *)calloc(h * w, sizeof(int));
}

// NOT THREAD SAFE
void class_integer_array::free() {
    width = 0;
    height = 0;
    ::free(value);
    value = nullptr;
}

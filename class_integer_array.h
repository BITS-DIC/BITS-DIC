#ifndef CLASS_INTEGER_ARRAY_H
#define CLASS_INTEGER_ARRAY_H

class class_integer_array {
public:
    // Constructor
    class_integer_array();                        // THREAD SAFE

    // Properties
    int width;
    int height;
    int *value;

    // Methods
    void reset();                                 // THREAD SAFE
    void alloc(const int &h,const int &w);        // NOT THREAD SAFE
    void free();                                  // NOT THREAD SAFE
};

#endif // CLASS_INTEGER_ARRAY_H

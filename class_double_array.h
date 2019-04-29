#ifndef CLASS_DOUBLE_ARRAY_H
#define CLASS_DOUBLE_ARRAY_H

class class_double_array {
public:
    // Constructor
    class_double_array();                         // THREAD SAFE
    class_double_array(const class_double_array &cda2);

    // Properties
    int width;
    int height;
    double* value;

    // Methods
    void reset();                                 // THREAD SAFE
    void alloc(const int &h,const int &w);        // NOT THREAD SAFE
    void free();                                  // NOT THREAD SAFE
};

#endif // CLASS_DOUBLE_ARRAY_H

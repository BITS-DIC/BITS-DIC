#ifndef CLASS_LOGICAL_ARRAY_H
#define CLASS_LOGICAL_ARRAY_H

class class_logical_array {
public:
    // Constructor
    class_logical_array();                        // THREAD SAFE

    // Properties
    int width;
    int height;
    bool *value;

    // Methods
    void reset();                                 // THREAD SAFE
    void alloc(const int &h,const int &w);        // NOT THREAD SAFE
    void free();                                  // NOT THREAD SAFE
};

#endif // CLASS_LOGICAL_ARRAY_H

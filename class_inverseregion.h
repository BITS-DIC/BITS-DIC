#ifndef CLASS_INVERSEREGION_H
#define CLASS_INVERSEREGION_H
#include "class_region.h"

class class_inverseregion : public class_region {
public:
    // Constructor
    class_inverseregion(class_region &region,const int &border_extrap); // NOT THREADSAFE
};

#endif // CLASS_INVERSEREGION_H

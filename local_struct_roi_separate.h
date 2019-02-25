#ifndef LOCAL_STRUCT_ROI_SEPARATE_H
#define LOCAL_STRUCT_ROI_SEPARATE_H
#include <vector>

class local_struct_roi_separate
{
public:
    local_struct_roi_separate();
    // Properties
    std::vector<std::vector<int> > nodelist;
    int leftbound;
    int rightbound;
    int totalpoints;
};

#endif // LOCAL_STRUCT_ROI_SEPARATE_H

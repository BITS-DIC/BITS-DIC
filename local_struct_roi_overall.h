#ifndef LOCAL_STRUCT_ROI_OVERALL_H
#define LOCAL_STRUCT_ROI_OVERALL_H
#include <vector>

class local_struct_roi_overall
{
public:
    local_struct_roi_overall();
    // Properties
    std::vector<std::vector<int> > nodelist;
    std::vector<std::vector<bool> > activelines;
    int leftbound;
    int rightbound;
};

#endif // LOCAL_STRUCT_ROI_OVERALL_H

#include "params.h"

Params::Params() {
    cutoff_diffnorm = 0.000001;
    cutoff_iteration = 50;
    subsetSize = 10;
    subsetSpacing = 10;
    seedPoint = std::pair<int,int>(0,0);
}

Params::Params(const Params &old) {
    this->cutoff_diffnorm = old.cutoff_diffnorm;
    this->cutoff_iteration = old.cutoff_diffnorm;
    this->seedPoint = std::pair<int, int>(old.seedPoint.first, old.seedPoint.second);
    this->subsetSize = old.subsetSize;
    this->subsetSpacing = old.subsetSpacing;
}

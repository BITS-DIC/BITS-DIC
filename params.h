#ifndef PARAMS_H
#define PARAMS_H
#include <utility>

/**
 * Encapsulate all the parameters user sets.
 */
class Params {
  public:
    Params();
    Params(const Params &old);
    double cutoff_diffnorm;
    double cutoff_iteration;
    int subsetSize;
    int subsetSpacing;
    std::pair<int, int> seedPoint;
};

#endif // PARAMS_H

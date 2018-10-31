#ifndef PARAMS_H
#define PARAMS_H
#include <utility>

/**
 * Encapsulate all the parameters user sets.
 */
class Params
{
        public:
                int subsetRadius;
                int subsetSpacing;
                std::pair<int, int> seedPoint;
};

#endif // PARAMS_H

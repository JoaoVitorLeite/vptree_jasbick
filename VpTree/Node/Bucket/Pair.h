#pragma once

#include <cstdlib>
#include <vector>

template <class DType>
class Pair{
    private:
        std::pair<DType, std::vector<double>> pair;

    public:
        Pair(DType obj, std::vector<double> distanceVector);

        DType first();
        std::vector<double> second();
};

#include <VpTree/Node/Bucket/Pair-inl.h>

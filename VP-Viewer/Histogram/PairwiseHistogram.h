#pragma once

#include <Histogram/Histogram.h>
#include <Distance/DistanceFunction.h>

class PairwiseHistogram: public Histogram{
    public:
        PairwiseHistogram();
        PairwiseHistogram(const DatasetDouble &dataset, const uint_fast32_t histogram_size, DistanceFunction<InstanceDouble> *df);
        PairwiseHistogram(const DatasetString &dataset, const uint_fast32_t histogram_size, DistanceFunction<InstanceString> *df);
};

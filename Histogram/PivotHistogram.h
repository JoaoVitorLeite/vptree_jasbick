#pragma once

#include <Histogram/Histogram.h>
#include <Distance/DistanceFunction.h>

class PivotHistogram: public Histogram{
    public:
        PivotHistogram();

        // histogram_size = número de bins
        PivotHistogram(const DatasetDouble &dataset, const InstanceDouble &pivot, const uint_fast32_t histogram_size,
                       DistanceFunction<InstanceDouble> *df);
        PivotHistogram(const DatasetString &dataset, const InstanceString &pivot, const uint_fast32_t histogram_size,
                       DistanceFunction<InstanceString> *df);

};

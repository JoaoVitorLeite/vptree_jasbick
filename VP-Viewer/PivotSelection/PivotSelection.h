#pragma once

#include <Dataset/Dataset.h>
#include <Distance/DistanceFunction.h>
#include <MathFunctions/Math.h>
#include <numeric>
#include <random>
#include <assert.h>

class PivotSelection{
    private:
        static InstanceDouble &randomPivots(DatasetDouble &dataset);
        static InstanceDouble &selectVp(DatasetDouble &dataset, DistanceFunction<InstanceDouble> *df);
        static InstanceDouble &hull_foci(DatasetDouble &dataset, DistanceFunction<InstanceDouble> *df);

        static InstanceString &randomPivots(DatasetString &dataset);
        static InstanceString &selectVp(DatasetString &dataset, DistanceFunction<InstanceString> *df);
        static InstanceString &hull_foci(DatasetString &dataset, DistanceFunction<InstanceString> *df);

//        std::vector<size_t> FisherYatesShuffle(size_t size, size_t max_size, std::mt19937& gen);

    public:
        enum Algorithm{RANDOM, VP_TREE, K_MEDOID, HULL_FOCI};

        static InstanceDouble &getPivot(DatasetDouble &dataset, Algorithm algo, DistanceFunction<InstanceDouble> *df=nullptr);
        static InstanceString &getPivot(DatasetString &dataset, Algorithm algo, DistanceFunction<InstanceString> *df=nullptr);
};

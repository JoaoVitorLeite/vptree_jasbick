#pragma once

#include <Dataset/Dataset.h>
#include <Distance/DistanceFunction.h>

class PivotSelection{
    private:
        // Seleciona pivôs de forma aleatória
        static InstanceDouble randomPivots(const DatasetDouble &dataset);
        // Seleciona pivôs de acordo com o método do Yianilos, no artigo original da VP-Tree.
        static InstanceDouble selectVp(DatasetDouble dataset, DistanceFunction<InstanceDouble> *df);
        // Seleciona pivôs com o método do fecho-convexo.
        static InstanceDouble hull_foci(const DatasetDouble &dataset, DistanceFunction<InstanceDouble> *df);

        static InstanceString randomPivots(const DatasetString &dataset);
        static InstanceString selectVp(DatasetString dataset, DistanceFunction<InstanceString> *df);
        static InstanceString hull_foci(const DatasetString &dataset, DistanceFunction<InstanceString> *df);

    public:
        enum Algorithm{RANDOM, VP_TREE, K_MEDOID, HULL_FOCI};

        static InstanceDouble getPivot(const DatasetDouble &dataset, Algorithm algo, DistanceFunction<InstanceDouble> *df=nullptr);
        static InstanceString getPivot(const DatasetString &dataset, Algorithm algo, DistanceFunction<InstanceString> *df=nullptr);
};

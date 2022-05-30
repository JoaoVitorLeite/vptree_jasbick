#pragma once

#include "../Dataset/Dataset.h"
#include "../Distance/DistanceFunction.h"
#include "../eigen/Eigenvalues"

class PivotSelection{
private:
    // Seleciona pivôs de forma aleatória
    static InstanceDouble randomPivots(const DatasetDouble &dataset); //RANDOM
    // Seleciona pivôs de acordo com o método do Yianilos, no artigo original da VP-Tree.
    static InstanceDouble selectVp(DatasetDouble dataset, DistanceFunction<InstanceDouble> *df); //MaxVariance
    // Seleciona pivôs com o método do fecho-convexo.
    static InstanceDouble hull_foci(const DatasetDouble &dataset, DistanceFunction<InstanceDouble> *df); //CONVEX
    //Implementacoes JOAO
    static InstanceDouble gnatPivot(const DatasetDouble &dataset, DistanceFunction<InstanceDouble> *df){

        static size_t nPivots = 1;
        size_t drop = 2, currentPivot = 0, p1, pos = 0;
        bool* bitmap = new bool[dataset.getCardinality()];
        size_t* pvtIndex = new size_t[nPivots+drop];
        size_t* aux;
        double max = std::numeric_limits<double>::min(), dist, currentDist;

        for(size_t x = 0; x < dataset.getCardinality(); x++)
            bitmap[x] = false;

        for(size_t x = 0; x < (nPivots+drop); x++)
            pvtIndex[x] = 0;

        aux = new size_t(static_cast<size_t>(rand()) %(dataset.getCardinality()-1));
        p1 = aux[0];
        bitmap[p1] = true;
        pvtIndex[currentPivot] = p1;
        currentPivot++;

        for(size_t x = 0; x < dataset.getCardinality(); x++)
        {

            dist = df->getDistance(dataset[pvtIndex[0]], dataset[x]);

            if(dist > max)
            {

                max = dist;
                pos = x;

            }

        }

        bitmap[pos] = true;
        pvtIndex[currentPivot] = pos;
        currentPivot++;

        while((currentPivot - drop) < nPivots)
        {

            pos = 0;
            max = std::numeric_limits<double>::min();

            for(size_t x = 0; x < dataset.getCardinality(); x++)
            {

                if(!bitmap[x])
                {

                    currentDist = std::numeric_limits<double>::max();

                    for(size_t y = 0; y < currentPivot; y++)
                    {

                        dist = df->getDistance(dataset[x], dataset[pvtIndex[y]]);
                        currentDist = std::min(currentDist, dist);

                    }

                    if(currentDist > max)
                    {

                        max = currentDist;
                        pos = x;

                    }

                }

            }

            bitmap[pos] = true;
            pvtIndex[currentPivot] = pos;
            currentPivot++;


        }

//        for(size_t x = drop; x < (nPivots+drop); x++)
//            setPivot(sample->instance(pvtIndex[x]), x-drop);

        delete [] (aux);
        delete [] (bitmap);
        delete [] (pvtIndex);

        return dataset[pvtIndex[drop]];

    }
    static InstanceDouble maxseparetedPivots(const DatasetDouble &dataset, DistanceFunction<InstanceDouble> *df){

        static size_t nPivots = 1;

        size_t drop = 2, currentPivot = 0, pos = 0, p1;
        bool* bitmap = new bool[dataset.getCardinality()];
        size_t* pvtIndex = new size_t[nPivots+drop];
        size_t* aux;
        double max = std::numeric_limits<double>::min(), dist, sum = 0;

        for(size_t x = 0; x < dataset.getCardinality(); x++)
            bitmap[x] = false;

        for(size_t x = 0; x < (nPivots+drop); x++)
            pvtIndex[x] = 0;

        aux = new size_t(static_cast<size_t>(rand()) %(dataset.getCardinality()-1));
        p1 = aux[0];
        bitmap[p1] = true;
        pvtIndex[currentPivot] = p1;
        currentPivot++;

        for(size_t x = 0; x < dataset.getCardinality(); x++)
        {

            dist = df->getDistance(dataset[p1], dataset[x]);

            if(dist > max)
            {

                max = dist;
                pos = x;

            }

        }

        bitmap[pos] = true;
        pvtIndex[currentPivot] = pos;
        currentPivot++;

        while((currentPivot-drop) < nPivots)
        {

            max = std::numeric_limits<double>::min();

            for(size_t x = 0; x < dataset.getCardinality(); x++)
            {

                if(!bitmap[x])
                {

                    sum = 0;

                    for(size_t y = 0; y < currentPivot; y++)
                        sum += df->getDistance(dataset[x], dataset[pvtIndex[y]]);

                    if(sum > max)
                    {

                        max = sum;
                        pos = x;

                    }

                }

            }

            bitmap[pos] = true;
            pvtIndex[currentPivot] = pos;
            currentPivot++;

        }

//        for(size_t x = drop; x < (getNumberOfPivots()+drop); x++)
//            setPivot(sample->instance(pvtIndex[x]), x-drop);

        delete [] (bitmap);
        delete [] (pvtIndex);

        return dataset[pvtIndex[drop]];

    }
    static InstanceDouble sssPivots(const DatasetDouble &dataset, DistanceFunction<InstanceDouble> *df){

        static size_t nPivots = 1;
        static double alpha = 0.35;
        size_t drop = 2, currentPivot = 0, p1, index = 0, count = 0;
        size_t* pvtIndex = new size_t[nPivots+drop];
        size_t* aux;
        double max = std::numeric_limits<double>::min(), dist, threshold;

        for(size_t x = 0; x < (nPivots+drop); x++)
            pvtIndex[x] = 0;

        for(size_t x = 0; x < dataset.getCardinality(); x++)
        {

            for(size_t y = 0; y < dataset.getCardinality(); y++)
            {

                if(x < y)
                {

                    dist = df->getDistance(dataset[x], dataset[y]);

                    if(dist > max)
                        max = dist;

                }

            }

        }

        threshold = max * alpha;

        aux = new size_t(static_cast<size_t>(rand()) %(dataset.getCardinality()-1));
        p1 = aux[0];
        pvtIndex[currentPivot] = p1;
        currentPivot++;

        while(index < dataset.getCardinality())
        {

            count = 0;

            for(size_t x = 0; x < currentPivot; x++)
            {

                dist = df->getDistance(dataset[index], dataset[pvtIndex[x]]);

                if(dist >= threshold)
                    count++;

            }

            if(count == currentPivot)
            {

                pvtIndex[currentPivot] = index;
                currentPivot++;

            }

            if((currentPivot-drop) == nPivots)
                break;
            else
                index++;

        }

//        for(size_t x = drop; x < (getNumberOfPivots()+drop); x++)
//            setPivot(sample->instance(pvtIndex[x]), x-drop);

        delete [] (aux);
        delete [] (pvtIndex);

        return dataset[pvtIndex[drop]];

    }
    static InstanceDouble pcaPivots(const DatasetDouble &dataset, DistanceFunction<InstanceDouble> *df){

        double max = std::numeric_limits<double>::min();
        double min = std::numeric_limits<double>::max();

        Eigen::MatrixXd A;
        A.resize(dataset.getCardinality(), dataset.getCardinality());

        for(size_t i = 0; i < dataset.getCardinality(); i++)
        {

            for(size_t j = 0; j < dataset.getCardinality(); j++)
            {

                if(i < j)
                {

                    A(i,j) = df->getDistance(dataset[i], dataset[j]);
                    A(j,i) = A(i,j);

                    if(A(i,j) > max) max = A(i,j);
                    if(A(i,j) < min) min = A(i,j);

                }

                if(i == j) A(i,j) = 0.0;

            }

        }

        for(size_t i = 0; i < dataset.getCardinality(); i++)
        {

            for(size_t j = 0; j < dataset.getCardinality(); j++)
            {

                if(i < j)
                {

                    A(i,j) = (A(i,j) - min)/(max - min);
                    A(j,i) = A(i,j);

                }

            }

        }

        Eigen::EigenSolver<Eigen::MatrixXd> s(A);
        Eigen::VectorXd eigenValues = s.eigenvalues().real();

        std::vector<std::pair<double, long>> v;

        for(long i = 0; i < eigenValues.size(); i++)
        {

            std::pair<double, long> tupleAux(eigenValues[i], i);
            v.push_back(tupleAux);

        }

        std::sort(v.begin(), v.end(), [](const std::pair<double, long>& a, const std::pair<double, long>& b){ return std::get<0>(a) > std::get<0>(b); });

//        for(size_t x = 0; x < getNumberOfPivots(); x++)
//            setPivot(sample->instance(v[x].second), x);

        return dataset[v[0].second];

    }
    static InstanceDouble kmedoidPivots(const DatasetDouble &dataset, DistanceFunction<InstanceDouble> *df){

        double min = std::numeric_limits<double>::max();
        size_t size = dataset.getCardinality(), pvt_index = 0;

        for(size_t x = 0; x < dataset.getCardinality(); x++)
        {

            double total = 0;

            for(size_t y = 0; y < dataset.getCardinality(); y++)
            {

                if(x != y)
                    total += df->getDistance(dataset[x], dataset[y])/(size-1);

            }

            if(total < min)
            {

                min = total;
                pvt_index = x;

            }

        }

        return dataset[pvt_index];

    }
    static InstanceDouble selectionPivots(const DatasetDouble &dataset, DistanceFunction<InstanceDouble> *df){

        return kmedoidPivots(dataset, df);

    }

    static InstanceString randomPivots(const DatasetString &dataset);
    static InstanceString selectVp(DatasetString dataset, DistanceFunction<InstanceString> *df);
    static InstanceString hull_foci(const DatasetString &dataset, DistanceFunction<InstanceString> *df);

public:
    enum Algorithm{RANDOM, VP_TREE, K_MEDOID, HULL_FOCI, GNAT, MAX_SEPARATED, SSS, PCA, SELECTION};

    static InstanceDouble getPivot(const DatasetDouble &dataset, Algorithm algo, DistanceFunction<InstanceDouble> *df=nullptr);
    static InstanceString getPivot(const DatasetString &dataset, Algorithm algo, DistanceFunction<InstanceString> *df=nullptr);
};

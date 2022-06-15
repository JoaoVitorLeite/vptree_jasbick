#include <iostream>
#include <VpTree/VpTree.h>
#include <Dataset/Dataset.h>
#include <Distance/DistanceFunction.h>
#include <Distance/EuclideanDistance.h>

typedef VpTree<InstanceDouble, DistanceFunction<InstanceDouble>> TreeInstanceDouble;

using namespace std;

int main(int argc, char *argv[]){

//    //    DatasetDouble *train = new DatasetDouble();
//    //    DatasetDouble::doubleFileToDataset(train, "/home/joaovictor/Code/vptree_jasbick/Datasets/train_ulcer_SPP.csv", 40403, 12);
//    //    DatasetDouble *test = new DatasetDouble();
//    //    DatasetDouble::doubleFileToDataset(test, "/home/joaovictor/Code/vptree_jasbick/Datasets/test_ulcer_SPP.csv", 4490, 12);


/*******************************************************************************************************************************/


    for(std::size_t w = 0; w < 4490; w++){

//        Dataset<InstanceDouble> *train = new Dataset<InstanceDouble>();
//        Dataset<InstanceDouble>::doubleFileToDataset(train, "/home/joaovictor/Code/Private.VP-Viewer/Datasets/cities.csv", 5507, 2);
        DatasetDouble *train = new DatasetDouble();
        DatasetDouble::doubleFileToDataset(train, "/home/joaovictor/Code/Private.VP-Viewer/Datasets/train_ulcer_SPP.csv", 40403, 12);
        DatasetDouble *test = new DatasetDouble();
        DatasetDouble::doubleFileToDataset(test, "/home/joaovictor/Code/Private.VP-Viewer/Datasets/test_ulcer_SPP.csv", 4490, 12);
        DistanceFunction<InstanceDouble> *df = new EuclideanDistance<InstanceDouble>();
        std::vector<double> v;
        size_t k = 10;
        InstanceDouble *query = test->getFeatureVector(w).clone();

        for(size_t x = 0; x < train->getCardinality(); x++){

            v.push_back(df->getDistance(*query, train->getFeatureVector(x)));

        }

        std::sort(v.begin(), v.end());
        v.resize(k);

        TreeInstanceDouble *tree = new TreeInstanceDouble(false,
                                                          0.0,
                                                          400,
                                                          PivotSelection::RANDOM,
                                                          train,
                                                          df);

        df->resetStatistics();
        Dataset<InstanceDouble> *ans = new Dataset<InstanceDouble>();

        tree->kNNInc(*query, k, tree->getRoot(), ans, df);

        for(size_t x = 0; x < ans->getCardinality(); x++){

            if(df->getDistance(ans->getFeatureVector(x), *query) != v[x])
                cout << "ERRO em : " << w << endl;

        }

    }

/******************************************************************************************************************************/

//    Dataset<InstanceDouble> *train = new Dataset<InstanceDouble>();
//    Dataset<InstanceDouble>::doubleFileToDataset(train, "/home/joaovictor/Code/Private.VP-Viewer/Datasets/cities.csv", 5507, 2);
//    DistanceFunction<InstanceDouble> *df = new EuclideanDistance<InstanceDouble>();
//    std::vector<std::pair<InstanceDouble, double>> v;
//    size_t k = 100;
//    size_t w = 21;
//    InstanceDouble *query = train->getFeatureVector(w).clone();

//    for(size_t x = 0; x < train->getCardinality(); x++){

//        v.push_back(std::pair(train->getFeatureVector(x), df->getDistance(*query, train->getFeatureVector(x))));

//    }

//    std::sort(v.begin(), v.end(), [](std::pair<InstanceDouble, double> a, std::pair<InstanceDouble, double> b){
//        return a.second < b.second;
//    });

//    v.resize(k);

//    TreeInstanceDouble *tree = new TreeInstanceDouble(false,
//                                                      0.0,
//                                                      400,
//                                                      PivotSelection::RANDOM,
//                                                      train,
//                                                      df);

//    df->resetStatistics();
//    Dataset<InstanceDouble> *ans = new Dataset<InstanceDouble>();

//    tree->kNN(*query, k, tree->getRoot(), ans, df);

//    for(size_t x = 0; x < ans->getCardinality(); x++){

//        if(df->getDistance(ans->getFeatureVector(x), *query) != v[x].second){

//            cout << "ERRO" << endl;

//        }

//    }


    return 0;

}

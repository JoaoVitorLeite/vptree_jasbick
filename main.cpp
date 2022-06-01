#include <iostream>
#include <Dataset/Dataset.h>
#include <VpTree/VpTree.h>
#include <PivotSelection/PivotSelection.h>
#include <Distance/DistanceFunction.h>
#include <Distance/EuclideanDistance.h>
#include <fstream>
#include <chrono>

//#include <QApplication>
//#include "mainwindow.h"

//QByteArray readTextFile(const QString &file_path) {
//  QFile input_file(file_path);
//  QByteArray input_data;

//  if (input_file.open(QIODevice::Text | QIODevice::Unbuffered | QIODevice::ReadOnly)) {
//    input_data = input_file.readAll();
//    input_file.close();
//    return input_data;
//  }
//  else {
//    return QByteArray();
//  }
//}

typedef VpTree<InstanceDouble, DistanceFunction<InstanceDouble>> TreeInstanceDouble;

using namespace std;

int main(int argc, char *argv[]){

    //    QApplication app(argc, argv);

    //    MainWindow *wMainWindow = new MainWindow();
    //    wMainWindow->show();

    //    QString stylesheet = readTextFile(":/lightbreeze.qss");

    //    app.setStyleSheet(stylesheet);

    //    return app.exec();

//    srand(20);

//    DatasetDouble *train = new DatasetDouble();
//    DatasetDouble::doubleFileToDataset(train, "/home/joaovictor/Code/vptree_jasbick/Datasets/train_ulcer_SPP.csv", 40402, 12);
//    DatasetDouble *train2 = new DatasetDouble();
//    DatasetDouble::doubleFileToDataset(train2, "/home/joaovictor/Code/vptree_jasbick/Datasets/train_ulcer_SPP.csv", 40402, 12);
//    DatasetDouble *test = new DatasetDouble();
//    DatasetDouble::doubleFileToDataset(test, "/home/joaovictor/Code/vptree_jasbick/Datasets/test_ulcer_SPP.csv", 4490, 12);
//    DistanceFunction<InstanceDouble> *df = new EuclideanDistance<InstanceDouble>();

//    TreeInstanceDouble *tree = new TreeInstanceDouble(false,
//                                                      0.0,
//                                                      400,
//                                                      PivotSelection::VP_TREE,
//                                                      train,
//                                                      df);
//    size_t k = 100;

//    DatasetDouble *ans = new DatasetDouble();
//    df->ResetStatistics();
//    tree->kNN(test->getFeatureVector(0), 10, tree->getRoot(), ans, df);
//    cout << df->getDistanceCount() << endl;

//    for(size_t x = 0; x < test->getCardinality(); x++){

//        tree->kNN(test->getFeatureVector(x), k, tree->getRoot(), ans, df);

//        vector<double> v;
//        for(size_t y = 0; y < train2->getCardinality(); y++)
//            v.push_back(df->getDistance(test->getFeatureVector(x), train2->getFeatureVector(y)));
//        std::sort(v.begin(), v.end());
//        v.resize(k);

//        for(size_t z = 0; z < k; z++){
//            if(df->getDistance(ans->getFeatureVector(z), test->getFeatureVector(x)) != v[z])
//                cout << "iteracao " << x << " : " << "ERRO" << endl;
//        }

//    }
    /*
    -DATASET_TRAIN => Caminho para o dataset de treino
    ** -DATASET_TRAIN_CARDINALITY => Cardinalidade do dataset de treino
    ** -DATASET_TRAIN_DIMENSIONALITY => Dimensionalidade do dataset de treino
    -DATASET_TEST => Caminho para o dataset de teste
    ** -DATASET_TEST_CARDINALITY => Cardinalidade do dataset de teste
    ** -DATASET_TEST_DIMENSIONALITY => Dimensionalidade do dataset de teste
    -PIVOT_TYPE => Tipo de pivo
    -SAMPLE_SIZE_PIVOT => Tamanho da amostra para gerar os pivôs
    -SEED = Seed
    -K_MAX => Valor máximo para os k-vizinhos mais próximos !DEFAULT = 50
    -NUM_QUERY => Quantidade de consulta a serem realizadas usando o dataset de treino
    -NUM_PER_LEAF => Quantidade máxima de elementos por nó folha
    -PATH_SAVE_RESULTS => Caminho para salvar os arquivos gerados !DEFAULT = ../results/

*/

    if((argc-1) % 2 != 0)
    {

        throw std::invalid_argument("Invalid number of arguments !_!");

    }
    else
    {


        DatasetDouble *train = new DatasetDouble(),
                *test = new DatasetDouble();

        DistanceFunction<InstanceDouble>* df = new EuclideanDistance<InstanceDouble>();

        std::string *dataset_train = nullptr,
                *dataset_test = nullptr,
                *pivot_type = nullptr,
                *path_save_results = nullptr;

        size_t *dataset_train_cardinality = nullptr,
                *dataset_train_dimensionality = nullptr,
                *dataset_test_cardinality = nullptr,
                *dataset_test_dimensionality = nullptr,
                *seed = nullptr,
                *k_max = nullptr,
                *num_query = nullptr,
                *num_per_leaf = nullptr;

        PivotSelection::Algorithm pvt_algo = PivotSelection::RANDOM;

        for(int x = 1; x < argc; x += 2)
        {

            std::string key = argv[x];
            for(size_t x = 0; x < key.size(); x++)
                key[x] = std::toupper(key[x]);

            std::string value = argv[x+1];

            if(key == "-DATASET_TRAIN")
            {

                dataset_train = new std::string(value);

            }
            else if(key == "-DATASET_TRAIN_CARDINALITY")
            {

                dataset_train_cardinality = new size_t(std::stoi(value));

            }
            else if(key == "-DATASET_TRAIN_DIMENSIONALITY")
            {

                dataset_train_dimensionality = new size_t(std::stoi(value));

            }
            else if(key == "-DATASET_TEST")
            {

                dataset_test = new std::string(value);

            }
            else if(key == "-DATASET_TEST_CARDINALITY")
            {

                dataset_test_cardinality = new size_t(std::stoi(value));

            }
            else if(key == "-DATASET_TEST_DIMENSIONALITY")
            {

                dataset_test_dimensionality = new size_t(std::stoi(value));

            }
            else if(key == "-PIVOT_TYPE")
            {

                pivot_type = new std::string(value);

            }
            else if(key == "-SEED")
            {

                seed = new size_t(std::stoi(value));

            }
            else if(key == "-K_MAX")
            {

                k_max = new size_t(std::stoi(value));

            }
            else if(key == "-PATH_SAVE_RESULTS")
            {

                path_save_results = new std::string(value);

            }
            else if(key == "-NUM_PER_LEAF")
            {

                num_per_leaf = new size_t(std::stoi(value));

            }
            else if(key == "-NUM_QUERY")
            {

                num_query = new size_t(std::stoi(value));

            }
            else
            {

                throw std::invalid_argument("Invalid key !_!");

            }

        }

        if((dataset_train == nullptr) || (dataset_test == nullptr) || (pivot_type == nullptr))
        {

            throw std::invalid_argument("Important arguments were not passed !_!");

        }

        //Read dataset train
        if((dataset_train_cardinality != nullptr) && (dataset_train_dimensionality != nullptr))
        {

            DatasetDouble::doubleFileToDataset(train, *dataset_train, *dataset_train_cardinality, *dataset_train_dimensionality);

        }


        //Read dataset test
        if((dataset_test_cardinality != nullptr) && (dataset_test_dimensionality != nullptr))
        {

            DatasetDouble::doubleFileToDataset(test, *dataset_test, *dataset_test_cardinality, *dataset_test_dimensionality);

        }


        //Read pivot
        if(*pivot_type == "RANDOM")
        {

            pvt_algo = PivotSelection::RANDOM;

        }
        else if(*pivot_type == "GNAT")
        {

            pvt_algo = PivotSelection::GNAT;

        }
        else if(*pivot_type == "CONVEX")
        {

            pvt_algo = PivotSelection::HULL_FOCI;

        }
        else if(*pivot_type == "KMEDOIDS")
        {

            pvt_algo = PivotSelection::K_MEDOID;

        }
        else if(*pivot_type == "MAXSEPARETED")
        {

            pvt_algo = PivotSelection::MAX_SEPARATED;

        }
        else if(*pivot_type == "MAXVARIANCE")
        {

            pvt_algo = PivotSelection::VP_TREE;

        }
        else if(*pivot_type == "SELECTION")
        {

            pvt_algo = PivotSelection::SELECTION;

        }
        else if(*pivot_type == "PCA")
        {

            pvt_algo = PivotSelection::PCA;

        }
        else if(*pivot_type == "SSS")
        {

            pvt_algo = PivotSelection::SSS;

        }

        //Read seed
        if(seed == nullptr)
        {

            seed = new size_t(100);

        }

        //Read K
        if(k_max == nullptr)
        {

            k_max = new size_t(50);

        }

        //Path save results
        if(path_save_results == nullptr)
        {

            path_save_results = new std::string("../results/");

        }


        //Maximo elementos por no folha
        if(num_per_leaf == nullptr)
        {

            *num_per_leaf = (size_t)std::ceil(0.1*train->getCardinality());

        }

        srand(*seed);

        TreeInstanceDouble *tree = new TreeInstanceDouble(false,
                                                          0.0,
                                                          (uint_fast32_t)*num_per_leaf,
                                                          pvt_algo,
                                                          train,
                                                          df);

        std::string fileName = *path_save_results + *pivot_type + ".csv";
        std::ofstream file(fileName);

        file << "VPTREE"
             << ","
             << "EUCLIDEANDISTANCE"
             << ","
             << pivot_type
             << ","
             << (num_query == nullptr ? test->getCardinality() : *num_query)
             << ","
             << *seed
             << "\n";

        file << "k,time,count\n";

        DatasetDouble *ans = new DatasetDouble();

        for(size_t k = 5; k <= *k_max; k += 5)
        {

            size_t max_query = test->getCardinality();

            if(num_query != nullptr)
            {

                max_query = std::min(*num_query, test->getCardinality());

            }

            for(size_t x = 0; x < max_query; x++)
            {

                df->resetStatistics();
                auto start = std::chrono::steady_clock::now();
                tree->kNNInc(test->getFeatureVector(x), k, tree->getRoot(), ans, df);
                auto end = std::chrono::steady_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

                file << k
                     << ","
                     << elapsed.count()
                     << ","
                     << df->getDistanceCount() << endl;

            }

        }

        file.close();

    }

    return 0;

}

//#include <QCoreApplication>

//#include <iostream>
//#include <thread>
//#include <sys/types.h>
//#include <dirent.h>
//#include <stdio.h>
//#include <map>
//#include <sstream>
//#include <mutex>

//#include <Dataset/Dataset.h>
//#include <VpTree/VpTree.h>
//#include <PivotSelection/PivotSelection.h>
//#include <Distance/DistanceFunction.h>
//#include <Distance/EuclideanDistance.h>
//#include <Distance/ManhattanDistance.h>
//#include <Distance/CanberraDistance.h>
//#include <Distance/ChebyshevDistance.h>
//#include <Distance/BrayCurtisDistance.h>


//int main(int argc, char *argv[]){

//    /*
//     *
//     * Criar novas Instancias (new InstanceDouble) no PivotSelection pode ser um problema...
//     *
//     */

//    QCoreApplication app(argc, argv);

//    srand(static_cast<unsigned int>(time(nullptr)));

//    std::cout << "Running..." << std::endl;

//    DatasetDouble *dataset = new DatasetDouble();
//    dataset->loadFromFile("/home/notox/VP-Viewer Experimentos Nuvem/Datasets/cities.csv", 5507, 2);
//    DatasetDouble *dataset2 = new DatasetDouble();
//    dataset2->loadFromFile("/home/notox/VP-Viewer Experimentos Nuvem/Datasets/cities.csv", 5507, 2);

//    EuclideanDistance<InstanceDouble> *df = new EuclideanDistance<InstanceDouble>();
//    VpTree<InstanceDouble, DistanceFunction<InstanceDouble>> vpt(false, 500, PivotSelection::RANDOM, dataset, df);

//    DatasetDouble result;

//    /*
//     * Incremental
//     */
//    std::cout << "Incremental: ";

//    df->resetStatistics();

//    clock_t begin = clock();

//    for (size_t i = 0; i < 25; i++)
//        vpt.kNN(dataset2->operator[](i), 5, vpt.getRoot(), &result, df, true);

//    clock_t end = clock();
//    std::cout << double(end - begin) / CLOCKS_PER_SEC << " - " << df->getDistanceCount() << std::endl;

//    /*
//     * Standard
//     */
//    std::cout << "Standard: ";

//    df->resetStatistics();

//    begin = clock();

//    for (size_t i = 0; i < 25; i++)
//        vpt.kNN(dataset2->operator[](i), 5, vpt.getRoot(), &result, df, false);

//    end = clock();
//    std::cout << double(end - begin) / CLOCKS_PER_SEC << " - " << df->getDistanceCount() << std::endl;

//    std::cout << "Finished." << std::endl;

//    return app.exec();
//}

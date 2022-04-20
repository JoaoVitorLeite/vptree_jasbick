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

////    while (true){

////    clock_t begin = clock();

//    std::cout << "Running..." << std::endl;

//    DatasetDouble *dataset = new DatasetDouble();
//    dataset->loadFromFile("test.csv", 50, 1);
//    DatasetDouble *dataset2 = new DatasetDouble();
//    dataset2->loadFromFile("test.csv", 50, 1);

//    EuclideanDistance<InstanceDouble> *df = new EuclideanDistance<InstanceDouble>();

//    DatasetDouble result_1 = dataset->kNN(dataset->operator [](0), 5, df);

//    VpTree<InstanceDouble, DistanceFunction<InstanceDouble>> vpt(false, 3, PivotSelection::RANDOM, dataset, df);
//    DatasetDouble result_2;
//    vpt.kNN(dataset2->operator [](0), 5, vpt.getRoot(), &result_2, df, true);

//    for (size_t i = 0; i < result_1.getSize(); i++)
//        std::cout << result_1[i].getOID() << std::endl;

//    std::cout  << "\n--------\n" << std::endl;

//    for (size_t i = 0; i < result_2.getSize(); i++)
//        std::cout << result_2[i].getOID() << std::endl;

//    for (size_t i = 0; i < result_2.getSize(); i++){
//        if (!(result_1.contains(&result_2[i]))){
//            std::cout << "\nDIFERENTES\n" << std::endl;
//            std::exit(0);
//        }
//    }

//    std::cout << "Finished." << std::endl;

//    return app.exec();
//}

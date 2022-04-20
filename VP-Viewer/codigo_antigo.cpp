//#include <iostream>
//#include <QCoreApplication>
//#include <QtConcurrent/QtConcurrentRun>
//#include <QtConcurrent/QtConcurrent>
//#include <Dataset/Dataset.h>
//#include <VpTree/VpTree.h>
//#include <PivotSelection/PivotSelection.h>
//#include <functional>
//#include <Distance/DistanceFunction.h>
//#include <Distance/EuclideanDistance.h>
//#include <Distance/ManhattanDistance.h>
//#include <Distance/CanberraDistance.h>
//#include <Distance/ChebyshevDistance.h>
//#include <Distance/BrayCurtisDistance.h>


//void test(std::string testName, std::string queryType, bool isBalanced, uint_fast32_t maxNumberOfElements,
//          PivotSelection::Algorithm pivotAlgo, DatasetDouble *dataset, DistanceFunction<InstanceDouble> *df){

//    std::string output_line;

//    for (int j = 1; j < 6; j++){

//        double ten_fold_mean = 0.0;

//        uint_fast32_t last_iterator_10p = 0;
//        uint_fast32_t first_iterator_10p = 0;

//        uint_fast32_t K = 10;

//        // For do cross-validation
//        for (uint_fast32_t k = 0; k < K; k++){

//            if (k == 0){
//                last_iterator_10p = ((dataset->getCardinality()/K)*(k+1)) - 1;
//            } else {
//                first_iterator_10p = last_iterator_10p+1;

//                if (k == K-1)
//                    last_iterator_10p = dataset->getCardinality();
//                else
//                    last_iterator_10p = (dataset->getCardinality()/K)*(k+1);
//            }

//            DatasetDouble dataset10p = dataset->subDataset(first_iterator_10p, last_iterator_10p);

//            DatasetDouble *dataset90p = new DatasetDouble(*dataset);
//            dataset90p->erase(first_iterator_10p, last_iterator_10p);

//            double maxDist = DatasetDouble::getMax(*dataset90p, df);
//            VpTree<InstanceDouble, DistanceFunction<InstanceDouble>> vpt(isBalanced, 0.0, maxNumberOfElements, pivotAlgo, dataset90p, df);

//            double distance_mean = 0.0;

//            for (uint_fast32_t i = 0; i < dataset10p.getCardinality(); i++){

//                df->resetStatistics();

//                InstanceDouble qElement = dataset10p.operator[](i);

//                DatasetDouble answer;

//                if (queryType == "range")
//                    vpt.rangeQuery(qElement, (maxDist * (j*5))/100, vpt.getRoot(), &answer, df);
//                else if (queryType == "kNN")
//                    vpt.kNN(qElement, (j*2)-1, vpt.getRoot(), &answer, df);

//                distance_mean += (double) df->getDistanceCount()/(double) dataset10p.getCardinality();

//            }

//            ten_fold_mean += distance_mean/K;

//        }

//        if (j < 5)
//            output_line.append(std::to_string(ten_fold_mean) + ",");
//        else
//            output_line.append(std::to_string(ten_fold_mean) + "\n");

//    }


//    std::ofstream file("Results/" + testName + ".txt");
//    file << testName << "," << output_line;
//    file.close();
//}

//void run_experiments_on(std::string fileName, std::string filePath, uint_fast32_t fileCardinality, uint_fast32_t fileDimensionality,
//                        uint_fast32_t maxNumberOfElements, DistanceFunction<InstanceDouble> *df, std::string df_name){

//    DatasetDouble *dataset = new DatasetDouble(fileCardinality);
//    DatasetDouble::doubleFileToDataset(dataset, filePath, fileCardinality, fileDimensionality);

//    std::vector<PivotSelection::Algorithm> pivot_algorithms;
//    std::vector<std::string> pivot_algorithm_names;

//    pivot_algorithms.push_back(PivotSelection::RANDOM);
//    pivot_algorithm_names.push_back("Random");
//    pivot_algorithms.push_back(PivotSelection::HULL_FOCI);
//    pivot_algorithm_names.push_back("HullFoci");
//    pivot_algorithms.push_back(PivotSelection::VP_TREE);
//    pivot_algorithm_names.push_back("SelectVP");

//    for (uint_fast32_t i = 0; i < 3; i++){

//        test(fileName + "," + df_name + ",Range,Unbalanced," + pivot_algorithm_names[i],
//             "range",
//             false,
//             maxNumberOfElements,
//             pivot_algorithms[i],
//             dataset,
//             df);

//        test(fileName + "," + df_name + ",Range,Balanced," + pivot_algorithm_names[i],
//             "range",
//             true,
//             maxNumberOfElements,
//             pivot_algorithms[i],
//             dataset,
//             df);

//        test(fileName + "," + df_name + ",kNN,Unbalanced," + pivot_algorithm_names[i],
//             "kNN",
//             false,
//             maxNumberOfElements,
//             pivot_algorithms[i],
//             dataset,
//             df);

//        test(fileName + "," + df_name + ",kNN,Balanced," + pivot_algorithm_names[i],
//             "kNN",
//             true,
//             maxNumberOfElements,
//             pivot_algorithms[i],
//             dataset,
//             df);

//    }
//}

//int main(int argc, char *argv[]){

//    QCoreApplication app(argc, argv);

//    // Prepare result file
//    std::ofstream file("Results/0 Results.csv");
//    file << "name,dist_func,query_type,balance_type,pivot_selection,v1,v2,v3,v4,v5\n";
//    file.close();

//    clock_t begin = clock();

//    std::cout << "Running..." << std::endl;


//    // Code test

////    QtConcurrent::run(std::bind(&run_experiments_on, "Poker_Hand", "Datasets/128503 | 10 poker-hand.csv", 501, 10, 50,
////                      new EuclideanDistance<InstanceDouble>(), "Euclidean"));

////    QtConcurrent::run(std::bind(&run_experiments_on, "Skin_NonSkin", "Datasets/245057 | 4 Skin_NonSkin.csv", 502, 4, 50,
////                      new ManhattanDistance<InstanceDouble>(), "Manhattan"));

////    QtConcurrent::run(std::bind(&run_experiments_on, "3D_spatial_network", "Datasets/434874 | 4 3D_spatial_network.csv", 503, 4, 50,
////                      new ChebyshevDistance<InstanceDouble>(), "Chebyshev"));

////    QtConcurrent::run(std::bind(&run_experiments_on, "YearPredictionMSD", "Datasets/515345 | 90 YearPredictionMSD.csv", 504, 90, 50,
////                      new CanberraDistance<InstanceDouble>(), "Canberra"));

////    QtConcurrent::run(std::bind(&run_experiments_on, "COVERTYPE", "Datasets/581012 | 54 COVERTYPE.csv", 505, 54, 50,
////                      new BrayCurtisDistance<InstanceDouble>(), "BrayCurtis"));

////    QtConcurrent::run(std::bind(&run_experiments_on, "Buzz_in_social_media_Twitter", "Datasets/583250 | 78 Buzz in Social media Dataset Twitter.csv", 506, 78, 50,
////                      new EuclideanDistance<InstanceDouble>(), "Euclidean"));

////    QtConcurrent::run(std::bind(&run_experiments_on, "FONTS", "Datasets/832822 | 410 FONTS.csv", 507, 410, 50,
////                      new ManhattanDistance<InstanceDouble>(), "Manhattan"));

////    QtConcurrent::run(std::bind(&run_experiments_on, "Gas_sensors_home", "Datasets/928991 | 12 Gas sensors for home activity monitoring Data Set.csv", 508, 12, 50,
////                      new ChebyshevDistance<InstanceDouble>(), "Chebyshev"));

////    QtConcurrent::run(std::bind(&run_experiments_on, "Gas_sensors_dynamic_methane", "Datasets/4178504 | 19 Gas sensor array under dynamic gas mixtures Data Set ethylene_methane.csv", 509, 19, 50,
////                      new CanberraDistance<InstanceDouble>(), "Canberra"));

////    QtConcurrent::run(std::bind(&run_experiments_on, "Gas_sensors_dynamic_CO2", "Datasets/4208261 | 19 Gas sensor array under dynamic gas mixtures Data Set ethylene_CO.csv", 510, 19, 50,
////                      new BrayCurtisDistance<InstanceDouble>(), "BrayCurtis"));

////    QtConcurrent::run(std::bind(&run_experiments_on, "SUSY", "Datasets/5000000 | 19 SUSY.csv", 511, 19, 50,
////                      new EuclideanDistance<InstanceDouble>(), "Euclidean"));

////    QtConcurrent::run(std::bind(&run_experiments_on, "HEPMASS", "Datasets/10500000 | 28 hepmass.csv", 512, 28, 50,
////                      new ManhattanDistance<InstanceDouble>(), "Manhattan"));

////    QtConcurrent::run(std::bind(&run_experiments_on, "HIGGS", "Datasets/11000000 | 29 HIGGS.csv", 513, 29, 50,
////                      new ChebyshevDistance<InstanceDouble>(), "Chebyshev"));

////    QtConcurrent::run(std::bind(&run_experiments_on, "Sgemm_product", "Datasets/241600 | 4 sgemm_product.csv", 514, 4, 50,
////                      new CanberraDistance<InstanceDouble>(), "Canberra"));

////    QtConcurrent::run(std::bind(&run_experiments_on, "Sensorless_drive", "Datasets/58509 | 59 Sensorless_drive_diagnosis.csv", 515, 59, 50,
////                      new BrayCurtisDistance<InstanceDouble>(), "BrayCurtis"));

////    QtConcurrent::run(std::bind(&run_experiments_on, "RelationNetwork", "Datasets/53414 | 23 Relation Network.csv", 516, 23, 50,
////                      new EuclideanDistance<InstanceDouble>(), "Euclidean"));

////    QtConcurrent::run(std::bind(&run_experiments_on, "Physicochemical_Properties", "Datasets/45730 | 9 Physicochemical_Properties.csv", 517, 9, 50,
////                      new ManhattanDistance<InstanceDouble>(), "Manhattan"));

////    QtConcurrent::run(std::bind(&run_experiments_on, "OnlineNewsPopularity", "Datasets/39644 | 60 OnlineNewsPopularity.csv", 518, 60, 50,
////                      new ChebyshevDistance<InstanceDouble>(), "Chebyshev"));

////    QtConcurrent::run(std::bind(&run_experiments_on, "Superconductivty", "Datasets/21263 | 81 Superconductivty.csv", 519, 81, 50,
////                      new CanberraDistance<InstanceDouble>(), "Canberra"));

////    QtConcurrent::run(std::bind(&run_experiments_on, "Buzz_in_social_media_TomsHardware", "Datasets/28179 | 97 Buzz in Social media Dataset TomsHardware.csv", 520, 97, 50,
////                      new BrayCurtisDistance<InstanceDouble>(), "BrayCurtis"));


//    // Real experiments

//    QtConcurrent::run(std::bind(&run_experiments_on, "Poker_Hand", "Datasets/128503 | 10 poker-hand.csv", 128503, 10, 500,
//                      new EuclideanDistance<InstanceDouble>(), "Euclidean"));

//    QtConcurrent::run(std::bind(&run_experiments_on, "Skin_NonSkin", "Datasets/245057 | 4 Skin_NonSkin.csv", 245057, 4, 500,
//                      new ManhattanDistance<InstanceDouble>(), "Manhattan"));

//    QtConcurrent::run(std::bind(&run_experiments_on, "3D_spatial_network", "Datasets/434874 | 4 3D_spatial_network.csv", 434874, 4, 500,
//                      new ChebyshevDistance<InstanceDouble>(), "Chebyshev"));

//    QtConcurrent::run(std::bind(&run_experiments_on, "YearPredictionMSD", "Datasets/515345 | 90 YearPredictionMSD.csv", 515345, 90, 500,
//                      new CanberraDistance<InstanceDouble>(), "Canberra"));

//    QtConcurrent::run(std::bind(&run_experiments_on, "COVERTYPE", "Datasets/581012 | 54 COVERTYPE.csv", 581012, 54, 500,
//                      new BrayCurtisDistance<InstanceDouble>(), "BrayCurtis"));

//    QtConcurrent::run(std::bind(&run_experiments_on, "Buzz_in_social_media_Twitter", "Datasets/583250 | 78 Buzz in Social media Dataset Twitter.csv", 583250, 78, 500,
//                      new EuclideanDistance<InstanceDouble>(), "Euclidean"));

//    QtConcurrent::run(std::bind(&run_experiments_on, "FONTS", "Datasets/832822 | 410 FONTS.csv", 832822, 410, 500,
//                      new ManhattanDistance<InstanceDouble>(), "Manhattan"));

//    QtConcurrent::run(std::bind(&run_experiments_on, "Gas_sensors_home", "Datasets/928991 | 12 Gas sensors for home activity monitoring Data Set.csv", 928991, 12, 500,
//                      new ChebyshevDistance<InstanceDouble>(), "Chebyshev"));

//    QtConcurrent::run(std::bind(&run_experiments_on, "Gas_sensors_dynamic_methane", "Datasets/4178504 | 19 Gas sensor array under dynamic gas mixtures Data Set ethylene_methane.csv", 4178504, 19, 500,
//                      new CanberraDistance<InstanceDouble>(), "Canberra"));

//    QtConcurrent::run(std::bind(&run_experiments_on, "Gas_sensors_dynamic_CO2", "Datasets/4208261 | 19 Gas sensor array under dynamic gas mixtures Data Set ethylene_CO.csv", 4208261, 19, 500,
//                      new BrayCurtisDistance<InstanceDouble>(), "BrayCurtis"));

//    QtConcurrent::run(std::bind(&run_experiments_on, "SUSY", "Datasets/5000000 | 19 SUSY.csv", 5000000, 19, 500,
//                      new EuclideanDistance<InstanceDouble>(), "Euclidean"));

//    QtConcurrent::run(std::bind(&run_experiments_on, "HEPMASS", "Datasets/10500000 | 28 hepmass.csv", 10500000, 28, 500,
//                      new ManhattanDistance<InstanceDouble>(), "Manhattan"));

//    QtConcurrent::run(std::bind(&run_experiments_on, "HIGGS", "Datasets/11000000 | 29 HIGGS.csv", 11000000, 29, 500,
//                      new ChebyshevDistance<InstanceDouble>(), "Chebyshev"));

//    QtConcurrent::run(std::bind(&run_experiments_on, "Sgemm_product", "Datasets/241600 | 4 sgemm_product.csv", 241600, 4, 500,
//                      new CanberraDistance<InstanceDouble>(), "Canberra"));

//    QtConcurrent::run(std::bind(&run_experiments_on, "Sensorless_drive", "Datasets/58509 | 59 Sensorless_drive_diagnosis.csv", 58509, 59, 500,
//                      new BrayCurtisDistance<InstanceDouble>(), "BrayCurtis"));

//    QtConcurrent::run(std::bind(&run_experiments_on, "RelationNetwork", "Datasets/53414 | 23 Relation Network.csv", 53414, 23, 500,
//                      new EuclideanDistance<InstanceDouble>(), "Euclidean"));

//    QtConcurrent::run(std::bind(&run_experiments_on, "Physicochemical_Properties", "Datasets/45730 | 9 Physicochemical_Properties.csv", 45730, 9, 500,
//                      new ManhattanDistance<InstanceDouble>(), "Manhattan"));

//    QtConcurrent::run(std::bind(&run_experiments_on, "OnlineNewsPopularity", "Datasets/39644 | 60 OnlineNewsPopularity.csv", 39644, 60, 500,
//                      new ChebyshevDistance<InstanceDouble>(), "Chebyshev"));

//    QtConcurrent::run(std::bind(&run_experiments_on, "Superconductivty", "Datasets/21263 | 81 Superconductivty.csv", 21263, 81, 500,
//                      new CanberraDistance<InstanceDouble>(), "Canberra"));

//    QtConcurrent::run(std::bind(&run_experiments_on, "Buzz_in_social_media_TomsHardware", "Datasets/28179 | 97 Buzz in Social media Dataset TomsHardware.csv", 28179, 97, 50,
//                      new BrayCurtisDistance<InstanceDouble>(), "BrayCurtis"));

//    std::cout << "Finished." << std::endl;

//    clock_t end = clock();
//    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

//    std::cout << QString::number(elapsed_secs).toStdString() << std::endl;

//    return app.exec();
//}

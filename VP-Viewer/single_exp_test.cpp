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

//static std::mutex mutex;

//void query_function(size_t first_iterator, size_t last_iterator, int j, double maxDist,
//    std::string queryType, DistanceFunction<InstanceDouble> *df, DatasetDouble *dataset_k_percent,
//    VpTree<InstanceDouble, DistanceFunction<InstanceDouble>> *vpt,
//    double *result
//){

//    DistanceFunction<InstanceDouble> *dist_func = nullptr;

//    if (dynamic_cast<EuclideanDistance<InstanceDouble>*>(df)){
//        dist_func = new EuclideanDistance<InstanceDouble>(
//            *dynamic_cast<EuclideanDistance<InstanceDouble>*>(df)
//        );
//    }
//    if (dynamic_cast<ManhattanDistance<InstanceDouble>*>(df)){
//        dist_func = new ManhattanDistance<InstanceDouble>(
//            *dynamic_cast<ManhattanDistance<InstanceDouble>*>(df)
//        );
//    }
//    if (dynamic_cast<CanberraDistance<InstanceDouble>*>(df)){
//        dist_func = new CanberraDistance<InstanceDouble>(
//            *dynamic_cast<CanberraDistance<InstanceDouble>*>(df)
//        );
//    }
//    if (dynamic_cast<ChebyshevDistance<InstanceDouble>*>(df)){
//        dist_func = new ChebyshevDistance<InstanceDouble>(
//            *dynamic_cast<ChebyshevDistance<InstanceDouble>*>(df)
//        );
//    }
//    if (dynamic_cast<BrayCurtisDistance<InstanceDouble>*>(df)){
//        dist_func = new BrayCurtisDistance<InstanceDouble>(
//            *dynamic_cast<BrayCurtisDistance<InstanceDouble>*>(df)
//        );
//    }

//    double distance_mean = 0.0;
//    size_t dataset_k_percent_cardinality = dataset_k_percent->getCardinality();

//    clock_t begin = clock();
//    size_t percentage_of_for_loop = (((last_iterator - first_iterator)*1)/100);

//    for (size_t i = first_iterator; i <= last_iterator; i++){

//        if (percentage_of_for_loop != 0 && i % percentage_of_for_loop == 0){

//            double queries_per_sec = ((double) (i - first_iterator)/(double) ((clock() - begin)/CLOCKS_PER_SEC))/NUM_THREADS;
//            double percentage = ((double) (i-first_iterator)/(last_iterator-first_iterator))*100;

//            std::stringstream ss;

//            ss << "Thread " <<
//                  std::this_thread::get_id() <<
//                  " is running around " <<
//                    queries_per_sec <<
//                    " queries/seg. [" <<
//                    percentage <<
//                    "%]\n";

//            mutex.lock();
//            std::ofstream iterators_log("iterators_log.txt", std::ios::binary);
//            iterators_log.write(ss.str().c_str(), ss.str().length());
//            iterators_log.close();
//            mutex.unlock();
//        }


//        dist_func->resetStatistics();

//        InstanceDouble qElement = dataset_k_percent->operator[](i);

//        DatasetDouble answer;

//        if (queryType == "range")
//            vpt->rangeQuery(qElement, (maxDist * (j*4))/100, vpt->getRoot(), &answer, dist_func);
//        else if (queryType == "kNN")
//            vpt->kNN(qElement, (j*2)-1, vpt->getRoot(), &answer, dist_func, false);

//        distance_mean += ((double) dist_func->getDistanceCount()/(double) dataset_k_percent_cardinality);

//    }

//    *result = distance_mean;
//}

//void test(std::string testName, std::string queryType, bool isBalanced, size_t maxNumberOfElements,
//          PivotSelection::Algorithm pivotAlgo, DatasetDouble *dataset, DistanceFunction<InstanceDouble> *df){

//    std::ofstream log_file("log.txt", std::fstream::app);

//    std::string output_line;
//    size_t dataset_cardinality = dataset->getCardinality();

//    for (int j = 1; j < 6; j++){

//        double k_fold_mean = 0.0;

//        size_t last_iterator_k_percent = 0;
//        size_t first_iterator_k_percent = 0;

//        // Folds
//        size_t K = 3;

//        // Cross-validation
//        for (size_t k = 0; k < K; k++){

//            log_file << "Fold " << k+1 << std::endl;

//            if (k == 0){
//                last_iterator_k_percent = ((dataset_cardinality/K)*(k+1)) - 1;
//            } else {
//                first_iterator_k_percent = last_iterator_k_percent+1;

//                if (k == K-1)
//                    last_iterator_k_percent = dataset_cardinality;
//                else
//                    last_iterator_k_percent = (dataset_cardinality/K)*(k+1);
//            }

//            DatasetDouble dataset_k_percent = dataset->subDataset(first_iterator_k_percent, last_iterator_k_percent);

//            DatasetDouble *dataset90p = new DatasetDouble(*dataset);
//            dataset90p->erase(first_iterator_k_percent, last_iterator_k_percent);

//            log_file << "Calculating maxDist using Hull Foci..." << std::flush;

//            clock_t marker_begin = clock();

//            double maxDist = dataset90p->getMaxUsingHullFoci(df);

//            clock_t marker_end = clock();
//            log_file << " [" << double(marker_end - marker_begin) / CLOCKS_PER_SEC << "seg]" << std::endl;

//            log_file << "Building tree..." << std::flush;

//            marker_begin = clock();

//            VpTree<InstanceDouble, DistanceFunction<InstanceDouble>> vpt(
//                isBalanced, maxNumberOfElements, pivotAlgo, dataset90p, df
//            );

//            marker_end = clock();
//            log_file << " [" << double(marker_end - marker_begin) / CLOCKS_PER_SEC << "seg]" << std::endl;

//            size_t dataset_k_percent_cardinality = dataset_k_percent.getCardinality();

//            std::vector<std::thread *> thread_list(NUM_THREADS);
//            std::vector<double> thread_results(NUM_THREADS);

//            size_t first_iterator = 0;
//            size_t last_iterator = 0;

//            double distance_mean = 0.0;

//            log_file << "Running queries..." << std::flush;
//            marker_begin = clock();

//            // Lança threads
//            for (size_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

//                if (thread_counter == 0){
//                    last_iterator = ((dataset_k_percent_cardinality/NUM_THREADS)*(thread_counter+1)) - 1;
//                } else {
//                    first_iterator = last_iterator+1;

//                    if (thread_counter == NUM_THREADS-1)
//                        last_iterator = dataset_k_percent_cardinality-1;
//                    else
//                        last_iterator = (dataset_k_percent_cardinality/NUM_THREADS)*(thread_counter+1);
//                }

//                thread_list[thread_counter] = (
//                    new std::thread(
//                        query_function, first_iterator, last_iterator, j, maxDist, queryType, df, &dataset_k_percent, &vpt,
//                        &thread_results[thread_counter]
//                    )
//                );

//            }

//            // Reune threads
//            for (size_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

//                thread_list[thread_counter]->join();
//                delete thread_list[thread_counter];
//                thread_list[thread_counter] = nullptr;

//                distance_mean += thread_results[thread_counter]/NUM_THREADS;
//            }

//            marker_end = clock();
//            log_file << "[" << double(marker_end - marker_begin) / CLOCKS_PER_SEC / NUM_THREADS << "seg]" << std::endl << std::endl << std::flush;

//            k_fold_mean += distance_mean/K;

//        }

//        if (j < 5)
//            output_line.append(std::to_string(k_fold_mean) + ",");
//        else
//            output_line.append(std::to_string(k_fold_mean) + "\n");

//    }

//    log_file.close();

//    std::ofstream file("Results/" + testName + ".txt");
//    file << testName << "," << output_line;
//    file.close();
//}

//void run_experiments_on(std::string fileName, std::string filePath, size_t fileCardinality, size_t fileDimensionality,
//                        size_t maxNumberOfElements, DistanceFunction<InstanceDouble> *df, std::string df_name){

//    DatasetDouble *dataset = new DatasetDouble(fileCardinality);
//    dataset->loadFromFile(filePath, fileCardinality, fileDimensionality);

//    std::vector<PivotSelection::Algorithm> pivot_algorithms;
//    std::vector<std::string> pivot_algorithm_names;

//    pivot_algorithms.push_back(PivotSelection::RANDOM);
//    pivot_algorithm_names.push_back("Random");
//    pivot_algorithms.push_back(PivotSelection::HULL_FOCI);
//    pivot_algorithm_names.push_back("HullFoci");
//    pivot_algorithms.push_back(PivotSelection::VP_TREE);
//    pivot_algorithm_names.push_back("SelectVP");

//    std::ofstream log_file("log.txt");

//    for (size_t i = 0; i < 3; i++){

//        log_file << std::endl << fileName + " - " + df_name + " - Range - Unbalanced - " + pivot_algorithm_names[i] << std::endl << std::endl;

//        test(fileName + "," + df_name + ",Range,Unbalanced," + pivot_algorithm_names[i],
//             "range",
//             false,
//             maxNumberOfElements,
//             pivot_algorithms[i],
//             dataset,
//             df);

//        log_file << fileName + "," + df_name + ",Range,Balanced," + pivot_algorithm_names[i] << std::endl;

//        test(fileName + "," + df_name + ",Range,Balanced," + pivot_algorithm_names[i],
//             "range",
//             true,
//             maxNumberOfElements,
//             pivot_algorithms[i],
//             dataset,
//             df);

//        log_file << fileName + "," + df_name + ",kNN,Unbalanced," + pivot_algorithm_names[i] << std::endl;

//        test(fileName + "," + df_name + ",kNN,Unbalanced," + pivot_algorithm_names[i],
//             "kNN",
//             false,
//             maxNumberOfElements,
//             pivot_algorithms[i],
//             dataset,
//             df);

//        log_file << fileName + "," + df_name + ",kNN,Balanced," + pivot_algorithm_names[i] << std::endl;

//        test(fileName + "," + df_name + ",kNN,Balanced," + pivot_algorithm_names[i],
//             "kNN",
//             true,
//             maxNumberOfElements,
//             pivot_algorithms[i],
//             dataset,
//             df);

//    }

//    log_file.close();
//}

//int main(int argc, char *argv[]){

//    QCoreApplication app(argc, argv);

//    srand(time(nullptr));

//    // Prepare result file
//    std::ofstream file("Results/0 Results.csv");
//    file << "name,dist_func,query_type,balance_type,pivot_selection,v1,v2,v3,v4,v5\n";
//    file.close();

//    // Clear iterators_log
//    std::ofstream iterators_log("iterators_log.txt");
//    iterators_log.close();

//    clock_t begin = clock();

//    std::cout << "Running..." << std::endl;

//    run_experiments_on("HIGGS", "/home/notox/VP-Viewer Experimentos Nuvem/Datasets/11000000 | 29 HIGGS.csv", 11000000, 29, 500,
//                      new ManhattanDistance<InstanceDouble>(), "Manhattan");

//    std::cout << "Finished." << std::endl;

//    clock_t end = clock();
//    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / NUM_THREADS;

//    std::cout << QString::number(elapsed_secs).toStdString() << std::endl;

//    return app.exec();
//}

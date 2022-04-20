//#pragma once

//#include <Dataset/Dataset.h>
//#include <thread>
//#include <math.h>

//#define IMPL_TEMPL template<class DType>

//#define NUM_THREADS 4

//IMPL_TEMPL Dataset<DType>::Dataset(){
//}

//IMPL_TEMPL Dataset<DType>::Dataset(size_t new_cap){
//    dataset.reserve(new_cap);
//}

//IMPL_TEMPL
//template<class DistanceFunction>
//Dataset<DType> Dataset<DType>::rangeQuery(const DType &qElement, const double radius, DistanceFunction df) const{

//    Dataset<DType> answer;
//    answer.reserve(cardinality);
//    answer.setCardinality(cardinality);
//    answer.setDimensionality(dimensionality);

//    for (uint_fast32_t i = 0; i < cardinality; i++){

//        DType fv = operator [](i);

//        double dist = df->getDistance(qElement, fv);

//        if (dist <= radius)
//            answer.push_back(fv);

//    }

//    answer.setCardinality(answer.getSize());

//    if (answer.getSize() == 0){
//        answer.setDimensionality(0);
//    }

//    return answer;
//}

//IMPL_TEMPL
//template<class DistanceFunction>
//Dataset<DType> Dataset<DType>::kNN(const DType &qElement, const uint_fast32_t k, DistanceFunction df) const{

//    Dataset<DType> answer;

//    answer.reserve(k);
//    answer.setCardinality(k);
//    answer.setDimensionality(dimensionality);

//    std::vector<double> distances;
//    getDistanceVector(qElement, df, &distances);

//    for (uint_fast32_t i = 0; i < k; i++){
//        uint_fast32_t min = i;
//        for (uint_fast32_t j = i+1; j < cardinality; j++){
//            if (distances[j] < distances[min]){
//                min = j;
//            }
//        }
//        answer.push_back(operator [](min));
//        std::swap(distances[i], distances[min]);
//    }

//    return answer;
//}

//IMPL_TEMPL
//template<class DistanceFunction>
//void Dataset<DType>::getDistanceVector(DistanceFunction df, std::vector<double> *distances) const{

//    distances->reserve(cardinality/2);

//    for (uint_fast32_t i = 0; i < cardinality; i++){

//        DType fv = operator [](i);

//        for (uint_fast32_t j = i+1; j < cardinality; j++)
//            distances->push_back(df->getDistance(fv, operator [](j)));
//    }
//}

//IMPL_TEMPL
//template<class DistanceFunction>
//void Dataset<DType>::getDistanceVector(const DType &element, DistanceFunction df, std::vector<double> *distances) const{

//    distances->reserve(cardinality);

//    for (uint_fast32_t i = 0; i < cardinality; i++){
//        distances->push_back(df->getDistance(element, operator [](i)));
//    }
//}

//IMPL_TEMPL void Dataset<DType>::doubleFileToDataset(Dataset<DType> *dataset,
//                                                    const std::string &fileLocation,
//                                                    const uint_fast32_t cardinality,
//                                                    const  uint_fast32_t dimensionality){


//    std::ifstream file;
//    file.open(fileLocation);

//    dataset->setCardinality(cardinality);
//    dataset->setDimensionality(dimensionality);

//    double readin;

//    if (file.is_open()){
//        for (uint_fast32_t x = 0; x < cardinality; x++){
//            BasicArrayObject<double> aux;
//            aux.setOID(x);
//            for (uint_fast32_t y = 0; y < dimensionality; y++){
//                file >> readin;
//                aux.set(readin);
//            }
//            dataset->push_back(aux);
//        }
//    } else {
//        std::cout << "File not found." << std::endl;
//    }

//    file.close();

//}

//IMPL_TEMPL
//template<class DistanceFunction>
//double Dataset<DType>::medianDistance(const DType &pivot, DistanceFunction df){

//    std::vector<double> distances;
//    getDistanceVector(pivot, df, &distances);

//    const uint_fast32_t size = distances.size();

//    if ((size % 2) == 0){

//        std::nth_element(distances.begin(), distances.begin()+(size/2)-1, distances.end());
//        double firstValue = distances[(size/2)-1];

//        std::nth_element(distances.begin(), distances.begin()+(size/2), distances.end());
//        double secondValue = distances[(size/2)];

//        return (firstValue + secondValue)/2;

//    } else {

//        std::nth_element(distances.begin(), distances.begin()+(size/2), distances.end());
//        return distances[size/2];
//    }
//}

//IMPL_TEMPL
//template <class DistanceFunction>
//double Dataset<DType>::meanDistance(const DType &pivot, DistanceFunction df){

//    std::vector<double> distances;
//    getDistanceVector(pivot, df, &distances);

//    return std::accumulate(distances.begin(), distances.end(), 0.0)/distances.size();
//}

//IMPL_TEMPL
//template<class DistanceFunction>
//void Dataset<DType>::getMax_parallel(uint_fast32_t first_iterator, uint_fast32_t last_iterator, uint_fast32_t cardinality, double *max,
//    Dataset<DType> *dataset, DistanceFunction df
//){
//    for (uint_fast32_t i = first_iterator; i < last_iterator; i++){

//        DType fv = dataset->operator[](i);

//        for (uint_fast32_t j = i+1; j < cardinality; j++){

//            double distance = df->getDistance(fv, dataset->operator[](j));

//            if (distance > *max)
//                *max = distance;
//        }
//    }
//}

//IMPL_TEMPL
//template<class DistanceFunction>
//double Dataset<DType>::getMax(Dataset<DType> &dataset, DistanceFunction df){

//    uint_fast32_t cardinality = dataset.getCardinality();

//    uint_fast32_t first_iterator = 0;
//    uint_fast32_t last_iterator = 0;

//    std::vector<std::thread *> thread_list(NUM_THREADS);
//    std::vector<double> thread_results(NUM_THREADS);

//    // Lança threads
//    for (uint_fast32_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

//        if (thread_counter == 0){
//            last_iterator = ((cardinality/NUM_THREADS)*(thread_counter+1)) - 1;
//        } else {
//            first_iterator = last_iterator+1;

//            if (thread_counter == NUM_THREADS-1)
//                last_iterator = cardinality;
//            else
//                last_iterator = (cardinality/NUM_THREADS)*(thread_counter+1);
//        }

//        double &thread_results_element = thread_results[thread_counter];

//        thread_list[thread_counter] = (
//            new std::thread(
//                [first_iterator, last_iterator, cardinality, &thread_results_element, &dataset, df]{
//                    getMax_parallel(first_iterator, last_iterator, cardinality, &thread_results_element, &dataset, df);
//                }
//                //&Dataset<DType>::getMax_parallel<DType, DistanceFunction>, first_iterator, last_iterator, cardinality, &thread_results[thread_counter], &dataset, df
//            )
//        );
//    }

//    double max = 0.0;

//    // Reune threads
//    for (uint_fast32_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

//        thread_list[thread_counter]->join();
//        delete thread_list[thread_counter];
//        thread_list[thread_counter] = nullptr;

//        if (thread_results[thread_counter] > max)
//            max = thread_results[thread_counter];
//    }

//    return max;
//}

//IMPL_TEMPL
//template<class DistanceFunction>
//void Dataset<DType>::getMax_parallel(uint_fast32_t first_iterator, uint_fast32_t last_iterator, double *max,
//    Dataset<DType> *dataset, DType *element, DistanceFunction df
//){

//    for (uint_fast32_t i = first_iterator; i < last_iterator; i++){

//        double dist = df->getDistance(dataset->operator[](i), *element);

//        if (dist > *max)
//            *max = dist;
//    }
//}

//IMPL_TEMPL
//template<class DistanceFunction>
//double Dataset<DType>::getMax(Dataset<DType> &dataset, const DType &element, DistanceFunction df){

//    uint_fast32_t cardinality = dataset.getCardinality();

//    uint_fast32_t first_iterator = 0;
//    uint_fast32_t last_iterator = 0;

//    std::vector<std::thread *> thread_list(NUM_THREADS);
//    std::vector<double> thread_results(NUM_THREADS);

//    // Lança threads
//    for (uint_fast32_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

//        if (thread_counter == 0){
//            last_iterator = ((cardinality/NUM_THREADS)*(thread_counter+1)) - 1;
//        } else {
//            first_iterator = last_iterator+1;

//            if (thread_counter == NUM_THREADS-1)
//                last_iterator = cardinality;
//            else
//                last_iterator = (cardinality/NUM_THREADS)*(thread_counter+1);
//        }

//        double &thread_results_element = thread_results[thread_counter];

//        thread_list[thread_counter] = (
//            new std::thread(
//                [first_iterator, last_iterator, &thread_results_element, &dataset, &element, df]{
//                    getMax_parallel(first_iterator, last_iterator, &thread_results_element, &dataset, &element, df);
//                }
//            )
//        );
//    }

//    double max = 0.0;

//    // Reune threads
//    for (uint_fast32_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

//        thread_list[thread_counter]->join();
//        delete thread_list[thread_counter];
//        thread_list[thread_counter] = nullptr;

//        if (thread_results[thread_counter] > max)
//            max = thread_results[thread_counter];
//    }

//    return max;
//}

//IMPL_TEMPL
//template<class DistanceFunction>
//void Dataset<DType>::getMax_parallel(uint_fast32_t first_iterator, uint_fast32_t last_iterator, double mu, double *max,
//    Dataset<DType> *dataset, DType *element, DistanceFunction df
//){

//    for (uint_fast32_t i = first_iterator; i < last_iterator; i++){

//        double dist = df->getDistance(dataset[i], *element);

//        if ((dist > *max) && (dist <= mu))
//            *max = dist;
//    }
//}

//IMPL_TEMPL
//template<class DistanceFunction>
//double Dataset<DType>::getMax(Dataset<DType> &dataset, const DType &element, double mu, DistanceFunction df){

//    uint_fast32_t cardinality = dataset.getCardinality();

//    uint_fast32_t first_iterator = 0;
//    uint_fast32_t last_iterator = 0;

//    std::vector<std::thread *> thread_list(NUM_THREADS);
//    std::vector<double> thread_results(NUM_THREADS);

//    // Lança threads
//    for (uint_fast32_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

//        if (thread_counter == 0){
//            last_iterator = ((cardinality/NUM_THREADS)*(thread_counter+1)) - 1;
//        } else {
//            first_iterator = last_iterator+1;

//            if (thread_counter == NUM_THREADS-1)
//                last_iterator = cardinality;
//            else
//                last_iterator = (cardinality/NUM_THREADS)*(thread_counter+1);
//        }

//        double &thread_results_element = thread_results[thread_counter];

//        thread_list[thread_counter] = (
//            new std::thread(
//                [first_iterator, last_iterator, mu, &thread_results_element, &dataset, &element, df]{
//                    getMax_parallel(first_iterator, last_iterator, mu, &thread_results_element, &dataset, &element, df);
//                }
//            )
//        );
//    }

//    double max = 0.0;

//    // Reune threads
//    for (uint_fast32_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

//        thread_list[thread_counter]->join();
//        delete thread_list[thread_counter];
//        thread_list[thread_counter] = nullptr;

//        if (thread_results[thread_counter] > max)
//            max = thread_results[thread_counter];
//    }

//    return max;
//}

//IMPL_TEMPL
//template<class DistanceFunction>
//double Dataset<DType>::getMaxUsingHullFoci(DistanceFunction df){

//    // At least 3 elements are needed to calculate the Hull Foci, randomly pick element [0]
//    if (cardinality < 3)
//        return 0;

//    // Randomly choose an object s_i e S
//    srand(time(nullptr));
//    DType &pivot = dataset[rand()% (cardinality)];

//    double maxDist = 0.0;

//    DType f_1;

//    for (uint_fast32_t i = 0; i < cardinality; i++){

//        DType &element = dataset[i];

//        double dist = df->getDistance(pivot, element);

//        if (dist > maxDist){
//            maxDist = dist;
//            f_1 = element;
//        }
//     }

//    DType f_2;

//    maxDist = 0.0;

//    for (uint_fast32_t i = 0; i < cardinality; i++){

//        DType &element = dataset[i];

//        double dist = df->getDistance(f_1, element);

//        if (dist > maxDist){
//            maxDist = dist;
//            f_2 = element;
//        }
//     }

//    return df->getDistance(f_1,f_2);
//}

//IMPL_TEMPL void Dataset<DType>::push_back(const DType &fv){
//    dataset.push_back(fv);
//    size++;

//    if (size > cardinality){
//        ++cardinality;
//    }
//}

//IMPL_TEMPL void Dataset<DType>::insert(uint_fast32_t pos, const DType &fv){
//    dataset.insert(dataset.begin() + pos, fv);
//}

//IMPL_TEMPL DType &Dataset<DType>::getFeatureVector(const uint_fast32_t pos){ return dataset[pos]; }
//IMPL_TEMPL const DType &Dataset<DType>::getFeatureVector(const uint_fast32_t pos) const { return dataset[pos]; }

//IMPL_TEMPL DType &Dataset<DType>::operator[](const uint_fast32_t idx) { return dataset[idx]; }
//IMPL_TEMPL const DType &Dataset<DType>::operator[](const uint_fast32_t idx) const { return dataset[idx]; }

//IMPL_TEMPL void Dataset<DType>::setCardinality(const uint_fast32_t paramCardinality) { cardinality = paramCardinality; }
//IMPL_TEMPL uint_fast32_t Dataset<DType>::getCardinality() const{ return cardinality; }

//IMPL_TEMPL void Dataset<DType>::setDimensionality(const uint_fast32_t paramDimensionality){ dimensionality = paramDimensionality;}
//IMPL_TEMPL uint_fast32_t Dataset<DType>::getDimensionality() const{ return dimensionality; }

//IMPL_TEMPL void Dataset<DType>::setSize(const uint_fast32_t paramSize){ size = paramSize; }
//IMPL_TEMPL uint_fast32_t Dataset<DType>::getSize() const{ return size; }

//IMPL_TEMPL void Dataset<DType>::reserve(size_t n){ dataset.reserve(n); }
//IMPL_TEMPL void Dataset<DType>::resize(size_t n){ dataset.resize(n); size = n; cardinality = n;}

//IMPL_TEMPL bool Dataset<DType>::contains(const DType& fv){

//    return (std::find_if(dataset.begin(), dataset.end(), [&fv](DType &datasetFv){
//        return datasetFv.getOID() == fv.getOID();
//    }) != dataset.end());
//}

//IMPL_TEMPL void Dataset<DType>::erase(uint_fast32_t position){

//    dataset.erase(dataset.begin() + position);
//    dataset.shrink_to_fit();

//    --size;
//    --cardinality;
//}

//IMPL_TEMPL void Dataset<DType>::erase(uint_fast32_t first, uint_fast32_t last){

//    dataset.erase(dataset.begin() + first, dataset.begin() + last);
//    dataset.shrink_to_fit();

//    size = dataset.size();
//    cardinality = dataset.size();
//}

//IMPL_TEMPL void Dataset<DType>::erase(const DType &fv){

//    for (uint_fast32_t i = 0; i < dataset.size(); i++){
//        if (fv.getOID() == dataset[i].getOID()){
//            dataset.erase(dataset.begin() + i);
//            dataset.shrink_to_fit();
//            break;
//        }
//    }

//    --size;
//    --cardinality;
//}

//IMPL_TEMPL void Dataset<DType>::swap_positions(uint_fast32_t position1, uint_fast32_t position2){
//    std::iter_swap(dataset.begin() + position1, dataset.begin() + position2);
//}


//IMPL_TEMPL void Dataset<DType>::shuffle(){
//    std::random_shuffle(dataset.begin(), dataset.end());

//    for (uint_fast32_t i = 0; i < dataset.size(); i++)
//        dataset[i].setOID(i);
//}

//IMPL_TEMPL
//Dataset<DType> Dataset<DType>::subDataset(uint_fast32_t begin, uint_fast32_t end){

//    Dataset<DType> newDataset;

//    newDataset.dataset = std::vector<DType>(dataset.begin() + begin, dataset.begin() + end);
//    newDataset.setCardinality(newDataset.dataset.size());
//    newDataset.setSize(newDataset.getCardinality());
//    newDataset.setDimensionality(this->dimensionality);

//    return newDataset;
//}

//IMPL_TEMPL
//Dataset<DType> Dataset<DType>::subDataset(uint_fast32_t begin1, uint_fast32_t end1,
//                                          uint_fast32_t begin2, uint_fast32_t end2){

//    Dataset<DType> newDataset;

//    newDataset.dataset = std::vector<DType>(dataset.begin() + begin1, dataset.begin() + end1);
//    std::copy(dataset.begin() + begin2, dataset.begin() + end2, newDataset.dataset.end());
//    newDataset.setCardinality((end1 - begin1) + (end2 - begin2));
//    newDataset.setDimensionality(this->dimensionality);

//    return newDataset;
//}

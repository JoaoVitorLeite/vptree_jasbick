#pragma once

#include <Dataset/Dataset.h>
#include <thread>
#include <math.h>
#include <type_traits>

#define IMPL_TEMPL template<class ObjectType>

IMPL_TEMPL Dataset<ObjectType>::Dataset(){
}

IMPL_TEMPL Dataset<ObjectType>::Dataset(size_t new_cap){
    dataset.reserve(new_cap);
}

IMPL_TEMPL Dataset<ObjectType>::~Dataset(){}

IMPL_TEMPL
template<class DistanceFunction>
Dataset<ObjectType> Dataset<ObjectType>::rangeQuery(ObjectType &qElement, double radius, DistanceFunction df){

    Dataset<ObjectType> answer;

    answer.reserve(cardinality);
    answer.setCardinality(cardinality);
    answer.setDimensionality(dimensionality);

    for (size_t i = 0; i < cardinality; i++){

        ObjectType &element = *dataset[i];

        if (df->getDistance(qElement, element) <= radius)
            answer.push_back(element);

    }

    answer.setCardinality(answer.getSize());

    if (answer.getSize() == 0){
        answer.setDimensionality(0);
    }

    return answer;
}

IMPL_TEMPL
template<class DistanceFunction>
Dataset<ObjectType> Dataset<ObjectType>::kNN(ObjectType &qElement, size_t k, DistanceFunction df){

    Dataset<ObjectType> answer;

    answer.reserve(k);
    answer.setCardinality(k);
    answer.setDimensionality(dimensionality);

    std::vector<double> distances = getDistanceVector(qElement, df);

    for (size_t i = 0; i < k; i++){
        size_t min = i;
        for (size_t j = i+1; j < cardinality; j++){
            if (distances[j] < distances[min]){
                min = j;
            }
        }
        answer.push_back(*dataset[min]);
        std::swap(distances[i], distances[min]);
    }

    return answer;
}

IMPL_TEMPL
template<class DistanceFunction>
std::vector<double> Dataset<ObjectType>::getDistanceVector(DistanceFunction df){

    std::vector<double> distances;
    distances.reserve(cardinality * (cardinality/2));

    for (size_t i = 0; i < cardinality; i++)
        for (size_t j = i+1; j < cardinality; j++)
            distances.push_back(df->getDistance(*dataset[i], *dataset[j]));

    return distances;
}

IMPL_TEMPL
template<class DistanceFunction>
std::vector<double> Dataset<ObjectType>::getDistanceVector(ObjectType &element, DistanceFunction df){

    if (cardinality < DONT_PARALLELIZE_THRESHOLD){
        std::vector<double> distances;
        distances.reserve(cardinality);

        for (size_t i = 0; i < cardinality; i++)
            distances.push_back(df->getDistance(element, *dataset[i]));

        return distances;
    }

    std::vector<ObjectType *> *dataset = &(this->dataset);

    size_t first_iterator = 0;
    size_t last_iterator = 0;

    std::vector<std::thread *> thread_list(NUM_THREADS);
    std::vector<std::vector<double>> thread_results(NUM_THREADS);

    for (size_t i = 0; i < NUM_THREADS; i++)
        thread_results[i].reserve(cardinality/NUM_THREADS);

    // Lança threads
    for (size_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

        if (thread_counter == 0){
            last_iterator = ((cardinality/NUM_THREADS)*(thread_counter+1)) - 1;
        } else {
            first_iterator = last_iterator+1;

            if (thread_counter == NUM_THREADS-1)
                last_iterator = cardinality-1;
            else
                last_iterator = (cardinality/NUM_THREADS)*(thread_counter+1);
        }

        std::vector<double> *thread_results_element = &thread_results[thread_counter];

        thread_list[thread_counter] = (
            new std::thread(
                [first_iterator, last_iterator, thread_results_element, &element, dataset, df]{
                    for (size_t i = first_iterator; i <= last_iterator; i++)
                        thread_results_element->push_back(df->getDistance(element, *(dataset->operator[](i))));
                }
            )
        );
    }

    std::vector<double> distances;
    distances.reserve(cardinality);

    // Reune threads
    for (size_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

        thread_list[thread_counter]->join();
        delete thread_list[thread_counter];
        thread_list[thread_counter] = nullptr;

        distances.insert(distances.end(), thread_results[thread_counter].begin(), thread_results[thread_counter].end());
    }

    return distances;
}

IMPL_TEMPL
template<class DistanceFunction>
void Dataset<ObjectType>::getDistanceVector(ObjectType &element, std::vector<double> *distances, DistanceFunction df){

    if (cardinality < DONT_PARALLELIZE_THRESHOLD){
        distances->reserve(cardinality);

        for (size_t i = 0; i < cardinality; i++)
            distances->push_back(df->getDistance(element, *dataset[i]));

        return;
    }

    std::vector<ObjectType *> *dataset = &(this->dataset);

    size_t first_iterator = 0;
    size_t last_iterator = 0;

    std::vector<std::thread *> thread_list(NUM_THREADS);
    std::vector<std::vector<double>> thread_results(NUM_THREADS);

    for (size_t i = 0; i < NUM_THREADS; i++)
        thread_results[i].reserve(cardinality/NUM_THREADS);

    // Lança threads
    for (size_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

        if (thread_counter == 0){
            last_iterator = ((cardinality/NUM_THREADS)*(thread_counter+1)) - 1;
        } else {
            first_iterator = last_iterator+1;

            if (thread_counter == NUM_THREADS-1)
                last_iterator = cardinality-1;
            else
                last_iterator = (cardinality/NUM_THREADS)*(thread_counter+1);
        }

        std::vector<double> *thread_results_element = &thread_results[thread_counter];

        thread_list[thread_counter] = (
            new std::thread(
                [first_iterator, last_iterator, thread_results_element, &element, dataset, df]{
                    for (size_t i = first_iterator; i <= last_iterator; i++)
                        thread_results_element->push_back(df->getDistance(element, *(dataset->operator[](i))));
                }
            )
        );
    }

    distances->reserve(cardinality);

    // Reune threads
    for (size_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

        thread_list[thread_counter]->join();
        delete thread_list[thread_counter];
        thread_list[thread_counter] = nullptr;

        distances->insert(distances->end(), thread_results[thread_counter].begin(), thread_results[thread_counter].end());
    }

}

IMPL_TEMPL void Dataset<ObjectType>::loadFromFile(std::string fileLocation,
    size_t cardinality, size_t dimensionality){

    dataset.reserve(cardinality);

    this->cardinality = cardinality;
    this->size = cardinality;
    this->dimensionality = dimensionality;

    std::ifstream file;
    file.open(fileLocation);

    double readin;

    if (file.is_open()){
        for (size_t x = 0; x < cardinality; x++){
            BasicArrayObject<double> *aux = new BasicArrayObject<double>();
            aux->setOID(x);
            for (size_t y = 0; y < dimensionality; y++){
                file >> readin;
                aux->set(readin);
            }
            dataset.push_back(aux);
        }
    } else {
        std::cout << "File not found." << std::endl;
    }

    file.close();
}

IMPL_TEMPL
template <class DistanceFunction>
double Dataset<ObjectType>::meanDistance(ObjectType &pivot, DistanceFunction df){

    std::vector<double> distances = getDistanceVector(pivot, df);

    return std::accumulate(distances.begin(), distances.end(), 0.0)/distances.size();
}

IMPL_TEMPL
template<class DistanceFunction>
void Dataset<ObjectType>::getMax_parallel(size_t first_iterator, size_t last_iterator, size_t cardinality,
    double *max, Dataset<ObjectType> *dataset, DistanceFunction df){

    for (size_t i = first_iterator; i <= last_iterator; i++){

        for (size_t j = i+1; j < cardinality; j++){

            double distance = df->getDistance(dataset->operator[](i), dataset->operator[](j));

            if (distance > *max)
                *max = distance;
        }
    }
}

IMPL_TEMPL
template<class DistanceFunction>
double Dataset<ObjectType>::getMax(Dataset<ObjectType> &dataset, DistanceFunction df){

    size_t cardinality = dataset.getCardinality();

    size_t first_iterator = 0;
    size_t last_iterator = 0;

    std::vector<std::thread *> thread_list(NUM_THREADS);
    std::vector<double> thread_results(NUM_THREADS);

    // Lança threads
    for (size_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

        if (thread_counter == 0){
            last_iterator = ((cardinality/NUM_THREADS)*(thread_counter+1)) - 1;
        } else {
            first_iterator = last_iterator+1;

            if (thread_counter == NUM_THREADS-1)
                last_iterator = cardinality-1;
            else
                last_iterator = (cardinality/NUM_THREADS)*(thread_counter+1);
        }

        double &thread_results_element = thread_results[thread_counter];

        thread_list[thread_counter] = (
            new std::thread(
                [first_iterator, last_iterator, cardinality, &thread_results_element, &dataset, df]{
                    getMax_parallel(first_iterator, last_iterator, cardinality,
                        &thread_results_element, &dataset, df);
                }
            )
        );
    }

    double max = 0.0;

    // Reune threads
    for (size_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

        thread_list[thread_counter]->join();
        delete thread_list[thread_counter];
        thread_list[thread_counter] = nullptr;

        if (thread_results[thread_counter] > max)
            max = thread_results[thread_counter];
    }

    return max;
}

IMPL_TEMPL
template<class DistanceFunction>
void Dataset<ObjectType>::getMax_parallel(size_t first_iterator, size_t last_iterator, double *max,
    Dataset<ObjectType> *dataset, ObjectType *element, DistanceFunction df){

    for (size_t i = first_iterator; i <= last_iterator; i++){

        double dist = df->getDistance(*dataset->operator[](i), *element);

        if (dist > *max)
            *max = dist;
    }
}

IMPL_TEMPL
template<class DistanceFunction>
double Dataset<ObjectType>::getMax(Dataset<ObjectType> &dataset, ObjectType &element, DistanceFunction df){

    size_t cardinality = dataset.getCardinality();

    size_t first_iterator = 0;
    size_t last_iterator = 0;

    std::vector<std::thread *> thread_list(NUM_THREADS);
    std::vector<double> thread_results(NUM_THREADS);

    // Lança threads
    for (size_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

        if (thread_counter == 0){
            last_iterator = ((cardinality/NUM_THREADS)*(thread_counter+1)) - 1;
        } else {
            first_iterator = last_iterator+1;

            if (thread_counter == NUM_THREADS-1)
                last_iterator = cardinality-1;
            else
                last_iterator = (cardinality/NUM_THREADS)*(thread_counter+1);
        }

        double &thread_results_element = thread_results[thread_counter];

        thread_list[thread_counter] = (
            new std::thread(
                [first_iterator, last_iterator, &thread_results_element, &dataset, &element, df]{
                    getMax_parallel(first_iterator, last_iterator, &thread_results_element,
                        &dataset, &element, df);
                }
            )
        );
    }

    double max = 0.0;

    // Reune threads
    for (size_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

        thread_list[thread_counter]->join();
        delete thread_list[thread_counter];
        thread_list[thread_counter] = nullptr;

        if (thread_results[thread_counter] > max)
            max = thread_results[thread_counter];
    }

    return max;
}

IMPL_TEMPL
template<class DistanceFunction>
void Dataset<ObjectType>::getMax_parallel(size_t first_iterator, size_t last_iterator, double mu, double *max,
    Dataset<ObjectType> *dataset, ObjectType *element, DistanceFunction df){

    for (size_t i = first_iterator; i <= last_iterator; i++){

        double dist = df->getDistance(*dataset->operator[](i), *element);

        if ((dist > *max) && (dist <= mu))
            *max = dist;
    }
}

IMPL_TEMPL
template<class DistanceFunction>
double Dataset<ObjectType>::getMax(Dataset<ObjectType> &dataset, ObjectType &element, double mu, DistanceFunction df){

    size_t cardinality = dataset.getCardinality();

    size_t first_iterator = 0;
    size_t last_iterator = 0;

    std::vector<std::thread *> thread_list(NUM_THREADS);
    std::vector<double> thread_results(NUM_THREADS);

    // Lança threads
    for (size_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

        if (thread_counter == 0){
            last_iterator = ((cardinality/NUM_THREADS)*(thread_counter+1)) - 1;
        } else {
            first_iterator = last_iterator+1;

            if (thread_counter == NUM_THREADS-1)
                last_iterator = cardinality-1;
            else
                last_iterator = (cardinality/NUM_THREADS)*(thread_counter+1);
        }

        double &thread_results_element = thread_results[thread_counter];

        thread_list[thread_counter] = (
            new std::thread(
                [first_iterator, last_iterator, mu, &thread_results_element, &dataset, &element, df]{
                    getMax_parallel(first_iterator, last_iterator, mu, &thread_results_element,
                        &dataset, &element, df);
                }
            )
        );
    }

    double max = 0.0;

    // Reune threads
    for (size_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

        thread_list[thread_counter]->join();
        delete thread_list[thread_counter];
        thread_list[thread_counter] = nullptr;

        if (thread_results[thread_counter] > max)
            max = thread_results[thread_counter];
    }

    return max;
}

IMPL_TEMPL
template <class DistanceFunction>
void Dataset<ObjectType>::farthest_element(size_t first_iterator, size_t last_iterator,
    std::vector<ObjectType *> *dataset, ObjectType *pivot, ObjectType **farthest, DistanceFunction df){

    double maxDist = 0.0;

    for (size_t i = first_iterator; i <= last_iterator; i++){

        double dist = df->getDistance(*pivot, *(dataset->operator[](i)));

        if (dist > maxDist){
            maxDist = dist;
            *farthest = dataset->operator[](i);
        }
     }
}

IMPL_TEMPL
template<class DistanceFunction>
double Dataset<ObjectType>::getMaxUsingHullFoci(DistanceFunction df){

    std::vector<ObjectType *> *dataset = &(this->dataset);

    // At least 3 elements are needed to calculate the Hull Foci, randomly pick element [0]
    if (cardinality < 3)
        return 0;

    // Randomly choose an object s_i e S
    ObjectType *pivot = dataset->operator[](static_cast<size_t>(rand()) % (cardinality-1));

    ObjectType *f_1;

    size_t first_iterator = 0;
    size_t last_iterator = 0;

    std::vector<std::thread *> thread_list(NUM_THREADS);
    std::vector<ObjectType *> thread_results(NUM_THREADS);

    // Lança threads
    for (size_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

        if (thread_counter == 0){
            last_iterator = ((cardinality/NUM_THREADS)*(thread_counter+1)) - 1;
        } else {
            first_iterator = last_iterator+1;

            if (thread_counter == NUM_THREADS-1)
                last_iterator = cardinality-1;
            else
                last_iterator = (cardinality/NUM_THREADS)*(thread_counter+1);
        }

        ObjectType **farthest_reference = &thread_results[thread_counter];

        thread_list[thread_counter] = (
            new std::thread(
                [this, first_iterator, last_iterator, dataset, pivot, farthest_reference, df] {
                    farthest_element(first_iterator, last_iterator, dataset, pivot, farthest_reference, df);
                }
            )
        );
    }

    double max = 0.0;

    // Reune threads
    for (size_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

        thread_list[thread_counter]->join();
        delete thread_list[thread_counter];
        thread_list[thread_counter] = nullptr;

        double dist = df->getDistance(*pivot, *thread_results[thread_counter]);

        if (dist > max){
            max = dist;
            f_1 = thread_results[thread_counter];
        }
    }

    thread_list.clear();
    thread_results.clear();

    ObjectType *f_2;

    first_iterator = 0;
    last_iterator = 0;

    // Lança threads
    for (size_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

        if (thread_counter == 0){
            last_iterator = ((cardinality/NUM_THREADS)*(thread_counter+1)) - 1;
        } else {
            first_iterator = last_iterator+1;

            if (thread_counter == NUM_THREADS-1)
                last_iterator = cardinality-1;
            else
                last_iterator = (cardinality/NUM_THREADS)*(thread_counter+1);
        }

        ObjectType **farthest_reference = &thread_results[thread_counter];

        thread_list[thread_counter] = (
            new std::thread(
                [this, first_iterator, last_iterator, dataset, f_1, farthest_reference, df] {
                    farthest_element(first_iterator, last_iterator, dataset, f_1, farthest_reference, df);
                }
            )
        );
    }

    max = 0.0;

    // Reune threads
    for (size_t thread_counter = 0; thread_counter < NUM_THREADS; thread_counter++){

        thread_list[thread_counter]->join();
        delete thread_list[thread_counter];
        thread_list[thread_counter] = nullptr;

        double dist = df->getDistance(*f_1, *thread_results[thread_counter]);

        if (dist > max){
            max = dist;
            f_2 = thread_results[thread_counter];
        }
    }

    return df->getDistance(*f_1,*f_2);
}

IMPL_TEMPL void Dataset<ObjectType>::push_back(ObjectType &fv){
    dataset.push_back(&fv);
    ++size;

    if (size > cardinality){
        ++cardinality;
    }
}

IMPL_TEMPL void Dataset<ObjectType>::insert(size_t pos, ObjectType &fv){
    dataset.insert(dataset.begin() + pos, fv);
}

IMPL_TEMPL
template<typename T>
void Dataset<ObjectType>::insert(size_t pos, T begin_iterator, T end_iterator){
    dataset.insert(dataset.begin() + pos, begin_iterator, end_iterator);
}

IMPL_TEMPL ObjectType &Dataset<ObjectType>::getFeatureVector(size_t pos) { return *dataset[pos]; }

IMPL_TEMPL ObjectType &Dataset<ObjectType>::operator [](size_t idx) { return *dataset[idx]; }

IMPL_TEMPL void Dataset<ObjectType>::setCardinality(size_t paramCardinality) { cardinality = paramCardinality; }
IMPL_TEMPL size_t Dataset<ObjectType>::getCardinality(){ return cardinality; }

IMPL_TEMPL void Dataset<ObjectType>::setDimensionality(size_t paramDimensionality){ dimensionality = paramDimensionality;}
IMPL_TEMPL size_t Dataset<ObjectType>::getDimensionality(){ return dimensionality; }

IMPL_TEMPL void Dataset<ObjectType>::setSize(size_t paramSize){ size = paramSize; }
IMPL_TEMPL size_t Dataset<ObjectType>::getSize(){ return size; }

IMPL_TEMPL void Dataset<ObjectType>::reserve(size_t n){ dataset.reserve(n); }
IMPL_TEMPL void Dataset<ObjectType>::resize(size_t n){ dataset.resize(n); size = n; cardinality = n;}

IMPL_TEMPL bool Dataset<ObjectType>::contains(ObjectType *fv){

    return (
        std::find_if(dataset.begin(), dataset.end(), [fv](ObjectType *datasetFv){
            return datasetFv->getOID() == fv->getOID();
        }) != dataset.end()
    );
}

IMPL_TEMPL void Dataset<ObjectType>::erase(size_t position){

    dataset.erase(dataset.begin() + position);
    dataset.shrink_to_fit();

    --size;
    --cardinality;
}

IMPL_TEMPL void Dataset<ObjectType>::erase(size_t first, size_t last){

    dataset.erase(dataset.begin() + first, dataset.begin() + last);
    dataset.shrink_to_fit();

    size = dataset.size();
    cardinality = dataset.size();
}

IMPL_TEMPL void Dataset<ObjectType>::erase(ObjectType &fv){

    for (size_t i = 0; i < dataset.size(); i++){
        if (fv.getOID() == dataset[i]->getOID()){
            dataset.erase(dataset.begin() + i);
            dataset.shrink_to_fit();
            break;
        }
    }

    --size;
    --cardinality;
}

IMPL_TEMPL void Dataset<ObjectType>::swap_positions(size_t position1, size_t position2){
    std::iter_swap(dataset.begin() + position1, dataset.begin() + position2);
}


IMPL_TEMPL void Dataset<ObjectType>::shuffle(){
    std::random_shuffle(dataset.begin(), dataset.end());

//    size_t size = dataset.size();

//    for (size_t i = 0; i < size; i++)
//        dataset[i]->setOID(i);
}

IMPL_TEMPL void Dataset<ObjectType>::hide_element(ObjectType *fv){
    // Removes from vector without deleting it from memory.
    std::remove(dataset.begin(), dataset.end(), fv);

    dataset.shrink_to_fit();

    size = cardinality = dataset.size();
}

IMPL_TEMPL
Dataset<ObjectType> Dataset<ObjectType>::subDataset(size_t begin, size_t end){

    Dataset<ObjectType> newDataset;

    newDataset.dataset = std::vector<ObjectType *>(dataset.begin() + begin, dataset.begin() + end);
    newDataset.setCardinality(newDataset.dataset.size());
    newDataset.setSize(newDataset.getCardinality());
    newDataset.setDimensionality(this->dimensionality);

    return newDataset;
}

IMPL_TEMPL
Dataset<ObjectType> Dataset<ObjectType>::subDataset(size_t begin1, size_t end1,
    size_t begin2, size_t end2){

    Dataset<ObjectType> newDataset;

    newDataset.dataset = std::vector<ObjectType *>(dataset.begin() + begin1, dataset.begin() + end1);
    std::copy(dataset.begin() + begin2, dataset.begin() + end2, newDataset.dataset.end());
    newDataset.setCardinality((end1 - begin1) + (end2 - begin2));
    newDataset.setDimensionality(this->dimensionality);

    return newDataset;
}

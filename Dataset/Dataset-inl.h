#pragma once

#include <Dataset/Dataset.h>

#define IMPL_TEMPL template<class DType>

IMPL_TEMPL Dataset<DType>::Dataset(){
}

IMPL_TEMPL Dataset<DType>::Dataset(size_t new_cap){
    dataset.reserve(new_cap);
}

IMPL_TEMPL
template<class DistanceFunction>
Dataset<DType> Dataset<DType>::rangeQuery(const DType &qElement, const double radius, DistanceFunction df) const{

    Dataset<DType> answer;
    answer.reserve(cardinality);
    answer.setCardinality(cardinality);
    answer.setDimensionality(dimensionality);

    for (uint_fast32_t i = 0; i < cardinality; i++){

        DType fv = operator [](i);

        double dist = df->getDistance(qElement, fv);

        if (dist <= radius)
            answer.push_back(fv);

    }

    answer.setCardinality(answer.getSize());

    if (answer.getSize() == 0){
        answer.setDimensionality(0);
    }

    return answer;
}

IMPL_TEMPL
template<class DistanceFunction>
Dataset<DType> Dataset<DType>::kNN(const DType &qElement, const uint_fast32_t k, DistanceFunction df) const{

    Dataset<DType> answer;

    answer.reserve(k);
    answer.setCardinality(k);
    answer.setDimensionality(dimensionality);

    std::vector<double> distances;
    getDistanceVector(qElement, df, &distances);

    for (uint_fast32_t i = 0; i < k; i++){
        uint_fast32_t min = i;
        for (uint_fast32_t j = i+1; j < cardinality; j++){
            if (distances[j] < distances[min]){
                min = j;
            }
        }
        answer.push_back(operator [](min));
        std::swap(distances[i], distances[min]);
    }

    return answer;
}

IMPL_TEMPL
template<class DistanceFunction>
void Dataset<DType>::getDistanceVector(DistanceFunction df, std::vector<double> *distances) const{

    distances->reserve(cardinality/2);

    for (uint_fast32_t i = 0; i < cardinality; i++){

        DType fv = operator [](i);

        for (uint_fast32_t j = i+1; j < cardinality; j++)
            distances->push_back(df->getDistance(fv, operator [](j)));
    }
}

IMPL_TEMPL
template<class DistanceFunction>
void Dataset<DType>::getDistanceVector(const DType &element, DistanceFunction df, std::vector<double> *distances) const{

    distances->reserve(cardinality);

    for (uint_fast32_t i = 0; i < cardinality; i++){
        distances->push_back(df->getDistance(element, operator [](i)));
    }
}

IMPL_TEMPL void Dataset<DType>::doubleFileToDataset(Dataset<DType> *dataset,
                                                    const std::string &fileLocation,
                                                    const uint_fast32_t cardinality,
                                                    const  uint_fast32_t dimensionality){

    std::ifstream file;
    file.open(fileLocation);

    dataset->setCardinality(cardinality);
    dataset->setDimensionality(dimensionality);

    double readin;

    if (file.is_open()){
        for (uint_fast32_t x = 0; x < cardinality; x++){
            BasicArrayObject<double> aux;
            aux.setOID(x);
            for (uint_fast32_t y = 0; y < dimensionality; y++){
                file >> readin;
                aux.set(readin);
            }
            dataset->push_back(aux);
        }
    } else {
        std::cout << "File not found." << std::endl;
    }

    file.close();
}

IMPL_TEMPL void Dataset<DType>::textFileToDataset(Dataset<DType> *dataset,
                                                  const std::string &fileLocation,
                                                  const uint_fast32_t cardinality,
                                                  const  uint_fast32_t dimensionality){

    std::ifstream file;
    file.open(fileLocation);

    dataset->setCardinality(cardinality);
    dataset->setDimensionality(dimensionality);

    if (file.is_open()){
        for (uint_fast32_t x = 0; x < cardinality; x++){

            BasicArrayObject<std::vector<char>> aux;
            aux.setOID(x);

            for (uint_fast32_t y = 0; y < dimensionality; y++){

                std::string s;
                file >> s;

                std::vector<char> charVec;

                for (uint_fast32_t k = 0; k < s.length(); k++){
                    charVec.push_back(s.at(k));
                }

                aux.set(charVec);

            }
            dataset->push_back(aux);
        }
    } else {
        std::cout << "File not found." << std::endl;
    }

    file.close();
}

IMPL_TEMPL
template<class DistanceFunction>
double Dataset<DType>::medianDistance(const DType &pivot, DistanceFunction df){

    std::vector<double> distances;
    getDistanceVector(pivot, df, &distances);

    const uint_fast32_t size = distances.size();

    if ((size % 2) == 0){

        std::nth_element(distances.begin(), distances.begin()+(size/2)-1, distances.end());
        double firstValue = distances[(size/2)-1];

        std::nth_element(distances.begin(), distances.begin()+(size/2), distances.end());
        double secondValue = distances[(size/2)];

        return (firstValue + secondValue)/2;

    } else {

        std::nth_element(distances.begin(), distances.begin()+(size/2), distances.end());
        return distances[size/2];
    }
}

IMPL_TEMPL
template <class DistanceFunction>
double Dataset<DType>::meanDistance(const DType &pivot, DistanceFunction df){

    std::vector<double> distances;
    getDistanceVector(pivot, df, &distances);

    return std::accumulate(distances.begin(), distances.end(), 0.0)/distances.size();
}

IMPL_TEMPL
template<class DistanceFunction>
double Dataset<DType>::getMax(const Dataset<DType> &dataset, DistanceFunction df){

    std::vector<double> distances;
    dataset.getDistanceVector(df, &distances);

    return *std::max_element(distances.begin(), distances.end());
}

IMPL_TEMPL
template<class DistanceFunction>
double Dataset<DType>::getMax(const Dataset<DType> &dataset, const DType &element, DistanceFunction df){

    double max = 0.0;
    for (uint_fast32_t i = 0; i < dataset.getCardinality(); i++){

        double dist = df->getDistance(dataset[i], element);

        if (dist > max)
            max = dist;
    }

    return max;
}

IMPL_TEMPL
template<class DistanceFunction>
double Dataset<DType>::getMax(const Dataset<DType> &dataset, const DType &element, double mu, DistanceFunction df){

    double max = 0.0;
    for (uint_fast32_t i = 0; i < dataset.getCardinality(); i++){

        double dist = df->getDistance(dataset[i], element);

        if ((dist > max) && (dist <= mu))
            max = dist;
    }

    return max;
}

IMPL_TEMPL void Dataset<DType>::push_back(const DType &fv){
    dataset.push_back(fv);
    size++;

    if (size > cardinality){
        ++cardinality;
    }
}

IMPL_TEMPL void Dataset<DType>::insert(uint_fast32_t pos, const DType &fv){
    dataset.insert(dataset.begin() + pos, fv);
}

IMPL_TEMPL DType &Dataset<DType>::getFeatureVector(const uint_fast32_t pos){ return dataset[pos]; }
IMPL_TEMPL const DType &Dataset<DType>::getFeatureVector(const uint_fast32_t pos) const { return dataset[pos]; }

IMPL_TEMPL DType &Dataset<DType>::operator[](const uint_fast32_t idx) { return dataset[idx]; }
IMPL_TEMPL const DType &Dataset<DType>::operator[](const uint_fast32_t idx) const { return dataset[idx]; }

IMPL_TEMPL void Dataset<DType>::setCardinality(const uint_fast32_t paramCardinality) { cardinality = paramCardinality; }
IMPL_TEMPL uint_fast32_t Dataset<DType>::getCardinality() const{ return cardinality; }

IMPL_TEMPL void Dataset<DType>::setDimensionality(const uint_fast32_t paramDimensionality){ dimensionality = paramDimensionality;}
IMPL_TEMPL uint_fast32_t Dataset<DType>::getDimensionality() const{ return dimensionality; }

IMPL_TEMPL void Dataset<DType>::setSize(const uint_fast32_t paramSize){ size = paramSize; }
IMPL_TEMPL uint_fast32_t Dataset<DType>::getSize() const{ return size; }

IMPL_TEMPL void Dataset<DType>::reserve(size_t n){ dataset.reserve(n); }
IMPL_TEMPL void Dataset<DType>::resize(size_t n){ dataset.resize(n); size = n; cardinality = n;}

IMPL_TEMPL bool Dataset<DType>::contains(const DType& fv){

    return (std::find_if(dataset.begin(), dataset.end(), [&fv](DType &datasetFv){
        return datasetFv.getOID() == fv.getOID();
    }) != dataset.end());
}

IMPL_TEMPL void Dataset<DType>::erase(uint_fast32_t position){

    dataset.erase(dataset.begin() + position);
    dataset.shrink_to_fit();

    --size;
    --cardinality;
}

IMPL_TEMPL void Dataset<DType>::erase(const DType &fv){

    for (uint_fast32_t i = 0; i < dataset.size(); i++){
        if (fv.getOID() == dataset[i].getOID()){
            dataset.erase(dataset.begin() + i);
            dataset.shrink_to_fit();
            break;
        }
    }

    --size;
    --cardinality;
}

IMPL_TEMPL void Dataset<DType>::swap_positions(uint_fast32_t position1, uint_fast32_t position2){
    std::iter_swap(dataset.begin() + position1, dataset.begin() + position2);
}

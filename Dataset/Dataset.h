#pragma once

#include <Dataset/BasicArrayObject.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <vector>

template <class DType>
class Dataset{
    private:
        std::vector<DType> dataset;
        uint_fast32_t cardinality = 0;
        uint_fast32_t dimensionality = 0;
        uint_fast32_t size = 0;

    public:
        Dataset();
        Dataset(size_t new_cap);
        ~Dataset(){}

        template <class DistanceFunction>
        Dataset<DType> rangeQuery(const DType &qElement, const double radius, DistanceFunction df) const;

        template <class DistanceFunction>
        Dataset<DType> kNN(const DType &qElement, const uint_fast32_t k, DistanceFunction df) const;

        template<class DistanceFunction>
        void getDistanceVector(DistanceFunction df, std::vector<double> *distances) const;

        template<class DistanceFunction>
        void getDistanceVector(const DType &element, DistanceFunction df, std::vector<double> *distances) const;

        template <class DistanceFunction>
        double medianDistance(const DType &pivot, DistanceFunction df);

        template <class DistanceFunction>
        double meanDistance(const DType &pivot, DistanceFunction df);

        static void doubleFileToDataset(Dataset<DType> *dataset,
                                        const std::string &fileLocation,
                                        const uint_fast32_t cardinality,
                                        const  uint_fast32_t dimensionality);

        static void textFileToDataset(Dataset<DType> *dataset,
                                      const std::string &fileLocation,
                                      const uint_fast32_t cardinality,
                                      const  uint_fast32_t dimensionality);

        template <class DistanceFunction>
        static double getMax(const Dataset<DType> &dataset, DistanceFunction df);

        template <class DistanceFunction>
        static double getMax(const Dataset<DType> &dataset, const DType &element, DistanceFunction df);

        template <class DistanceFunction>
        static double getMax(const Dataset<DType> &dataset, const DType &element, double mu, DistanceFunction df);

        void setCardinality(const uint_fast32_t paramCardinality);
        uint_fast32_t getCardinality() const;

        void setDimensionality(const uint_fast32_t paramDimensionality);
        uint_fast32_t getDimensionality() const;

        void setSize(const uint_fast32_t paramSize);
        uint_fast32_t getSize() const;

        DType &operator[](const uint_fast32_t idx);
        const DType &operator[](const uint_fast32_t idx) const;

        void push_back(const DType &fv);
        void insert(uint_fast32_t pos, const DType &fv);

        DType &getFeatureVector(const uint_fast32_t pos);
        const DType &getFeatureVector(const uint_fast32_t pos) const;

        bool contains(const DType &fv);

        void swap_positions(uint_fast32_t position1, uint_fast32_t position2);

        void erase(uint_fast32_t position);
        void erase(const DType &fv);

        void reserve(size_t n);
        void resize(size_t n);

};

typedef BasicArrayObject<double> InstanceDouble;
typedef BasicArrayObject<std::vector<char> > InstanceString;
typedef Dataset<InstanceDouble> DatasetDouble;
typedef Dataset<InstanceString> DatasetString;

#include <Dataset/Dataset-inl.h>

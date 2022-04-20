#pragma once

#include <Dataset/BasicArrayObject.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <vector>

#define NUM_THREADS 3
#define DONT_PARALLELIZE_THRESHOLD 2500

template <class ObjectType>
class Dataset{

    private:
        std::vector<ObjectType *> dataset;
        size_t cardinality = 0;
        size_t dimensionality = 0;
        size_t size = 0;

        template <class DistanceFunction>
        static void getMax_parallel(size_t first_iterator, size_t last_iterator, size_t cardinality,
            double *max, Dataset<ObjectType> *dataset, DistanceFunction df);

        template <class DistanceFunction>
        static void getMax_parallel(size_t first_iterator, size_t last_iterator, double *max,
            Dataset<ObjectType> *dataset, ObjectType *element, DistanceFunction df);

        template <class DistanceFunction>
        static void getMax_parallel(size_t first_iterator, size_t last_iterator, double mu, double *max,
            Dataset<ObjectType> *dataset, ObjectType *element, DistanceFunction df);

    public:
        Dataset();
        Dataset(size_t new_cap);
        ~Dataset();

        void loadFromFile(std::string fileLocation, size_t cardinality, size_t dimensionality);

        Dataset<ObjectType> subDataset(size_t begin, size_t end);
        Dataset<ObjectType> subDataset(size_t begin1, size_t end1, size_t begin2, size_t end2);

        template <class DistanceFunction>
        Dataset<ObjectType> rangeQuery(ObjectType &qElement, double radius, DistanceFunction df);

        template <class DistanceFunction>
        Dataset<ObjectType> kNN(ObjectType &qElement, size_t k, DistanceFunction df);

        template<class DistanceFunction>
        std::vector<double> getDistanceVector(DistanceFunction df);

        template<class DistanceFunction>
        std::vector<double> getDistanceVector(ObjectType &element, DistanceFunction df);

        template<class DistanceFunction>
        void getDistanceVector(ObjectType &element, std::vector<double> *distances, DistanceFunction df);

        template <class DistanceFunction>
        double meanDistance(ObjectType &pivot, DistanceFunction df);

        template <class DistanceFunction>
        static double getMax(Dataset<ObjectType> &dataset, DistanceFunction df);

        template <class DistanceFunction>
        static double getMax(Dataset<ObjectType> &dataset, ObjectType &element, DistanceFunction df);

        template <class DistanceFunction>
        static double getMax(Dataset<ObjectType> &dataset, ObjectType &element, double mu, DistanceFunction df);

        template <class DistanceFunction>
        static void farthest_element(size_t first_iterator, size_t last_iterator,
            std::vector<ObjectType *> *dataset, ObjectType *pivot, ObjectType **farthest, DistanceFunction df);

        template <class DistanceFunction>
        double getMaxUsingHullFoci(DistanceFunction df);

        void setCardinality(size_t paramCardinality);
        size_t getCardinality();

        void setDimensionality(size_t paramDimensionality);
        size_t getDimensionality();

        void setSize(size_t paramSize);
        size_t getSize();

        ObjectType &operator [](size_t idx);

        void push_back(ObjectType &fv);
        void insert(size_t pos, ObjectType &fv);

        template <typename T>
        void insert(size_t pos, T begin_iterator, T end_iterator);

        ObjectType &getFeatureVector(size_t pos);

        bool contains(ObjectType *fv);

        void swap_positions(size_t position1, size_t position2);

        void erase(size_t first, size_t last);
        void erase(size_t position);
        void erase(ObjectType &fv);

        void hide_element(ObjectType *fv);

        void reserve(size_t n);
        void resize(size_t n);

        void shuffle();

};

typedef BasicArrayObject<double> InstanceDouble;
typedef BasicArrayObject<std::vector<char> > InstanceString;
typedef Dataset<InstanceDouble> DatasetDouble;
typedef Dataset<InstanceString> DatasetString;

#include <Dataset/Dataset-inl.h>

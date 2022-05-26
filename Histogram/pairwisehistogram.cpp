#include <Histogram/PairwiseHistogram.h>

PairwiseHistogram::PairwiseHistogram(){}

PairwiseHistogram::PairwiseHistogram(const DatasetDouble &dataset,
                                     const uint_fast32_t histogram_size,
                                     DistanceFunction<InstanceDouble> *df){

    std::vector<uint_fast32_t> histogram;

    std::cout << "Be patient, this may take a while...\n";

    // Sets the histogram size.
    histogram.resize(histogram_size);

    const uint_fast32_t cardinality = dataset.getCardinality();

    // Creates an aux structure with [0, 1*max/histogram_size, 2*max/histogram_size, ..., max].
    double* aux = new double[histogram_size+1];
    this->setMax(Dataset<InstanceDouble>::getMax(dataset, df));
    double x = this->getMax()/histogram_size;
    for (uint_fast32_t i = 0; i <= histogram_size; i++){
        aux[i] = i*x;
    }

    /*
     * Calculates the distance between any two elements of
     * the dataset and mounts the histogram based on that
     * distances.
     */
    for (uint_fast32_t i = 0; i < cardinality; i++){
        for (uint_fast32_t j = i+1; j < cardinality; j++){

            const double dist = df->getDistance(dataset[i],dataset[j]);

            // Binary search to find the right position to increment.
            uint_fast32_t inf = 0;
            uint_fast32_t sup = histogram_size;
            uint_fast32_t mid = 0;

            while (inf <= sup){

                mid = inf + (sup - inf)/2;

                if (dist >= aux[mid] && dist < aux[mid+1])
                    histogram[mid]++;

                if (dist < aux[mid])
                    sup = mid-1;
                else
                    inf = mid+1;
            }
        }
    }
    delete [] aux;
    aux = nullptr;

    this->setHistogram(histogram);
}

PairwiseHistogram::PairwiseHistogram(const DatasetString &dataset,
                                     const uint_fast32_t histogram_size,
                                     DistanceFunction<InstanceString> *df){

    std::vector<uint_fast32_t> histogram;

    std::cout << "Be patient, this may take a while...\n";

    // Sets the histogram size.
    histogram.resize(histogram_size);

    const uint_fast32_t cardinality = dataset.getCardinality();

    // Creates an aux structure with [0, 1*max/histogram_size, 2*max/histogram_size, ..., max].
    double* aux = new double[histogram_size+1];
    this->setMax(Dataset<InstanceString>::getMax(dataset, df));
    double x = this->getMax()/histogram_size;
    for (uint_fast32_t i = 0; i <= histogram_size; i++){
        aux[i] = i*x;
    }

    /*
     * Calculates the distance between any two elements of
     * the dataset and mounts the histogram based on that
     * distances.
     */
    for (uint_fast32_t i = 0; i < cardinality; i++){
        for (uint_fast32_t j = i+1; j < cardinality; j++){

            const double dist = df->getDistance(dataset[i],dataset[j]);

            // Binary search to find the right position to increment.
            uint_fast32_t inf = 0;
            uint_fast32_t sup = histogram_size;
            uint_fast32_t mid = 0;

            while (inf <= sup){

                mid = inf + (sup - inf)/2;

                if (dist >= aux[mid] && dist < aux[mid+1])
                    histogram[mid]++;

                if (dist < aux[mid])
                    sup = mid-1;
                else
                    inf = mid+1;
            }
        }
    }
    delete [] aux;
    aux = nullptr;

    this->setHistogram(histogram);
}

//#include <Histogram/PivotHistogram.h>

//PivotHistogram::PivotHistogram(){}

//PivotHistogram::PivotHistogram(const DatasetDouble &dataset,
//                               const InstanceDouble &pivot,
//                               const uint_fast32_t histogram_size,
//                               DistanceFunction<InstanceDouble> *df){

//    std::vector<uint_fast32_t> histogram;

//    // Sets the histogram size.
//    histogram.resize(histogram_size);

//    const uint_fast32_t cardinality = dataset.getCardinality();

//    // Creates an aux structure with [0, 1*max/histogram_size, 2*max/histogram_size, ..., max].
//    double* aux = new double[histogram_size];
//    this->setMax(Dataset<InstanceDouble>::getMax(dataset, pivot, df));
//    double x = this->getMax()/(histogram_size-1);
//    std::vector<double> histValues;
//    for (uint_fast32_t i = 0; i < histogram_size; i++){
//        aux[i] = i*x;
//        histValues.push_back(i*x);
//    }

//    this->setHistValues(histValues);

//    /*
//     * Calculates the distance between the pivot and every other element
//     * of the dataset and mounts the histogram based on that distances.
//     */
//    for (uint_fast32_t i = 0; i < cardinality; i++){

//        double dist = df->getDistance(pivot,dataset[i]);

//        uint_fast32_t inf = 0;
//        uint_fast32_t sup = histogram_size-1;
//        uint_fast32_t mid;

//        // Binary search to find the right position to increment.
//        while (inf <= sup){

//            mid = (inf + (sup - inf)/2);

//            if (dist >= aux[mid] && dist < aux[mid+1])
//                histogram[mid]++;

//            if (dist < aux[mid])
//                sup = --mid;
//            else
//                inf = ++mid;

//        }
//    }
//    delete [] aux;
//    aux = nullptr;

//    this->setHistogram(histogram);
//}

//PivotHistogram::PivotHistogram(const DatasetString &dataset,
//                               const InstanceString &pivot,
//                               const uint_fast32_t histogram_size,
//                               DistanceFunction<InstanceString> *df){

//    std::vector<uint_fast32_t> histogram;

//    // Sets the histogram size.
//    histogram.resize(histogram_size);

//    const uint_fast32_t cardinality = dataset.getCardinality();

//    // Creates an aux structure with [0, 1*max/histogram_size, 2*max/histogram_size, ..., max].
//    double* aux = new double[histogram_size];
//    this->setMax(Dataset<InstanceString>::getMax(dataset, pivot, df));
//    double x = this->getMax()/(histogram_size-1);
//    std::vector<double> histValues;
//    for (uint_fast32_t i = 0; i < histogram_size; i++){
//        aux[i] = i*x;
//        histValues.push_back(i*x);
//    }

//    this->setHistValues(histValues);

//    /*
//     * Calculates the distance between the pivot and every other element
//     * of the dataset and mounts the histogram based on that distances.
//     */
//    for (uint_fast32_t i = 0; i < cardinality; i++){

//        double dist = df->getDistance(pivot,dataset[i]);

//        uint_fast32_t inf = 0;
//        uint_fast32_t sup = histogram_size-1;
//        uint_fast32_t mid;

//        // Binary search to find the right position to increment.
//        while (inf <= sup){

//            mid = (inf + (sup - inf)/2);

//            if (dist >= aux[mid] && dist < aux[mid+1])
//                histogram[mid]++;

//            if (dist < aux[mid])
//                sup = --mid;
//            else
//                inf = ++mid;

//        }
//    }
//    delete [] aux;
//    aux = nullptr;

//    this->setHistogram(histogram);
//}

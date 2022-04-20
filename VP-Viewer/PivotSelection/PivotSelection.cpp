#include <PivotSelection/PivotSelection.h>

//// Fisher–Yates_shuffle
//std::vector<size_t> PivotSelection::FisherYatesShuffle(size_t size, size_t max_size, std::mt19937& gen)
//{
//    assert(size < max_size);
//    std::vector<size_t> b(size);

//    for(size_t i = 0; i != max_size; ++i) {
//        std::uniform_int_distribution<> dis(0, i);
//        size_t j = dis(gen);
//        if(j < b.size()) {
//            if(i < j) {
//                b[i] = b[j];
//            }
//            b[j] = i;
//        }
//    }
//    return b;
//}

InstanceDouble &PivotSelection::randomPivots(DatasetDouble &dataset){

    if (dataset.getCardinality() > 1){
        //srand(time(nullptr));
        return dataset[static_cast<size_t>(rand()) %(dataset.getCardinality()-1)];
    } else
        return dataset[0];
}

InstanceString &PivotSelection::randomPivots(DatasetString &dataset){

    if (dataset.getCardinality() > 1){
        //srand(time(nullptr));
        return dataset[static_cast<size_t>(rand()) %(dataset.getCardinality()-1)];
    } else
        return dataset[0];
}

InstanceDouble &PivotSelection::selectVp(DatasetDouble &dataset, DistanceFunction<InstanceDouble> *df){

    size_t cardinality = dataset.getCardinality();

    if (cardinality == 1) return dataset[0];

    size_t firstSampleSize = static_cast<size_t>(std::ceil((double) (cardinality * 10)/100));
    size_t secondSampleSize = cardinality - firstSampleSize;

//    std::vector<size_t> random_numbers(cardinality);
//    std::iota(random_numbers.begin(), random_numbers.end(), 0);
//    std::random_shuffle(random_numbers.begin(), random_numbers.end());

    DatasetDouble P(firstSampleSize);
    for (size_t i = 0; i < firstSampleSize; i++)
        P.push_back(dataset[i]);

    DatasetDouble D(secondSampleSize);
    for (size_t i = firstSampleSize; i < cardinality; i++)
        D.push_back(dataset[i]);

    double bestSpread = 0.0;
    size_t bestVpPosition = 0;

    for (size_t i = 0; i < firstSampleSize; i++){

        std::vector<double> distances = D.getDistanceVector(P[i], df);
        double mu = MathFunctions::medianDistance(distances);

        double spread = 0.0;

        std::for_each(distances.begin(), distances.end(), [mu, &spread](double dist){
            spread += pow(dist-mu, 2);
        });

        if (spread > bestSpread){
            bestSpread = spread;
            bestVpPosition = i;
        }
    }

    //InstanceDouble *result = new InstanceDouble(P[bestVpPosition]);

    return P[bestVpPosition];
}

InstanceString &PivotSelection::selectVp(DatasetString &dataset, DistanceFunction<InstanceString> *df){

    size_t cardinality = dataset.getCardinality();

    if (cardinality == 1) return dataset[0];

    size_t firstSampleSize = static_cast<size_t>(std::ceil(static_cast<double>((cardinality * 10)/100)));
    size_t secondSampleSize = cardinality - firstSampleSize;

//    std::vector<size_t> random_numbers(cardinality);
//    std::iota(random_numbers.begin(), random_numbers.end(), 0);
//    std::random_shuffle(random_numbers.begin(), random_numbers.end());

    DatasetString P(firstSampleSize);
    for (size_t i = 0; i < firstSampleSize; i++)
        P.push_back(dataset[i]);

    DatasetString D(secondSampleSize);
    for (size_t i = firstSampleSize; i < cardinality; i++)
        D.push_back(dataset[i]);

    double bestSpread = 0.0;
    size_t bestVpPosition = 0;

    for (size_t i = 0; i < firstSampleSize; i++){

        std::vector<double> distances = D.getDistanceVector(P[i], df);
        double mu = MathFunctions::medianDistance(distances);

        double spread = 0.0;

        std::for_each(distances.begin(), distances.end(), [mu, &spread](double dist){
            spread += pow(dist-mu, 2);
        });

        if (spread > bestSpread){
            bestSpread = spread;
            bestVpPosition = i;
        }
    }

    //InstanceString *result = new InstanceString(P[bestVpPosition]);

    return P[bestVpPosition];
}

InstanceDouble &PivotSelection::hull_foci(DatasetDouble &dataset, DistanceFunction<InstanceDouble> *df){

    // At least 3 elements are needed to calculate the Hull Foci, randomly pick element [0]
    if (dataset.getSize() < 3)
        return dataset[0];

    DatasetDouble vector;
    vector.setSize(0);

    // Randomly choose an object s_i e S
    //srand(time(nullptr));
    InstanceDouble &pivot = dataset[static_cast<size_t>(rand()) % (dataset.getCardinality())];

    std::vector<double> distances;

    // Find the farthest object f_1 from s_i.
    distances = dataset.getDistanceVector(pivot, df);
    InstanceDouble &farthest_f_1 = dataset[static_cast<size_t>(std::distance(distances.begin(), std::max_element(distances.begin(), distances.end())))];

    // Insert f_1 in F.
    vector.push_back(farthest_f_1);

    // Find the farthest object f_2 from f_1.
    distances.clear();
    distances = dataset.getDistanceVector(farthest_f_1, df);
    InstanceDouble &farthest_f_2 = dataset[static_cast<size_t>(std::distance(distances.begin(), std::max_element(distances.begin(), distances.end())))];

    // Insert f_2 in F.
    vector.push_back(farthest_f_2);

    // Set edge = d(f_1, f_2), used to calculate error_i
    double edge = df->getDistance(farthest_f_1, farthest_f_2);

    size_t datasetSize = dataset.getSize();

    std::vector<std::pair<size_t, double>> errorList;
    for (size_t i = 0; i < datasetSize; i++){

        // For each s_i e S, s_i -e F: calculate error
        InstanceDouble &s_i = dataset[i];

        if (!vector.contains(&s_i)){

            double error = 0;
            size_t privateVectorSize = vector.getSize();
            for (size_t j = 0; j < privateVectorSize; j++){
                error += abs(edge - df->getDistance(vector[j], s_i));
            }

            errorList.push_back(std::pair<size_t, double>(i, error));
        }

    }

    // Select s_i e S such that s_i -e F and error_i is minimal.
    double min = errorList[0].second;
    size_t idxMin = errorList[0].first;
    std::for_each(errorList.begin(), errorList.end(), [&min, &idxMin](std::pair<size_t, double> &pair){
        if (pair.second < min){
            min = pair.second;
            idxMin = pair.first;
        }
    });

    // Select the next focus as the object that produced the minimum error.
    return dataset[idxMin];
}

InstanceString &PivotSelection::hull_foci(DatasetString &dataset, DistanceFunction<InstanceString> *df){

    // At least 3 elements are needed to calculate the Hull Foci, randomly pick element [0]
    if (dataset.getSize() < 3)
        return dataset[0];

    DatasetString vector;
    vector.setSize(0);

    // Randomly choose an object s_i e S
    //srand(time(nullptr));
    InstanceString &pivot = dataset[static_cast<size_t>(rand()) % (dataset.getCardinality())];

    std::vector<double> distances;

    // Find the farthest object f_1 from s_i.
    distances = dataset.getDistanceVector(pivot, df);
    InstanceString &farthest_f_1 = dataset[static_cast<size_t>(std::distance(distances.begin(), std::max_element(distances.begin(), distances.end())))];

    // Insert f_1 in F.
    vector.push_back(farthest_f_1);

    // Find the farthest object f_2 from f_1.
    distances.clear();
    distances = dataset.getDistanceVector(farthest_f_1, df);
    InstanceString &farthest_f_2 = dataset[static_cast<size_t>(std::distance(distances.begin(), std::max_element(distances.begin(), distances.end())))];

    // Insert f_2 in F.
    vector.push_back(farthest_f_2);

    // Set edge = d(f_1, f_2), used to calculate error_i
    double edge = df->getDistance(farthest_f_1, farthest_f_2);

    size_t datasetSize = dataset.getSize();

    std::vector<std::pair<size_t, double>> errorList;
    for (size_t i = 0; i < datasetSize; i++){

        // For each s_i e S, s_i -e F: calculate error
        InstanceString &s_i = dataset[i];

        if (!vector.contains(&s_i)){

            double error = 0;
            size_t privateVectorSize = vector.getSize();
            for (size_t j = 0; j < privateVectorSize; j++){
                error += abs(edge - df->getDistance(vector[j], s_i));
            }

            errorList.push_back(std::pair<size_t, double>(i, error));
        }

    }

    // Select s_i e S such that s_i -e F and error_i is minimal.
    double min = errorList[0].second;
    size_t idxMin = errorList[0].first;
    std::for_each(errorList.begin(), errorList.end(), [&min, &idxMin](std::pair<size_t, double> &pair){
        if (pair.second < min){
            min = pair.second;
            idxMin = pair.first;
        }
    });

    // Select the next focus as the object that produced the minimum error.
    return dataset[idxMin];
}

InstanceDouble &PivotSelection::getPivot(DatasetDouble &dataset, Algorithm algo, DistanceFunction<InstanceDouble> *df){

    switch (algo){

        case RANDOM: return randomPivots(dataset);
        case VP_TREE: return selectVp(dataset, df);
        case K_MEDOID: break;
        case HULL_FOCI: return hull_foci(dataset, df);
    }
}

InstanceString &PivotSelection::getPivot(DatasetString &dataset, Algorithm algo, DistanceFunction<InstanceString> *df){

    switch (algo){

        case RANDOM: return randomPivots(dataset);
        case VP_TREE: return selectVp(dataset, df);
        case K_MEDOID: break;
        case HULL_FOCI: return hull_foci(dataset, df);
    }
}

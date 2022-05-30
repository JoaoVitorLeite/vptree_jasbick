#include <PivotSelection/PivotSelection.h>

InstanceDouble PivotSelection::randomPivots(const DatasetDouble &dataset){

    //srand(time_t(nullptr));
    return dataset[rand()% dataset.getCardinality()-1];
}

InstanceString PivotSelection::randomPivots(const DatasetString &dataset){

    srand(time_t(nullptr));
    return dataset[rand()% dataset.getCardinality()-1];
}

InstanceDouble PivotSelection::selectVp(DatasetDouble dataset, DistanceFunction<InstanceDouble> *df){

    const uint_fast32_t cardinality = dataset.getCardinality();
    const uint_fast32_t firstSampleSize = std::floor((cardinality * 10)/100);
    const uint_fast32_t secondSampleSize = cardinality - firstSampleSize;

    DatasetDouble P;
    P.reserve(firstSampleSize);

    while (P.getSize() < firstSampleSize){

        srand(time_t(nullptr));
        const uint_fast32_t randomInteger = rand()% ((cardinality-1)-P.getSize());

        P.push_back(dataset[randomInteger]);
        dataset.swap_positions(randomInteger, (cardinality-1)-P.getSize());
    }

    DatasetDouble D;
    D.reserve(secondSampleSize);

    while (D.getSize() < secondSampleSize){

        if (((cardinality-1)-firstSampleSize-D.getSize()) != 0){

            srand(time_t(nullptr));
            const uint_fast32_t randomInteger = rand()% ((cardinality-1)-firstSampleSize-D.getSize());

            D.push_back(dataset[randomInteger]);
            dataset.swap_positions(randomInteger, (cardinality-1)-firstSampleSize-D.getSize());

        } else {
            D.push_back(dataset[0]);
        }

    }

    double bestSpread = 0.0;
    InstanceDouble bestVp;

    for (uint_fast32_t i = 0; i < firstSampleSize; i++){

        const InstanceDouble &p_i = P[i];

        double mu = D.medianDistance(p_i, df);

        std::vector<double> distances;
        D.getDistanceVector(p_i, df, &distances);

        double spread = 0.0;

        std::for_each(distances.begin(), distances.end(), [&mu, &spread](double dist){
            spread += pow(dist-mu, 2);
        });

        if (spread > bestSpread){
            bestSpread = spread;
            bestVp = p_i;
        }
    }

    return bestVp;
}

InstanceString PivotSelection::selectVp(DatasetString dataset, DistanceFunction<InstanceString> *df){

    const uint_fast32_t cardinality = dataset.getCardinality();
    const uint_fast32_t firstSampleSize = std::floor((cardinality * 10)/100);
    const uint_fast32_t secondSampleSize = cardinality - firstSampleSize;

    DatasetString P;
    P.reserve(firstSampleSize);

    while (P.getSize() < firstSampleSize){

        srand(time_t(nullptr));
        const uint_fast32_t randomInteger = rand()% ((cardinality-1)-P.getSize());

        P.push_back(dataset[randomInteger]);
        dataset.swap_positions(randomInteger, (cardinality-1)-P.getSize());
    }

    DatasetString D;
    D.reserve(secondSampleSize);

    while (D.getSize() < secondSampleSize){

        if (((cardinality-1)-firstSampleSize-D.getSize()) != 0){

            srand(time_t(nullptr));
            const uint_fast32_t randomInteger = rand()% ((cardinality-1)-firstSampleSize-D.getSize());

            D.push_back(dataset[randomInteger]);
            dataset.swap_positions(randomInteger, (cardinality-1)-firstSampleSize-D.getSize());

        } else {
            D.push_back(dataset[0]);
        }

    }

    double bestSpread = 0.0;
    InstanceString bestVp;

    for (uint_fast32_t i = 0; i < firstSampleSize; i++){

        const InstanceString &p_i = P[i];

        double mu = D.medianDistance(p_i, df);

        std::vector<double> distances;
        D.getDistanceVector(p_i, df, &distances);

        double spread = 0.0;

        std::for_each(distances.begin(), distances.end(), [&mu, &spread](double dist){
            spread += pow(dist-mu, 2);
        });

        if (spread > bestSpread){
            bestSpread = spread;
            bestVp = p_i;
        }
    }

    return bestVp;
}

InstanceDouble PivotSelection::hull_foci(const DatasetDouble &dataset, DistanceFunction<InstanceDouble> *df){


    DatasetDouble vector;
    vector.setSize(0);

    // Randomly choose an object s_i e S
    srand(time_t(nullptr));
    const InstanceDouble pivot = dataset[rand()% (dataset.getCardinality())];

    std::vector<double> distances;

    // Find the farthest object f_1 from s_i.
    dataset.getDistanceVector(pivot, df, &distances);
    const InstanceDouble &farthest_f_1 = dataset[std::distance(distances.begin(), std::max_element(distances.begin(), distances.end()))];

    // Insert f_1 in F.
    vector.push_back(farthest_f_1);

    // Find the farthest object f_2 from f_1.
    distances.clear();
    dataset.getDistanceVector(farthest_f_1, df, &distances);
    const InstanceDouble &farthest_f_2 = dataset[std::distance(distances.begin(), std::max_element(distances.begin(), distances.end()))];

    // Insert f_2 in F.
    vector.push_back(farthest_f_2);

    // Set edge = d(f_1, f_2), used to calculate error_i
    double edge = df->getDistance(farthest_f_1, farthest_f_2);

    uint_fast32_t datasetSize = dataset.getSize();

    std::vector<std::pair<uint_fast32_t, double>> errorList;
    for (uint_fast32_t i = 0; i < datasetSize; i++){

        // For each s_i e S, s_i -e F: calculate error
        const InstanceDouble &s_i = dataset[i];

        if (!vector.contains(s_i)){

            double error = 0;
            uint_fast32_t privateVectorSize = vector.getSize();
            for (uint_fast32_t j = 0; j < privateVectorSize; j++){
                error += abs(edge - df->getDistance(vector[j], s_i));
            }

            errorList.push_back(std::pair<uint_fast32_t, double>(i, error));
        }

    }

    // Select s_i e S such that s_i -e F and error_i is minimal.
    double min = errorList[0].second;
    uint_fast32_t idxMin = errorList[0].first;
    std::for_each(errorList.begin(), errorList.end(), [&min, &idxMin](const std::pair<uint_fast32_t, double> &pair){
        if (pair.second < min){
            min = pair.second;
            idxMin = pair.first;
        }
    });

    // Select the next focus as the object that produced the minimum error.
    return dataset[idxMin];
}

InstanceString PivotSelection::hull_foci(const DatasetString &dataset, DistanceFunction<InstanceString> *df){


    DatasetString vector;
    vector.setSize(0);

    // Randomly choose an object s_i e S
    srand(time_t(nullptr));
    const InstanceString pivot = dataset[rand()% (dataset.getCardinality())];

    std::vector<double> distances;

    // Find the farthest object f_1 from s_i.
    dataset.getDistanceVector(pivot, df, &distances);
    const InstanceString &farthest_f_1 = dataset[std::distance(distances.begin(), std::max_element(distances.begin(), distances.end()))];

    // Insert f_1 in F.
    vector.push_back(farthest_f_1);

    // Find the farthest object f_2 from f_1.
    distances.clear();
    dataset.getDistanceVector(farthest_f_1, df, &distances);
    const InstanceString &farthest_f_2 = dataset[std::distance(distances.begin(), std::max_element(distances.begin(), distances.end()))];

    // Insert f_2 in F.
    vector.push_back(farthest_f_2);

    // Set edge = d(f_1, f_2), used to calculate error_i
    double edge = df->getDistance(farthest_f_1, farthest_f_2);

    uint_fast32_t datasetSize = dataset.getSize();

    std::vector<std::pair<uint_fast32_t, double>> errorList;
    for (uint_fast32_t i = 0; i < datasetSize; i++){

        // For each s_i e S, s_i -e F: calculate error
        const InstanceString &s_i = dataset[i];

        if (!vector.contains(s_i)){

            double error = 0;
            uint_fast32_t privateVectorSize = vector.getSize();
            for (uint_fast32_t j = 0; j < privateVectorSize; j++){
                error += abs(edge - df->getDistance(vector[j], s_i));
            }

            errorList.push_back(std::pair<uint_fast32_t, double>(i, error));
        }

    }

    // Select s_i e S such that s_i -e F and error_i is minimal.
    double min = errorList[0].second;
    uint_fast32_t idxMin = errorList[0].first;
    std::for_each(errorList.begin(), errorList.end(), [&min, &idxMin](const std::pair<uint_fast32_t, double> &pair){
        if (pair.second < min){
            min = pair.second;
            idxMin = pair.first;
        }
    });

    // Select the next focus as the object that produced the minimum error.
    return dataset[idxMin];
}

InstanceDouble PivotSelection::getPivot(const DatasetDouble &dataset, Algorithm algo, DistanceFunction<InstanceDouble> *df){
    switch (algo){

        case RANDOM: return randomPivots(dataset);
        case VP_TREE: return selectVp(dataset, df);
        //case K_MEDOID: break;
        case K_MEDOID: return kmedoidPivots(sample_datasetPivot(dataset,1), df);
        case HULL_FOCI: return hull_foci(dataset, df);
        case GNAT: return gnatPivot(sample_datasetPivot(dataset,1), df);
        case MAX_SEPARATED: return maxseparetedPivots(sample_datasetPivot(dataset,1), df);
        case SSS: return sssPivots(sample_datasetPivot(dataset,1), df);
        case PCA: return pcaPivots(sample_datasetPivot(dataset,0.03), df);
        case SELECTION: return selectionPivots(sample_datasetPivot(dataset,1), df);
        default: return randomPivots(dataset);

    }
}

InstanceString PivotSelection::getPivot(const DatasetString &dataset, Algorithm algo, DistanceFunction<InstanceString> *df){
    switch (algo){

        case RANDOM: return randomPivots(dataset);
        case VP_TREE: return selectVp(dataset, df);
        case K_MEDOID: break;
        case HULL_FOCI: return hull_foci(dataset, df);
        default: return randomPivots(dataset);
    }
}

#pragma once

#include <Distance/EditDistance.h>

/**
* @deprecated Use getDistance(ObjectType &obj1, ObjectType &obj2) instead.
*
* @copydoc getDistance(ObjectType &obj1, ObjectType &obj2) .
*/
template <class ObjectType>
double EditDistance<ObjectType>::GetDistance(const ObjectType &obj1, const ObjectType &obj2){

    return getDistance(obj1, obj2);
}

/**
* Calculates the Edit distance between two feature vectors.
* This calculus is based on the math form sqrt((feature_1[i] - feature_2[i])^2).
* To make this computations both feature vectors should have the same size().
*
* @param obj1: The first feature vector.
* @param obj2: The second feature vector.
* @return The Edit distance between feature vector 1 and feature vector 2.
*/
template <class ObjectType>
double EditDistance<ObjectType>::getDistance(const ObjectType &obj1, const ObjectType &obj2){

    // Distance variable to be incremented.
    double dist = 0;

    //Size of the FeatureVectors.
    uint_fast32_t s = obj1.size();

    //Iterates through the size of the FeatureVector.
    for (uint_fast32_t x = 0; x < s; x++){

        //Gets the size of both strings.
        uint_fast32_t size_str1 = obj1[x].size();
        uint_fast32_t size_str2 = obj2[x].size();

        // Gets the strings at pos x of the objects.
        const char *str1 = &obj1[x][0];
        const char *str2 = &obj2[x][0];

        // Column receives a new array of size (size_str1+1).
        uint_fast32_t *column = new uint_fast32_t [size_str1 + 1];

        // Fills column with 0s.
        std::iota(column, column + size_str1 + 1, 0);

        // Finds the best option [Delete, Insert, Replace] for every character.
        for (uint_fast32_t i = 1; i <= size_str2; i++) {

            column[0] = i;
            uint_fast32_t last_diagonal = i - 1;

            for (uint_fast32_t j = 1; j <= size_str1; j++) {
                uint_fast32_t aux = column[j];
                column[j] = std::min(std::min(column[j] + 1, // Delete
                                              column[j - 1] + 1), // Insert
                                              last_diagonal + (str1[j - 1] != str2[i - 1])); // Replace
                last_diagonal = aux;
            }

        }
        dist += column[size_str1];

        delete [] column;
    }

    // Statistic support
    this->updateDistanceCount();

    return dist;
}

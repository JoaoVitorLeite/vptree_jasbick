#pragma once

#include <Distance/EuclideanDistance.h>

/**
* @deprecated Use getDistance(ObjectType &obj1, ObjectType &obj2) instead.
*
* @copydoc getDistance(ObjectType &obj1, ObjectType &obj2) .
*/
template <class ObjectType>
double EuclideanDistance<ObjectType>::GetDistance(const ObjectType &obj1, const ObjectType &obj2){

    return getDistance(obj1, obj2);
}

/**
* Calculates the Euclidean distance between two feature vectors.
* This calculus is based on the math form sqrt((feature_1[i] - feature_2[i])^2).
* To make this computations both feature vectors should have the same size().
*
* @param obj1: The first feature vector.
* @param obj2: The second feature vector.
* @return The Euclidean distance between feature vector 1 and feature vector 2.
*/
template <class ObjectType>
double EuclideanDistance<ObjectType>::getDistance(const ObjectType &obj1, const ObjectType &obj2){

    double d = 0;

    uint_fast32_t s = obj1.getSize();

    for (uint_fast32_t i = 0; i < s; i++)
        d += pow(obj1[i] - obj2[i], 2);

    // Statistic support
    this->updateDistanceCount();

    return sqrt(d);
}

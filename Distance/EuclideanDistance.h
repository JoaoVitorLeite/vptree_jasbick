/**
* @file
*
* This file defines the Euclidean distance.
*
* @version 1.0
* @date 10-29-2014
*/

#pragma once

#include "Distance/DistanceFunction.h"

/**
* Class to obtain the Euclidean (or geometric) Distance
*
* @brief L2 distance class.
* @author 006.
* @version 1.0.
*/
template <class ObjectType>
class EuclideanDistance : public DistanceFunction <ObjectType>{

    public:
        EuclideanDistance(){}
        virtual ~EuclideanDistance(){}

        inline double GetDistance(const ObjectType &obj1, const ObjectType &obj2);
        inline double getDistance(const ObjectType &obj1, const ObjectType &obj2);
};

#include "Distance/EuclideanDistance-inl.h"

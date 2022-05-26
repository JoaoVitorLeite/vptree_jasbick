/**
* @file
*
* This file defines the Manhattan distance.
*
* @version 1.0
* @date 10-29-2014
*/

#pragma once

#include "Distance/DistanceFunction.h"

/**
* Class to obtain the Manhattan (city block) Distance
*
* @brief L1 distance class.
* @author 006.
* @version 1.0.
*/
template <class ObjectType>
class ManhattanDistance : public DistanceFunction <ObjectType>{

    public:
        ManhattanDistance(){}
        virtual ~ManhattanDistance(){}

        inline double GetDistance(const ObjectType &obj1, const ObjectType &obj2);
        inline double getDistance(const ObjectType &obj1, const ObjectType &obj2);
};

#include "Distance/ManhattanDistance-inl.h"

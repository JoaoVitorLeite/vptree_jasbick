/**
* @file
*
* This file defines the Edit distance.
*
* @version 1.0
* @date 10-29-2014
*/

#pragma once

#include "Distance/DistanceFunction.h"
#include <math.h>
#include <iostream>
#include <numeric>

/**
* Class to obtain the Edit Distance
*
* @brief Edit distance class.
* @author 006.
* @version 1.0.
*/
template <class ObjectType>
class EditDistance : public DistanceFunction <ObjectType>{

    public:
        EditDistance(){}
        virtual ~EditDistance(){}

        inline double GetDistance(const ObjectType &obj1, const ObjectType &obj2);
        inline double getDistance(const ObjectType &obj1, const ObjectType &obj2);
};

#include "Distance/EditDistance-inl.h"

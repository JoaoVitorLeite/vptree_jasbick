/* Copyright 2003-2017 GBDI-ICMC-USP <caetano@icmc.usp.br>
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*   http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#pragma once

#include <Distance/CanberraDistance.h>

/**
*ructor.
*/
template <class ObjectType>
CanberraDistance<ObjectType>::CanberraDistance(){
}

/**
* Destructor.
*/
template <class ObjectType>
CanberraDistance<ObjectType>::~CanberraDistance(){
}

/**
* @deprecated Use getDistance(const ObjectType &obj1, const ObjectType &obj2) instead.
*
* @copydoc getDistance(const ObjectType &obj1, const ObjectType &obj2) .
*/
template <class ObjectType>
double CanberraDistance<ObjectType>::GetDistance(const ObjectType &obj1, const ObjectType &obj2){

    return getDistance(obj1, obj2);
}

/**
* To make this computations both feature vectors should have the same size().
*
* @param obj1: The first feature vector.
* @param obj2: The second feature vector.
* @throw Exception If the computation is not possible.
* @return The distance between feature vector 1 and feature vector 2.
*/
template <class ObjectType>
double CanberraDistance<ObjectType>::getDistance(const ObjectType &obj1, const ObjectType &obj2){

    size_t size_obj1 = obj1.getSize();
    size_t size_obj2 = obj2.getSize();

    if (size_obj1 != size_obj2)
        throw std::length_error("The feature vectors do not have the same size.");

    double d = 0;
    double tmp;
    double ai, bi, mai, mbi;

    ai = bi = 0.0;

    for (size_t i = 0; i < size_obj1; i++){

        ai = obj1[i];
        bi = obj2[i];

        mai = sqrt(pow(ai, 2.0));
        mbi = sqrt(pow(bi, 2.0));

        double den = mai+mbi;
        if (den == 0.0){
            den = 1.0;
        }

        tmp = (sqrt(pow((ai - bi), 2.0)))/den;
        d += tmp;
    }

    // Statistic support
    this->updateDistanceCount();

    return d;
}


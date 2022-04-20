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

#include <Distance/JeffreyDivergenceDistance.h>


/**
*ructor.
*/
template <class ObjectType>
JeffreyDivergenceDistance<ObjectType>::JeffreyDivergenceDistance(){
}

/**
* Destructor.
*/
template <class ObjectType>
JeffreyDivergenceDistance<ObjectType>::~JeffreyDivergenceDistance(){
}

/**
* @deprecated Use getDistance(const ObjectType &obj1, const ObjectType &obj2) instead.
*
* @copydoc getDistance(const ObjectType &obj1, const ObjectType &obj2) .
*/
template <class ObjectType>
double JeffreyDivergenceDistance<ObjectType>::GetDistance(const ObjectType &obj1, const ObjectType &obj2){

    return getDistance(obj1, obj2);
}

/**
* To make this computations both feature vectors should have the same size().
*
* @param obj1: The first feature vector.
* @param obj2: The second feature vector.
* @throw Exception If the computation is not possible.
*
* @return The distance between feature vector 1 and feature vector 2.
*/
template <class ObjectType>
double JeffreyDivergenceDistance<ObjectType>::getDistance(const ObjectType &obj1, const ObjectType &obj2){

    size_t size_obj1 = obj1.getSize();
    size_t size_obj2 = obj2.getSize();

    if (size_obj1 != size_obj2)
        throw std::length_error ("The feature vectors do not have the same size.");

    double d = 0.0;
    double tmp;
    double mi, ai, bi;

    ai = bi = mi = tmp = 0.0;

    for (size_t i = 0; i < size_obj1; i++){

        auto obj1_data = obj1[i];
        auto obj2_data = obj2[i];

        mi = (obj1_data + obj2_data)/2;
        ai = obj1_data;
        bi = obj2_data;

        if ((ai == 0.0) || (bi == 0.0) || (mi == 0.0)){
            if (ai == 0){
                if (bi == 0){
                    tmp = 0.0;
                } else {
                    tmp = bi*log(bi/mi);
                }
            } else {
                if (bi == 0){
                    tmp = ai*log(ai/mi);
                } else {
                    tmp = 0.0;
                }
            }
        } else {
            tmp = ((ai*log(ai/mi)) + (bi*log(bi/mi)));
        }

        d += tmp;
    }

    // Statistic support
    this->updateDistanceCount();

    return d;
}

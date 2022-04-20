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

#include <Distance/SquaredChordDistance.h>

/**
*ructor.
*/
template <class ObjectType>
SquaredChordDistance<ObjectType>::SquaredChordDistance(){
}

/**
* Destructor.
*/
template <class ObjectType>
SquaredChordDistance<ObjectType>::~SquaredChordDistance(){
}

/**
* @copydoc DistanceFunction::GetDistance()
*/
template <class ObjectType>
double SquaredChordDistance<ObjectType>::GetDistance(const ObjectType &obj1, const ObjectType &obj2){

    return getDistance(obj1, obj2);
}

/**
* @copydoc DistanceFunction::getDistance()
*/
template <class ObjectType>
double SquaredChordDistance<ObjectType>::getDistance(const ObjectType &obj1, const ObjectType &obj2){

    size_t size_obj1 = obj1.getSize();
    size_t size_obj2 = obj2.getSize();

    if (size_obj1 != size_obj2)
        throw std::length_error("The feature vectors do not have the same size.");

    double d;
    double tmp;

    d = 0;

    for (size_t i = 0; i < size_obj1; i++){
        tmp = sqrt(obj1[i]) - sqrt(obj2[i]);
        d += (tmp*tmp);
    }

    // Statistic support
    this->updateDistanceCount();

    return d;
}

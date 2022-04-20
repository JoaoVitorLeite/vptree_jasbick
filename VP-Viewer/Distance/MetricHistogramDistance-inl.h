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

#include <Distance/MetricHistogramDistance.h>


/**
*ructor.
*/
template <class ObjectType>
MetricHistogramDistance<ObjectType>::MetricHistogramDistance() {
}

/**
* Destructor.
*/
template <class ObjectType>
MetricHistogramDistance<ObjectType>::~MetricHistogramDistance() {
}

/**
* @deprecated Use getDistance(const ObjectType &obj1, const ObjectType &obj2) instead.
*
* @copydoc getDistance(const ObjectType &obj1, const ObjectType &obj2) .
*/
template <class ObjectType>
double MetricHistogramDistance<ObjectType>::GetDistance(const ObjectType &obj1, const ObjectType &obj2){

    return getDistance(obj1, obj2);
}

/**
* Calculates similariry between the two metric histograms.
* This calculus is based on the histograms.
*
* @param obj1: The first feature vector.
* @param obj2: The second feature vector.
* @return The distance between feature vector 1 and feature vector 2.
*/
template <class ObjectType>
double MetricHistogramDistance<ObjectType>::getDistance(const ObjectType &obj1, const ObjectType &obj2){

    size_t size_obj1 = obj1.getSize();
    size_t size_obj2 = obj2.getSize();

    double *new_obj1_gray  = new double[(size_obj1/2)];
    double *new_obj1_value = new double[(size_obj1/2)];

    double *new_obj2_gray  = new double[(size_obj2/2)];
    double *new_obj2_value = new double[(size_obj2/2)];

    for (size_t x = 0; x < (size_obj1/2); x++){
        new_obj1_gray[x] = obj1[x];
        new_obj1_value[x] = obj1[(size_obj1/2) + x];
    }

    for (size_t x = 0; x < (size_obj2/2); x++){
        new_obj2_gray[x] = obj2[x];
        new_obj2_value[x] = obj2[(size_obj2/2) + x];
    }

    double d1, d2;
    double m;
    d1 = d2 = 0.0;

    for (size_t x = 0; x < ((size_obj1/2)-1); x++){
        m = (new_obj1_value[x+1] - new_obj1_value[x])/(new_obj1_gray[x+1] - new_obj1_gray[x]);
        d1 += ((m*new_obj1_gray[x+1]*new_obj1_gray[x+1])/2.0) + (new_obj1_value[x]*new_obj1_gray[x+1]);
        d1 -= ((m*new_obj1_gray[x]*new_obj1_gray[x])/2.0) + (new_obj1_value[x]*new_obj1_gray[x]);
    }

    for (size_t x = 0; x < ((size_obj2/2)-1); x++){
        m = (new_obj2_value[x+1] - new_obj2_value[x])/(new_obj2_gray[x+1] - new_obj2_gray[x]);
        d2 += ((m*new_obj2_gray[x+1]*new_obj2_gray[x+1])/2.0) + (new_obj2_value[x]*new_obj2_gray[x+1]);
        d2 -= ((m*new_obj2_gray[x]*new_obj2_gray[x])/2.0) + (new_obj2_value[x]*new_obj2_gray[x]);
    }

    delete[] (new_obj1_gray);
    delete[] (new_obj1_value);
    delete[] (new_obj2_gray);
    delete[] (new_obj2_value);

    new_obj1_gray = nullptr;
    new_obj1_value = nullptr;
    new_obj2_gray = nullptr;
    new_obj2_value = nullptr;

    this->updateDistanceCount();

    return fabs(d1 - d2);
}

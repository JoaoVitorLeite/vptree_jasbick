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

#include <Distance/MorositaDistance.h>


template <class ObjectType>
MorositaDistance<ObjectType>::MorositaDistance(){
}

template <class ObjectType>
MorositaDistance<ObjectType>::~MorositaDistance(){
}

template <class ObjectType>
double MorositaDistance<ObjectType>::GetDistance(const ObjectType &obj1, const ObjectType &obj2){

    return getDistance(obj1, obj2);
}

template <class ObjectType>
double MorositaDistance<ObjectType>::getDistance(const ObjectType &obj1, const ObjectType &obj2){

    size_t size_obj1 = obj1.getSize();
    size_t size_obj2 = obj2.getSize();

    if (size_obj1 != size_obj2) {
        throw std::length_error("The feature vectors do not have the same size.");
    }

    double sumx, sumy, sumxy, lambda1, lambda2;
    double sumaux1, sumaux2, sumaux3, sumaux4;

    sumx = sumy = sumxy = 0.0;
    sumaux1 = sumaux2 = sumaux3 = sumaux4 = 0.0;

    for (size_t x = 0; x < size_obj1; x++){

        auto obj1_data = obj1[x];

        sumaux2 += obj1_data;
        sumaux1 += obj1_data - 1;
        sumaux3 += obj1_data*(obj1_data - 1);
    }
    lambda1 = sumaux3/(sumaux1*sumaux2);

    sumaux1 = sumaux3 = 0.0;
    for (size_t x = 0; x < size_obj1; x++){

        auto obj2_data = obj2[x];

        sumaux4 += obj2_data;
        sumaux1 += obj2_data - 1;
        sumaux3 += obj2_data*(obj2_data - 1);
    }
    lambda2 = sumaux3/(sumaux1*sumaux4);


    if (((lambda1 + lambda2) == 0.0) || (sumaux2 == 0.0) || (sumaux4 == 0.0)){
        return 0;
    } else {
        sumaux1 = 0.0;
        for (size_t x = 0; x < size_obj1; x++){
            sumaux1 = obj1[x]*obj2[x];
        }
        return 2*(sumaux1/((lambda1 + lambda2)*sumaux2*sumaux4));
    }
}

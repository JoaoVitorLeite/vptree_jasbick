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

#include <Distance/SpearmanDistance.h>


/**
*ructor.
*/
template <class ObjectType>
SpearmanDistance<ObjectType>::SpearmanDistance(){
}

/**
* Destructor.
*/
template <class ObjectType>
SpearmanDistance<ObjectType>::~SpearmanDistance(){
}

/**
* @deprecated Use getDistance() instead.
*
* @copydoc getDistance(const ObjectType &obj1, const ObjectType &obj2)
*/
template <class ObjectType>
double SpearmanDistance<ObjectType>::GetDistance(const ObjectType &obj1, const ObjectType &obj2){

    return getDistance(obj1, obj2);
}

/**
* Calculates the Spearman's Rank correlation between two feature vectors.
*
* To make this computations both feature vectors should have the same size().
*
* @param obj1: The first feature vector.
* @param obj2: The second feature vector.
* @throw Exception If the computation is not possible.
* @return The Spearman's Rank correlation between feature vector 1 and feature vector 2.
*/
template <class ObjectType>
double SpearmanDistance<ObjectType>::getDistance(const ObjectType &obj1, const ObjectType &obj2){

    size_t size_obj1 = obj1.getSize();
    size_t size_obj2 = obj2.getSize();

    if (size_obj1 != size_obj2){
        throw std::length_error ("The feature vectors do not have the same size.");
    }

    double* xrank = new double[size_obj1];
    double* yrank = new double[size_obj1];

    for (size_t i = 0; i < size_obj1; i++){
        xrank[i] = 0.0;
        yrank[i] = 0.0;
    }

    int index = 1;

    double xElement = obj1[0];
    double yElement = obj2[0];

    //Gets the minor value and set it to *Element
    for (size_t i = 0; i < size_obj1; i++){

        auto obj1_data = obj1[i];
        auto obj2_data = obj2[i];

        if (obj1_data < xElement)
            xElement = obj1_data;

        if (obj2_data < yElement)
            yElement = obj2_data;
    }

    bool ranking = true;

    //It ranks first time series
    while (ranking)	{
        u_int32_t recurrence = 0;
        //Count the recurrence
        for (size_t i = 0; i < size_obj1; i++)
            if (obj1[i] == xElement)
                recurrence++;

        double rank = (index * 2) + recurrence - 1;
        rank /= (double) 2;

        //Set rank to the proper positions
        for (size_t i = 0; i < size_obj1; i++)
            if (obj1[i] == xElement)
                xrank[i] = rank;

        ranking = false;
        double newElement;

        for (size_t i = 0; i < size_obj1; i++) {

            auto obj1_data = obj1[i];

            //Continue if there's a number higher than xElement
            if (obj1_data > xElement){
                ranking = true;
                newElement = obj1_data;
            }
        }

        // it stops if there isn't more numbers to rank in the sequence
        if (ranking){
            for (size_t i = 0; i < size_obj1; i++)
                if ((obj1[i] > xElement) && (obj1[i] < newElement))
                    newElement = obj1[i];

            // sets to xElement the minor number not ranked of the sequence
            xElement = newElement;
            // xindex gets the next number to be used in the rank
            index += recurrence;
        }
    }


    ranking = true;
    index = 1;

    //It ranks second time series
    while (ranking) {

        int recurrence = 0;

        for (size_t i = 0; i < size_obj1; i++)
            if (obj2[i] == yElement)
                recurrence++;

        double rank = (index * 2) + recurrence - 1;
        rank /= (double) 2;

        for (size_t i = 0; i < size_obj1; i++)
            if (obj2[i] == yElement)
                yrank[i] = rank;

        ranking = false;
        double newElement;

        for (size_t i = 0; i < size_obj1; i++){

            auto obj2_data = obj2[i];

            if (obj2_data > yElement){
                ranking = true;
                newElement = obj2_data;
            }
        }

        if (ranking){
            for (size_t i = 0; i < size_obj1; i++)
                if ((obj2[i] > yElement) && (obj2[i] < newElement))
                    newElement = obj2[i];

            yElement = newElement;
            index += recurrence;
        }
    }

    double sum = 0;

    for (size_t i = 0; i < size_obj1; i++){
        double difference = xrank[i] - yrank[i];
        sum += difference * difference;
    }

    // Spearman's Rank Correlation formula
    double result = (1 - 6 * sum / (size_obj1* (size_obj1 * size_obj1 - 1)));

    delete [] xrank;
    delete [] yrank;

    // Statistic support
    this->updateDistanceCount();

    return result;
}


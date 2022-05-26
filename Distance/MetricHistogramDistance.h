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
/**
* @file
*
* This file defines the distance functions of the Metric Histogram Distance.
*
* @version 1.0
*/

#pragma once

#include "Distance/DistanceFunction.h"
#include <stdexcept>

/**
* Class to the area diferences between two metric histograms.
*
* @brief Gets the area between the metric histograms.
* @author 006.
* @version 1.0.
*/
template <class ObjectType>
class MetricHistogramDistance : public DistanceFunction <ObjectType> {

    public:

        MetricHistogramDistance();
        virtual ~MetricHistogramDistance();

        inline double GetDistance(const ObjectType &obj1, const ObjectType &obj2);
        inline double getDistance(const ObjectType &obj1, const ObjectType &obj2);
};

#include "Distance/MetricHistogramDistance-inl.h"
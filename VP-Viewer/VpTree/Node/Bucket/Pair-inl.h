#pragma once

#include <VpTree/Node/Bucket/Pair.h>

template <class DType>
Pair<DType>::Pair(DType obj, std::vector<double> distanceVector){
    pair.first = obj;
    pair.second = distanceVector;
}

template <class DType>
DType Pair<DType>::first(){
    return pair.first;
}

template <class DType>
std::vector<double> Pair<DType>::second(){
    return pair.second;
}

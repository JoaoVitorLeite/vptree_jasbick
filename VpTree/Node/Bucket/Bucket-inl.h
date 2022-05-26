#pragma once

#include <VpTree/Node/Bucket/Bucket.h>

template <class DType>
Bucket<DType>::Bucket(){
    currentPosition = 0;
}

template <class DType>
uint_fast32_t Bucket<DType>::numberOfElements() const{
    return currentPosition;
}

template <class DType>
void Bucket<DType>::setPair(const Pair<DType> &pair, const uint_fast32_t idx){
    bucket[idx] = pair;
}

template <class DType>
Pair<DType> Bucket<DType>::getPair(const uint_fast32_t idx){
    return bucket[idx];
}

template <class DType>
void Bucket<DType>::push_back(const Pair<DType> &pair){
    bucket.push_back(pair);
    currentPosition++;
}

template <class DType>
Pair<DType> &Bucket<DType>::operator[](const uint_fast32_t idx){
    return bucket[idx];
}

template <class DType>
const Pair<DType> &Bucket<DType>::operator[](const uint_fast32_t idx) const{
    return bucket[idx];
}

#pragma once

#include <VpTree/Node/LeafNode.h>

#define IMPL_TEMPL template<class DType>

IMPL_TEMPL LeafNode<DType>::LeafNode(){
    maxElements = 0;
}

IMPL_TEMPL LeafNode<DType>::LeafNode(size_t paramMaxElements){
    maxElements = paramMaxElements;
}

IMPL_TEMPL LeafNode<DType>::~LeafNode(){}

IMPL_TEMPL void LeafNode<DType>::setBucket(const Bucket<DType> &paramBucket,
                                           const uint_fast32_t numberOfElements){
    bucket = paramBucket;
    bucket.setCurrentPosition(numberOfElements);
}

IMPL_TEMPL Bucket<DType> &LeafNode<DType>::getBucket() { return bucket; }

IMPL_TEMPL void LeafNode<DType>::resetBucket(){
    bucket.reset();
    bucket.setCurrentPosition(0);
}

IMPL_TEMPL void LeafNode<DType>::setPreviousPivots(const std::vector<DType> &paramPreviousPivots){
    previousPivots = paramPreviousPivots;
}

IMPL_TEMPL const std::vector<DType> &LeafNode<DType>::getPreviousPivots() const{ return previousPivots; }

IMPL_TEMPL void LeafNode<DType>::setDistanceVector(const std::vector<std::vector<double>> &paramDistanceVector){
    distanceVector = paramDistanceVector;
}

IMPL_TEMPL const std::vector<std::vector<double> > &LeafNode<DType>::getDistanceVector() const{ return distanceVector; }

IMPL_TEMPL void LeafNode<DType>::setCircunscribed(const bool paramIsCircunscribed){
    isCircunscribed = paramIsCircunscribed;
}

IMPL_TEMPL bool LeafNode<DType>::circunscribed() const{
    return isCircunscribed;
}

IMPL_TEMPL uint_fast32_t LeafNode<DType>::numberOfElements() const{ return bucket.numberOfElements(); }

IMPL_TEMPL void LeafNode<DType>::setPair(Pair<DType> pair, const uint_fast32_t idx){
    bucket[idx] = pair;
}

IMPL_TEMPL Pair<DType> LeafNode<DType>::getPair(const uint_fast32_t idx){
    return bucket[idx];
}

IMPL_TEMPL void LeafNode<DType>::push_back(const Pair<DType> &pair){
    bucket.push_back(pair);
}

IMPL_TEMPL Pair<DType> &LeafNode<DType>::operator[](const uint_fast32_t idx){
    return bucket[idx];
}

IMPL_TEMPL const Pair<DType> &LeafNode<DType>::operator[](const uint_fast32_t idx) const{
    return bucket[idx];
}

IMPL_TEMPL void LeafNode<DType>::push_exceeded_node(Node<DType> *leaf){
    exceededNodes.push_back(leaf);
}

IMPL_TEMPL std::vector<Node<DType>*> LeafNode<DType>::getExceededNodes(){
    return exceededNodes;
}

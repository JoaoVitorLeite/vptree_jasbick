#pragma once

#include <VpTree/Node/LeafNode.h>

#define IMPL_TEMPL template<class ObjectType>

IMPL_TEMPL LeafNode<ObjectType>::LeafNode(){}
IMPL_TEMPL LeafNode<ObjectType>::~LeafNode(){}

IMPL_TEMPL size_t LeafNode<ObjectType>::numberOfElements(){ return bucket.getSize(); }

IMPL_TEMPL void LeafNode<ObjectType>::push_back(ObjectType &item, double distance){
    bucket.push_back(item);
    distances_to_pivot.push_back(distance);
}

IMPL_TEMPL void LeafNode<ObjectType>::setBucket(Dataset<ObjectType> &dataset){
    this->bucket = dataset;
}

IMPL_TEMPL Dataset<ObjectType> &LeafNode<ObjectType>::getBucket(){
    return bucket;
}

IMPL_TEMPL ObjectType &LeafNode<ObjectType>::operator[](size_t idx){
    return bucket[idx];
}

IMPL_TEMPL double LeafNode<ObjectType>::distance_at(size_t idx){
    return distances_to_pivot[idx];
}

IMPL_TEMPL void LeafNode<ObjectType>::push_exceeded_node(Node<ObjectType> *leaf){
    exceededNodes.push_back(leaf);
}

IMPL_TEMPL std::vector<Node<ObjectType>*> LeafNode<ObjectType>::getExceededNodes(){
    return exceededNodes;
}

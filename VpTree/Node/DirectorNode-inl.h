#pragma once

#include <VpTree/Node/DirectorNode.h>

#define IMPL_TEMPL template<class DType>

IMPL_TEMPL DirectorNode<DType>::DirectorNode(){
    rightNode = nullptr;
    leftNode = nullptr;
}

IMPL_TEMPL void DirectorNode<DType>::setHistogram(const PivotHistogram &paramHistogram){ histogram = paramHistogram; }
IMPL_TEMPL const PivotHistogram &DirectorNode<DType>::getHistogram() const{ return histogram; }

IMPL_TEMPL void DirectorNode<DType>::setRightNode(Node<DType> *paramRightNode){ rightNode = paramRightNode; }
IMPL_TEMPL Node<DType> *DirectorNode<DType>::getRightNode() const{ return rightNode; }

IMPL_TEMPL void DirectorNode<DType>::setLeftNode(Node<DType> *paramLeftNode){ leftNode = paramLeftNode; }
IMPL_TEMPL Node<DType> *DirectorNode<DType>::getLeftNode() const{ return leftNode; }

#pragma once

#include <VpTree/Node/DirectorNode.h>

#define IMPL_TEMPL template<class ObjectType>

IMPL_TEMPL DirectorNode<ObjectType>::DirectorNode(){
    rightNode = nullptr;
    leftNode = nullptr;
}

IMPL_TEMPL void DirectorNode<ObjectType>::setRightNode(Node<ObjectType> *paramRightNode){ rightNode = paramRightNode; }
IMPL_TEMPL Node<ObjectType> *DirectorNode<ObjectType>::getRightNode(){ return rightNode; }

IMPL_TEMPL void DirectorNode<ObjectType>::setLeftNode(Node<ObjectType> *paramLeftNode){ leftNode = paramLeftNode; }
IMPL_TEMPL Node<ObjectType> *DirectorNode<ObjectType>::getLeftNode(){ return leftNode; }

IMPL_TEMPL const Node<ObjectType> *DirectorNode<ObjectType>::getRightNode() const { return rightNode; }
IMPL_TEMPL const Node<ObjectType> *DirectorNode<ObjectType>::getLeftNode() const{ return leftNode; }

#pragma once

#include <VpTree/Node/Node.h>

#undef IMPL_TEMPL
#define IMPL_TEMPL template<class ObjectType>

IMPL_TEMPL ObjectType &Node<ObjectType>::getPivot() { return *pivot; }
IMPL_TEMPL void Node<ObjectType>::setPivot(ObjectType &paramPivot){

    pivot = &paramPivot;
}

IMPL_TEMPL void Node<ObjectType>::setMu(double paramMu){ mu = paramMu; }
IMPL_TEMPL double Node<ObjectType>::getMu(){ return mu; }

//IMPL_TEMPL void Node<ObjectType>::setBall(Dataset<ObjectType> &ball){
//    this->ball = ball;
//}

//IMPL_TEMPL Dataset<ObjectType> &Node<ObjectType>::getBall(){
//    return ball;
//}

IMPL_TEMPL void Node<ObjectType>::setMin(double paramMin){ min = paramMin; }
IMPL_TEMPL double Node<ObjectType>::getMin(){ return min; }

IMPL_TEMPL void Node<ObjectType>::setMax(double paramMax){ max = paramMax; }
IMPL_TEMPL double Node<ObjectType>::getMax(){ return max; }

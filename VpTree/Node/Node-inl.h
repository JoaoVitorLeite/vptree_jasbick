#pragma once

#include <VpTree/Node/Node.h>

#undef IMPL_TEMPL
#define IMPL_TEMPL template<class DType>

IMPL_TEMPL const DType &Node<DType>::getPivot() const{ return pivot; }
IMPL_TEMPL void Node<DType>::setPivot(const DType &paramPivot){ pivot = paramPivot; }

IMPL_TEMPL void Node<DType>::setMu(const double paramMu){ mu = paramMu; }
IMPL_TEMPL double Node<DType>::getMu() const{ return mu; }

IMPL_TEMPL void Node<DType>::setDMin(const double paramDMin){ dMin = paramDMin; }
IMPL_TEMPL double Node<DType>::getDMin() const{ return dMin; }

IMPL_TEMPL void Node<DType>::setDMax(const double paramDMax){ dMax = paramDMax; }
IMPL_TEMPL double Node<DType>::getDMax() const{ return dMax; }

IMPL_TEMPL void Node<DType>::setCoverage(double maxDistFromPivot) { coverage = maxDistFromPivot; }
IMPL_TEMPL double Node<DType>::getCoverage() { return coverage; }


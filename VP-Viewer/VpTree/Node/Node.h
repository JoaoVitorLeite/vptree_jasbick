#pragma once

#include <algorithm>
#include <VpTree/OrdinalBlock.h>

template <class ObjectType>
class Node{
    private:
        ObjectType *pivot;
        double mu;
        double min;
        double max;

    public:
        virtual ~Node() = default;

        void setPivot(ObjectType &paramPivot);
        ObjectType &getPivot();

        void setMu(double paramMu);
        double getMu();

        void setMin(double paramMin);
        double getMin();

        void setMax(double paramMax);
        double getMax();

//        void setBall(Dataset<ObjectType> &ball);
//        Dataset<ObjectType> &getBall();

};

#include <VpTree/Node/Node-inl.h>

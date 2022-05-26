#pragma once

template <class DType>
class Node{
    private:
        DType pivot;
        double mu;
        double dMin;
        double dMax;
        double coverage;

    public:
        virtual ~Node() = default;

        bool wasVisited = false;

        void setPivot(const DType &paramPivot);
        const DType &getPivot() const;

        void setMu(const double paramMu);
        double getMu() const;

        void setDMin(const double paramDMin);
        double getDMin() const;

        void setDMax(const double paramDMax);
        double getDMax() const;

        void setCoverage(double maxDistFromPivot);
        double getCoverage();

        bool operator <(const Node &node) const{
            return dMin < node.dMin;
        }

        bool operator >(const Node &node) const{
            return dMin > node.dMin;
        }
};

#include <VpTree/Node/Node-inl.h>

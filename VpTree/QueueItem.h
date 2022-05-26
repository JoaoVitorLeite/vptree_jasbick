#pragma once
#include <queue>

template <class DType>
class QueueItem{
    public:
        QueueItem(double dist, DType featureVector){
            this->dist = dist;
            this->featureVector = featureVector;
        }

        double dist;
        DType featureVector;

        bool operator <(const QueueItem &item) const{
            return dist < item.dist;
        }
        bool operator >(const QueueItem &item) const{
            return dist > item.dist;
        }
};

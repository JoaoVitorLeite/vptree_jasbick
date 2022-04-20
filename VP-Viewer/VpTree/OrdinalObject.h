#pragma once

template <class ObjectType>
class OrdinalObject{
    public:
        double dist;
        ObjectType *featureVector;

        OrdinalObject(double dist, ObjectType &featureVector){
            this->dist = dist;
            this->featureVector = &featureVector;
        }

        bool operator <(const OrdinalObject &item) const{
            return dist < item.dist;
        }
};

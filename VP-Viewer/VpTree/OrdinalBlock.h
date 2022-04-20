#pragma once
#include <Dataset/Dataset.h>

template <class ObjectType>
class OrdinalBlock{
    public:
        double min;
        double max;
        Dataset<ObjectType> *dataset;

        OrdinalBlock(double min, double max, Dataset<ObjectType> &dataset){
            this->min = min;
            this->max = max;
            this->dataset = &dataset;
        }

        bool operator <(const OrdinalBlock &block) const{
            if (min == block.min)
                return max < block.max;
            else
                return min < block.min;
        }

        void setDataset(Dataset<ObjectType> &dataset){
            this->dataset = &dataset;
        }

        Dataset<ObjectType> &getDataset(){
            return *dataset;
        }

        double getMin(){
            return min;
        }

        double getMax(){
            return max;
        }
};

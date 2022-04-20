#pragma once

#include <vector>
#include <cstdlib>
#include <VpTree/Node/Bucket/Pair.h>

template <class DType>
class Bucket {
    private:
        std::vector<Pair<DType>> bucket;
        uint_fast32_t currentPosition;

    public:
        Bucket();

        void reset(){ bucket.clear(); }

        void setPair(const Pair<DType> &pair, const uint_fast32_t idx);
        Pair<DType> getPair(const uint_fast32_t idx);

        void push_back(const Pair<DType> &pair);

        Pair<DType> &operator[](const uint_fast32_t idx);
        const Pair<DType> &operator[](const uint_fast32_t idx) const;

        uint_fast32_t numberOfElements() const;

        void setCurrentPosition(uint_fast32_t paramCurrentPosition){
            currentPosition = paramCurrentPosition;
        }

};

#include <VpTree/Node/Bucket/Bucket-inl.h>

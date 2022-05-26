#pragma once

#include <VpTree/Node/Node.h>
#include <VpTree/Node/Bucket/Bucket.h>

template <class DType>
class LeafNode: public Node<DType>{
    private:
        uint_fast32_t maxElements;
        bool isCircunscribed;
        Bucket<DType> bucket;
        std::vector<Node<DType>*> exceededNodes;
        std::vector<DType> previousPivots;
        std::vector<std::vector<double>> distanceVector;

    public:
        LeafNode();
        LeafNode(size_t paramMaxElements);

        ~LeafNode();

        void setPreviousPivots(const std::vector<DType> &paramPreviousPivots);
        const std::vector<DType> &getPreviousPivots() const;

        void setDistanceVector(const std::vector<std::vector<double>> &paramDistanceVector);
        const std::vector<std::vector<double>> &getDistanceVector() const;

        void setBucket(const Bucket<DType> &paramBucket,
                       const uint_fast32_t numberOfElements);
        Bucket<DType> &getBucket();

        void resetBucket();

        void setPair(Pair<DType> pair, const uint_fast32_t idx);
        Pair<DType> getPair(const uint_fast32_t idx);

        void push_back(const Pair<DType> &pair);

        Pair<DType> &operator[](const uint_fast32_t idx);
        const Pair<DType> &operator[](const uint_fast32_t idx) const;

        void push_exceeded_node(Node<DType> *leaf);

        std::vector<Node<DType>*> getExceededNodes();

        void setCircunscribed(const bool paramIsCircunscribed);
        bool circunscribed() const;
        uint_fast32_t numberOfElements() const;
};

#include <VpTree/Node/LeafNode-inl.h>

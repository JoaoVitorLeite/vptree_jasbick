#pragma once

#include <VpTree/Node/Node.h>
#include <Dataset/Dataset.h>
#include <VpTree/OrdinalObject.h>
#include <VpTree/OrdinalBlock.h>

template <class ObjectType>
class LeafNode: public Node<ObjectType>{
    private:
        Dataset<ObjectType> bucket;
        std::vector<double> distances_to_pivot;
        std::vector<Node<ObjectType> *> exceededNodes;

    public:
        LeafNode();
        ~LeafNode();

        void push_back(ObjectType &element, double distance);

        void setBucket(Dataset<ObjectType> &dataset);
        Dataset<ObjectType> &getBucket();

        ObjectType &operator[](size_t idx);
        double distance_at(size_t idx);

        void push_exceeded_node(Node<ObjectType> *leaf);

        std::vector<Node<ObjectType>*> getExceededNodes();

        size_t numberOfElements();
};

#include <VpTree/Node/LeafNode-inl.h>

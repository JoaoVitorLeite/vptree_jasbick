#pragma once
#include <queue>

template <class Node>
class QueueNode{
    public:
        QueueNode(double dist, Node *node){
            this->dist = dist;
            this->node = node;
        }

        double dist;
        Node *node;

        bool operator <(const QueueNode &node) const{
            return dist < node.dist;
        }
};

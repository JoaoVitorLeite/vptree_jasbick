#pragma once

#include <VpTree/Node/Node.h>
#include <vector>
#include <iostream>

template <class ObjectType>
class DirectorNode: public Node<ObjectType>{
    private:
        Node<ObjectType> *rightNode;
        Node<ObjectType> *leftNode;

    public:
        DirectorNode();
        ~DirectorNode(){ delete(rightNode); rightNode = nullptr; delete(leftNode); leftNode = nullptr; }

        void setRightNode(Node<ObjectType> *paramRightNode);
        Node<ObjectType> *getRightNode();

        void setLeftNode(Node<ObjectType> *paramLeftNode);
        Node<ObjectType> *getLeftNode();

        const Node<ObjectType> *getLeftNode() const;
        const Node<ObjectType> *getRightNode() const;
};

#include <VpTree/Node/DirectorNode-inl.h>

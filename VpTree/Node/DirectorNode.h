#pragma once

#include <VpTree/Node/Node.h>
#include <Histogram/PivotHistogram.h>

template <class DType>
class DirectorNode: public Node<DType>{
    private:
        Node<DType> *rightNode;
        Node<DType> *leftNode;
        PivotHistogram histogram;

    public:
        DirectorNode();
        ~DirectorNode(){ delete(rightNode); rightNode = nullptr; delete(leftNode); leftNode = nullptr; }

        void setHistogram(const PivotHistogram &paramHistogram);
        const PivotHistogram &getHistogram() const;

        void setRightNode(Node<DType> *paramRightNode);
        Node<DType> *getRightNode() const;

        void setLeftNode(Node<DType> *paramLeftNode);
        Node<DType> *getLeftNode() const;
};

#include <VpTree/Node/DirectorNode-inl.h>

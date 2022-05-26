#pragma once

#include <iostream>
#include <VpTree/Node/LeafNode.h>
#include <VpTree/Node/DirectorNode.h>
#include <QGraphicsView>
#include <QTextStream>
#include <QProcess>
#include <QMainWindow>

template <class DType>
class View{
    private:
        Node<DType> *root;
        uint_fast32_t maxElementsPerLeaf;
        double width = 0;
        double height = 0;

        void graphWalk(Node<DType>* node, QTextStream *stream);
        QByteArray prepareGraph();

    public:
        View(Node<DType> *root, uint_fast32_t maxElementsPerLeaf);

        QPixmap getPixmap();
        QPixmap getPixmap(double width, double height);
};

#include <VpTree/View-inl.h>

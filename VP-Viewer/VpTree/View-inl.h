#pragma once

#include <VpTree/View.h>

template<class DType>
View<DType>::View(Node<DType> *root, uint_fast32_t maxElementsPerLeaf){
    this->root = root;
    this->maxElementsPerLeaf = maxElementsPerLeaf;
    this->width = width;
    this->height = height;
}

template<class DType>
void View<DType>::graphWalk(Node<DType> *node, QTextStream *stream) {

    DirectorNode<DType> *dirNode = dynamic_cast<DirectorNode<DType>*>(node);

    if (dirNode != nullptr){

        u_int32_t pivotOID = dirNode->getPivot().getOID();

        // Creates a directorNode
        if (dirNode->wasVisited){
            *stream << "\t\t" << "n" << pivotOID << "[label=\"pid-" << pivotOID <<"\" fillcolor=antiquewhite4];" << endl;
            dirNode->wasVisited = false;
        } else {
            *stream << "\t\t" << "n" << pivotOID << "[label=\"pid-" << pivotOID <<"\"];" << endl;
        }

        if(dirNode->getLeftNode() != NULL){

            u_int32_t leftNodePivotOID = dirNode->getLeftNode()->getPivot().getOID();

            // Points the node with pivotOID to the node with leftNodePivotOID
            *stream << "\t\tn" << pivotOID << "--" << "n" << leftNodePivotOID << ";" << endl;
            graphWalk(dirNode->getLeftNode(), stream);

        } else {
            // Creates a null node at the left of node
            *stream << "\t\t" << "n" << pivotOID << "leftNull" << "[style=\"filled\",label=\"NULL\"];" << endl;

            // Points the node with pivotOID to the node with leftNull
            *stream << "\t\tn" << pivotOID << "--" << "n" << pivotOID << "leftNull" << endl;
        }

        if(dirNode->getRightNode() != NULL){

            u_int32_t rightNodePivotOID = dirNode->getRightNode()->getPivot().getOID();

            // Points the node with pivotOID to the node with rightNodePivotOID
            *stream << "\t\tn" << pivotOID << "--" << "n" << rightNodePivotOID << ";" << endl;
            graphWalk(dirNode->getRightNode(), stream);

        }/* else {
            // Creates a null node at the right of node
            *stream << "\t\t" << "n" << pivotOID << "rightNull" << "[style=\"filled\",label=\"NULL\"];" << endl;

            // Points the node with pivotOID to the node with rightNull
            *stream << "\t\tn" << pivotOID << "--" << "n" << pivotOID << "rightNull" << endl;
        }*/

    }  else {

        LeafNode<DType> *leafNode = dynamic_cast<LeafNode<DType>*>(node);

        // Creates a leafNode with the number of elements in its bucket,
        // or, if the node is carrying exceeded nodes, with the number of exceeded nodes.
        if (leafNode->wasVisited){

            if (leafNode->numberOfElements() > maxElementsPerLeaf)
                *stream << "\t\t" << "n" << leafNode->getPivot().getOID() << "[label=\"" << leafNode->getBucket().numberOfElements() << "\" fillcolor=gold4, width=\"2.1\", height=\"1.1\"];" << endl;
            else
                *stream << "\t\t" << "n" << leafNode->getPivot().getOID() << "[label=\"" << leafNode->numberOfElements() << "\" fillcolor=forestgreen, width=\"2.1\", height=\"1.1\"];" << endl;

            leafNode->wasVisited = false;

        } else {

            if (leafNode->numberOfElements() > maxElementsPerLeaf)
                *stream << "\t\t" << "n" << leafNode->getPivot().getOID() << "[label=\"" << leafNode->getBucket().numberOfElements() << "\" fillcolor=orange, width=\"2.1\", height=\"1.1\"];" << endl;
            else
                *stream << "\t\t" << "n" << leafNode->getPivot().getOID() << "[label=\"" << leafNode->numberOfElements() << "\" fillcolor=green, width=\"2.1\", height=\"1.1\"];" << endl;
        }
    }
}

template<class DType>
QByteArray View<DType>::prepareGraph(){
    QByteArray a = QByteArray();

    QTextStream stream(&a, QIODevice::ReadWrite);
    stream << "graph {" << endl;

//    stream << "\tsize=\"" << width << "\"," << height << "\";" << endl;
//    stream << "\tsize=\"8,6\";" << endl; // low res
//    stream << "\tsize=\"19.20,10.80\";" << endl; // Full HD
//    stream << "\tsize=\"38.40,21.60\";" << endl; // 4k
//    stream << "\tsize=\"76.80,43.20\";" << endl; // 8K

    stream << "\tsize=\"32,24\";" << endl; // 3200x2400

    stream << "\tratio=fill;" << endl;

    // 44, 3, 1.2
    stream << "\tnode[fontname=\"arial\",fontsize=44,margin=0,width=\"3\", height=\"1.2\", style=filled];" << endl;

    // Extra options
//    stream << "\tnodesep=\".05\";" << endl;
//    stream << "\tranksep=\".1\";" << endl;

    stream << "\tsubgraph cluster17{" << endl;

    graphWalk(this->root, &stream);
    stream << "\t}\n" << "}" << endl;
    stream.flush();

    return a;
}

template<class DType>
QPixmap View<DType>::getPixmap(double width, double height){

    this->width = width;
    this->height = height;

    QProcess p;
    p.setProcessChannelMode(QProcess::MergedChannels);
    p.start("dot", QStringList() << "-Tsvg");
    p.write(prepareGraph());

    QByteArray data;
    QPixmap pixmap;

    while(p.waitForReadyRead(300))
        data.append(p.readAll());

    p.close();

    pixmap.loadFromData(data);

    return pixmap;
}

template<class DType>
QPixmap View<DType>::getPixmap(){

    this->width = width;
    this->height = height;

    QProcess p;
    p.setProcessChannelMode(QProcess::MergedChannels);
    p.start("dot", QStringList() << "-Tpng");
    p.write(prepareGraph());

    QByteArray data;
    QPixmap pixmap;

    while(p.waitForReadyRead(300))
        data.append(p.readAll());

    p.close();

    pixmap.loadFromData(data);

    return pixmap;
}

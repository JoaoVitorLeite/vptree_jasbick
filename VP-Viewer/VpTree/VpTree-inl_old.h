#pragma once

#include <VpTree/VpTree.h>

#undef IMPL_TEMPL
#define IMPL_TEMPL template <class DType, class DistanceFunction>

IMPL_TEMPL VpTree<DType, DistanceFunction>::VpTree(bool balance,
                                                   double threshold,
                                                   uint_fast32_t maxElements,
                                                   PivotSelection::Algorithm algorithm,
                                                   Dataset<DType> *dataset,
                                                   DistanceFunction *df){

    //this->dataset = *dataset;
    this->algorithm = algorithm;

    std::vector<DType> previousPivots;
    std::vector<std::vector<double>> distanceVector;

    root = buildTree(false, threshold, maxElements, previousPivots, distanceVector, dataset, df);

    if (balance) { balanceTree(); }
}

IMPL_TEMPL Node<DType> *VpTree<DType, DistanceFunction>::buildTree(const bool isCircunscribed,
                                                                   const double threshold,
                                                                   const uint_fast32_t maxElements,
                                                                   std::vector<DType> previousPivots,
                                                                   std::vector<std::vector<double>> distanceVector,
                                                                   Dataset<DType> *dataset,
                                                                   DistanceFunction *df){


    const DType pivot = PivotSelection::getPivot(*dataset, algorithm, df);

    const double mu = dataset->medianDistance(pivot, df);

    if (mu > threshold && dataset->getSize() > maxElements){

        DirectorNode<DType> *dirNode = new DirectorNode<DType>;

        dirNode->setPivot(pivot);
        dirNode->setMu(mu);

        //getNodeHistogram(*dataset, pivot, df, dirNode);

        incrementDistanceVector(pivot, previousPivots.back(), &distanceVector, df);
        previousPivots.push_back(pivot);

        Dataset<DType> *innerDataset = new Dataset<DType>;
        Dataset<DType> *outerDataset = new Dataset<DType>;
        splitDataset(pivot, mu, *dataset, innerDataset, outerDataset, df);

        delete(dataset);

        if (innerDataset->getSize() > 0){
            dirNode->setLeftNode(buildTree(true, threshold, maxElements, previousPivots, distanceVector,
                                           innerDataset, df));
        } else {
            delete(innerDataset);
            dirNode->setLeftNode(nullptr);
        }

        if (outerDataset->getSize() > 0){
            dirNode->setRightNode(buildTree(false, threshold, maxElements, previousPivots, distanceVector,
                                            outerDataset, df));
        } else {
            delete(outerDataset);
            dirNode->setRightNode(nullptr);
        }

        return dirNode;

    } else {

        LeafNode<DType> *leaf = new LeafNode<DType>;

        leaf->setCircunscribed(isCircunscribed);
        leaf->setPivot(pivot);
        leaf->setMu(mu);

        incrementDistanceVector(pivot, previousPivots.back(), &distanceVector, df);
        leaf->setDistanceVector(distanceVector);

        previousPivots.push_back(pivot);
        leaf->setPreviousPivots(previousPivots);

        dataset->erase(pivot);

        for (uint_fast32_t i = 0; i < dataset->getSize(); i++){

            leaf->push_back(Pair<DType>(dataset->operator [](i), distanceVector.back()));
        }

        delete(dataset);

        return leaf;
    }
}

IMPL_TEMPL void VpTree<DType, DistanceFunction>::getBucket(const double threshold,
                                                           std::vector<DType> previousPivots,
                                                           std::vector<std::vector<double>> distanceVector,
                                                           Dataset<DType> *dataset,
                                                           DistanceFunction *df,
                                                           Bucket<DType> *bucket){


    srand(time(nullptr));
    const DType pivot = dataset->operator [](rand()% dataset->getCardinality());

    const double mu = dataset->medianDistance(pivot, df);

    if ((mu > threshold) && (dataset->getCardinality() > 1)){

        // Split the dataset in innerDataset (< mu) and outerDataset (>= mu).
        Dataset<DType> *innerDataset = new Dataset<DType>;
        Dataset<DType> *outerDataset = new Dataset<DType>;
        splitDataset(pivot, mu, *dataset, innerDataset, outerDataset, df);

        // Deletes the dataset to save memory.
        delete(dataset);

        // Increments the DistanceVector with a vector of distances for this node.
        incrementDistanceVector(pivot, previousPivots.back(), &distanceVector, df);

        bucket->push_back(Pair<DType>(pivot, distanceVector.back()));

        previousPivots.push_back(pivot);

        // Recursively calls itself with the inner part of the dataset.
        if (innerDataset->getSize() > 0){
            getBucket(threshold, previousPivots, distanceVector, innerDataset, df, bucket);
        } else {
            delete(innerDataset);
        }

        // Recursively calls itself with the outer part of the dataset.
        if (outerDataset->getSize() > 0){
            getBucket(threshold, previousPivots, distanceVector, outerDataset, df, bucket);
        } else {
            delete(outerDataset);
        }

    } else {
        delete(dataset);

        incrementDistanceVector(pivot, previousPivots.back(), &distanceVector, df);

        bucket->push_back(Pair<DType>(pivot, distanceVector.back()));
    }

}

IMPL_TEMPL void VpTree<DType, DistanceFunction>::splitDataset(const DType &pivot,
                                                              const double mu,
                                                              const Dataset<DType> &sourceDataset,
                                                              Dataset<DType> *innerDataset,
                                                              Dataset<DType> *outerDataset,
                                                              DistanceFunction *df){

    const uint_fast32_t cardinality = sourceDataset.getCardinality();

    const u_int32_t pivotOID = pivot.getOID();

    for (uint_fast32_t i = 0; i < cardinality; i++){

        const DType &fv = sourceDataset.getFeatureVector(i);

        if (pivotOID != fv.getOID()){
            if (df->getDistance(pivot, fv) < mu)
                innerDataset->push_back(fv);
            else
                outerDataset->push_back(fv);
        }

    }

    innerDataset->setCardinality(innerDataset->getSize());
    outerDataset->setCardinality(outerDataset->getSize());

    innerDataset->setDimensionality(sourceDataset.getDimensionality());
    outerDataset->setDimensionality(sourceDataset.getDimensionality());
}

IMPL_TEMPL void VpTree<DType, DistanceFunction>::incrementDistanceVector(const DType &pivot, const DType &parentPivot,
                                                                         std::vector<std::vector<double>> *distanceVector,
                                                                         DistanceFunction *df) const{

    std::vector<double> distances;

    if (distanceVector->begin() != distanceVector->end()){

        distances = distanceVector->back();

        const double distanceToParent = df->getDistance(pivot, parentPivot);

        // Increments every element of distances by distanceToParent.
        std::for_each(distances.begin(), distances.end(), [distanceToParent](double &dist){
            dist += distanceToParent;
        });

        distances.push_back(distanceToParent);
    }
    distanceVector->push_back(distances);

}

IMPL_TEMPL int VpTree<DType, DistanceFunction>::getHeight(Node<DType> *node) const{

    if (node == nullptr) return -1;

    DirectorNode<DType> *dirNode = dynamic_cast<DirectorNode<DType>*>(node);

    if (dirNode != nullptr)
        return 1 + std::max(getHeight(dirNode->getLeftNode()), getHeight(dirNode->getRightNode()));
    else
        return 1;
}

IMPL_TEMPL void VpTree<DType, DistanceFunction>::getLeafs(Node<DType> *node, std::vector<LeafNode<DType>*>*leafVec) const{

    if (node != nullptr){

        const DirectorNode<DType> *dirNode = dynamic_cast<DirectorNode<DType>*>(node);

        if (dirNode != nullptr){
            getLeafs(dirNode->getLeftNode(), leafVec);
            getLeafs(dirNode->getRightNode(), leafVec);
        } else {
            leafVec->push_back(dynamic_cast<LeafNode<DType>*>(node));
        }

    }

}

IMPL_TEMPL void VpTree<DType, DistanceFunction>::getDirectorNodes(Node<DType> *node, std::vector<DirectorNode<DType>*> *ids){

    if (node != nullptr){

        DirectorNode<DType> *dirNode = dynamic_cast<DirectorNode<DType>*>(node);

        if (dirNode != nullptr){

            ids->push_back(dirNode);

            getDirectorNodes(dirNode->getLeftNode(), ids);
            getDirectorNodes(dirNode->getRightNode(), ids);
        }

    }

}

IMPL_TEMPL void VpTree<DType, DistanceFunction>::getDirectorNodesByHeight(Node<DType> *node,
        std::vector<std::vector<DirectorNode<DType>*>> *dirVec,
        uint_fast32_t height) const{

    if (node != nullptr){

        DirectorNode<DType> *dirNode = dynamic_cast<DirectorNode<DType>*>(node);

        if (dirNode != nullptr){

            dirVec->at(height).push_back(dirNode);

            getDirectorNodesByHeight(dirNode->getLeftNode(), dirVec, height+1);
            getDirectorNodesByHeight(dirNode->getRightNode(), dirVec, height+1);
        }

    }
}

IMPL_TEMPL void VpTree<DType, DistanceFunction>::getNodeHistogram(const Dataset<DType> &dataset,
                                                                  const DType &pivot,
                                                                  DistanceFunction *df,
                                                                  DirectorNode<DType>* dirNode) const{

    dirNode->setHistogram(PivotHistogram(dataset, pivot, 20, df));
}

IMPL_TEMPL LeafNode<DType> *VpTree<DType, DistanceFunction>::generateBalancedLeaf(uint_fast32_t i, uint_fast32_t j, std::vector<std::vector<DirectorNode<DType>*>> heightList){

    LeafNode<DType> *newLeaf = new LeafNode<DType>;

    newLeaf->setPivot(heightList[i+1][j]->getPivot());
    newLeaf->setMu(heightList[i+1][j]->getMu());
    newLeaf->setCircunscribed(true);

    pushExceededNodes(heightList[i+1][j]->getLeftNode(), newLeaf);
    pushExceededNodes(heightList[i+1][j]->getRightNode(), newLeaf);

    return newLeaf;
}

IMPL_TEMPL void VpTree<DType, DistanceFunction>::balanceTree(){

    int height = getHeight(root);
    std::vector<std::vector<DirectorNode<DType>*>> heightList(height);
    getDirectorNodesByHeight(root, &heightList);

    for (uint_fast32_t i = 0; i < heightList.size()-1; i++){

        // If next height is less than double the size of actual height, the next height is unbalanced.
        if (heightList[i].size()*2 > heightList[i+1].size()){

            // For every node in the unbalanced height.
            for (uint_fast32_t j = 0; j < heightList[i+1].size(); j++){

                // Search for nodes pointing to the unbalanced node and points it to the new node.
                for (uint_fast32_t k = 0; k < heightList[i].size(); k++){

                    if (heightList[i][k]->getLeftNode() == heightList[i+1][j])
                        heightList[i][k]->setLeftNode(generateBalancedLeaf(i, j, heightList));

                    if (heightList[i][k]->getRightNode() == heightList[i+1][j])
                        heightList[i][k]->setRightNode(generateBalancedLeaf(i, j, heightList));
                }
            }

            break;
        }
    }
}

IMPL_TEMPL void VpTree<DType, DistanceFunction>::pushExceededNodes(Node<DType> *node,
                                                                   LeafNode<DType> *newLeaf){

    if (node == nullptr) return;

    newLeaf->push_exceeded_node(node);

    DirectorNode<DType> *dirNode = dynamic_cast<DirectorNode<DType>*>(node);

    if (dirNode != nullptr){

        pushExceededNodes(dirNode->getLeftNode(), newLeaf);
        pushExceededNodes(dirNode->getRightNode(), newLeaf);

    } else {

        LeafNode<DType> *leafNode = static_cast<LeafNode<DType>*>(node);

        for (uint_fast32_t i = 0; i < leafNode->getBucket().numberOfElements(); i++){
            newLeaf->push_back(leafNode->getPair(i));
        }
    }
}

/**
 *@brief A getter to the root.
 *@returns a pointer to the root of the tree
 */
IMPL_TEMPL Node<DType> *VpTree<DType, DistanceFunction>::getRoot() const{ return root; }

IMPL_TEMPL void VpTree<DType, DistanceFunction>::rangeQuery(const DType &qElement,
                                                            double radius,
                                                            Node<DType> *node,
                                                            Dataset<DType> *answer,
                                                            DistanceFunction *df){


     if (node == nullptr) return;
     node->wasVisited = true;

     if (df->getDistance(qElement, node->getPivot()) <= radius)
         answer->push_back(node->getPivot());

     LeafNode<DType> *leaf = dynamic_cast<LeafNode<DType>*>(node);

     if (leaf != nullptr) {

         for (uint_fast32_t i = 0; i < leaf->numberOfElements(); i++){

             if (df->getDistance(qElement, leaf->getPair(i).first()) <= radius)
                 answer->push_back(leaf->getPair(i).first());
         }

     } else {

        double dist = df->getDistance(node->getPivot(), qElement);

        DirectorNode<DType> *dirNode = dynamic_cast<DirectorNode<DType>*>(node);

        if (dist < node->getMu()) {

            if ((dist - radius) <= node->getMu())
                rangeQuery(qElement, radius, dirNode->getLeftNode(), answer, df);

            if ((dist + radius) >= node->getMu())
                rangeQuery(qElement, radius, dirNode->getRightNode(), answer, df);

        } else {

            if ((dist + radius) >= node->getMu())
                rangeQuery(qElement, radius, dirNode->getRightNode(), answer, df);

            if ((dist - radius) <= node->getMu())
                rangeQuery(qElement, radius, dirNode->getLeftNode(), answer, df);
        }

     }

}

IMPL_TEMPL void VpTree<DType, DistanceFunction>::kNNWalk(const DType &qElement,
                                                         double &tau,
                                                         uint_fast32_t k,
                                                         Node<DType> *node,
                                                         std::priority_queue<QueueItem<DType>> *queue,
                                                         DistanceFunction *df){

    node->wasVisited = true;

    LeafNode<DType> *leaf = dynamic_cast<LeafNode<DType>*>(node);

    if (leaf != nullptr) {

        for (uint_fast32_t i = 0; i < leaf->numberOfElements(); i++){

            double dist = df->getDistance(qElement, leaf->getPair(i).first());
            queue->push(QueueItem<DType>(dist, leaf->getPair(i).first()));

            if (queue->size() > k)
                queue->pop();
        }

    } else {

        DirectorNode<DType> *dirNode = dynamic_cast<DirectorNode<DType>*>(node);

        double dist = df->getDistance(dirNode->getPivot(), qElement);

        if (dist <= tau){

            queue->push(QueueItem<DType>(dist, dirNode->getPivot()));

            while (queue->size() > k)
                queue->pop();

            if (queue->size() == k)
                tau = queue->top().dist;
        }

        if (dist < node->getMu()){

            if ((dist - tau <= dirNode->getMu()) && dirNode->getLeftNode() != nullptr)
                kNNWalk(qElement, tau, k, dirNode->getLeftNode(), queue, df);

            if ((dist + tau >= dirNode->getMu()) && dirNode->getRightNode() != nullptr)
                kNNWalk(qElement, tau, k, dirNode->getRightNode(), queue, df);

        } else {

            if ((dist + tau >= dirNode->getMu()) && dirNode->getRightNode() != nullptr)
                kNNWalk(qElement, tau, k, dirNode->getRightNode(), queue, df);

            if ((dist - tau <= node->getMu()) && dirNode->getLeftNode() != nullptr)
                kNNWalk(qElement, tau, k, dirNode->getLeftNode(), queue, df);

        }

    }
}

IMPL_TEMPL void VpTree<DType, DistanceFunction>::kNN(const DType &qElement,
                                                     uint_fast32_t k,
                                                     Node<DType> *node,
                                                     Dataset<DType> *answer,
                                                     DistanceFunction *df){


    std::priority_queue<QueueItem<DType>> queue;

    double tau = std::numeric_limits<double>::infinity();

    kNNWalk(qElement, tau, k, node, &queue, df);

    std::vector<DType> result;

    result.reserve(k);
    for (uint_fast32_t i = 0; i < k; i++){
        result.push_back(queue.top().featureVector);
        queue.pop();
    }

    answer->reserve(k);
    for (int i = k-1; i >= 0; i--)
        answer->push_back(result[i]);

}

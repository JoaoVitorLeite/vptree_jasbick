#pragma once

#include <VpTree/VpTree.h>

#undef IMPL_TEMPL
#define IMPL_TEMPL template <class ObjectType, class DistanceFunction>

IMPL_TEMPL VpTree<ObjectType, DistanceFunction>::VpTree(bool balance, size_t maxElements,
    PivotSelection::Algorithm algorithm, Dataset<ObjectType> *dataset, DistanceFunction *df){

    this->algorithm = algorithm;

    root = buildTree(maxElements, dataset, df);

    if (balance) { balanceTree(); }
}

IMPL_TEMPL Node<ObjectType> *VpTree<ObjectType, DistanceFunction>::buildTree(size_t maxElements,
    Dataset<ObjectType> *dataset, DistanceFunction *df){

    ObjectType &pivot = PivotSelection::getPivot(*dataset, algorithm, df);

    std::vector<double> *distances = new std::vector<double>();
    dataset->getDistanceVector(pivot, distances, df);

    if (distances->size() > 1){
        auto iterator = std::find(distances->begin(), distances->end(), 0);
        if (iterator != distances->end()){
            distances->erase(iterator); // erases d(p,p)
            distances->shrink_to_fit(); // resize after erase
        }
    }

    auto minmax = std::minmax_element(distances->begin(), distances->end());
    double min = *minmax.first;
    double max = *minmax.second;

    double mu = MathFunctions::medianDistance(*distances);

    delete(distances);

    if (dataset->getSize() > maxElements){

        DirectorNode<ObjectType> *dirNode = new DirectorNode<ObjectType>;
        dirNode->setPivot(pivot);
        dirNode->setMu(mu);
        dirNode->setMin(min);
        dirNode->setMax(max);

//        dataset->erase(pivot);

        Dataset<ObjectType> *innerDataset = new Dataset<ObjectType>();
        Dataset<ObjectType> *outerDataset = new Dataset<ObjectType>();
        splitDataset(pivot, mu, *dataset, innerDataset, outerDataset, df);

        delete(dataset);

        size_t innerDatasetSize = innerDataset->getSize();
        size_t outerDatasetSize = outerDataset->getSize();

        /*
         * NOTE:
         * The first "if" is a way to prevent a deadlock. If one dataset is empty and the other is not,
         * the code would again call buildTree with the same dataset that it received, resulting in a deadlock.
         */
        if ((outerDatasetSize == 0) && (innerDatasetSize > 0)){
            dirNode->setLeftNode(buildTree(INT_MAX, innerDataset, df));
        } else if (innerDatasetSize > 0){
            dirNode->setLeftNode(buildTree(maxElements, innerDataset, df));
        } else {
            delete(innerDataset);
            dirNode->setLeftNode(nullptr);
        }

        if ((innerDatasetSize == 0) && (outerDatasetSize > 0)){
            dirNode->setRightNode(buildTree(INT_MAX, outerDataset, df));
        } else if (outerDatasetSize > 0){
            dirNode->setRightNode(buildTree(maxElements, outerDataset, df));
        } else {
            delete(outerDataset);
            dirNode->setRightNode(nullptr);
        }

//        if (innerDataset->getSize() > 0){
//            dirNode->setLeftNode(buildTree(maxElements, innerDataset, df));
//        } else {
//            delete(innerDataset);
//            dirNode->setLeftNode(nullptr);
//        }

//        if (outerDataset->getSize() > 0){
//            dirNode->setRightNode(buildTree(maxElements, outerDataset, df));
//        } else {
//            delete(outerDataset);
//            dirNode->setRightNode(nullptr);
//        }

        return dirNode;

    } else {

        LeafNode<ObjectType> *leaf = new LeafNode<ObjectType>;

        leaf->setPivot(pivot);
        leaf->setMu(mu);
        leaf->setMin(min);
        leaf->setMax(max);

//        dataset->erase(pivot);

        size_t dataset_size = dataset->getSize();
        std::vector<OrdinalObject<ObjectType> *> queue;

        for (size_t i = 0; i < dataset_size; i++){

            ObjectType &element = dataset->operator[](i);
            double dist = df->getDistance(element, pivot);
            queue.push_back(new OrdinalObject<ObjectType>(dist, element));
        }

        std::sort(queue.begin(), queue.end());

        for (size_t i = 0; i < dataset_size; i++)
            leaf->push_back(*(queue[i]->featureVector), queue[i]->dist);

        delete(dataset);

        return leaf;
    }
}

IMPL_TEMPL void VpTree<ObjectType, DistanceFunction>::splitDataset(ObjectType &pivot,
    double mu, Dataset<ObjectType> &sourceDataset, Dataset<ObjectType> *innerDataset,
    Dataset<ObjectType> *outerDataset, DistanceFunction *df){

    size_t cardinality = sourceDataset.getCardinality();

    for (size_t i = 0; i < cardinality; i++){

        ObjectType &fv = sourceDataset[i];

        if (df->getDistance(pivot, fv) < mu)
            innerDataset->push_back(fv);
        else
            outerDataset->push_back(fv);

    }

    innerDataset->setCardinality(innerDataset->getSize());
    outerDataset->setCardinality(outerDataset->getSize());

    innerDataset->setDimensionality(sourceDataset.getDimensionality());
    outerDataset->setDimensionality(sourceDataset.getDimensionality());
}

IMPL_TEMPL int VpTree<ObjectType, DistanceFunction>::getHeight(Node<ObjectType> *node){

    if (node == nullptr) return -1;

    DirectorNode<ObjectType> *dirNode = dynamic_cast<DirectorNode<ObjectType>*>(node);

    if (dirNode != nullptr)
        return 1 + std::max(getHeight(dirNode->getLeftNode()), getHeight(dirNode->getRightNode()));
    else
        return 1;
}

IMPL_TEMPL void VpTree<ObjectType, DistanceFunction>::getLeafs(Node<ObjectType> *node,
    std::vector<LeafNode<ObjectType>*>*leafVec){

    if (node != nullptr){

        DirectorNode<ObjectType> *dirNode = dynamic_cast<DirectorNode<ObjectType>*>(node);

        if (dirNode != nullptr){
            getLeafs(dirNode->getLeftNode(), leafVec);
            getLeafs(dirNode->getRightNode(), leafVec);
        } else {
            leafVec->push_back(dynamic_cast<LeafNode<ObjectType>*>(node));
        }

    }

}

IMPL_TEMPL void VpTree<ObjectType, DistanceFunction>::getDirectorNodes(Node<ObjectType> *node,
    std::vector<DirectorNode<ObjectType>*> *ids){

    if (node != nullptr){

        DirectorNode<ObjectType> *dirNode = dynamic_cast<DirectorNode<ObjectType>*>(node);

        if (dirNode != nullptr){

            ids->push_back(dirNode);

            getDirectorNodes(dirNode->getLeftNode(), ids);
            getDirectorNodes(dirNode->getRightNode(), ids);
        }

    }

}

IMPL_TEMPL void VpTree<ObjectType, DistanceFunction>::getDirectorNodesByHeight(Node<ObjectType> *node,
    std::vector<std::vector<DirectorNode<ObjectType>*>> *dirVec, size_t height){

    if (node != nullptr){

        DirectorNode<ObjectType> *dirNode = dynamic_cast<DirectorNode<ObjectType>*>(node);

        if (dirNode != nullptr){

            dirVec->at(height).push_back(dirNode);

            getDirectorNodesByHeight(dirNode->getLeftNode(), dirVec, height+1);
            getDirectorNodesByHeight(dirNode->getRightNode(), dirVec, height+1);
        }

    }
}

IMPL_TEMPL LeafNode<ObjectType> *VpTree<ObjectType, DistanceFunction>::generateBalancedLeaf(size_t i, size_t j,
    std::vector<std::vector<DirectorNode<ObjectType>*>> heightList){

    LeafNode<ObjectType> *newLeaf = new LeafNode<ObjectType>;

    newLeaf->setPivot(heightList[i+1][j]->getPivot());
    newLeaf->setMu(heightList[i+1][j]->getMu());
    //newLeaf->setCircunscribed(true);

    pushExceededNodes(heightList[i+1][j]->getLeftNode(), newLeaf);
    pushExceededNodes(heightList[i+1][j]->getRightNode(), newLeaf);

    return newLeaf;
}

IMPL_TEMPL void VpTree<ObjectType, DistanceFunction>::balanceTree(){

    int height = getHeight(root);
    std::vector<std::vector<DirectorNode<ObjectType>*>> heightList(height);
    getDirectorNodesByHeight(root, &heightList);

    for (size_t i = 0; i < heightList.size()-1; i++){

        // If next height is less than double the size of actual height, the next height is unbalanced.
        if (heightList[i].size()*2 > heightList[i+1].size()){

            // For every node in the unbalanced height.
            for (size_t j = 0; j < heightList[i+1].size(); j++){

                // Search for nodes pointing to the unbalanced node and points it to the new node.
                for (size_t k = 0; k < heightList[i].size(); k++){

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

IMPL_TEMPL void VpTree<ObjectType, DistanceFunction>::pushExceededNodes(Node<ObjectType> *node,
    LeafNode<ObjectType> *newLeaf){

    if (node == nullptr) return;

    newLeaf->push_exceeded_node(node);

    DirectorNode<ObjectType> *dirNode = dynamic_cast<DirectorNode<ObjectType>*>(node);

    if (dirNode != nullptr){

        pushExceededNodes(dirNode->getLeftNode(), newLeaf);
        pushExceededNodes(dirNode->getRightNode(), newLeaf);

    } else {

        LeafNode<ObjectType> *leafNode = static_cast<LeafNode<ObjectType>*>(node);

//        newLeaf->setBucket(leafNode->getBucket());

        for (size_t i = 0; i < leafNode->numberOfElements(); i++){
            newLeaf->push_back(leafNode->operator[](i), leafNode->distance_at(i));
        }
    }
}
IMPL_TEMPL Node<ObjectType> *VpTree<ObjectType, DistanceFunction>::getRoot(){ return root; }

IMPL_TEMPL void VpTree<ObjectType, DistanceFunction>::rangeQuery(ObjectType &qElement,
    double radius, Node<ObjectType> *node, Dataset<ObjectType> *answer, DistanceFunction *df){

     ObjectType &pivot = node->getPivot();

     double dist_p_sq = df->getDistance(pivot, qElement);

//     if (dist_p_sq <= radius)
//         answer->push_back(pivot);

     LeafNode<ObjectType> *leaf = dynamic_cast<LeafNode<ObjectType>*>(node);

     if (leaf != nullptr) {

         size_t numberOfElements = leaf->numberOfElements();

         for (size_t i = 0; i < numberOfElements; i++){

             ObjectType &s_i = leaf->operator[](i);
             double dist_p_si = leaf->distance_at(i);
             double lim_inf = std::abs(dist_p_si - dist_p_sq);
             double lim_sup = dist_p_si + dist_p_sq;

             // Talvez
             if (lim_inf <= radius){

                 // Sim
                 if (lim_sup <= radius)
                    answer->push_back(s_i);
                 // Talvez
                 else if (df->getDistance(qElement, s_i) <= radius)
                    answer->push_back(s_i);
             }

         }

     } else {

        DirectorNode<ObjectType> *dirNode = static_cast<DirectorNode<ObjectType>*>(node);

        double mu = node->getMu();

        if (dist_p_sq < mu) {

            if (dirNode->getLeftNode() != nullptr && ((dist_p_sq - radius) <= mu))
                rangeQuery(qElement, radius, dirNode->getLeftNode(), answer, df);

            if (dirNode->getRightNode() != nullptr && ((dist_p_sq + radius) >= mu))
                rangeQuery(qElement, radius, dirNode->getRightNode(), answer, df);

        } else {

            if (dirNode->getRightNode() != nullptr && ((dist_p_sq + radius) >= mu))
                rangeQuery(qElement, radius, dirNode->getRightNode(), answer, df);

            if (dirNode->getLeftNode() != nullptr && ((dist_p_sq - radius) <= mu))
                rangeQuery(qElement, radius, dirNode->getLeftNode(), answer, df);
        }

     }

}

IMPL_TEMPL void VpTree<ObjectType, DistanceFunction>::buildBlockVector(ObjectType &qElement, double &tau,
    Node<ObjectType> *node, OrdinalBlockVector *block_vector, DistanceFunction *df, double minDist, double maxDist){

    ObjectType &pivot = node->getPivot();
    double dist_p_sq = df->getDistance(pivot, qElement);
    double mu = node->getMu();
    double min = node->getMin();
    double max = node->getMax();

    LeafNode<ObjectType> *leaf = dynamic_cast<LeafNode<ObjectType>*>(node);

    if (leaf != nullptr){

        block_vector->push_back(OrdinalBlock<ObjectType>(minDist, maxDist, leaf->getBucket()));

    } else {
        DirectorNode<ObjectType> *dirNode = dynamic_cast<DirectorNode<ObjectType>*>(node);

        // Dentro da bola
        if (dist_p_sq - tau < mu){

            std::cout << "a" << std::endl;

            // Dentro
            if (dirNode->getLeftNode() != nullptr && (dist_p_sq + tau >= min))
                buildBlockVector(qElement, tau, dirNode->getLeftNode(), block_vector, df, 0, mu + dist_p_sq);

            // Anel
            if (dirNode->getRightNode() != nullptr && (dist_p_sq + tau > mu))
                buildBlockVector(qElement, tau, dirNode->getRightNode(), block_vector, df, std::fabs(mu - dist_p_sq), max + dist_p_sq);

        }
        // Dentro do anel
        else if (dist_p_sq + tau <= max){

            std::cout << "b" << std::endl;

            // Dentro
            if (dirNode->getLeftNode() != nullptr && (dist_p_sq - tau < mu))
                buildBlockVector(qElement, tau, dirNode->getLeftNode(), block_vector, df, std::fabs(dist_p_sq - mu), dist_p_sq + mu);

            // Anel
            if (dirNode->getRightNode() != nullptr && (dist_p_sq - tau >= mu))
                buildBlockVector(qElement, tau, dirNode->getRightNode(), block_vector, df, 0, dist_p_sq + max);

        }
        // Fora da partição
        else {

            std::cout << "c" << std::endl;

            // Dentro
            if (dirNode->getLeftNode() != nullptr && (dist_p_sq - tau < mu))
                buildBlockVector(qElement, tau, dirNode->getLeftNode(), block_vector, df, std::fabs(dist_p_sq - mu), dist_p_sq + mu);

            // Anel
            if (dirNode->getRightNode() != nullptr && (dist_p_sq - tau <= max))
                buildBlockVector(qElement, tau, dirNode->getRightNode(), block_vector, df, std::fabs(dist_p_sq - max), dist_p_sq + max);

        }

    }

}

IMPL_TEMPL void VpTree<ObjectType, DistanceFunction>::kNNIncremental(ObjectType &qElement, double &tau,
    size_t k, Node<ObjectType> *node, std::vector<ObjectType *> *results, DistanceFunction *df){

    OrdinalBlockVector block_vector;
    buildBlockVector(qElement, tau, node, &block_vector, df, 0, 0);
    std::sort(block_vector.begin(), block_vector.end());

    OrdinalObjectVector object_vector;

    size_t i = 0;
    while (i < k){
//        if (object_vector.size() > 0)
//            std::cout << object_vector[0].dist << " - " << block_vector[0].min << std::endl;
//            std::cout << block_vector.size() << std::endl;

        for (size_t j = 0; j < object_vector.size(); j++){
            if (object_vector[j].dist < block_vector[0].min){
                results->push_back(object_vector[j].featureVector);
                object_vector.erase(object_vector.begin() + j);
                object_vector.shrink_to_fit();
                --j;
                ++i;
            }
        }

        if (i < k){
            Dataset<ObjectType> dataset = block_vector[0].getDataset();
            size_t dataset_size = dataset.getSize();
            for (size_t j = 0; j < dataset_size; j++){
                ObjectType &element = dataset[j];
                object_vector.push_back(OrdinalObject<ObjectType>(df->getDistance(qElement, element), element));
            }
            std::sort(object_vector.begin(), object_vector.end());
            block_vector.erase(block_vector.begin());
            block_vector.shrink_to_fit();
        }
    }

}

IMPL_TEMPL void VpTree<ObjectType, DistanceFunction>::kNNWalk(ObjectType &qElement, double &tau,
    size_t k, Node<ObjectType> *node, std::priority_queue<OrdinalObject<ObjectType>> *queue, DistanceFunction *df){

    ObjectType &pivot = node->getPivot();

    double dist_p_sq = df->getDistance(pivot, qElement);

//    if (dist_p_sq <= tau){

//        if (queue->size() == k) queue->pop();
//        queue->push(OrdinalObject<ObjectType>(dist_p_sq, pivot));
//        if (queue->size() == k) tau = queue->top().dist;
//    }

    LeafNode<ObjectType> *leaf = dynamic_cast<LeafNode<ObjectType>*>(node);

    if (leaf != nullptr) {

        size_t numberOfElements = leaf->numberOfElements();

        for (size_t i = 0; i < numberOfElements; i++){

            ObjectType &s_i = leaf->operator[](i);
            double dist_p_si = leaf->distance_at(i);
            double lim_inf = std::abs(dist_p_si - dist_p_sq);
            double lim_sup = dist_p_si + dist_p_sq;

            // Talvez
            if (lim_inf <= tau){

                // Sim
                if (lim_sup <= tau){

                    if (queue->size() == k) queue->pop();
                    queue->push(OrdinalObject<ObjectType>(df->getDistance(qElement, s_i), s_i));
                    if (queue->size() == k) tau = queue->top().dist;

                // Talvez
                } else {

                    double dist_sq_si = df->getDistance(qElement, s_i);

                    if (dist_sq_si <= tau){

                        if (queue->size() == k) queue->pop();
                        queue->push(OrdinalObject<ObjectType>(dist_sq_si, s_i));
                        if (queue->size() == k) tau = queue->top().dist;
                    }
                }
            }
        }

    } else {

        DirectorNode<ObjectType> *dirNode = dynamic_cast<DirectorNode<ObjectType>*>(node);

        if (dist_p_sq < node->getMu()){

            if (dirNode->getLeftNode() != nullptr && (dist_p_sq - tau <= dirNode->getMu()))
                kNNWalk(qElement, tau, k, dirNode->getLeftNode(), queue, df);

            if (dirNode->getRightNode() != nullptr && (dist_p_sq + tau >= dirNode->getMu()))
                kNNWalk(qElement, tau, k, dirNode->getRightNode(), queue, df);

        } else {

            if (dirNode->getRightNode() != nullptr && (dist_p_sq + tau >= dirNode->getMu()))
                kNNWalk(qElement, tau, k, dirNode->getRightNode(), queue, df);

            if (dirNode->getLeftNode() != nullptr && (dist_p_sq - tau <= dirNode->getMu()))
                kNNWalk(qElement, tau, k, dirNode->getLeftNode(), queue, df);

        }

    }
}

IMPL_TEMPL void VpTree<ObjectType, DistanceFunction>::kNN(ObjectType &qElement, size_t k, Node<ObjectType> *node,
    Dataset<ObjectType> *answer, DistanceFunction *df, bool isIncremental){

    double tau = std::numeric_limits<double>::infinity();

    if (isIncremental){
        std::vector<ObjectType *> results;

        kNNIncremental(qElement, tau, k, node, &results, df);

        answer->reserve(k);
        for (int i = 0; i < k; i++)
            answer->push_back(*results[i]);

    } else {

        std::priority_queue<OrdinalObject<ObjectType>> queue;

        kNNWalk(qElement, tau, k, node, &queue, df);

        std::vector<ObjectType *> result;

        result.reserve(k);
        for (size_t i = 0; i < k; i++){
            result.push_back(queue.top().featureVector);
            queue.pop();
        }

        answer->reserve(k);
        for (int i = k-1; i >= 0; i--)
            answer->push_back(*result[i]);
    }

}

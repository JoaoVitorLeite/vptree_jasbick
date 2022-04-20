#pragma once

#include <queue>
#include <VpTree/OrdinalObject.h>
#include <Dataset/Dataset.h>
#include <VpTree/Node/LeafNode.h>
#include <VpTree/Node/DirectorNode.h>
#include <PivotSelection/PivotSelection.h>
#include <MathFunctions/Math.h>
#include <climits>

template <class ObjectType, class DistanceFunction>
class VpTree{

    typedef std::vector<OrdinalObject<ObjectType>> OrdinalObjectVector;
    typedef std::vector<OrdinalBlock<ObjectType>> OrdinalBlockVector;

    private:
        Node<ObjectType> *root;
        PivotSelection::Algorithm algorithm;

        Node<ObjectType> *buildTree(size_t maxElements, Dataset<ObjectType> *dataset, DistanceFunction *df);

        void balanceTree();

        LeafNode<ObjectType> *generateBalancedLeaf(size_t i, size_t j,
            std::vector<std::vector<DirectorNode<ObjectType>*>> heightList);

        void pushExceededNodes(Node<ObjectType> *node, LeafNode<ObjectType> *newLeaf);

        static void buildBlockVector(ObjectType &qElement, double &tau, Node<ObjectType> *node,
            OrdinalBlockVector *block_queue, DistanceFunction *df, double minDist, double maxDist);

        static void kNNIncremental(ObjectType &qElement, double &tau, size_t k, Node<ObjectType> *node,
            std::vector<ObjectType *> *result, DistanceFunction *df);

        static void kNNWalk(ObjectType &qElement, double &tau, size_t k, Node<ObjectType> *node,
            std::priority_queue<OrdinalObject<ObjectType> > *queue, DistanceFunction *df);

    public:
        VpTree(bool balance, size_t maxElements, PivotSelection::Algorithm algorithm,
            Dataset<ObjectType> *dataset, DistanceFunction * df);

        ~VpTree(){ delete(root); root = nullptr; }

        static void kNN(ObjectType &qElement, size_t k, Node<ObjectType> *node, Dataset<ObjectType> *answer,
            DistanceFunction * df, bool isIncremental);

        static void rangeQuery(ObjectType &qElement, double radius, Node<ObjectType> *node,
            Dataset<ObjectType> *answer, DistanceFunction *df);

        static void splitDataset(ObjectType &pivot, double mu, Dataset<ObjectType> &sourceDataset,
            Dataset<ObjectType> *innerDataset, Dataset<ObjectType> *outerDataset, DistanceFunction *df);

        int getHeight(Node<ObjectType> *node);

        void getLeafs(Node<ObjectType> *node, std::vector<LeafNode<ObjectType>*> *vec);

        void getDirectorNodes(Node<ObjectType> *node, std::vector<DirectorNode<ObjectType> *> *ids);

        void getDirectorNodesByHeight(Node<ObjectType> *node,
            std::vector<std::vector<DirectorNode<ObjectType>*>> *dirVec, size_t height=0);

        Node<ObjectType> *getRoot();
};

#include <VpTree/VpTree-inl.h>

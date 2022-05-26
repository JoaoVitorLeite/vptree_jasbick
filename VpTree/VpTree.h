#pragma once

#include <queue>
#include <VpTree/QueueItem.h>
#include <Dataset/Dataset.h>
#include <VpTree/Node/LeafNode.h>
#include <VpTree/Node/DirectorNode.h>
#include <PivotSelection/PivotSelection.h>
#include <QProgressBar>
#include <QObject>

class SignalsAndSlots: public QObject{
    Q_OBJECT

    signals:
        void progressBarValueChanged(int newValue);
};

template <class DType, class DistanceFunction>
class VpTree: public SignalsAndSlots{

    private:
        Node<DType> *root;
        Dataset<DType> dataset;
        PivotSelection::Algorithm algorithm;
        uint_fast32_t progress = 0;

        Node<DType> *buildTree(const bool isCircunscribed,
                               const double threshold,
                               const uint_fast32_t maxElements,
                               std::vector<DType> previousPivots,
                               std::vector<std::vector<double>> distanceVector,
                               Dataset<DType> *dataset,
                               DistanceFunction * df,
                               QProgressBar *progressBar);

        void getBucket(const double threshold,
                       std::vector<DType> previousPivots,
                       std::vector<std::vector<double>> distanceVector,
                       Dataset<DType> *dataset,
                       DistanceFunction * df,
                       Bucket<DType>* bucket,
                       QProgressBar *progressBar);

        void incrementDistanceVector(const DType &pivot,
                                     const DType &parentPivot,
                                     std::vector<std::vector<double>> *distanceVector,
                                     DistanceFunction * df) const;

        void getNodeHistogram(const Dataset<DType> &dataset,
                              const DType &pivot,
                              DistanceFunction * df,
                              DirectorNode<DType>* dirNode) const;

        void balanceTree();

        LeafNode<DType> *generateBalancedLeaf(uint_fast32_t i,
                                              uint_fast32_t j,
                                              std::vector<std::vector<DirectorNode<DType>*>> heightList);

        void pushExceededNodes(Node<DType> *node, LeafNode<DType> *newLeaf);

        bool nodeCmpFromPtr(Node<DType> *n1, Node<DType> *n2);
        auto checkSqPosition(double dist, double mu, double max);
        void setLeftRightMinMax(const DType &qElement, DirectorNode<DType> *dirNode, DistanceFunction *df);

        void kNNIncWalk(const DType &qElement,
                      uint_fast32_t k,
                      Node<DType> *node,
                      std::priority_queue<QueueItem<DType>,
                                          std::vector<QueueItem<DType>>,
                                          std::greater<QueueItem<DType>>> *queue,
                      DistanceFunction *df);

        void kNNWalk(const DType &qElement,
                        double &tau,
                        uint_fast32_t k,
                        Node<DType> *node,
                        std::priority_queue<QueueItem<DType>,
                                            std::vector<QueueItem<DType>>,
                                            std::less<QueueItem<DType>>> *queue,
                        DistanceFunction *df);

        void updateProgress(QProgressBar *progressBar);

    public:
        VpTree(bool balance,
               const double paramThreshold,
               const uint_fast32_t maxElements,
               PivotSelection::Algorithm algorithm,
               Dataset<DType> *dataset,
               DistanceFunction * df,
               QProgressBar *progressBar);

        ~VpTree(){ delete(root); root = nullptr; }

        void kNN(const DType &qElement,
                 uint_fast32_t k,
                 Node<DType> *node,
                 Dataset<DType> *answer,
                 DistanceFunction * df);

        void kNNInc(const DType &qElement,
                    uint_fast32_t k,
                    Node<DType> *node,
                    Dataset<DType> *answer,
                    DistanceFunction * df);

        void rangeQuery(const DType &qElement,
                        double radius,
                        Node<DType> *node,
                        Dataset<DType> *answer,
                        DistanceFunction * df);

        static void splitDataset(const DType &pivot,
                          const double mu,
                          const Dataset<DType> &sourceDataset,
                          Dataset<DType> *innerDataset,
                          Dataset<DType> *outerDataset,
                          DistanceFunction * df);

        uint_fast32_t getHeight(Node<DType> *node) const;

        void getLeafs(Node<DType> *node, std::vector<LeafNode<DType>*> *vec) const;

        void getDirectorNodes(Node<DType> *node, std::vector<DirectorNode<DType> *> *ids);

        void getDirectorNodesByHeight(Node<DType> *node,
                                      std::vector<std::vector<DirectorNode<DType>*>> *dirVec,
                                      uint_fast32_t height=0) const;

        Node<DType> *getRoot() const;
};

#include <VpTree/VpTree-inl.h>

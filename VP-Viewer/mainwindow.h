#pragma once

#include <VpTree/VpTree.h>
#include <VpTree/View.h>
#include <Distance/EuclideanDistance.h>
#include <Distance/ManhattanDistance.h>
#include <Distance/EditDistance.h>
#include <QProgressBar>
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include <QSpinBox>
#include <QComboBox>
#include <QStringList>
#include <QtConcurrent/QtConcurrent>
#include <QApplication>
#include <QtCharts>
#include <stack>

Q_DECLARE_METATYPE(DirectorNode<InstanceDouble>)
Q_DECLARE_METATYPE(DirectorNode<InstanceString>)
Q_DECLARE_METATYPE(Node<InstanceDouble>)
Q_DECLARE_METATYPE(Node<InstanceString>)
Q_DECLARE_METATYPE(InstanceDouble)
Q_DECLARE_METATYPE(InstanceString)

typedef VpTree<InstanceDouble, EuclideanDistance<InstanceDouble>> TreeEuclidean;
typedef VpTree<InstanceDouble, ManhattanDistance<InstanceDouble>> TreeManhattan;
typedef VpTree<InstanceString, EditDistance<InstanceString>> TreeEdit;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnGenerate_clicked();
    void on_btnReset_clicked();
    void on_btnFileDialog_clicked();
    void on_btnQuery_clicked();
    void on_btnResetQuery_clicked();
    void on_btnChangeStackedWidget_clicked();

    void on_cbxNodesID_selected();

    void scaleImage(int newValue);

private:
    Ui::MainWindow *ui;

    double maxDist;

    QPixmap fullSizeTreePixmap;
    QPixmap* paintedTreePixmap = nullptr;

    TreeEuclidean *euclideanTree = nullptr;
    TreeManhattan *manhattanTree = nullptr;
    TreeEdit *editTree = nullptr;

    QStringList availableDistances();

    void lockButtons();
    void unlockButtons();

    void setupCbxDistanceFunction();
    void setupCbxPivotType();
    void setupCbxBalance();
    void setupProgressBar();
    void setupCbxQueryAlgorithm();
    void setupNodesID(TreeEuclidean *vpt);
    void setupNodesID(TreeManhattan *vpt);
    void setupNodesID(TreeEdit *vpt);
    void setupElementsToQuery(DatasetDouble *dataset);
    void setupElementsToQuery(DatasetString *dataset);
    void setupLabelsForCharVec();
    void setupLabelsForDoubles();

    void generateEuclidean();
    void generateManhattan();
    void generateEdit();

    void generateHistogram(DirectorNode<InstanceDouble> node);
    void generateHistogram(DirectorNode<InstanceString> node);

    void generateDistCalcHistogram(DistanceFunction<InstanceDouble> *df);
    void generateDistCalcHistogram(DistanceFunction<InstanceString> *df);

    PivotSelection::Algorithm getAlgorithm();

    void buildImageEuclidean();
    void buildImageManhattan();
    void buildImageEdit();

    void euclideanQuery();
    void manhattanQuery();
    void editQuery();

    void sortRangeQueryByOID(Dataset<InstanceDouble> *answer);
    void sortRangeQueryByOID(Dataset<InstanceString> *answer);

    void resetTrees();

    void updateEuclideanPixmap();
    void updateManhattanPixmap();
    void updateEditPixmap();
};

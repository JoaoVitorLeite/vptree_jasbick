#pragma once

#include <VpTree/VpTree.h>
#include <VpTree/View.h>
#include <Distance/EuclideanDistance.h>
#include <Distance/ManhattanDistance.h>
#include <Distance/EditDistance.h>
#include <Distance/BrayCurtisDistance.h>
#include <Distance/CanberraDistance.h>
#include <Distance/ChebyshevDistance.h>
#include <Distance/ColorLayoutDistance.h>
#include <Distance/DTWDistance.h>
#include <Distance/JeffreyDivergenceDistance.h>
#include <Distance/KullbackLeiblerDivergenceDistance.h>
#include <Distance/MetricHistogramDistance.h>
#include <Distance/MorositaDistance.h>
#include <Distance/QuiSquareDistance.h>
#include <Distance/SpearmanDistance.h>
#include <Distance/SquaredChordDistance.h>
#include <Distance/SumProductDistance.h>
#include <Distance/WarpDistance.h>
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

typedef VpTree<InstanceDouble, DistanceFunction<InstanceDouble>> TreeInstanceDouble;
typedef VpTree<InstanceString, DistanceFunction<InstanceString>> TreeInstanceString;

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

    void on_cbxNodesIDSelected();

    void scaleImage(int newValue);

private:
    Ui::MainWindow *ui;

    QPixmap fullSizeTreePixmap;
    QPixmap* paintedTreePixmap = nullptr;

    TreeInstanceDouble *doubleTree = nullptr;
    TreeInstanceString *stringTree = nullptr;

    QStringList availableDistances();

    PivotSelection::Algorithm getAlgorithm();

    void lockButtons();
    void unlockButtons();

    void setupCbxDistanceFunction();
    void setupCbxPivotType();
    void setupCbxBalance();
    void setupProgressBar();
    void setupCbxQueryAlgorithm();
    void setupNodesID(TreeInstanceDouble *vpt);
    void setupNodesID(TreeInstanceString *vpt);
    void setupElementsToQuery(DatasetDouble *dataset);
    void setupElementsToQuery(DatasetString *dataset);
    void setupLabelsForCharVec();
    void setupLabelsForDoubles();

    void generateInstanceDouble(DistanceFunction<InstanceDouble> *df);
    void generateInstanceString(DistanceFunction<InstanceString> *df);

    void generateHistogram(DirectorNode<InstanceDouble> node);
    void generateHistogram(DirectorNode<InstanceString> node);

    void generateDistCalcHistogram(DistanceFunction<InstanceDouble> *df);
    void generateDistCalcHistogram(DistanceFunction<InstanceString> *df);

    void buildImageInstanceDouble();
    void buildImageInstanceString();

    void instanceDoubleQuery(DistanceFunction<InstanceDouble> *df);
    void instanceStringQuery(DistanceFunction<InstanceString> *df);

    void sortRangeQueryByOID(Dataset<InstanceDouble> *answer);
    void sortRangeQueryByOID(Dataset<InstanceString> *answer);

    void resetTrees();

    void updateInstanceDoublePixmap();
    void updateInstanceStringPixmap();

};

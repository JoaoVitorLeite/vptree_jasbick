#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);

    setupCbxDistanceFunction();
    setupCbxPivotType();
    setupCbxBalance();
    setupCbxQueryAlgorithm();

    ui->btnChangeStackedWidget->setEnabled(false);
    ui->btnResetQuery->setEnabled(false);
    ui->btnReset->setEnabled(false);

    ui->lblTree->setScaledContents(true);

    connect(ui->cbxNodesID, SIGNAL(activated(int)), this, SLOT(on_cbxNodesIDSelected()));
    connect(ui->cbxQueryAlgorithm, SIGNAL(currentIndexChanged(int)), ui->swgetQueryAlgorithms, SLOT(setCurrentIndex(int)));
    connect(ui->sldrZoom, SIGNAL(valueChanged(int)), this, SLOT(scaleImage(int)));

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::scaleImage(int newValue){

    if (!ui->lblTree->pixmap())
        return;

    QPixmap *pixmap = nullptr;

    if (paintedTreePixmap != nullptr)
        pixmap = paintedTreePixmap;
    else
        pixmap = new QPixmap(fullSizeTreePixmap);

    int dist = ui->sldrZoom->maximum() - newValue;

    if (dist > 1){

        int width = pixmap->width() / dist;
        int height = pixmap->height() / dist;

        ui->lblTree->setPixmap(pixmap->scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    } else if (dist == 1){

        int width = pixmap->width() / 1.5;
        int height = pixmap->height() / 1.5;

        ui->lblTree->setPixmap(pixmap->scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    } else {
        ui->lblTree->setPixmap(fullSizeTreePixmap);
    }

}

void MainWindow::on_btnReset_clicked(){

    if (paintedTreePixmap != nullptr){
        delete(paintedTreePixmap);
        paintedTreePixmap = nullptr;
    }

    // Clearing labels
    ui->lblTree->clear();
    ui->lblTree->setText("Empty");
    ui->lblMedianValue->clear();
    ui->lblPivotValue->clear();
    ui->lblHistogram->clear();

    // Clearing boxes.
    ui->cbxNodesID->clear();
    ui->cbxQueryElementID->clear();
    ui->spboxK->clear();
    ui->dspboxRange->clear();

    // Reseting trees;
    doubleTree = nullptr;
    stringTree = nullptr;

    // Reseting progressBar
    ui->progressBar->setValue(0);

    // Reseting histograms.
    ui->swgetResultOrHistogram->setCurrentIndex(2);
    qDeleteAll(ui->wgetHistogram->children());

    // Reseting results
    ui->pTxtEdtResults->clear();

    // Reseting zoom.
    ui->sldrZoom->setValue(ui->sldrZoom->minimum());
}

void MainWindow::on_btnFileDialog_clicked(){
    QString filediretory = QFileDialog::getOpenFileName(this, tr("Select CSV File"), "/home/notox/FileToMemory", "CSV Files (*.csv)");

    ui->edtDatasetLocation->setText(filediretory);
}

void MainWindow::on_btnGenerate_clicked(){

    on_btnReset_clicked();

    ui->lblTree->setText("Running...");

    setupProgressBar();

    QString choosenDistanceFunction = ui->cbxDistanceFunction->currentText();
    QFuture<void> future;

    if (choosenDistanceFunction == "Euclidean Distance")
        future = QtConcurrent::run(&MainWindow::generateInstanceDouble, this, new EuclideanDistance<InstanceDouble>());
    else if (choosenDistanceFunction == "Manhattan Distance")
        future = QtConcurrent::run(&MainWindow::generateInstanceDouble, this, new ManhattanDistance<InstanceDouble>());
    else if (choosenDistanceFunction == "Canberra Distance")
        future = QtConcurrent::run(&MainWindow::generateInstanceDouble, this, new CanberraDistance<InstanceDouble>());
    else if (choosenDistanceFunction == "Chebyshev Distance")
        future = QtConcurrent::run(&MainWindow::generateInstanceDouble, this, new ChebyshevDistance<InstanceDouble>());
    else if (choosenDistanceFunction == "Bray Curtis Distance")
        future = QtConcurrent::run(&MainWindow::generateInstanceDouble, this, new BrayCurtisDistance<InstanceDouble>());
    else if (choosenDistanceFunction == "Jeffrey Divergence Distance")
        future = QtConcurrent::run(&MainWindow::generateInstanceDouble, this, new JeffreyDivergenceDistance<InstanceDouble>());
    else if (choosenDistanceFunction == "Kullback Leibler Distance")
        future = QtConcurrent::run(&MainWindow::generateInstanceDouble, this, new KullbackLeiblerDivergenceDistance<InstanceDouble>());
    else if (choosenDistanceFunction == "Morisita Distance")
        future = QtConcurrent::run(&MainWindow::generateInstanceDouble, this, new MorositaDistance<InstanceDouble>());
    else if (choosenDistanceFunction == "Qui Square Distance")
        future = QtConcurrent::run(&MainWindow::generateInstanceDouble, this, new QuiSquareDistance<InstanceDouble>());
    else if (choosenDistanceFunction == "Spearman Distance")
        future = QtConcurrent::run(&MainWindow::generateInstanceDouble, this, new SpearmanDistance<InstanceDouble>());
    else if (choosenDistanceFunction == "Metric Histogram Distance")
        future = QtConcurrent::run(&MainWindow::generateInstanceDouble, this, new MetricHistogramDistance<InstanceDouble>());
    else if (choosenDistanceFunction == "Warp Distance")
        future = QtConcurrent::run(&MainWindow::generateInstanceDouble, this, new WarpDistance<InstanceDouble>());
    else if (choosenDistanceFunction == "Edit Distance")
        future = QtConcurrent::run(&MainWindow::generateInstanceString, this, new EditDistance<InstanceString>());

//    if (choosenDistanceFunction == "Euclidean Distance")
//        generateInstanceDouble(new EuclideanDistance<InstanceDouble>());
//    else if (choosenDistanceFunction == "Manhattan Distance")
//        generateInstanceDouble(new ManhattanDistance<InstanceDouble>());
//    else if (choosenDistanceFunction == "Canberra Distance")
//        generateInstanceDouble(new CanberraDistance<InstanceDouble>());
//    else if (choosenDistanceFunction == "Chebyshev Distance")
//        generateInstanceDouble(new ChebyshevDistance<InstanceDouble>());
//    else if (choosenDistanceFunction == "Bray Curtis Distance")
//        generateInstanceDouble(new BrayCurtisDistance<InstanceDouble>());
//    else if (choosenDistanceFunction == "Jeffrey Divergence Distance")
//        generateInstanceDouble(new JeffreyDivergenceDistance<InstanceDouble>());
//    else if (choosenDistanceFunction == "Kullback Leibler Distance")
//        generateInstanceDouble(new KullbackLeiblerDivergenceDistance<InstanceDouble>());
//    else if (choosenDistanceFunction == "Morisita Distance")
//        generateInstanceDouble(new MorositaDistance<InstanceDouble>());
//    else if (choosenDistanceFunction == "Qui Square Distance")
//        generateInstanceDouble(new QuiSquareDistance<InstanceDouble>());
//    else if (choosenDistanceFunction == "Spearman Distance")
//        generateInstanceDouble(new SpearmanDistance<InstanceDouble>());
//    else if (choosenDistanceFunction == "Metric Histogram Distance")
//        generateInstanceDouble(new MetricHistogramDistance<InstanceDouble>());
//    else if (choosenDistanceFunction == "Warp Distance")
//        generateInstanceDouble(new WarpDistance<InstanceDouble>());
//    else if (choosenDistanceFunction == "Edit Distance")
//        generateInstanceString(new EditDistance<InstanceString>());

}

void MainWindow::on_cbxNodesIDSelected(){

    QString choosenDistanceFunction = ui->cbxDistanceFunction->currentText();

    if (choosenDistanceFunction == "Euclidean Distance" ||
        choosenDistanceFunction == "Manhattan Distance" ||
        choosenDistanceFunction == "Canberra Distance" ||
        choosenDistanceFunction == "Chebyshev Distance" ||
        choosenDistanceFunction == "Bray Curtis Distance" ||
        choosenDistanceFunction == "Jeffrey Divergence Distance" ||
        choosenDistanceFunction == "Kullback Leibler Distance" ||
        choosenDistanceFunction == "Morisita Distance" ||
        choosenDistanceFunction == "QuiSquare Distance" ||
        choosenDistanceFunction == "Spearman Distance" ||
        choosenDistanceFunction == "Metric Histogram Distance" ||
        choosenDistanceFunction == "Warp Distance")

        setupLabelsForDoubles();
    else
        setupLabelsForCharVec();

}

void MainWindow::generateInstanceDouble(DistanceFunction<InstanceDouble> *df){

    lockButtons();

    resetTrees();

    ui->lblTree->setText("Reading file...");

    DatasetDouble *dataset = new DatasetDouble(ui->spboxCardinality->value());
    DatasetDouble::doubleFileToDataset(dataset,
                                       ui->edtDatasetLocation->displayText().toStdString(),
                                       ui->spboxCardinality->value(),
                                       ui->spboxDimensionality->value());

    setupElementsToQuery(dataset);

    ui->lblTree->setText("Building tree...");

    bool balance;
    if (ui->cbxBalance->currentText() == "true")
        balance = true;

    doubleTree = new TreeInstanceDouble(balance,
                                        0.0,
                                        ui->spboxMaxElementsPerLeaf->value(),
                                        getAlgorithm(),
                                        dataset,
                                        df,
                                        ui->progressBar);

    ui->lblTree->setText("Building image...");

    buildImageInstanceDouble();

    setupNodesID(doubleTree);

    unlockButtons();

}

void MainWindow::generateInstanceString(DistanceFunction<InstanceString> *df){

    lockButtons();

    resetTrees();

    ui->lblTree->setText("Reading file...");

    DatasetString *dataset = new DatasetString(ui->spboxCardinality->value());
    DatasetString::textFileToDataset(dataset,
                                     ui->edtDatasetLocation->displayText().toStdString(),
                                     ui->spboxCardinality->value(),
                                     ui->spboxDimensionality->value());

    setupElementsToQuery(dataset);

    ui->lblTree->setText("Building tree...");

    bool balance;
    if (ui->cbxBalance->currentText() == "true")
        balance = true;

    stringTree = new TreeInstanceString(balance,
                                        0.0,
                                        ui->spboxMaxElementsPerLeaf->value(),
                                        getAlgorithm(),
                                        dataset,
                                        df,
                                        ui->progressBar);

    ui->lblTree->setText("Building image...");

    buildImageInstanceString();

    setupNodesID(stringTree);

    unlockButtons();
}

void MainWindow::generateHistogram(DirectorNode<InstanceDouble> node){

    delete(ui->wgetHistogram->layout());

    std::vector<uint_fast32_t> histogram = node.getHistogram().getHistFrequencies();
    std::vector<double> histogramValues = node.getHistogram().getHistValues();

    ui->lblHistogram->setText(QString::number(*std::max_element(histogramValues.begin(), histogramValues.end())));

    QChart *chart = new QChart();
    QBarCategoryAxis *axis = new QBarCategoryAxis();

    for (uint_fast32_t i = 0; i < histogram.size(); i++){

        QBarSet *set = new QBarSet("");

        *set << histogram[i];

        if (node.getMu() >= (histogramValues[i]) && (node.getMu() < (histogramValues[i+1])))
            set->setColor(QColor("orange"));
        else
            set->setColor(QColor(50,50,50));

        axis->append(QString::number(i));

        QBarSeries *series = new QBarSeries();
        series->append(set);

        chart->addSeries(series);

        chart->createDefaultAxes();
        chart->setAxisX(axis, series);

        chart->legend()->markers(series)[0]->setVisible(false);
    }

    chart->setAnimationOptions(QChart::SeriesAnimations);

    chart->setTitle("Distance distribution for pivot pid-" + QString::number(node.getPivot().getOID()));

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(ui->wgetHistogram);
    layout->addWidget(chartView);
    ui->wgetHistogram->setLayout(layout);

}

void MainWindow::generateHistogram(DirectorNode<InstanceString> node){

    delete(ui->wgetHistogram->layout());

    std::vector<uint_fast32_t> histogram = node.getHistogram().getHistFrequencies();
    std::vector<double> histogramValues = node.getHistogram().getHistValues();

    ui->lblHistogram->setText(QString::number(*std::max_element(histogramValues.begin(), histogramValues.end())));

    QChart *chart = new QChart();
    QBarCategoryAxis *axis = new QBarCategoryAxis();

    for (uint_fast32_t i = 0; i < histogramValues.size(); i++){

        QBarSet *set = new QBarSet("");

        *set << histogram[i];

        if (node.getMu() >= (histogramValues[i]) && (node.getMu() < (histogramValues[i+1])))
            set->setColor(QColor("orange"));
        else
            set->setColor(QColor(50,50,50));

        if (i == 15)
            set->setColor(QColor("orange"));

        axis->append(QString::number(i));

        QBarSeries *series = new QBarSeries();
        series->append(set);

        chart->addSeries(series);

        chart->createDefaultAxes();
        chart->setAxisX(axis, series);

        chart->legend()->markers(series)[0]->setVisible(false);
    }

    chart->setAnimationOptions(QChart::SeriesAnimations);

    chart->setTitle("Distance distribution for pivot pid-" + QString::number(node.getPivot().getOID()));

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(ui->wgetHistogram);
    layout->addWidget(chartView);
    ui->wgetHistogram->setLayout(layout);

}

void MainWindow::generateDistCalcHistogram(DistanceFunction<InstanceDouble> *df){

    delete(ui->wgetDistCalcHistogram->layout());

    QChart *chart = new QChart();
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axis = new QBarCategoryAxis();

    QBarSeries *series = new QBarSeries();

    QBarSet *set1 = new QBarSet("Vp-Tree");
    QBarSet *set2 = new QBarSet("Brute Force");

    *set1 << df->getDistanceCount();
    set1->setColor(QColor("orange"));

    series->append(set1);

    *set2 << ui->spboxCardinality->value();
    set2->setColor(QColor(50,50,50));

    series->append(set2);

    int percentage = 100 - (((double) df->getDistanceCount()/ui->spboxCardinality->value())*100);

    axis->append(QString::number(percentage) + "% difference");

    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    //chart->legend()->setAlignment

    chart->setTitle("Distance calculations comparison.");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(ui->wgetDistCalcHistogram);
    layout->addWidget(chartView);
    ui->wgetDistCalcHistogram->setLayout(layout);
}

void MainWindow::generateDistCalcHistogram(DistanceFunction<InstanceString> *df){

    delete(ui->wgetDistCalcHistogram->layout());

    QChart *chart = new QChart();
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axis = new QBarCategoryAxis();

    QBarSeries *series = new QBarSeries();

    QBarSet *set1 = new QBarSet("Vp-Tree");
    QBarSet *set2 = new QBarSet("Brute Force");

    *set1 << df->getDistanceCount();
    set1->setColor(QColor("orange"));

    series->append(set1);

    *set2 << ui->spboxCardinality->value();
    set2->setColor(QColor(50,50,50));

    series->append(set2);

    int percentage = 100 - (((double) df->getDistanceCount()/ui->spboxCardinality->value())*100);

    axis->append(QString::number(percentage) + "% difference");

    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    //chart->legend()->setAlignment

    chart->setTitle("Distance calculations comparison.");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(ui->wgetDistCalcHistogram);
    layout->addWidget(chartView);
    ui->wgetDistCalcHistogram->setLayout(layout);
}

void MainWindow::setupCbxPivotType(){

    QStringList strl;
    strl.append("Random");
    strl.append("Hull Foci");
    strl.append("Yianilos's SelectVp");

    ui->cbxPivotType->addItems(strl);

}

void MainWindow::setupCbxBalance(){
    QStringList strl;
    strl.append("false");
    strl.append("true");
    ui->cbxBalance->addItems(strl);
}

void MainWindow::setupProgressBar(){

    if (ui->spboxCardinality->value() < SHRT_MAX)
        ui->progressBar->setRange(0, ui->spboxCardinality->value());
    else
        ui->progressBar->setRange(0, ui->spboxCardinality->value()/SHRT_MAX);

    ui->progressBar->setValue(0);
}

void MainWindow::setupCbxDistanceFunction(){
    QStringList strl;

    strl.append("Euclidean Distance");
    strl.append("Manhattan Distance");
    strl.append("Canberra Distance");
    strl.append("Chebyshev Distance");
    strl.append("Bray Curtis Distance");
    strl.append("Jeffrey Divergence Distance");
    strl.append("Kullback Leibler Distance");
    strl.append("Morisita Distance");
    strl.append("Qui Square Distance");
    strl.append("Spearman Distance");
    strl.append("Metric Histogram Distance");
    strl.append("Warp Distance");
    strl.append("Edit Distance");

    ui->cbxDistanceFunction->addItems(strl);
}

void MainWindow::setupLabelsForDoubles(){

    DirectorNode<InstanceDouble> dirNode = ui->cbxNodesID->currentData().value<DirectorNode<InstanceDouble>>();

    QString str;
    for (uint_fast32_t i = 0; i < dirNode.getPivot().size(); i++){
        str.append(QString::number(dirNode.getPivot()[i]));
        str.append(' ');
    }

    ui->lblPivotValue->setText(str);
    ui->lblMedianValue->setText(QString::number(dirNode.getMu()));

    generateHistogram(dirNode);
}

void MainWindow::setupLabelsForCharVec(){

    DirectorNode<InstanceString> dirNode = ui->cbxNodesID->currentData().value<DirectorNode<InstanceString>>();

    QString str;
    for (uint_fast32_t i = 0; i < dirNode.getPivot().size(); i++){

        for (uint_fast32_t j = 0; j < dirNode.getPivot()[i].size(); j++){
            str.append(dirNode.getPivot()[i][j]);
        }
        str.append(' ');
    }

    ui->lblPivotValue->setText(str);
    ui->lblMedianValue->setText(QString::number(dirNode.getMu()));

    generateHistogram(dirNode);
}

void MainWindow::setupElementsToQuery(DatasetDouble *dataset){

    uint_fast32_t size = dataset->getSize();

    for (uint_fast32_t i = 0; i < size; i++){
        ui->cbxQueryElementID->addItem(QString::number(dataset->operator [](i).getOID()),
                                       QVariant::fromValue<InstanceDouble>(dataset->operator [](i)));
    }

}

void MainWindow::setupElementsToQuery(DatasetString *dataset){

    uint_fast32_t size = dataset->getSize();

    for (uint_fast32_t i = 0; i < size; i++){
        ui->cbxQueryElementID->addItem(QString::number(dataset->operator [](i).getOID()),
                                       QVariant::fromValue<InstanceString>(dataset->operator [](i)));
    }

}

void MainWindow::setupNodesID(TreeInstanceDouble *vpt){

    std::vector<DirectorNode<InstanceDouble>*> ids;
    vpt->getDirectorNodes(vpt->getRoot(), &ids);

    for (uint_fast32_t i = 0; i < ids.size(); i++){
        for (uint_fast32_t j = 0; j < ids.size()-i-1; j++){
            if (ids[j]->getPivot().getOID() > ids[j+1]->getPivot().getOID()){
                DirectorNode<InstanceDouble> *temp = ids[j+1];
                ids[j+1] = ids[j];
                ids[j] = temp;
            }
        }
    }

    for (uint_fast32_t i = 0; i < ids.size(); i++){

        DirectorNode<InstanceDouble> dirNode;
        dirNode.setPivot(ids[i]->getPivot());
        dirNode.setMu(ids[i]->getMu());
        dirNode.setHistogram(ids[i]->getHistogram());

        ui->cbxNodesID->addItem(QString::number(dirNode.getPivot().getOID()),
                                QVariant::fromValue<DirectorNode<InstanceDouble>>(dirNode));

    }

}

void MainWindow::setupNodesID(TreeInstanceString *vpt){

    std::vector<DirectorNode<InstanceString>*> ids;
    vpt->getDirectorNodes(vpt->getRoot(), &ids);

    for (uint_fast32_t i = 0; i < ids.size(); i++){
        for (uint_fast32_t j = 0; j < ids.size()-i-1; j++){
            if (ids[j]->getPivot().getOID() > ids[j+1]->getPivot().getOID()){
                DirectorNode<InstanceString> *temp = ids[j+1];
                ids[j+1] = ids[j];
                ids[j] = temp;
            }
        }
    }

    for (uint_fast32_t i = 0; i < ids.size(); i++){

        DirectorNode<InstanceString> dirNode;
        dirNode.setPivot(ids[i]->getPivot());
        dirNode.setMu(ids[i]->getMu());
        dirNode.setHistogram(ids[i]->getHistogram());

        ui->cbxNodesID->addItem(QString::number(dirNode.getPivot().getOID()),
                                QVariant::fromValue<DirectorNode<InstanceString>>(dirNode));

    }

}

void MainWindow::sortRangeQueryByOID(DatasetDouble *answer){

    uint_fast32_t size = answer->getSize();

    for (uint_fast32_t i = 0; i < size; i++){
        for (uint_fast32_t j = 0; j < (size-i)-1; j++){
            if (answer->operator [](j).getOID() > answer->operator [](j+1).getOID()){
                InstanceDouble temp = answer->operator [](j);
                answer->operator [](j) = answer->operator [](j+1);
                answer->operator [](j+1) = temp;
            }
        }
    }

}

void MainWindow::sortRangeQueryByOID(DatasetString *answer){

    uint_fast32_t size = answer->getSize();

    for (uint_fast32_t i = 0; i < size; i++){
        for (uint_fast32_t j = 0; j < (size-i)-1; j++){
            if (answer->operator [](j).getOID() > answer->operator [](j+1).getOID()){
                InstanceString temp = answer->operator [](j);
                answer->operator [](j) = answer->operator [](j+1);
                answer->operator [](j+1) = temp;
            }
        }
    }

}

void MainWindow::instanceDoubleQuery(DistanceFunction<InstanceDouble> *df){

    DatasetDouble answer;

    InstanceDouble qElement = ui->cbxQueryElementID->currentData().value<InstanceDouble>();

    if (ui->cbxQueryAlgorithm->currentText() == "kNN"){

        doubleTree->kNN(qElement,
                        ui->spboxK->value(),
                        doubleTree->getRoot(),
                        &answer,
                        df);

    } else if (ui->cbxQueryAlgorithm->currentText() == "kNNInc"){

        doubleTree->kNNInc(qElement,
                           ui->spboxK->value(),
                           doubleTree->getRoot(),
                           &answer,
                           df);

    } else if (ui->cbxQueryAlgorithm->currentText() == "Range Query"){

        doubleTree->rangeQuery(qElement,
                                ui->dspboxRange->value(),
                                doubleTree->getRoot(),
                                &answer,
                                df);

        sortRangeQueryByOID(&answer);

    }

    for (uint_fast32_t i = 0; i < answer.getSize(); i++)
        ui->pTxtEdtResults->appendPlainText(QString::number(answer[i].getOID()) + "; ");

    //ui->pTxtEdtResults->

    updateInstanceDoublePixmap();
    generateDistCalcHistogram(df);
}

void MainWindow::instanceStringQuery(DistanceFunction<InstanceString> *df){

    EditDistance<InstanceString> edd;
    DatasetString answer;

    InstanceString qElement = ui->cbxQueryElementID->currentData().value<InstanceString>();

    if (ui->cbxQueryAlgorithm->currentText() == "kNN"){

        stringTree->kNN(qElement,
                      ui->spboxK->value(),
                      stringTree->getRoot(),
                      &answer,
                      df);

    } else if (ui->cbxQueryAlgorithm->currentText() == "Range Query"){

        stringTree->rangeQuery(qElement,
                             ui->dspboxRange->value(),
                             stringTree->getRoot(),
                             &answer,
                             df);

        sortRangeQueryByOID(&answer);

    }

    for (uint_fast32_t i = 0; i < answer.getSize(); i++)
        ui->pTxtEdtResults->appendPlainText(QString::number(answer[i].getOID()) + "; ");

    updateInstanceStringPixmap();
    generateDistCalcHistogram(df);
}

void MainWindow::on_btnQuery_clicked(){

    on_btnResetQuery_clicked();

    QString choosenDistanceFunction = ui->cbxDistanceFunction->currentText();

    if (choosenDistanceFunction == "Euclidean Distance")
        instanceDoubleQuery(new EuclideanDistance<InstanceDouble>);
    else if (choosenDistanceFunction == "Manhattan Distance")
        instanceDoubleQuery(new ManhattanDistance<InstanceDouble>);
    else if (choosenDistanceFunction == "Canberra Distance")
        instanceDoubleQuery(new CanberraDistance<InstanceDouble>);
    else if (choosenDistanceFunction == "Chebyshev Distance")
        instanceDoubleQuery(new ChebyshevDistance<InstanceDouble>);
    else if (choosenDistanceFunction == "Bray Curtis Distance")
        instanceDoubleQuery(new BrayCurtisDistance<InstanceDouble>);
    else if (choosenDistanceFunction == "Jeffrey Divergence Distance")
        instanceDoubleQuery(new JeffreyDivergenceDistance<InstanceDouble>);
    else if (choosenDistanceFunction == "Kullback Leibler Distance")
        instanceDoubleQuery(new KullbackLeiblerDivergenceDistance<InstanceDouble>);
    else if (choosenDistanceFunction == "Morisita Distance")
        instanceDoubleQuery(new MorositaDistance<InstanceDouble>);
    else if (choosenDistanceFunction == "Qui Square Distance")
        instanceDoubleQuery(new QuiSquareDistance<InstanceDouble>);
    else if (choosenDistanceFunction == "Spearman Distance")
        instanceDoubleQuery(new SpearmanDistance<InstanceDouble>);
    else if (choosenDistanceFunction == "Metric Histogram Distance")
        instanceDoubleQuery(new MetricHistogramDistance<InstanceDouble>);
    else if (choosenDistanceFunction == "Edit Distance")
        instanceStringQuery(new EditDistance<InstanceString>);

    ui->btnChangeStackedWidget->setEnabled(true);
    ui->btnResetQuery->setEnabled(true);
}

void MainWindow::setupCbxQueryAlgorithm(){

    QStringList strl;
    strl.append("Range Query");
    strl.append("kNN");
    strl.append("kNNInc");
    ui->cbxQueryAlgorithm->addItems(strl);
    ui->cbxQueryAlgorithm->setCurrentIndex(1);
}

void MainWindow::on_btnResetQuery_clicked(){

    ui->btnChangeStackedWidget->setEnabled(false);
    ui->btnResetQuery->setEnabled(false);

    ui->cbxQueryElementID->clearEditText();
    ui->cbxQueryAlgorithm->clearEditText();

    if (paintedTreePixmap != nullptr){
        delete(paintedTreePixmap);
        paintedTreePixmap = nullptr;
    }

    scaleImage(ui->sldrZoom->value());

    ui->pTxtEdtResults->clear();
}

void MainWindow::resetTrees(){

    if (doubleTree != nullptr){
        delete(doubleTree);
        doubleTree = nullptr;
    }

    if (stringTree != nullptr){
        delete(stringTree);
        stringTree = nullptr;
    }
}

void MainWindow::updateInstanceDoublePixmap(){

    View<InstanceDouble> view(doubleTree->getRoot(), ui->spboxMaxElementsPerLeaf->value());
    paintedTreePixmap = new QPixmap(view.getPixmap());
    scaleImage(ui->sldrZoom->value());

}

void MainWindow::updateInstanceStringPixmap(){

    View<InstanceString> view(stringTree->getRoot(), ui->spboxMaxElementsPerLeaf->value());
    paintedTreePixmap = new QPixmap(view.getPixmap());
    scaleImage(ui->sldrZoom->value());

}

void MainWindow::on_btnChangeStackedWidget_clicked(){

    if (ui->swgetResultOrHistogram->currentIndex() == 0){
        ui->swgetResultOrHistogram->setCurrentIndex(1);
        ui->btnChangeStackedWidget->setText("Show Comparison");

    } else  if (ui->swgetResultOrHistogram->currentIndex() == 1){

        ui->swgetResultOrHistogram->setCurrentIndex(0);
        ui->btnChangeStackedWidget->setText("Show Results");

    } else if (ui->swgetResultOrHistogram->currentIndex() == 2){
        ui->swgetResultOrHistogram->setCurrentIndex(0);
    }
}

void MainWindow::buildImageInstanceDouble(){

    View<InstanceDouble> view(doubleTree->getRoot(), ui->spboxMaxElementsPerLeaf->value());

    QPixmap px = view.getPixmap();
    fullSizeTreePixmap = px;

    if (px.width() > 400 || px.height() > 300)
        px = px.scaled(400,300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    ui->lblTree->setPixmap(px);
}

void MainWindow::buildImageInstanceString(){

    View<InstanceString> view(stringTree->getRoot(), ui->spboxMaxElementsPerLeaf->value());

    QPixmap px = view.getPixmap();
    fullSizeTreePixmap = px;

    if (px.width() > 400 || px.height() > 300)
        px = px.scaled(400,300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    ui->lblTree->setPixmap(px);
}

PivotSelection::Algorithm MainWindow::getAlgorithm(){

    if (ui->cbxPivotType->currentText() == "Random")
        return PivotSelection::RANDOM;
    else if (ui->cbxPivotType->currentText() == "Hull Foci")
        return PivotSelection::HULL_FOCI;
    else // if (ui->cbxQueryAlgorithm->currentText() == "Yianilos's SelectVp")
        return PivotSelection::VP_TREE;
}

void MainWindow::lockButtons(){
    ui->btnGenerate->setEnabled(false);
    ui->btnReset->setEnabled(false);
    ui->sldrZoom->setEnabled(false);
}

void MainWindow::unlockButtons(){
    ui->btnGenerate->setEnabled(true);
    ui->btnReset->setEnabled(true);
    ui->sldrZoom->setEnabled(true);
}

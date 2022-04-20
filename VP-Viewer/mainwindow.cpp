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

    connect(ui->cbxNodesID, SIGNAL(activated(int)), this, SLOT(on_cbxNodesID_selected()));
    connect(ui->cbxQueryAlgorithm, SIGNAL(currentIndexChanged(int)), ui->swgetQueryAlgorithms, SLOT(setCurrentIndex(int)));
    connect(ui->sldrZoom, SIGNAL(valueChanged(int)), this, SLOT(scaleImage(int)));

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::scaleImage(int newValue){

    if (ui->lblTree->pixmap() == nullptr)
        return;

    QPixmap *pixmap = nullptr;

    if (paintedTreePixmap != nullptr)
        pixmap = paintedTreePixmap;
    else
        pixmap = new QPixmap(fullSizeTreePixmap);

    int dist = ui->sldrZoom->maximum() - newValue;

    if (dist > 1){

        double width = pixmap->width() / dist;
        double height = pixmap->height() / dist;

        ui->lblTree->setPixmap(pixmap->scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    } else if (dist == 1){

        double width = pixmap->width() / 1.5;
        double height = pixmap->height() / 1.5;

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
    euclideanTree = nullptr;
    manhattanTree = nullptr;
    editTree = nullptr;

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

    if (choosenDistanceFunction == "Euclidean Distance")
        QtConcurrent::run(this, &MainWindow::generateEuclidean);
    else if (choosenDistanceFunction == "Manhattan Distance")
        QtConcurrent::run(this, &MainWindow::generateManhattan);
    else if (choosenDistanceFunction == "Edit Distance")
        QtConcurrent::run(this, &MainWindow::generateEdit);
}

void MainWindow::on_cbxNodesID_selected(){

    QString choosenDistanceFunction = ui->cbxDistanceFunction->currentText();

    if (choosenDistanceFunction == "Euclidean Distance" || choosenDistanceFunction == "Manhattan Distance")
        setupLabelsForDoubles();
    else
        setupLabelsForCharVec();

}

void MainWindow::generateEuclidean(){

    lockButtons();

    resetTrees();

    ui->lblTree->setText("Reading file...");

    DatasetDouble *dataset = new DatasetDouble(ui->spboxCardinality->value());
    DatasetDouble::doubleFileToDataset(dataset,
                                       ui->edtDatasetLocation->displayText().toStdString(),
                                       ui->spboxCardinality->value(),
                                       ui->spboxDimensionality->value());

    setupElementsToQuery(dataset);

    EuclideanDistance<InstanceDouble> ed;

    maxDist = DatasetDouble::getMax(*dataset, &ed);

    ui->lblTree->setText("Building tree...");

    bool balance;
    if (ui->cbxBalance->currentText() == "true")
        balance = true;

    euclideanTree = new TreeEuclidean(balance,
                                      0.0,
                                      ui->spboxMaxElementsPerLeaf->value(),
                                      getAlgorithm(),
                                      dataset,
                                      &ed,
                                      ui->progressBar);

    ui->lblTree->setText("Building image...");

    buildImageEuclidean();

    setupNodesID(euclideanTree);

    unlockButtons();
}

void MainWindow::generateManhattan(){

    lockButtons();

    resetTrees();

    ui->lblTree->setText("Reading file...");

    DatasetDouble *dataset = new DatasetDouble(ui->spboxCardinality->value());
    DatasetDouble::doubleFileToDataset(dataset,
                                       ui->edtDatasetLocation->displayText().toStdString(),
                                       ui->spboxCardinality->value(),
                                       ui->spboxDimensionality->value());

    setupElementsToQuery(dataset);

    ManhattanDistance<InstanceDouble> md;

    ui->lblTree->setText("Building tree...");

    bool balance;
    if (ui->cbxBalance->currentText() == "true")
        balance = true;

    manhattanTree = new TreeManhattan(balance,
                                      0.0,
                                      ui->spboxMaxElementsPerLeaf->value(),
                                      getAlgorithm(),
                                      dataset,
                                      &md,
                                      ui->progressBar);

    ui->lblTree->setText("Building image...");

    buildImageManhattan();

    setupNodesID(manhattanTree);

    unlockButtons();
}

void MainWindow::generateEdit(){

    lockButtons();

    resetTrees();

    ui->lblTree->setText("Reading file...");

    DatasetString *dataset = new DatasetString(ui->spboxCardinality->value());
    DatasetString::textFileToDataset(dataset,
                                     ui->edtDatasetLocation->displayText().toStdString(),
                                     ui->spboxCardinality->value(),
                                     ui->spboxDimensionality->value());

    setupElementsToQuery(dataset);

    EditDistance<InstanceString> edd;

    ui->lblTree->setText("Building tree...");

    bool balance;
    if (ui->cbxBalance->currentText() == "true")
        balance = true;

    editTree = new TreeEdit(balance,
                            0.0,
                            ui->spboxMaxElementsPerLeaf->value(),
                            getAlgorithm(),
                            dataset,
                            &edd,
                            ui->progressBar);

    ui->lblTree->setText("Building image...");

    buildImageEdit();

    setupNodesID(editTree);

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

void MainWindow::setupNodesID(TreeEuclidean *vpt){

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

void MainWindow::setupNodesID(TreeManhattan *vpt){


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

void MainWindow::setupNodesID(TreeEdit *vpt){

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

void MainWindow::euclideanQuery(){

    EuclideanDistance<InstanceDouble> ed;
    DatasetDouble answer;

    InstanceDouble qElement = ui->cbxQueryElementID->currentData().value<InstanceDouble>();

    if (ui->cbxQueryAlgorithm->currentText() == "kNN"){

        euclideanTree->kNN(qElement,
                           ui->spboxK->value(),
                           euclideanTree->getRoot(),
                           &answer,
                           &ed);

    } else if (ui->cbxQueryAlgorithm->currentText() == "Range Query"){

        std::ofstream file;
        file.open("/home/notox/VP-Viewer\ Tests/output");

        if (file.is_open()){

            for (int j = 1; j < 6; j++){

                file << "\n";

                for (int i = 0; i < ui->cbxQueryElementID->count(); i++){

                    ed.resetStatistics();

                    clock_t begin = clock();

                    euclideanTree->rangeQuery(ui->cbxQueryElementID->itemData(i).value<InstanceDouble>(),
                                              (maxDist * (j*5))/100,
                                              euclideanTree->getRoot(),
                                              &answer,
                                              &ed);

                    clock_t end = clock();
                    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

                    QString s;

                    s.append(QString::number(ui->cbxQueryElementID->itemData(i).value<InstanceDouble>().getOID()) + " ");
                    s.append(QString::number(elapsed_secs) + " ");
                    s.append(QString::number(ed.getDistanceCount()) + "\n");

                    file << s.toStdString();

                }

            }

            file.close();

        }

        sortRangeQueryByOID(&answer);

    }

    for (uint_fast32_t i = 0; i < answer.getSize(); i++)
        ui->pTxtEdtResults->appendPlainText(QString::number(answer[i].getOID()) + "; ");

    //ui->pTxtEdtResults->

    updateEuclideanPixmap();
    generateDistCalcHistogram(&ed);
}

void MainWindow::manhattanQuery(){

    ManhattanDistance<InstanceDouble> md;
    DatasetDouble answer;

    InstanceDouble qElement = ui->cbxQueryElementID->currentData().value<InstanceDouble>();

    if (ui->cbxQueryAlgorithm->currentText() == "kNN"){

        manhattanTree->kNN(qElement,
                           ui->spboxK->value(),
                           manhattanTree->getRoot(),
                           &answer,
                           &md);

    } else if (ui->cbxQueryAlgorithm->currentText() == "Range Query"){

        manhattanTree->rangeQuery(qElement,
                                  ui->dspboxRange->value(),
                                  manhattanTree->getRoot(),
                                  &answer,
                                  &md);

        sortRangeQueryByOID(&answer);

    }

    for (uint_fast32_t i = 0; i < answer.getSize(); i++)
        ui->pTxtEdtResults->appendPlainText(QString::number(answer[i].getOID()) + "; ");

    updateManhattanPixmap();
    generateDistCalcHistogram(&md);
}

void MainWindow::editQuery(){

    EditDistance<InstanceString> edd;
    DatasetString answer;

    InstanceString qElement = ui->cbxQueryElementID->currentData().value<InstanceString>();

    if (ui->cbxQueryAlgorithm->currentText() == "kNN"){

        editTree->kNN(qElement,
                      ui->spboxK->value(),
                      editTree->getRoot(),
                      &answer,
                      &edd);

    } else if (ui->cbxQueryAlgorithm->currentText() == "Range Query"){

        editTree->rangeQuery(qElement,
                             ui->dspboxRange->value(),
                             editTree->getRoot(),
                             &answer,
                             &edd);

        sortRangeQueryByOID(&answer);

    }

    for (uint_fast32_t i = 0; i < answer.getSize(); i++)
        ui->pTxtEdtResults->appendPlainText(QString::number(answer[i].getOID()) + "; ");

    updateEditPixmap();
    generateDistCalcHistogram(&edd);
}

void MainWindow::on_btnQuery_clicked(){

    on_btnResetQuery_clicked();

    QString choosenDistanceFunction = ui->cbxDistanceFunction->currentText();

    if (choosenDistanceFunction == "Euclidean Distance")
        euclideanQuery();
    else if (choosenDistanceFunction == "Manhattan Distance")
        manhattanQuery();
    else if (choosenDistanceFunction == "Edit Distance")
        editQuery();

    ui->btnChangeStackedWidget->setEnabled(true);
    ui->btnResetQuery->setEnabled(true);
}

void MainWindow::setupCbxQueryAlgorithm(){

    QStringList strl;
    strl.append("Range Query");
    strl.append("kNN");
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
    if (euclideanTree != nullptr){
        delete(euclideanTree);
        euclideanTree = nullptr;
    }

    if (manhattanTree != nullptr){
        delete(manhattanTree);
        manhattanTree = nullptr;
    }

    if (editTree != nullptr){
        delete(editTree);
        editTree = nullptr;
    }
}

void MainWindow::updateEuclideanPixmap(){

    View<InstanceDouble> view(euclideanTree->getRoot(), ui->spboxMaxElementsPerLeaf->value());
    paintedTreePixmap = new QPixmap(view.getPixmap());
    scaleImage(ui->sldrZoom->value());

}

void MainWindow::updateManhattanPixmap(){

    View<InstanceDouble> view(manhattanTree->getRoot(), ui->spboxMaxElementsPerLeaf->value());
    paintedTreePixmap = new QPixmap(view.getPixmap());
    scaleImage(ui->sldrZoom->value());

}

void MainWindow::updateEditPixmap(){

    View<InstanceString> view(editTree->getRoot(), ui->spboxMaxElementsPerLeaf->value());
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

void MainWindow::buildImageEuclidean(){

    View<InstanceDouble> view(euclideanTree->getRoot(), ui->spboxMaxElementsPerLeaf->value());

    QPixmap px = view.getPixmap();
    fullSizeTreePixmap = px;

    if (px.width() > 400 || px.height() > 300)
        px = px.scaled(400,300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    ui->lblTree->setPixmap(px);
}

void MainWindow::buildImageManhattan(){

    View<InstanceDouble> view(manhattanTree->getRoot(), ui->spboxMaxElementsPerLeaf->value());

    QPixmap px = view.getPixmap();
    fullSizeTreePixmap = px;

    if (px.width() > 400 || px.height() > 300)
        px = px.scaled(400,300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    ui->lblTree->setPixmap(px);

}

void MainWindow::buildImageEdit(){

    View<InstanceString> view(editTree->getRoot(), ui->spboxMaxElementsPerLeaf->value());

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
    else // if (ui->cbxQueryAlgorithm->currentText() == "Yianilos's SelectVp)
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

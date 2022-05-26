#include <iostream>
#include <Dataset/Dataset.h>
#include <VpTree/VpTree.h>
#include <PivotSelection/PivotSelection.h>
#include <Distance/DistanceFunction.h>
#include <Distance/EuclideanDistance.h>
#include <QProgressBar>

//#include <QApplication>
//#include "mainwindow.h"

//QByteArray readTextFile(const QString &file_path) {
//  QFile input_file(file_path);
//  QByteArray input_data;

//  if (input_file.open(QIODevice::Text | QIODevice::Unbuffered | QIODevice::ReadOnly)) {
//    input_data = input_file.readAll();
//    input_file.close();
//    return input_data;
//  }
//  else {
//    return QByteArray();
//  }
//}

int main(int argc, char *argv[]){

//    QApplication app(argc, argv);

//    MainWindow *wMainWindow = new MainWindow();
//    wMainWindow->show();

//    QString stylesheet = readTextFile(":/lightbreeze.qss");

//    app.setStyleSheet(stylesheet);

//    return app.exec();

    srand(20);

    DatasetDouble dataset = DatasetDouble();
    dataset.doubleFileToDataset(&dataset, "/home/joaovictor/Code/Private.VP-Viewer/Datasets/cities.csv", 5506, 2);
    DistanceFunction<InstanceDouble> *df = new EuclideanDistance<InstanceDouble>();
    InstanceDouble pivot = PivotSelection::getPivot(dataset, PivotSelection::GNAT, df);


}

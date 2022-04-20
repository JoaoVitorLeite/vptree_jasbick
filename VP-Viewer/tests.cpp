#include <Dataset/Dataset.h>
#include <VpTree/VpTree.h>
#include <PivotSelection/PivotSelection.h>
#include <Distance/EuclideanDistance.h>
#include <Distance/ManhattanDistance.h>
#include <Distance/EditDistance.h>

void generateTree(){

    DatasetDouble *dataset = new DatasetDouble(500);
    DatasetDouble::doubleFileToDataset(dataset,
                                       "/home/notox/Samples/10%\ cities.csv",
                                       500,
                                       2);

    EuclideanDistance<InstanceDouble> ed;

    double maxDist = DatasetDouble::getMax(*dataset, &ed);

    typedef VpTree<InstanceDouble, EuclideanDistance> VantagePointTree;

    VantagePointTree vpt(false, 0.0, 50, PivotSelection::RANDOM, dataset, &ed);

    std::ofstream file;
    file.open("/home/notox/VP-Viewer\ Tests/output");

    if (file.is_open()){

        for (int j = 1; j < 6; j++){

            file << "\n";

            for (uint_fast32_t i = 0; i < dataset->getSize(); i++){

                ed.resetStatistics();

                clock_t begin = clock();

                vpt.rangeQuery(dataset->operator [](i),
                               (maxDist * (j*5))/100,
                               vpt.getRoot(),
                               &ed);

                clock_t end = clock();
                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

                QString s;

                s.append(QString::number(dataset->operator [](i).getOID()) + " ");
                s.append(QString::number(elapsed_secs) + " ");
                s.append(QString::number(ed.getDistanceCount()) + "\n");

                file << s.toStdString();

            }

        }

        file.close();

    }

}

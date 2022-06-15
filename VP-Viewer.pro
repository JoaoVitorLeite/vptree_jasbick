QT += core
QT += gui
#QT += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VP-Viewer
TEMPLATE = app

# CONFIG += c++11 console
#QMAKE_CXXFLAGS += -ffast-math

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    #mainwindow.cpp \
    Histogram/histogram.cpp \
    Histogram/pairwisehistogram.cpp \
    Histogram/pivothistogram.cpp \
    PivotSelection/PivotSelection.cpp

HEADERS += \
    Dataset/BasicArrayObject.h \
    Dataset/Dataset-inl.h \
    Dataset/Dataset.h \
    Distance/DistanceFunction.h \
    Distance/EditDistance-inl.h \
    Distance/EditDistance.h \
    Distance/EuclideanDistance-inl.h \
    Distance/EuclideanDistance.h \
    Distance/ManhattanDistance-inl.h \
    Distance/ManhattanDistance.h \
    Distance/BrayCurtisDistance-inl.h \
    Distance/BrayCurtisDistance.h \
    Distance/CanberraDistance-inl.h \
    Distance/CanberraDistance.h \
    Distance/ChebyshevDistance-inl.h \
    Distance/ChebyshevDistance.h \
    Distance/ColorLayoutDistance-inl.h \
    Distance/ColorLayoutDistance.h \
    Distance/DTWDistance-inl.h \
    Distance/DTWDistance.h \
    Distance/JeffreyDivergenceDistance-inl.h \
    Distance/JeffreyDivergenceDistance.h \
    Distance/KullbackLeiblerDivergenceDistance-inl.h \
    Distance/KullbackLeiblerDivergenceDistance.h \
    Distance/MetricHistogramDistance-inl.h \
    Distance/MetricHistogramDistance.h \
    Distance/MorositaDistance-inl.h \
    Distance/MorositaDistance.h \
    Distance/QuiSquareDistance-inl.h \
    Distance/QuiSquareDistance.h \
    Distance/SpearmanDistance-inl.h \
    Distance/SpearmanDistance.h \
    Distance/SquaredChordDistance-inl.h \
    Distance/SquaredChordDistance.h \
    Distance/SumProductDistance-inl.h \
    Distance/SumProductDistance.h \
    Distance/WarpDistance-inl.h \
    Distance/WarpDistance.h \
    Histogram/Histogram.h \
    Histogram/PairwiseHistogram.h \
    Histogram/PivotHistogram.h \
    PivotSelection/PivotSelection.h \
    VpTree/VpTree-inl.h \
    VpTree/VpTree.h \
    VpTree/Node/DirectorNode-inl.h \
    VpTree/Node/DirectorNode.h \
    VpTree/Node/LeafNode-inl.h \
    VpTree/Node/LeafNode.h \
    VpTree/Node/Node-inl.h \
    VpTree/Node/Node.h \
    VpTree/Node/Bucket/Bucket-inl.h \
    VpTree/Node/Bucket/Bucket.h \
    VpTree/Node/Bucket/Pair-inl.h \
    VpTree/Node/Bucket/Pair.h \
    VpTree/View.h \
    VpTree/View-inl.h \
    #mainwindow.h \
    VpTree/QueueItem.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    cities.csv \
    names.csv

RESOURCES += \
    resources.qrc

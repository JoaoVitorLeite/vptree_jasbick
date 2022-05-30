#!/bin/bash

dataset_train="Datasets/train_ulcer_SPP.csv"
dataset_train_cardinality=40402
dataset_train_dimensionality=12
dataset_test="Datasets/test_ulcer_SPP.csv"
dataset_test_cardinality=4490
dataset_test_dimensionality=12
pivot_type=("RANDOM" "GNAT" "CONVEX" "KMEDOIDS" "MAXSEPARETED" "MAXVARIANCE" "SELECTION" "PCA" "SSS")
seed=($(shuf -i 0-500000 -n 9))
k_max=100
num_query=1000
num_per_leaf=400
path_save_results="results/"

make clean
cp query.cpp main.cpp
/usr/lib/qt5/bin/qmake -makefile VP-Viewer.pro
#Qt/6.1.0/gcc_64/bin/qmake -makefile VP-Viewer.pro 
make

for((i=0; i<9; i++));
do
    nohup ./VP-Viewer.pro -DATASET_TRAIN ${dataset_train} -DATASET_TRAIN_CARDINALITY ${dataset_train_cardinality} -DATASET_TRAIN_DIMENSIONALITY ${dataset_train_dimensionality} -DATASET_TEST ${dataset_test} -DATASET_TEST_CARDINALITY ${dataset_test_cardinality} -DATASET_TEST_DIMENSIONALITY ${dataset_test_dimensionality} -PIVOT_TYPE ${pivot_type[$i]} -SEED ${seed[$i]} -K_MAX ${k_max} -PATH_SAVE_RESULTS ${path_save_results} -NUM_PER_LEAF ${num_per_leaf} &
done


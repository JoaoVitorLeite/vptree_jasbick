# VP-Viewer

This repository contains the *VP-Viewer*, a software for the understanding and assessment of the indexing structure *Vantage Point Tree* (VP-Tree).

Our tool was implemented in C++11 standard, on the Qt 5.4 Framework (https://www.qt.io/).

If you either find any bugs or want new features to be added, please report it.

### 1. Minimum Requirements

* Screen resolution: 1366×768 (or higher).
* 350 MB free disk space.
* 6 GB RAM.
* Intel i5 4th generation core processor.

### 2. Using *VP-Viewer*

1. Launch the *VP-Viewer* application. 

2. On the tab *Tree Parameters*, choose a .csv file from your computer. The file must be separated by spaces. 

3. Insert the cardinality and dimensionality of the dataset. 

4. Choose the maximum number of elements per leaf-node.

5. Choose a distance function.

6. Choose a pivot selection algorithm.

7. Choose if you want the tree to be balanced (with overflow) or unbalanced (without overflow).

8. Click the Generate button and wait for the tree to be built. You may see the progress on the progress bar in the bottom.

Now, you may go to the *Node visualization* tab to see the directory node pivot-based distance histogram and its median. The *Query Parameters* tab enables the running of either *range* or *neighborhood* queries so that the user can see the algorithm path on the tree.

Please, see this [Youtube video](https://) for an example of the *VP-Viewer* usage.
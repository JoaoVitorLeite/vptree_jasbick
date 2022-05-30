/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_3;
    QSlider *sldrZoom;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *horizontalSpacer_4;
    QLabel *lblTree;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_4;
    QProgressBar *progressBar;
    QTabWidget *tabWidget;
    QWidget *tabTreeParameters;
    QVBoxLayout *verticalLayout;
    QFrame *frTreeParameters;
    QGridLayout *gridLayout;
    QSpinBox *spboxDimensionality;
    QComboBox *cbxPivotType;
    QSpacerItem *verticalSpacer;
    QLineEdit *edtDatasetLocation;
    QSpinBox *spboxCardinality;
    QLabel *label_16;
    QSpinBox *spboxMaxElementsPerLeaf;
    QLabel *label_5;
    QComboBox *cbxBalance;
    QPushButton *btnFileDialog;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label;
    QComboBox *cbxDistanceFunction;
    QLabel *label_15;
    QFrame *frGenerateButton;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnGenerate;
    QPushButton *btnReset;
    QSpacerItem *horizontalSpacer_6;
    QWidget *tabNodeVisualization;
    QGridLayout *gridLayout_4;
    QFrame *frame;
    QFormLayout *formLayout_2;
    QLabel *label_6;
    QComboBox *cbxNodesID;
    QLabel *label_7;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *lblPivotValue;
    QLabel *lblMedianValue;
    QLabel *lblHistogram;
    QWidget *wgetHistogram;
    QWidget *tabQueryParameters;
    QVBoxLayout *verticalLayout_3;
    QFrame *frQueryParameters;
    QGridLayout *gridLayout_5;
    QLabel *label_10;
    QLabel *label_13;
    QComboBox *cbxQueryElementID;
    QComboBox *cbxQueryAlgorithm;
    QStackedWidget *swgetQueryAlgorithms;
    QWidget *wgetRange;
    QHBoxLayout *horizontalLayout_5;
    QLabel *lblRange;
    QDoubleSpinBox *dspboxRange;
    QWidget *wgetKNN;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lblK;
    QSpinBox *spboxK;
    QStackedWidget *swgetResultOrHistogram;
    QWidget *wgetDistCalcHistogram;
    QWidget *wgetResults;
    QGridLayout *gridLayout_6;
    QPlainTextEdit *pTxtEdtResults;
    QFrame *frQueryButton;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnQuery;
    QPushButton *btnChangeStackedWidget;
    QPushButton *btnResetQuery;
    QSpacerItem *horizontalSpacer_3;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 768);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(0, 0));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMaximumSize(QSize(20, 16777215));
        frame_2->setStyleSheet(QString::fromUtf8("border: 0px"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_2->setLineWidth(0);
        horizontalLayout_3 = new QHBoxLayout(frame_2);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        sldrZoom = new QSlider(frame_2);
        sldrZoom->setObjectName(QString::fromUtf8("sldrZoom"));
        sldrZoom->setMaximumSize(QSize(30, 16777215));
        sldrZoom->setStyleSheet(QString::fromUtf8("border: 0px"));
        sldrZoom->setMinimum(0);
        sldrZoom->setMaximum(5);
        sldrZoom->setSingleStep(1);
        sldrZoom->setPageStep(1);
        sldrZoom->setValue(0);
        sldrZoom->setSliderPosition(0);
        sldrZoom->setOrientation(Qt::Vertical);
        sldrZoom->setInvertedAppearance(false);
        sldrZoom->setInvertedControls(false);

        horizontalLayout_3->addWidget(sldrZoom);


        gridLayout_2->addWidget(frame_2, 0, 1, 1, 1);

        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setStyleSheet(QString::fromUtf8(""));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 527, 697));
        gridLayout_3 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalSpacer_5 = new QSpacerItem(20, 183, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_5, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(195, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 1, 0, 1, 1);

        lblTree = new QLabel(scrollAreaWidgetContents);
        lblTree->setObjectName(QString::fromUtf8("lblTree"));
        sizePolicy1.setHeightForWidth(lblTree->sizePolicy().hasHeightForWidth());
        lblTree->setSizePolicy(sizePolicy1);
        lblTree->setScaledContents(false);
        lblTree->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(lblTree, 1, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(194, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_5, 1, 2, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 183, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_4, 2, 1, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_2->addWidget(scrollArea, 0, 0, 1, 1);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        gridLayout_2->addWidget(progressBar, 1, 0, 1, 3);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy2);
        tabWidget->setMinimumSize(QSize(450, 0));
        tabWidget->setMaximumSize(QSize(450, 16777215));
        tabTreeParameters = new QWidget();
        tabTreeParameters->setObjectName(QString::fromUtf8("tabTreeParameters"));
        verticalLayout = new QVBoxLayout(tabTreeParameters);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frTreeParameters = new QFrame(tabTreeParameters);
        frTreeParameters->setObjectName(QString::fromUtf8("frTreeParameters"));
        sizePolicy1.setHeightForWidth(frTreeParameters->sizePolicy().hasHeightForWidth());
        frTreeParameters->setSizePolicy(sizePolicy1);
        frTreeParameters->setStyleSheet(QString::fromUtf8(""));
        frTreeParameters->setFrameShape(QFrame::StyledPanel);
        frTreeParameters->setFrameShadow(QFrame::Plain);
        gridLayout = new QGridLayout(frTreeParameters);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        spboxDimensionality = new QSpinBox(frTreeParameters);
        spboxDimensionality->setObjectName(QString::fromUtf8("spboxDimensionality"));
        spboxDimensionality->setMaximum(999999999);
        spboxDimensionality->setValue(2);

        gridLayout->addWidget(spboxDimensionality, 3, 1, 1, 2);

        cbxPivotType = new QComboBox(frTreeParameters);
        cbxPivotType->setObjectName(QString::fromUtf8("cbxPivotType"));

        gridLayout->addWidget(cbxPivotType, 6, 1, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 8, 1, 1, 1);

        edtDatasetLocation = new QLineEdit(frTreeParameters);
        edtDatasetLocation->setObjectName(QString::fromUtf8("edtDatasetLocation"));

        gridLayout->addWidget(edtDatasetLocation, 0, 1, 1, 1);

        spboxCardinality = new QSpinBox(frTreeParameters);
        spboxCardinality->setObjectName(QString::fromUtf8("spboxCardinality"));
        spboxCardinality->setMaximum(999999999);
        spboxCardinality->setValue(5507);

        gridLayout->addWidget(spboxCardinality, 2, 1, 1, 2);

        label_16 = new QLabel(frTreeParameters);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout->addWidget(label_16, 5, 0, 1, 1);

        spboxMaxElementsPerLeaf = new QSpinBox(frTreeParameters);
        spboxMaxElementsPerLeaf->setObjectName(QString::fromUtf8("spboxMaxElementsPerLeaf"));
        spboxMaxElementsPerLeaf->setMaximum(999999999);
        spboxMaxElementsPerLeaf->setValue(350);

        gridLayout->addWidget(spboxMaxElementsPerLeaf, 4, 1, 1, 2);

        label_5 = new QLabel(frTreeParameters);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        cbxBalance = new QComboBox(frTreeParameters);
        cbxBalance->setObjectName(QString::fromUtf8("cbxBalance"));
        cbxBalance->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(cbxBalance, 7, 1, 1, 2);

        btnFileDialog = new QPushButton(frTreeParameters);
        btnFileDialog->setObjectName(QString::fromUtf8("btnFileDialog"));
        sizePolicy.setHeightForWidth(btnFileDialog->sizePolicy().hasHeightForWidth());
        btnFileDialog->setSizePolicy(sizePolicy);
        btnFileDialog->setMinimumSize(QSize(24, 24));
        btnFileDialog->setMaximumSize(QSize(24, 24));
        btnFileDialog->setBaseSize(QSize(24, 24));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/folderIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnFileDialog->setIcon(icon);

        gridLayout->addWidget(btnFileDialog, 0, 2, 1, 1);

        label_3 = new QLabel(frTreeParameters);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 6, 0, 1, 1);

        label_2 = new QLabel(frTreeParameters);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        label_4 = new QLabel(frTreeParameters);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 7, 0, 1, 1);

        label = new QLabel(frTreeParameters);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        cbxDistanceFunction = new QComboBox(frTreeParameters);
        cbxDistanceFunction->setObjectName(QString::fromUtf8("cbxDistanceFunction"));

        gridLayout->addWidget(cbxDistanceFunction, 5, 1, 1, 2);

        label_15 = new QLabel(frTreeParameters);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout->addWidget(label_15, 3, 0, 1, 1);


        verticalLayout->addWidget(frTreeParameters);

        frGenerateButton = new QFrame(tabTreeParameters);
        frGenerateButton->setObjectName(QString::fromUtf8("frGenerateButton"));
        frGenerateButton->setStyleSheet(QString::fromUtf8(""));
        frGenerateButton->setFrameShape(QFrame::StyledPanel);
        frGenerateButton->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frGenerateButton);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnGenerate = new QPushButton(frGenerateButton);
        btnGenerate->setObjectName(QString::fromUtf8("btnGenerate"));
        btnGenerate->setAutoDefault(true);

        horizontalLayout_2->addWidget(btnGenerate);

        btnReset = new QPushButton(frGenerateButton);
        btnReset->setObjectName(QString::fromUtf8("btnReset"));

        horizontalLayout_2->addWidget(btnReset);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);


        verticalLayout->addWidget(frGenerateButton);

        tabWidget->addTab(tabTreeParameters, QString());
        tabNodeVisualization = new QWidget();
        tabNodeVisualization->setObjectName(QString::fromUtf8("tabNodeVisualization"));
        gridLayout_4 = new QGridLayout(tabNodeVisualization);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        frame = new QFrame(tabNodeVisualization);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy3);
        frame->setStyleSheet(QString::fromUtf8(""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        formLayout_2 = new QFormLayout(frame);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_6);

        cbxNodesID = new QComboBox(frame);
        cbxNodesID->setObjectName(QString::fromUtf8("cbxNodesID"));
        cbxNodesID->setInsertPolicy(QComboBox::InsertAtBottom);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, cbxNodesID);

        label_7 = new QLabel(frame);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_7);

        label_9 = new QLabel(frame);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_9);

        label_11 = new QLabel(frame);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_11);

        lblPivotValue = new QLabel(frame);
        lblPivotValue->setObjectName(QString::fromUtf8("lblPivotValue"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lblPivotValue->sizePolicy().hasHeightForWidth());
        lblPivotValue->setSizePolicy(sizePolicy4);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, lblPivotValue);

        lblMedianValue = new QLabel(frame);
        lblMedianValue->setObjectName(QString::fromUtf8("lblMedianValue"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, lblMedianValue);

        lblHistogram = new QLabel(frame);
        lblHistogram->setObjectName(QString::fromUtf8("lblHistogram"));

        formLayout_2->setWidget(5, QFormLayout::FieldRole, lblHistogram);


        gridLayout_4->addWidget(frame, 0, 0, 1, 1);

        wgetHistogram = new QWidget(tabNodeVisualization);
        wgetHistogram->setObjectName(QString::fromUtf8("wgetHistogram"));

        gridLayout_4->addWidget(wgetHistogram, 1, 0, 1, 1);

        tabWidget->addTab(tabNodeVisualization, QString());
        tabQueryParameters = new QWidget();
        tabQueryParameters->setObjectName(QString::fromUtf8("tabQueryParameters"));
        verticalLayout_3 = new QVBoxLayout(tabQueryParameters);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frQueryParameters = new QFrame(tabQueryParameters);
        frQueryParameters->setObjectName(QString::fromUtf8("frQueryParameters"));
        frQueryParameters->setStyleSheet(QString::fromUtf8(""));
        frQueryParameters->setFrameShape(QFrame::StyledPanel);
        frQueryParameters->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frQueryParameters);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_10 = new QLabel(frQueryParameters);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy5);

        gridLayout_5->addWidget(label_10, 1, 0, 1, 1);

        label_13 = new QLabel(frQueryParameters);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy5.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy5);

        gridLayout_5->addWidget(label_13, 0, 0, 1, 1);

        cbxQueryElementID = new QComboBox(frQueryParameters);
        cbxQueryElementID->setObjectName(QString::fromUtf8("cbxQueryElementID"));

        gridLayout_5->addWidget(cbxQueryElementID, 0, 1, 1, 1);

        cbxQueryAlgorithm = new QComboBox(frQueryParameters);
        cbxQueryAlgorithm->setObjectName(QString::fromUtf8("cbxQueryAlgorithm"));
        QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(cbxQueryAlgorithm->sizePolicy().hasHeightForWidth());
        cbxQueryAlgorithm->setSizePolicy(sizePolicy6);

        gridLayout_5->addWidget(cbxQueryAlgorithm, 1, 1, 1, 1);

        swgetQueryAlgorithms = new QStackedWidget(frQueryParameters);
        swgetQueryAlgorithms->setObjectName(QString::fromUtf8("swgetQueryAlgorithms"));
        sizePolicy6.setHeightForWidth(swgetQueryAlgorithms->sizePolicy().hasHeightForWidth());
        swgetQueryAlgorithms->setSizePolicy(sizePolicy6);
        swgetQueryAlgorithms->setLineWidth(1);
        wgetRange = new QWidget();
        wgetRange->setObjectName(QString::fromUtf8("wgetRange"));
        horizontalLayout_5 = new QHBoxLayout(wgetRange);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        lblRange = new QLabel(wgetRange);
        lblRange->setObjectName(QString::fromUtf8("lblRange"));
        sizePolicy.setHeightForWidth(lblRange->sizePolicy().hasHeightForWidth());
        lblRange->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(lblRange);

        dspboxRange = new QDoubleSpinBox(wgetRange);
        dspboxRange->setObjectName(QString::fromUtf8("dspboxRange"));
        sizePolicy6.setHeightForWidth(dspboxRange->sizePolicy().hasHeightForWidth());
        dspboxRange->setSizePolicy(sizePolicy6);
        dspboxRange->setDecimals(4);
        dspboxRange->setMaximum(99999999.000000000000000);

        horizontalLayout_5->addWidget(dspboxRange);

        swgetQueryAlgorithms->addWidget(wgetRange);
        wgetKNN = new QWidget();
        wgetKNN->setObjectName(QString::fromUtf8("wgetKNN"));
        horizontalLayout_4 = new QHBoxLayout(wgetKNN);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lblK = new QLabel(wgetKNN);
        lblK->setObjectName(QString::fromUtf8("lblK"));
        sizePolicy.setHeightForWidth(lblK->sizePolicy().hasHeightForWidth());
        lblK->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(lblK);

        spboxK = new QSpinBox(wgetKNN);
        spboxK->setObjectName(QString::fromUtf8("spboxK"));
        sizePolicy6.setHeightForWidth(spboxK->sizePolicy().hasHeightForWidth());
        spboxK->setSizePolicy(sizePolicy6);
        spboxK->setMaximum(99999999);

        horizontalLayout_4->addWidget(spboxK);

        swgetQueryAlgorithms->addWidget(wgetKNN);

        gridLayout_5->addWidget(swgetQueryAlgorithms, 2, 0, 1, 2);

        swgetResultOrHistogram = new QStackedWidget(frQueryParameters);
        swgetResultOrHistogram->setObjectName(QString::fromUtf8("swgetResultOrHistogram"));
        wgetDistCalcHistogram = new QWidget();
        wgetDistCalcHistogram->setObjectName(QString::fromUtf8("wgetDistCalcHistogram"));
        swgetResultOrHistogram->addWidget(wgetDistCalcHistogram);
        wgetResults = new QWidget();
        wgetResults->setObjectName(QString::fromUtf8("wgetResults"));
        gridLayout_6 = new QGridLayout(wgetResults);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        pTxtEdtResults = new QPlainTextEdit(wgetResults);
        pTxtEdtResults->setObjectName(QString::fromUtf8("pTxtEdtResults"));

        gridLayout_6->addWidget(pTxtEdtResults, 0, 0, 1, 1);

        swgetResultOrHistogram->addWidget(wgetResults);

        gridLayout_5->addWidget(swgetResultOrHistogram, 3, 0, 1, 2);


        verticalLayout_3->addWidget(frQueryParameters);

        frQueryButton = new QFrame(tabQueryParameters);
        frQueryButton->setObjectName(QString::fromUtf8("frQueryButton"));
        frQueryButton->setStyleSheet(QString::fromUtf8(""));
        frQueryButton->setFrameShape(QFrame::StyledPanel);
        frQueryButton->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frQueryButton);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnQuery = new QPushButton(frQueryButton);
        btnQuery->setObjectName(QString::fromUtf8("btnQuery"));

        horizontalLayout->addWidget(btnQuery);

        btnChangeStackedWidget = new QPushButton(frQueryButton);
        btnChangeStackedWidget->setObjectName(QString::fromUtf8("btnChangeStackedWidget"));
        btnChangeStackedWidget->setEnabled(true);

        horizontalLayout->addWidget(btnChangeStackedWidget);

        btnResetQuery = new QPushButton(frQueryButton);
        btnResetQuery->setObjectName(QString::fromUtf8("btnResetQuery"));

        horizontalLayout->addWidget(btnResetQuery);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout_3->addWidget(frQueryButton);

        tabWidget->addTab(tabQueryParameters, QString());

        gridLayout_2->addWidget(tabWidget, 0, 2, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        btnGenerate->setDefault(true);
        cbxQueryAlgorithm->setCurrentIndex(-1);
        swgetQueryAlgorithms->setCurrentIndex(1);
        swgetResultOrHistogram->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "VP-Viewer", nullptr));
        lblTree->setText(QCoreApplication::translate("MainWindow", "Empty", nullptr));
        cbxPivotType->setCurrentText(QString());
        edtDatasetLocation->setText(QCoreApplication::translate("MainWindow", "/home/notox/VP-Viewer/Datasets/cities.csv", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Distance function:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Cardinality:", nullptr));
        btnFileDialog->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "Pivot algorithm:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "MaxElementsPerLeaf:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Balance:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Data set:", nullptr));
        cbxDistanceFunction->setCurrentText(QString());
        label_15->setText(QCoreApplication::translate("MainWindow", "Dimensionality:", nullptr));
        btnGenerate->setText(QCoreApplication::translate("MainWindow", "Generate", nullptr));
        btnReset->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabTreeParameters), QCoreApplication::translate("MainWindow", "Tree Parameters", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Node ID:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Pivot Value:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Median:", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Maximum Distance:", nullptr));
        lblPivotValue->setText(QCoreApplication::translate("MainWindow", "NULL", nullptr));
        lblMedianValue->setText(QCoreApplication::translate("MainWindow", "NULL", nullptr));
        lblHistogram->setText(QCoreApplication::translate("MainWindow", "NULL", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabNodeVisualization), QCoreApplication::translate("MainWindow", "Node Visualization", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Query Algorithm:", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Query Element ID:", nullptr));
        lblRange->setText(QCoreApplication::translate("MainWindow", "Range:", nullptr));
        lblK->setText(QCoreApplication::translate("MainWindow", "K: ", nullptr));
        btnQuery->setText(QCoreApplication::translate("MainWindow", "Query!", nullptr));
        btnChangeStackedWidget->setText(QCoreApplication::translate("MainWindow", "Show Results", nullptr));
        btnResetQuery->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabQueryParameters), QCoreApplication::translate("MainWindow", "Query Parameters", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

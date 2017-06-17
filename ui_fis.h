/********************************************************************************
** Form generated from reading UI file 'fis.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIS_H
#define UI_FIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FIS
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QGraphicsView *originalimage;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_2;
    QRadioButton *radioSeg1;
    QRadioButton *radioSeg2;
    QGraphicsView *initseg;
    QGraphicsView *post;
    QLabel *label_5;
    QLabel *label_6;
    QFrame *line;
    QFrame *line_2;
    QGraphicsView *reference;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QLabel *label_7;
    QRadioButton *radioSeg2_2;
    QGraphicsView *comparison;
    QLabel *label_8;
    QLabel *label_3;
    QLabel *label_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FIS)
    {
        if (FIS->objectName().isEmpty())
            FIS->setObjectName(QStringLiteral("FIS"));
        FIS->resize(833, 633);
        QIcon icon;
        icon.addFile(QStringLiteral(":/resource/img/fingerprint.png"), QSize(), QIcon::Normal, QIcon::Off);
        FIS->setWindowIcon(icon);
        centralWidget = new QWidget(FIS);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(30, 10, 75, 23));
        originalimage = new QGraphicsView(centralWidget);
        originalimage->setObjectName(QStringLiteral("originalimage"));
        originalimage->setGeometry(QRect(30, 40, 301, 231));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 270, 251, 20));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 390, 141, 20));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 310, 111, 23));
        radioSeg1 = new QRadioButton(centralWidget);
        radioSeg1->setObjectName(QStringLiteral("radioSeg1"));
        radioSeg1->setGeometry(QRect(50, 420, 131, 17));
        radioSeg2 = new QRadioButton(centralWidget);
        radioSeg2->setObjectName(QStringLiteral("radioSeg2"));
        radioSeg2->setGeometry(QRect(50, 450, 141, 17));
        initseg = new QGraphicsView(centralWidget);
        initseg->setObjectName(QStringLiteral("initseg"));
        initseg->setGeometry(QRect(200, 310, 301, 231));
        post = new QGraphicsView(centralWidget);
        post->setObjectName(QStringLiteral("post"));
        post->setGeometry(QRect(510, 310, 301, 231));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(290, 550, 131, 20));
        label_5->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(590, 550, 131, 20));
        label_6->setAlignment(Qt::AlignCenter);
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 290, 801, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(380, 20, 20, 251));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        reference = new QGraphicsView(centralWidget);
        reference->setObjectName(QStringLiteral("reference"));
        reference->setGeometry(QRect(430, 70, 150, 115));
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(430, 10, 121, 23));
        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(540, 240, 121, 23));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(430, 199, 361, 31));
        QFont font;
        font.setPointSize(18);
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignCenter);
        radioSeg2_2 = new QRadioButton(centralWidget);
        radioSeg2_2->setObjectName(QStringLiteral("radioSeg2_2"));
        radioSeg2_2->setGeometry(QRect(50, 480, 141, 17));
        comparison = new QGraphicsView(centralWidget);
        comparison->setObjectName(QStringLiteral("comparison"));
        comparison->setGeometry(QRect(630, 70, 150, 115));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(20, 520, 161, 31));
        QFont font1;
        font1.setPointSize(12);
        label_8->setFont(font1);
        label_8->setLayoutDirection(Qt::LeftToRight);
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(430, 190, 151, 20));
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(630, 190, 151, 20));
        label_4->setAlignment(Qt::AlignCenter);
        FIS->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FIS);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 833, 21));
        FIS->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FIS);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        FIS->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FIS);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        FIS->setStatusBar(statusBar);

        retranslateUi(FIS);

        QMetaObject::connectSlotsByName(FIS);
    } // setupUi

    void retranslateUi(QMainWindow *FIS)
    {
        FIS->setWindowTitle(QApplication::translate("FIS", "Fingerprint Image Segmentation", Q_NULLPTR));
        pushButton->setText(QApplication::translate("FIS", "Import Image", Q_NULLPTR));
        label->setText(QApplication::translate("FIS", "Original ", Q_NULLPTR));
        label_2->setText(QApplication::translate("FIS", "Segmentation method", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("FIS", "Apply Segmentation", Q_NULLPTR));
        radioSeg1->setText(QApplication::translate("FIS", "Simple Segmentation", Q_NULLPTR));
        radioSeg2->setText(QApplication::translate("FIS", "Simple Segmentation 2", Q_NULLPTR));
        label_5->setText(QApplication::translate("FIS", "Initial segmentation", Q_NULLPTR));
        label_6->setText(QApplication::translate("FIS", "Post-processing", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("FIS", "Import Reference", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("FIS", "Calc. Comparison Score", Q_NULLPTR));
        label_7->setText(QString());
        radioSeg2_2->setText(QApplication::translate("FIS", "Harris Corner Point", Q_NULLPTR));
        label_8->setText(QString());
        label_3->setText(QApplication::translate("FIS", "Reference Image", Q_NULLPTR));
        label_4->setText(QApplication::translate("FIS", "Segmented Comparison", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FIS: public Ui_FIS {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIS_H

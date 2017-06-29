#include "FIS.h"
#include "SimpleSegmentation.h"
#include "SimpleSegmentation2.h"
#include "HarrisCornerPoint.h"

#include "ui_fis.h"
#include <iostream>
#include <QtDebug>
#include <qfiledialog.h>
#include <QFile>
#include <QPixmap>
#include <QGraphicsPixmapItem>

using namespace std;

FIS::FIS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FIS)
{
    ui->setupUi(this);
    ui->radioSeg1->setChecked(true);
    image = new QImage(NULL);

}

FIS::~FIS()
{
    delete ui;
}

void FIS::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),"",tr("Image Files (*.png *.jpg *.bpm *.jpeg *.TIF)"));
    if (fileName == "")
        return;
    image = new QImage(fileName);
    clearViews();

    scene = new QGraphicsScene(this);
    ui->originalimage->setScene(scene);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));
    scene->addItem(item);
    ui->originalimage->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
    ui->originalimage->show();

}

void FIS::on_pushButton_2_clicked()
{
    if(image->isNull())
        return;

    cv::Mat img = convertQImageToMat(*image,CV_8UC4);
    QImage  _postP, _initS, _comp;

    if(ui->radioSeg1->isChecked()){
        const clock_t begin_time = clock();
        SimpleSegmentation simpleSeg;
        simpleSeg.Segmentation(img);
        comparableImg = simpleSeg.comparisonImg;

        _postP = convertMatToQImage(simpleSeg.postProcessing);
        _initS = convertMatToQImage(simpleSeg.initSeg);
        _comp = convertMatToQImage(comparableImg);

        postP = &_postP;
        initSeg = &_initS;
        comp = &_comp;
        updateViews(*postP, *initSeg, *comp,float( clock () - begin_time ) /  CLOCKS_PER_SEC);

    }else if(ui->radioSeg2->isChecked()){
        const clock_t begin_time = clock();

        SimpleSegmentation2 simpleSeg;
        simpleSeg.Segmentation(img);

        comparableImg = simpleSeg.comparisonImg;

        _postP = convertMatToQImage(simpleSeg.postProcessing);
        _initS = convertMatToQImage(simpleSeg.initSeg);
        _comp = convertMatToQImage(comparableImg);

        postP = &_postP;
        initSeg = &_initS;
        comp = &_comp;
        updateViews(*postP, *initSeg,*comp,float( clock () - begin_time ) /  CLOCKS_PER_SEC);

    }else if(ui->radioSeg2_2->isChecked()){
        const clock_t begin_time = clock();
        HarrisCornerPoint harris(img,50);
        comparableImg = harris.comparisonImg;

        _postP = convertMatToQImage(harris.postProcessing);
        _initS = convertMatToQImage(harris.initSeg);
        _comp = convertMatToQImage(comparableImg);

        postP = &_postP;
        initSeg = &_initS;
        comp = &_comp;
        updateViews(*postP, *initSeg, *comp,float( clock () - begin_time ) /  CLOCKS_PER_SEC);

    }

    img.release();
}

cv::Mat FIS::convertQImageToMat(QImage &img, int format){
    return cv::Mat(img.height(), img.width(),
                   format, img.bits(), img.bytesPerLine());
}
QImage FIS::convertMatToQImage(cv::Mat &mat){
    return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
}

void FIS::updateViews(QImage postP, QImage initSeg, QImage comp, double time){

    scene = new QGraphicsScene(this);
    ui->post->setScene(scene);
    QGraphicsPixmapItem* gradY = new QGraphicsPixmapItem(QPixmap::fromImage(postP));
    scene->addItem(gradY);
    ui->post->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
    ui->post->show();

    scene = new QGraphicsScene(this);
    ui->initseg->setScene(scene);
    QGraphicsPixmapItem* inits = new QGraphicsPixmapItem(QPixmap::fromImage(initSeg));
    scene->addItem(inits);
    ui->initseg->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
    ui->initseg->show();

    scene = new QGraphicsScene(this);
    ui->comparison->setScene(scene);
    QGraphicsPixmapItem* _comp = new QGraphicsPixmapItem(QPixmap::fromImage(comp));
    scene->addItem(_comp);
    ui->comparison->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
    ui->comparison->show();

    ui->label_8->setText("Time : "+QString::number(time) + "s");
}

void FIS::on_pushButton_5_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),"",tr("Image Files (*.png *.jpg *.bpm *.jpeg *.TIF)"));
    if (fileName == "")
        return;
    comparisonImage = new QImage(fileName);
    referenceImg = convertQImageToMat(*comparisonImage,CV_8UC4);

    scene = new QGraphicsScene(this);
    ui->reference->setScene(scene);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*comparisonImage));
    scene->addItem(item);
    ui->reference->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
    ui->reference->show();
}

void FIS::on_pushButton_6_clicked()
{
    if(comparableImg.size != referenceImg.size){
        ui->label_7->setText("<font color='red'>Images are not same size!</font>");
        return;
    }else
        ui->label_7->setText("");

    cv::Mat referenceImgg, bitwise;
    cvtColor( referenceImg, referenceImgg, CV_BGR2GRAY );
    bitwise_and(comparableImg, referenceImgg, bitwise);
    double dice = 2*countNonZero(bitwise)/(double)(countNonZero(comparableImg) + countNonZero(referenceImgg));

    double under = 0, over = 0;
    for(int i = 0; i < comparableImg.cols;i++){
        for(int h = 0; h < comparableImg.rows;h++){
            if((referenceImg.col(i).row(h).data[0] == 255) && (comparableImg.col(i).row(h).data[0] != 255))
                under++;
            if((referenceImg.col(i).row(h).data[0] != 255) && (comparableImg.col(i).row(h).data[0] == 255))
                over++;
        }
    }

    cv::Mat m;
    cv::extractChannel(referenceImg, m, 0);
    int nonZeros = countNonZero(m);

    under = under/(double)(nonZeros) * 100;
    over = over/(double)((referenceImg.cols*referenceImg.rows)-nonZeros) * 100;
    ui->label_7->setText("Dice distance : "+QString::number( dice*100, 'f', 2) + "%" );
    ui->label_9->setText("Over segmented area : "+QString::number(over, 'f', 2) + "%, under segmented area : " + QString::number(under, 'f', 2)+"%");
}

void FIS::clearViews(){
    scene = new QGraphicsScene(this);
    ui->reference->setScene(scene);
    scene->clear();

    ui->originalimage->setScene(scene);
    scene->clear();

    ui->initseg->setScene(scene);
    scene->clear();

    ui->post->setScene(scene);
    scene->clear();

    ui->comparison->setScene(scene);
    scene->clear();

    ui->label_7->clear();
    ui->label_9->clear();
}

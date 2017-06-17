#ifndef FIS_H
#define FIS_H

#include <QMainWindow>
#include <QGraphicsScene>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace Ui {
class FIS;
}

class FIS : public QMainWindow
{
    Q_OBJECT
public:
    explicit FIS(QWidget *parent = 0);
    ~FIS();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();


private:
    Ui::FIS *ui;
    QGraphicsScene *scene;
    QImage* image, *comparisonImage;
    QImage* initSeg,*postP,*comp;
    cv::Mat comparableImg,referenceImg;

    cv::Mat convertQImageToMat(QImage &img, int format);
    QImage convertMatToQImage(cv::Mat &mat);
    void updateViews(QImage postP,QImage initSeg, QImage comp, double time);
    void clearViews();

};

#endif // FIS_H

#ifndef SEGMENTATION1_H
#define SEGMENTATION1_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class SimpleSegmentation
{
public:
    void Segmentation(cv::Mat& img);
    cv::Mat postProcessing, initSeg, comparisonImg;

private:
     void setGradientImage(int type, cv::Mat image);
     bool makeForeground(cv::Mat result,int blockCol, int blockRow, int blockSize,int foregroundColor);
};

#endif // SEGMENTATION1_H

#ifndef SIMPLESEGMENTATION2_H
#define SIMPLESEGMENTATION2_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class SimpleSegmentation2
{
public:
    void Segmentation(cv::Mat& img);
    cv::Mat postProcessing, initSeg, comparisonImg;

private:
    cv::Mat fspecialLoG(int WinSize, double sigma);
};

#endif // SIMPLESEGMENTATION2_H

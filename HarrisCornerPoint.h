#ifndef HARRISCORNERPOINT_H
#define HARRISCORNERPOINT_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class HarrisCornerPoint
{
public:
    HarrisCornerPoint(cv::Mat& img, double thresh);
    cv::Mat postProcessing, initSeg, comparisonImg;

};

#endif // HARRISCORNERPOINT_H

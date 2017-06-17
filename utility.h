#ifndef UTILITY_H
#define UTILITY_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
class Utility
{
public:
    static double calcBlockMean(cv::Mat gradientMat, int blockCol, int blockRow, int blockSize);
    static double calcBlockVariance(cv::Mat gradientMat,double blockMean, int blockCol, int blockRow, int blockSize);
    static void colorBlock(cv::Mat& image, int blockCol, int blockRow, int blockSize,int blockColor);

};

#endif // UTILITY_H

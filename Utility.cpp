#include "utility.h"



void Utility::colorBlock(cv::Mat& image, int blockCol, int blockRow, int blockSize, int blockColor){
    int startCol, startRow;
    if((blockCol - blockSize) < 0 )
        startCol = (int)(blockSize / 2);
    else
        startCol = blockCol - blockSize;

    if(blockRow - blockSize < 0)
        startRow = (int)(blockSize / 2);
    else
        startRow = blockRow - blockSize;

    for(int i = startCol;i < blockCol; i ++){
        for(int h = startRow;h < blockRow; h ++){
            image.col(i).row(h).data[0] = blockColor;
        }
    }
}

double Utility::calcBlockMean(cv::Mat gradientMat, int blockCol, int blockRow, int blockSize){
    double mean = 0;
    for(int i = blockCol - blockSize;i < blockCol; i ++){
        for(int h = blockRow - blockSize;h < blockRow; h ++){
            mean +=  gradientMat.col(i).row(h).data[0];
        }
    }
   return mean / (pow(blockSize,2));
}

double Utility::calcBlockVariance(cv::Mat gradientMat,double blockMean, int blockCol, int blockRow, int blockSize){
    double variance = 0;
    for(int i = blockCol - blockSize;i < blockCol; i ++){
        for(int h = blockRow - blockSize;h < blockRow; h ++){
            variance +=  pow(gradientMat.col(i).row(h).data[0]-blockMean,2);
        }
    }
    if(variance < 0.1)
        variance = 0.1;

    return (variance / pow(blockSize,2));
}



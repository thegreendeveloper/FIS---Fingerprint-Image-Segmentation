#include "SimpleSegmentation.h"
#include <QtDebug>
#include "utility.h"

void SimpleSegmentation::Segmentation(cv::Mat& img){
    cv::Mat result;
    cv::cvtColor(img,result,CV_BGR2GRAY);

    /* 2-dimensional gaussian function. Gaussian blur has been minimized because the
    image quality of a smartphone picture is very high. */
    cv::GaussianBlur(result,result,cv::Size(7,7),0,0);

    //Histogam euqualization
    cv::equalizeHist(result,result);

    //Computing gradients on x an y directions
    cv::Mat gradientX,gradientY;
    cv::Sobel( result, gradientX, result.depth(), 0, 1, 5, 1, 0, cv::BORDER_DEFAULT );
    cv::Sobel( result, gradientY, result.depth(), 1, 0, 5, 1, 0, cv::BORDER_DEFAULT );

    //Calculate each block mean, variance and deviation ( 8 x 8 blocks)
    int blocksize = 8, blockNo = 0, numberOfBlocks = gradientX.cols * gradientX.rows / (blocksize*blocksize);
    double meanX[numberOfBlocks] = {0}, meanY[numberOfBlocks] = {0}, varX[numberOfBlocks] = {0}, varY[numberOfBlocks] = {0};

    for(int i = blocksize; i < gradientX.cols;i+=blocksize){
        for(int h = blocksize; h < gradientX.rows; h+=blocksize){
            blockNo++;
            meanX[blockNo] = Utility::calcBlockMean(gradientX,i,h,blocksize);
            meanY[blockNo] = Utility::calcBlockMean(gradientY,i,h,blocksize);
            varX[blockNo] = Utility::calcBlockVariance(gradientX,meanX[blockNo],i,h,blocksize);
            varY[blockNo] = Utility::calcBlockVariance(gradientY,meanY[blockNo],i,h,blocksize);
        }
    }

    //Compute gradient variance mean (step 5 )
    double gradientVarianceMeanX = 0,gradientVarianceMeanY = 0,blockGradientSumX = 0,blockGradientSumY = 0;
    for(int i = 0; i < numberOfBlocks;i++){        
        gradientVarianceMeanX += varX[i];
        gradientVarianceMeanY += varY[i];

    }

    gradientVarianceMeanX = (gradientVarianceMeanX/numberOfBlocks);
    gradientVarianceMeanY = (gradientVarianceMeanY/numberOfBlocks);

    //qDebug() <<"gradientvariancemeanX "<< gradientVarianceMeanX;
    //qDebug() <<"gradientvariancemeanY "<< gradientVarianceMeanY;

    //Specified regional variance (step 6)
    int NSx = 0, NSy = 0;
    double VFx = 0, VFy = 0;
    for(int i = 0; i < numberOfBlocks;i++){
        if(varX[i] >= gradientVarianceMeanX){
            NSx++;
            blockGradientSumX += varX[i];
        }
        if(varY[i] >= gradientVarianceMeanY){
            NSy++;
            blockGradientSumY += varY[i];
        }
    }

    VFx = (blockGradientSumX / NSx);
    VFy = (blockGradientSumY / NSy);

    //qDebug() << "NSx "<< NSx << "\nNSy " << NSy << "\nVFx " << VFx << "\nVFy " << VFy;

    //Calculate threshold (step 7)
    blockGradientSumX = 0, blockGradientSumY = 0;
    int NSTx = 0, NSTy = 0;
    double VTx = 0, VTy = 0;
    for(int i = 0; i < numberOfBlocks;i++){
        if(VFx <= varX[i]/*meanX[i]*/){
            NSTx++;
            blockGradientSumX += varX[i];
        }
        if(VFy <= varY[i]/*meanY[i]*/){
            NSTy++;
            blockGradientSumY += varY[i];
        }
    }
    VTx = blockGradientSumX / NSTx;
    VTy = blockGradientSumY / NSTy;

    //qDebug() <<"\nNSTx " <<NSTx << "\nNSTy " << NSTy <<"\nVTx "<< VTx << "\nVTy " << VTy;

    result.copyTo(comparisonImg);
    result.copyTo(postProcessing);
    //Apply segmentation
    int counter = 0;
    blockNo = 0;
    for(int i = blocksize; i < gradientX.cols;i+=blocksize){
        for(int h = blocksize; h < gradientX.rows; h+=blocksize){
            blockNo++;
            if(varX[blockNo] < VTx && varY[blockNo] < VTy){
                counter++;
                Utility::colorBlock(result,i,h,blocksize,100);
                Utility::colorBlock(comparisonImg,i,h,blocksize,0);
            }else{
                Utility::colorBlock(comparisonImg,i,h,blocksize,255);
            }

        }
    }
    initSeg = result;
    //qDebug() << "counter : "<<counter << " blocks " << blockNo;

    //post processing (5x5 blocks)
    blocksize = 5;
    counter = 0;
    for(int i = blocksize; i < gradientX.cols;i+=blocksize){
        for(int h = blocksize; h < gradientX.rows; h+=blocksize){
            bool changeColor = makeForeground(result,i, h, blocksize,100);
            blockNo++;
            if (changeColor){
                    counter++;
                    Utility::colorBlock(result,i,h,blocksize,result.col(i).row(h).data[0]);
                    Utility::colorBlock(postProcessing,i,h,blocksize,255);
                    Utility::colorBlock(comparisonImg,i,h,blocksize,255);
            }
        }
    }
    //qDebug() << "blocks to be changed : "<<counter;
    img = result;

}

bool SimpleSegmentation::makeForeground(cv::Mat result,int blockCol, int blockRow, int blockSize,int foregroundColor){
    if(result.col(blockCol).row(blockRow).data[0] != foregroundColor)
        return false;

    int counter = 0;
    if(blockCol - 2*blockSize >= 0){
        if(result.col(blockCol-blockSize).row(blockRow).data[0] != foregroundColor)
            counter++;
        if(blockRow - 2*blockSize >= 0){
            if(result.col(blockCol-blockSize).row(blockRow-blockSize).data[0] != foregroundColor)
                counter++;
        }
        if(blockRow + blockSize < result.rows){
            if(result.col(blockCol-blockSize).row(blockRow+blockSize).data[0] != foregroundColor)
                counter++;
        }
    }
    if(blockCol + blockSize < result.cols){
        if(blockRow - 2*blockSize >= 0){
            if(result.col(blockCol+blockSize).row(blockRow-blockSize).data[0] != foregroundColor)
                counter++;
        }
        if(blockRow + blockSize < result.rows){
            if(result.col(blockCol+blockSize).row(blockRow+blockSize).data[0] != foregroundColor)
                counter++;
        }
    }
    if(blockRow + blockSize < result.rows){
        if(result.col(blockCol).row(blockRow+blockSize).data[0] != foregroundColor)
            counter++;
    }
    if(blockRow - 2*blockSize >= 0){
        if(result.col(blockCol).row(blockRow-blockSize).data[0] != foregroundColor)
            counter++;
    }
    if (counter > 3)
        return true;
    return false;
}




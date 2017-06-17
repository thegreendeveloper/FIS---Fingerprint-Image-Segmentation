#include "SimpleSegmentation2.h"
#include "utility.h"

#include <QtDebug>

/*Does not work at all on the captured smartphone photos. This is due to the normalization of the image,
where the kontrast are simply not strong enough on the smartphone photos. This solution would also needs another
way of comparing the results as in only returns 'lines' in the fingerprint*/

void SimpleSegmentation2::Segmentation(cv::Mat& img){
    cv::Mat result;
    cv::cvtColor(img,result,CV_BGR2GRAY);

    //Normalize (step 2)
    normalize(result, result, 0, 1, cv::NORM_MINMAX, CV_8U);

    //Apply LOG (step 3) Laplacian of Gaussian http://homepages.inf.ed.ac.uk/rbf/HIPR2/log.htm
    cv::GaussianBlur(result,result,cv::Size(7,7),3.5,3.5);
    cv::Laplacian( result, result, result.depth(), 7, 1, 0, cv::BORDER_DEFAULT );

    //Normalize (step 4)
    normalize(result, result, 0, 1, cv::NORM_MINMAX, CV_8U);

    //Apply threshold (step 5) threshold : 0.004
    double threshold = 0.004;
    for(int i = 0; i < result.cols;i++){
        for(int h= 0;h < result.rows;h++){
            if(result.col(i).row(h).data[0] < threshold)
                result.col(i).row(h).data[0] = 0;
        }
    }
    cv::GaussianBlur(result,result,cv::Size(7,7),2,2);
    cv::Laplacian( result, result, result.depth(), 7, 1, 0, cv::BORDER_DEFAULT );

    //Compute gradient (step 6)
    cv::Mat gradientY;
    cv::Sobel( result, gradientY, result.depth(), 1, 0, 5, 1, 0, cv::BORDER_DEFAULT );

    //Apply morpheological methods (step 7)
    cv::morphologyEx(gradientY,gradientY, cv::MORPH_CLOSE, 5);

    gradientY.copyTo(initSeg);
    gradientY.copyTo(comparisonImg);
    gradientY.copyTo(result);

    for(int i = 0; i<result.cols;i++){
        for(int h = 0; h < result.rows;h++){
            if(result.col(i).row(h).data[0] != 0){
                Utility::colorBlock(comparisonImg,i,h,5,255);
            }
        }
    }
    comparisonImg.copyTo(postProcessing);
    img = result;
}

// return NxN (square kernel) of Laplacian of Gaussian as is returned by     Matlab's: fspecial(Winsize,sigma)
cv::Mat SimpleSegmentation2::fspecialLoG(int WinSize, double sigma){
    // I wrote this only for square kernels as I have no need for kernels that aren't square
    cv::Mat xx (WinSize,WinSize,CV_64F);
    for (int i=0;i<WinSize;i++){
        for (int j=0;j<WinSize;j++){
            xx.at<double>(j,i) = (i-(WinSize-1)/2)*(i-(WinSize-1)/2);
        }
    }

    cv::Mat yy;
    cv::transpose(xx,yy);
    cv::Mat arg = -(xx+yy)/(2*pow(sigma,2));
    cv::Mat h (WinSize,WinSize,CV_64F);
    for (int i=0;i<WinSize;i++){
        for (int j=0;j<WinSize;j++){
            h.at<double>(j,i) = pow(exp(1),(arg.at<double>(j,i)));
        }
    }
    double minimalVal, maximalVal;
    minMaxLoc(h, &minimalVal, &maximalVal);
    cv::Mat tempMask = (h>DBL_EPSILON*maximalVal)/255;
    tempMask.convertTo(tempMask,h.type());
    cv::multiply(tempMask,h,h);

    if (cv::sum(h)[0]!=0)
    {h=h/cv::sum(h)[0];}

    cv::Mat h1 = (xx+yy-2*(pow(sigma,2))/(pow(sigma,4)));
    cv::multiply(h,h1,h1);
    h = h1 - cv::sum(h1)[0]/(WinSize*WinSize);
    return h;
}



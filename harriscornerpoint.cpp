#include "HarrisCornerPoint.h"
#include <QtDebug>
#include "utility.h"

HarrisCornerPoint::HarrisCornerPoint(cv::Mat& src, double thresh)
{
    cv::Mat src_gray;
    cvtColor( src, src_gray, CV_BGR2GRAY );
    cv::Canny( src_gray, src_gray, 0, 100, 3,false );


    cv::Mat dst, dst_norm, dst_norm_scaled;
    dst = cv::Mat::zeros( src.size(), CV_32FC1 );

    /// Detector parameters
    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.04;

    /// Detecting corners
    cv::cornerHarris( src_gray, dst, blockSize, apertureSize, k, cv::BORDER_DEFAULT );

    /// Normalizing
    cv::normalize( dst, dst_norm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat() );
    cv::convertScaleAbs( dst_norm, dst_norm_scaled );

    dst_norm_scaled.copyTo(comparisonImg);

    /// Drawing a circle around corners
    for( int j = 0; j < dst_norm.rows ; j++ )
    { for( int i = 0; i < dst_norm.cols; i++ )
        {
            if( (int) dst_norm.at<float>(j,i) > thresh )
            {
                circle( dst_norm_scaled, cv::Point( i, j ), 5,  cv::Scalar(0), 2, 8, 0 );
                Utility::colorBlock(comparisonImg,i,j,5,255);
            }
            else{
                comparisonImg.row(j).col(i).data[0] = 0;
            }
        }
    }

    src_gray.copyTo(initSeg);
    comparisonImg.copyTo(postProcessing);
    dst_norm_scaled.copyTo(src);

}




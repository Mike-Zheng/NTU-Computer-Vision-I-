#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat image = imread("lena.bmp");
cv::Size s = image.size();
int rows = s.height;
int cols = s.width;
Mat upsideDown = image.clone();
Mat rightSideLeft = image.clone();
Mat diagonallyMirrored = image.clone();

int main(int argc, const char * argv[]) {
    cout<<"R04525092 工科 鄭力文"<<endl;
    
    //upsideDown
    //    (a)  upside-down lena.im
    for (int y=0;y<rows;y++){
        for(int x=0;x<cols;x++){
            for(int z=0;z<3;z++){
                upsideDown.at<Vec3b>(x,y)[z] =image.at<Vec3b>(cols-x,y)[z];
            }
        }
    }
    
    //rightSideLeft
    //     (b)  right-side-left lena.im
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            for(int z=0;z<3;z++){
                rightSideLeft.at<Vec3b>(x,y)[z] =image.at<Vec3b>(x,cols-y)[z];
            }
        }
    }
    
    //diagonallyMirrored
    //    (c)  diagonally mirrored lena.im
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            for(int z=0;z<3;z++){
                diagonallyMirrored.at<Vec3b>(x,y)[z] =image.at<Vec3b>(rows-y,cols-x)[z];
            }
        }
    }
    
    namedWindow("ori", WINDOW_AUTOSIZE);
    imshow("ori", image);
    namedWindow("upside-down", WINDOW_AUTOSIZE);
    imshow("upside-down", upsideDown);
    imwrite( "upsideDown.jpg", upsideDown );
    
    namedWindow("right-side-left", WINDOW_AUTOSIZE);
    imshow("right-side-left", rightSideLeft);
    imwrite( "rightSideLeft.jpg", rightSideLeft );

    namedWindow("diagonally mirrored", WINDOW_AUTOSIZE);
    imshow("diagonally mirrored", diagonallyMirrored);
    imwrite( "diagonallyMirrored.jpg", diagonallyMirrored );

    
    waitKey(0);
    
    return 0;
}

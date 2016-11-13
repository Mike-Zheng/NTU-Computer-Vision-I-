#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
using namespace cv;
using namespace std;

//histogram array
int histogram [256]={0};
int histogram2 [256]={0};
//讀取lena圖
Mat image = imread("lena.bmp");
//讀取lena圖 的寬高
cv::Size s = image.size();
int rows = s.height;
int cols = s.width;
//2值化 畫布
Mat image2 = image.clone();
Mat erosionImg = image.clone();
Mat dilationImg = image.clone();
int kernel[5][5] = {{0,255,255,255,0},{255,255,255,255,255},{255,255,255,255,255},{255,255,255,255,255},{0,255,255,255,0}};




//進行消退
int erosion(int x,int y,Mat im){
    int localMin=255;
    if(x>1&&y>1)
    for(int j=-2;j<2;j++){
        for(int i=-2;i<2;i++){
            if(kernel[i+2][j+2]==255){
                if(localMin > im.at<Vec3b>(x+i,y+j)[0])
                    localMin = im.at<Vec3b>(x+i,y+j)[0];
            }
        }
    }
    return localMin;
    
}

//進行膨脹
int dilation(int x,int y,Mat im){
    
    int localMax=0;
        for(int j=-2;j<2;j++){
            for(int i=-2;i<2;i++){
                if(kernel[i+2][j+2]==255){
                    if(localMax < im.at<Vec3b>(x+i,y+j)[0])
                        localMax = im.at<Vec3b>(x+i,y+j)[0];
                }
            }
        }
    return localMax;
}

//主函式
int main(int argc, const char * argv[]) {
    cout<<"R04525092 工科 鄭力文"<<endl;

    
    dilationImg = image.clone();
    
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            for(int z=0;z<3;z++){
                dilationImg.at<Vec3b>(x,y)[z] = dilation(x,y,image);
            }
        }
    }
    
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            for(int z=0;z<3;z++){
                erosionImg.at<Vec3b>(x,y)[z] = erosion(x,y,image);
            }
        }
    }
    

    
    Mat closingImg = dilationImg.clone();
    
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            for(int z=0;z<3;z++){
                closingImg.at<Vec3b>(x,y)[z] = erosion(x,y,dilationImg);
            }
            
        }
    }
    
    Mat openingImg=erosionImg.clone();
    
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            for(int z=0;z<3;z++){
                openingImg.at<Vec3b>(x,y)[z] = dilation(x,y,erosionImg);
            }
        }
    }
    
    
    
    
    
    //顯示結果
    namedWindow("Dilation", WINDOW_AUTOSIZE);
    imshow("Dilation", dilationImg);
    imwrite( "Dilation_gray.jpg", dilationImg );
    
    namedWindow("Erosion", WINDOW_AUTOSIZE);
    imshow("Erosion", erosionImg);
    imwrite( "Erosion_gray.jpg", erosionImg );
    
    namedWindow("Opening", WINDOW_AUTOSIZE);
    imshow("Opening", openingImg);
    imwrite( "Opening_gray.jpg", openingImg );
    
    namedWindow("Closing", WINDOW_AUTOSIZE);
    imshow("Closing", closingImg);
    imwrite( "Closing_gray.jpg", closingImg );
    

    
    waitKey(0);
    return 0;
}

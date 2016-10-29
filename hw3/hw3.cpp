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
Mat thresholdingImg = image.clone();


//fuction sk

double sk(int k){
    double value=0;
    for (int i=0;i<k;i++){
        value+=histogram[i];
    }
    
    value=value*255/(rows*cols);
    
    return value;
}

//主函式
int main(int argc, const char * argv[]) {
    cout<<"R04525092 工科 鄭力文"<<endl;
    //建立histogram table
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            
            //            將每一像素除以3
            for(int z=0;z<3;z++){
                image.at<Vec3b>(x,y)[z] =image.at<Vec3b>(x,y)[z]/3;
                thresholdingImg.at<Vec3b>(x,y)[z] =thresholdingImg.at<Vec3b>(x,y)[z]/3;
                
            }
            histogram[thresholdingImg.at<Vec3b>(x,y)[0]]+=1;
        }
    }
    
    
    
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            int k =thresholdingImg.at<Vec3b>(x,y)[0];
            int ske=int(sk(k));
            for(int z=0;z<3;z++){
                thresholdingImg.at<Vec3b>(x,y)[z] =ske;
            }
            histogram2[ske]+=1;
        }
    }
    
    
    //2值化 輸出csv
    
    ofstream fsOutput("histogram.csv", ios::app);
    ofstream fsOutput2("histogram2.csv", ios::app);
    
    for(int i=0;i<256;i++){
        fsOutput <<i<<","<<histogram[i] << endl;
        fsOutput2 <<i<<","<<histogram2[i] << endl;
    }
    
    fsOutput.close();
    fsOutput2.close();
    
    
    
    
    
    //顯示結果
    namedWindow("image", WINDOW_AUTOSIZE);
    imshow("image", image);
    imwrite( "HistogramEqualization_before.jpg", image );
    
    namedWindow("Histogram Equalization", WINDOW_AUTOSIZE);
    imshow("Histogram Equalization", thresholdingImg);
    imwrite( "HistogramEqualization_after.jpg", thresholdingImg );
    
    waitKey(0);
    
    return 0;
}

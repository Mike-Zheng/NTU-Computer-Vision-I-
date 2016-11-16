#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
using namespace cv;
using namespace std;

//lena64 array
int yokoiArray [64][64]={0};

//讀取lena圖
Mat image = imread("lena.bmp");
//讀取lena圖 的寬高
cv::Size s = image.size();
int rows = s.height;
int cols = s.width;
//2值化 畫布
Mat image2 = image.clone();


//fuction getNewValue
//input pixel內的灰階值
//output 取2值化thresholding後的直
//取2值化
int getNewValue(int value){
    int newValue=0;
    int thresholding=128;
    
    if(value>=thresholding)
        newValue=255;
    
    return newValue;
}



char h(int b,int c,int d,int e){
    
    if(b==c&&(d!=b||e!=b)){
        return 'q';
    }
    else if(b==c&&(d==b&&e==b)){
        return 'r';
    }
    else {
        return 's';
    }
    
}



int f(int a1,int a2,int a3,int a4){
    if(a1=='r'&&a2=='r'&&a3=='r'&&a4=='r'){
        return 5;
    }
    else{
        int number=0;
        if(a1=='q')number++;
        if(a2=='q')number++;
        if(a3=='q')number++;
        if(a4=='q')number++;
        return number;
        
    }
}


//主函式
int main(int argc, const char * argv[]) {
    cout<<"R04525092 工科 鄭力文"<<endl;
    
    //取2值化
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            for(int z=0;z<3;z++){
                image2.at<Vec3b>(x,y)[z] = getNewValue( image2.at<Vec3b>(x,y)[z]);
            }
        }
    }
    
    //縮成64*64
    Mat lena64(64, 64, CV_8UC3);
    for (int y=0;y<64;y++){
        for(int x=0;x<64;x++){
            for(int z=0;z<3;z++){
                lena64.at<Vec3b>(x,y)[z] = image2.at<Vec3b>(x*8,y*8)[z];
            }
        }
    }
    
    
    
    int x0,x1,x2,x3,x4,x5,x6,x7,x8;
    
    //yokoi
    for (int y=0;y<64;y++){
        for(int x=0;x<64;x++){
            if(lena64.at<Vec3b>(x,y)[0]==255){
                x0=lena64.at<Vec3b>(x,y)[0];
                x1=lena64.at<Vec3b>(x+1,y)[0];
                if(y!=0)
                    x2=lena64.at<Vec3b>(x,y-1)[0];
                else
                    x2=0;
                if(x!=0)
                    x3=lena64.at<Vec3b>(x-1,y)[0];
                else
                    x3=0;
                x4=lena64.at<Vec3b>(x,y+1)[0];
                x5=lena64.at<Vec3b>(x+1,y+1)[0];
                if(y!=0)
                    x6=lena64.at<Vec3b>(x+1,y-1)[0];
                else
                    x6=0;
                if(y!=0&&x!=0)
                    x7=lena64.at<Vec3b>(x-1,y-1)[0];
                else
                    x7=0;
                if(x!=0)
                    x8=lena64.at<Vec3b>(x-1,y+1)[0];
                else
                    x8=0;
                
                char a1=h(x0,x1,x6,x2);
                char a2=h(x0,x2,x7,x3);
                char a3=h(x0,x3,x8,x4);
                char a4=h(x0,x4,x5,x1);
                yokoiArray[x][y]=f(a1,a2,a3,a4);
            }
            else{
                yokoiArray[x][y]=-1;
            }
        }
    }
    
    
    
    
    ofstream fsOutput("lena.txt", ios::out);
    
    for (int y=0;y<64;y++){
        for(int x=0;x<64;x++){
            if(yokoiArray[y][x]==-1){
                fsOutput<<" ";
                cout<<" ";
            }
            else{
                fsOutput<<yokoiArray[y][x] ;
                cout<<yokoiArray[y][x] ;
            }
        }
        cout<<endl;
        fsOutput<<endl;
    }
    
    fsOutput.close();
    
    
    //顯示結果
    namedWindow("lena64", WINDOW_AUTOSIZE);
    imshow("lena64", lena64);
    imwrite( "lena64.jpg", lena64 );
    
    
    waitKey(0);
    return 0;
}

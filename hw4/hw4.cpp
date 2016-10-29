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
Mat dilationImg;
int kernel[3][3] = {{0,255,0},{255,255,255},{0,255,0}};
int kernelJ[3][3] = {{0,0,0},{255,255,0},{0,255,0}};
int kernelK[3][3] = {{0,255,255},{0,0,255},{0,0,0}};


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


//針對3種kernel進行消退
int erosion(int x,int y,Mat im,char type){
    int centerX=1;
    int centerY=1;
    int count=0;
    int kn[3][3]={0};
    switch (type) {
        case 'o':
            memcpy ( &kn, &kernel, sizeof(kernel) );
            if(x!=0||y!=0){
                if(int(im.at<Vec3b>(x,y-1)[0])==kn[centerX][centerY-1]){
                    count++;
                }
                if(int(im.at<Vec3b>(x-1,y)[0])==kn[centerX-1][centerY]){
                    count++;
                }
                if(int(im.at<Vec3b>(x,y)[0])==kn[centerX][centerY]){
                    count++;
                }
                if(int(im.at<Vec3b>(x+1,y)[0])==kn[centerX+1][centerY]){
                    count++;
                }
                
                if(int(im.at<Vec3b>(x,y+1)[0])==kn[centerX][centerY+1]){
                    count++;
                }
            }
            if(count>=5)
                return 255;
            else
                return 0;
            break;
        case 'j':
            memcpy ( &kn, &kernelJ, sizeof(kernelJ) );
            if(x!=0||y!=0){
                if(int(im.at<Vec3b>(x-1,y)[0])==kn[centerX-1][centerY]){
                    count++;
                }
                if(int(im.at<Vec3b>(x,y)[0])==kn[centerX][centerY]){
                    count++;
                }
                if(int(im.at<Vec3b>(x,y+1)[0])==kn[centerX][centerY+1]){
                    count++;
                }
            }
            if(count>=3)
                return 255;
            else
                return 0;//false
            break;
        case 'k':
            memcpy ( &kn, &kernelK, sizeof(kernelK) );
            if(x!=0||y!=0){
                
                if(int(im.at<Vec3b>(x,y-1)[0])==kn[centerX][centerY-1]){
                    count++;
                }
                
                if(int(im.at<Vec3b>(x+1,y-1)[0])==kn[centerX+1][centerY-1]){
                    count++;
                }
                
                if(int(im.at<Vec3b>(x+1,y)[0])==kn[centerX+1][centerY]){
                    count++;
                }
            }
            if(count>=3)
                return 255;
            else
                return 0;//false
            break;
        default:
            memcpy ( &kn, &kernel, sizeof(kernel) );
            if(x!=0||y!=0){
                if(int(im.at<Vec3b>(x,y-1)[0])==kn[centerX][centerY-1]){
                    count++;
                }
                if(int(im.at<Vec3b>(x-1,y)[0])==kn[centerX-1][centerY]){
                    count++;
                }
                if(int(im.at<Vec3b>(x,y)[0])==kn[centerX][centerY]){
                    count++;
                }
                if(int(im.at<Vec3b>(x+1,y)[0])==kn[centerX+1][centerY]){
                    count++;
                }
                
                if(int(im.at<Vec3b>(x,y+1)[0])==kn[centerX][centerY+1]){
                    count++;
                }
            }
            if(count>=5)
                return 255;
            else
                return 0;
            break;
    }
    
}

//進行膨脹
void dilation(int x,int y,Mat im,Mat newIm){
    if(im.at<Vec3b>(x,y)[0] == 255)
    {
        for(int j=-1;j<2;j++){
            for(int i=-1;i<2;i++){
                if(kernel[i][j]==255){
                    for(int z=0;z<3;z++){
                        newIm.at<Vec3b>(x+i,y+j)[z] = 255;
                    }
                }
            }
        }
    }
}

//主函式
int main(int argc, const char * argv[]) {
    cout<<"R04525092 工科 鄭力文"<<endl;
    //取2值化 image2
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            for(int z=0;z<3;z++){
                image2.at<Vec3b>(x,y)[z] =getNewValue(image.at<Vec3b>(x,y)[z]);
            }
        }
    }
    
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            for(int z=0;z<3;z++){
                erosionImg.at<Vec3b>(x,y)[z] = erosion(x,y,image2,'o');
            }
        }
    }
    
    dilationImg = image2.clone();
    
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            dilation(x,y,image2,dilationImg);
            
        }
    }
    
    Mat closingImg = dilationImg.clone();
    
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            for(int z=0;z<3;z++){
                closingImg.at<Vec3b>(x,y)[z] = erosion(x,y,dilationImg,'o');
            }
            
        }
    }
    
    Mat openingImg=erosionImg.clone();
    
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            dilation(x,y,erosionImg,openingImg);
            
        }
    }
    
    
    //
    //    J對A侵蝕
    //    K對A"侵蝕
    //    再做交集
    //
    Mat hitAndMissJ=image.clone();
    
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            for(int z=0;z<3;z++){
                hitAndMissJ.at<Vec3b>(x,y)[z] = erosion(x,y,image2,'j');
            }
        }
    }
    Mat hitAndMiss=image.clone();
    
    Mat image2P=image2.clone();
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            for(int z=0;z<3;z++){
                if(image2.at<Vec3b>(x,y)[z]==0)
                    image2P.at<Vec3b>(x,y)[z] =255;
                else
                    image2P.at<Vec3b>(x,y)[z] =0;
            }
        }
    }
    
    
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            for(int z=0;z<3;z++){
                hitAndMiss.at<Vec3b>(x,y)[z] = erosion(x,y,image2P,'k');
            }
        }
    }
    
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            for(int z=0;z<3;z++){
                if(hitAndMiss.at<Vec3b>(x,y)[z]==255&&hitAndMissJ.at<Vec3b>(x,y)[z]==255)
                    hitAndMiss.at<Vec3b>(x,y)[z] =255;
                else
                    hitAndMiss.at<Vec3b>(x,y)[z] =0;
            }
        }
    }
    
    
    
    
    //顯示結果
    namedWindow("Dilation", WINDOW_AUTOSIZE);
    imshow("Dilation", dilationImg);
    imwrite( "Dilation.jpg", dilationImg );
    
    namedWindow("Erosion", WINDOW_AUTOSIZE);
    imshow("Erosion", erosionImg);
    imwrite( "Erosion.jpg", erosionImg );

    namedWindow("Opening", WINDOW_AUTOSIZE);
    imshow("Opening", openingImg);
    imwrite( "Opening.jpg", openingImg );
    
    namedWindow("Closing", WINDOW_AUTOSIZE);
    imshow("Closing", closingImg);
    imwrite( "Closing.jpg", closingImg );
    
    namedWindow("hit And Miss", WINDOW_AUTOSIZE);
    imshow("hit And Miss", hitAndMiss);
    imwrite( "hitAndMiss.jpg", hitAndMiss );
    
    waitKey(0);
    return 0;
}

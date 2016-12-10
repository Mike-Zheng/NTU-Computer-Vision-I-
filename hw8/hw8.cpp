#include <iostream>
#include <opencv2/opencv.hpp>
#include <algorithm>
using namespace cv;
using namespace std;

Mat image = imread("lena.bmp");
cv::Size s = image.size();
int rows = s.height;
int cols = s.width;
int mask3x3[3][3]={1,1,1,1,1,1,1,1,1};
int mask5x5[5][5]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
void addWhiteGaussianNoise(Mat,Mat&,int);
void addSaltAndPepperNoise(Mat,Mat&,double);
void boxfilter3x3(Mat,Mat&,Mat);
void boxfilter5x5(Mat,Mat&,Mat);
void medianfilter3x3(Mat,Mat&,Mat);
void medianfilter5x5(Mat,Mat&,Mat);
void openingClosing(Mat,Mat&,Mat);
void closingOpening(Mat,Mat&,Mat);
//Generate additive white Gaussian noise
//
//Generate salt-and-pepper noise
//
//Run box filter (3X3, 5X5) on all noisy images
//
//Run median filter (3X3, 5X5) on all noisy images
//
//Run opening followed by closing or closing followed by opening



void addWhiteGaussianNoise(Mat image,Mat& addImg,int amp){
    Mat imageTemp=image.clone();
    int rows = imageTemp.rows;
    int cols = imageTemp.cols;
    RNG rng;
    for (int y=0;y<rows;y++){
        for(int x=0;x<cols;x++){
            double rnd = rng.gaussian(1);
            int v = (int)imageTemp.at<Vec3b>(x,y)[0]+amp*rnd;
            imageTemp.at<Vec3b>(x,y)[0] = v;
            imageTemp.at<Vec3b>(x,y)[1] = v;
            imageTemp.at<Vec3b>(x,y)[2] = v;
        }
    }
    addImg=imageTemp;
    
}


void addSaltAndPepperNoise(Mat image,Mat& addImg,double threshold){
    Mat imageTemp=image.clone();
    int rows = imageTemp.rows;
    int cols = imageTemp.cols;
    RNG rng;
    for (int y=0;y<rows;y++){
        for(int x=0;x<cols;x++){
            
            double rnd = rng.uniform((double)0,(double)1);
            if ( rnd<threshold ) {
                imageTemp.at<Vec3b>(x,y)[0] = 0;
                imageTemp.at<Vec3b>(x,y)[1] = 0;
                imageTemp.at<Vec3b>(x,y)[2] = 0;
            }
            else if ( rnd > 1-threshold ) {
                imageTemp.at<Vec3b>(x,y)[0] = 255;
                imageTemp.at<Vec3b>(x,y)[1] = 255;
                imageTemp.at<Vec3b>(x,y)[2] = 255;
            }
            
            
        }
    }
    addImg=imageTemp;
    
}

void boxfilter3x3(Mat image,Mat& addImg,Mat noiseImg){
    Mat imageTemp=image.clone();
    int rows = imageTemp.rows;
    int cols = imageTemp.cols;
    for (int y=1;y<rows-1;y++){
        for(int x=1;x<cols-1;x++){
            double sum=0.;
            sum+=noiseImg.at<Vec3b>(x-1,y-1)[0]* mask3x3[0][0];
            sum+=noiseImg.at<Vec3b>(x,y-1)[0]* mask3x3[1][0];
            sum+=noiseImg.at<Vec3b>(x+1,y-1)[0]* mask3x3[2][0];
            sum+=noiseImg.at<Vec3b>(x-1,y)[0]* mask3x3[0][1];
            sum+=noiseImg.at<Vec3b>(x,y)[0]* mask3x3[1][1];
            sum+=noiseImg.at<Vec3b>(x+1,y)[0]* mask3x3[2][1];
            sum+=noiseImg.at<Vec3b>(x-1,y+1)[0]* mask3x3[0][2];
            sum+=noiseImg.at<Vec3b>(x,y+1)[0]* mask3x3[1][2];
            sum+=noiseImg.at<Vec3b>(x+1,y+1)[0]* mask3x3[2][2];
            sum=sum/9;
            
            imageTemp.at<Vec3b>(x,y)[0]=int(sum);
            imageTemp.at<Vec3b>(x,y)[1]=int(sum);
            imageTemp.at<Vec3b>(x,y)[2]=int(sum);
            
            
            
            
        }
    }
    addImg=imageTemp;
    
}


void boxfilter5x5(Mat image,Mat& addImg,Mat noiseImg){
    Mat imageTemp=image.clone();
    int rows = imageTemp.rows;
    int cols = imageTemp.cols;
    for (int y=2;y<rows-2;y++){
        for(int x=2;x<cols-2;x++){
            double sum=0.;
            sum+=noiseImg.at<Vec3b>(x-2,y-2)[0]* mask5x5[0][0];
            sum+=noiseImg.at<Vec3b>(x-1,y-2)[0]* mask5x5[1][0];
            sum+=noiseImg.at<Vec3b>(x,y-2)[0]* mask5x5[2][0];
            sum+=noiseImg.at<Vec3b>(x+1,y-2)[0]* mask5x5[3][0];
            sum+=noiseImg.at<Vec3b>(x+2,y-2)[0]* mask5x5[4][0];
            sum+=noiseImg.at<Vec3b>(x-2,y-1)[0]* mask5x5[0][1];
            sum+=noiseImg.at<Vec3b>(x-1,y-1)[0]* mask5x5[1][1];
            sum+=noiseImg.at<Vec3b>(x,y-1)[0]* mask5x5[2][1];
            sum+=noiseImg.at<Vec3b>(x+1,y-1)[0]* mask5x5[3][1];
            sum+=noiseImg.at<Vec3b>(x+2,y-1)[0]* mask5x5[4][1];
            sum+=noiseImg.at<Vec3b>(x-2,y)[0]* mask5x5[0][2];
            sum+=noiseImg.at<Vec3b>(x-1,y)[0]* mask5x5[1][2];
            sum+=noiseImg.at<Vec3b>(x,y)[0]* mask5x5[2][2];
            sum+=noiseImg.at<Vec3b>(x+1,y)[0]* mask5x5[3][2];
            sum+=noiseImg.at<Vec3b>(x+2,y)[0]* mask5x5[4][2];
            sum+=noiseImg.at<Vec3b>(x-2,y+1)[0]* mask5x5[0][3];
            sum+=noiseImg.at<Vec3b>(x-1,y+1)[0]* mask5x5[1][3];
            sum+=noiseImg.at<Vec3b>(x,y+1)[0]* mask5x5[2][3];
            sum+=noiseImg.at<Vec3b>(x+1,y+1)[0]* mask5x5[3][3];
            sum+=noiseImg.at<Vec3b>(x+1,y+1)[0]* mask5x5[4][3];
            sum+=noiseImg.at<Vec3b>(x-2,y+2)[0]* mask5x5[0][4];
            sum+=noiseImg.at<Vec3b>(x-1,y+2)[0]* mask5x5[1][4];
            sum+=noiseImg.at<Vec3b>(x,y+2)[0]* mask5x5[2][4];
            sum+=noiseImg.at<Vec3b>(x+1,y+2)[0]* mask5x5[3][4];
            sum+=noiseImg.at<Vec3b>(x+1,y+2)[0]* mask5x5[4][4];
            sum=sum/25;
            
            imageTemp.at<Vec3b>(x,y)[0]=int(sum);
            imageTemp.at<Vec3b>(x,y)[1]=int(sum);
            imageTemp.at<Vec3b>(x,y)[2]=int(sum);
            
            
            
            
        }
    }
    addImg=imageTemp;
    
}

void medianfilter3x3(Mat image,Mat& addImg,Mat noiseImg){
    Mat imageTemp=image.clone();
    int rows = imageTemp.rows;
    int cols = imageTemp.cols;
    for (int y=1;y<rows-1;y++){
        for(int x=1;x<cols-1;x++){
            int tempArray[9]={};
            tempArray[0]=noiseImg.at<Vec3b>(x-1,y-1)[0];
            tempArray[1]=noiseImg.at<Vec3b>(x,y-1)[0];
            tempArray[2]=noiseImg.at<Vec3b>(x+1,y-1)[0];
            tempArray[3]=noiseImg.at<Vec3b>(x-1,y)[0];
            tempArray[4]=noiseImg.at<Vec3b>(x,y)[0];
            tempArray[5]=noiseImg.at<Vec3b>(x+1,y)[0];
            tempArray[6]=noiseImg.at<Vec3b>(x-1,y+1)[0];
            tempArray[7]=noiseImg.at<Vec3b>(x,y+1)[0];
            tempArray[8]=noiseImg.at<Vec3b>(x+1,y+1)[0];
            sort(begin(tempArray), end(tempArray));
            imageTemp.at<Vec3b>(x,y)[0]= tempArray[4];
            imageTemp.at<Vec3b>(x,y)[1]= tempArray[4];
            imageTemp.at<Vec3b>(x,y)[2]= tempArray[4];
        }
    }
    addImg=imageTemp;
    
}

void medianfilter5x5(Mat image,Mat& addImg,Mat noiseImg){
    Mat imageTemp=image.clone();
    int rows = imageTemp.rows;
    int cols = imageTemp.cols;
    for (int y=2;y<rows-2;y++){
        for(int x=2;x<cols-2;x++){
            int tempArray[25]={};
            tempArray[0]=noiseImg.at<Vec3b>(x-2,y-2)[0];
            tempArray[1]=noiseImg.at<Vec3b>(x-1,y-2)[0];
            tempArray[2]=noiseImg.at<Vec3b>(x,y-2)[0];
            tempArray[3]=noiseImg.at<Vec3b>(x+1,y-2)[0];
            tempArray[4]=noiseImg.at<Vec3b>(x+2,y-2)[0];
            tempArray[5]=noiseImg.at<Vec3b>(x-2,y-1)[0];
            tempArray[6]=noiseImg.at<Vec3b>(x-1,y-1)[0];
            tempArray[7]=noiseImg.at<Vec3b>(x,y-1)[0];
            tempArray[8]=noiseImg.at<Vec3b>(x+1,y-1)[0];
            tempArray[9]=noiseImg.at<Vec3b>(x+2,y-1)[0];
            tempArray[10]=noiseImg.at<Vec3b>(x-2,y)[0];
            tempArray[11]=noiseImg.at<Vec3b>(x-1,y)[0];
            tempArray[12]=noiseImg.at<Vec3b>(x,y)[0];
            tempArray[13]=noiseImg.at<Vec3b>(x+1,y)[0];
            tempArray[14]=noiseImg.at<Vec3b>(x+2,y)[0];
            tempArray[15]=noiseImg.at<Vec3b>(x-2,y+1)[0];
            tempArray[16]=noiseImg.at<Vec3b>(x-1,y+1)[0];
            tempArray[17]=noiseImg.at<Vec3b>(x,y+1)[0];
            tempArray[18]=noiseImg.at<Vec3b>(x+1,y+1)[0];
            tempArray[19]=noiseImg.at<Vec3b>(x+1,y+1)[0];
            tempArray[20]=noiseImg.at<Vec3b>(x-2,y+2)[0];
            tempArray[21]=noiseImg.at<Vec3b>(x-1,y+2)[0];
            tempArray[22]=noiseImg.at<Vec3b>(x,y+2)[0];
            tempArray[23]=noiseImg.at<Vec3b>(x+1,y+2)[0];
            tempArray[24]=noiseImg.at<Vec3b>(x+1,y+2)[0];
            sort(begin(tempArray), end(tempArray));
            imageTemp.at<Vec3b>(x,y)[0]= tempArray[12];
            imageTemp.at<Vec3b>(x,y)[1]= tempArray[12];
            imageTemp.at<Vec3b>(x,y)[2]= tempArray[12];
        }
    }
    addImg=imageTemp;
    
}

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

void openingClosing(Mat image,Mat& addImg,Mat noiseImg){
    Mat imageTemp=image.clone();
    int rows = imageTemp.rows;
    int cols = imageTemp.cols;
    
    
    
    Mat dilationImg = image.clone();
    
    
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            for(int z=0;z<3;z++){
                dilationImg.at<Vec3b>(x,y)[z] = dilation(x,y,noiseImg);
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
    
    Mat erosionImg = image.clone();
    
    
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            for(int z=0;z<3;z++){
                erosionImg.at<Vec3b>(x,y)[z] = erosion(x,y,closingImg);
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
    
    
    
    
    addImg=openingImg;
    
}

void closingOpening(Mat image,Mat& addImg,Mat noiseImg){
    Mat imageTemp=image.clone();
    int rows = imageTemp.rows;
    int cols = imageTemp.cols;
    
    
    
    
    Mat erosionImg = image.clone();
    
    
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            for(int z=0;z<3;z++){
                erosionImg.at<Vec3b>(x,y)[z] = erosion(x,y,noiseImg);
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
    
    
    Mat dilationImg = image.clone();
    
    
    for (int y=0;y<cols;y++){
        for(int x=0;x<rows;x++){
            for(int z=0;z<3;z++){
                dilationImg.at<Vec3b>(x,y)[z] = dilation(x,y,openingImg);
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
    
    
    addImg=closingImg;
    
}


int main(int argc, const char * argv[]) {
    //
    //    for (int y=0;y<rows;y++){
    //        for(int x=0;x<cols;x++){
    //            //cout<<image.at<Vec3b>(x,y)[0]<<" ";
    //        }
    //        //cout<<endl;
    //    }
    
    //Generate additive white Gaussian noise
    Mat GaussianNoise10, GaussianNoise30;
    addWhiteGaussianNoise(image, GaussianNoise10, 10);
    namedWindow("GaussianNoise10", WINDOW_AUTOSIZE);
    imshow("GaussianNoise10", GaussianNoise10);
    imwrite("GaussianNoise10.bmp", GaussianNoise10);
    addWhiteGaussianNoise(image, GaussianNoise30, 30);
    namedWindow("GaussianNoise30", WINDOW_AUTOSIZE);
    imshow("GaussianNoise30", GaussianNoise30);
    imwrite("GaussianNoise30.bmp", GaussianNoise30);
    
    //Generate salt-and-pepper noise
    Mat SaltandPepper05, SaltandPepper1;
    addSaltAndPepperNoise(image, SaltandPepper05, 0.05);
    namedWindow("SaltandPepper05", WINDOW_AUTOSIZE);
    imshow("SaltandPepper05", SaltandPepper05);
    imwrite("SaltandPepper05.bmp", SaltandPepper05);
    addSaltAndPepperNoise(image, SaltandPepper1, 0.1);
    namedWindow("SaltandPepper1", WINDOW_AUTOSIZE);
    imshow("SaltandPepper1", SaltandPepper1);
    imwrite("SaltandPepper1.bmp", SaltandPepper1);
    
    
    
    //Run box filter (3X3, 5X5) on all noisy images
    
    Mat boxfilter3x3GN10;
    Mat boxfilter3x3GN30;
    Mat boxfilter3x3SP05;
    Mat boxfilter3x3SP1;
    boxfilter3x3(image,boxfilter3x3GN10,GaussianNoise10);
    namedWindow("boxfilter3x3GN10", WINDOW_AUTOSIZE);
    imshow("boxfilter3x3GN10", boxfilter3x3GN10);
    imwrite("boxfilter3x3GN10.bmp", boxfilter3x3GN10);
    
    boxfilter3x3(image,boxfilter3x3GN30,GaussianNoise30);
    namedWindow("boxfilter3x3GN30", WINDOW_AUTOSIZE);
    imshow("boxfilter3x3GN30", boxfilter3x3GN30);
    imwrite("boxfilter3x3GN30.bmp", boxfilter3x3GN30);
    
    boxfilter3x3(image,boxfilter3x3SP05,SaltandPepper05);
    namedWindow("boxfilter3x3SP05", WINDOW_AUTOSIZE);
    imshow("boxfilter3x3SP05", boxfilter3x3SP05);
    imwrite("boxfilter3x3SP05.bmp", boxfilter3x3SP05);
    
    boxfilter3x3(image,boxfilter3x3SP1,SaltandPepper1);
    namedWindow("boxfilter3x3SP1", WINDOW_AUTOSIZE);
    imshow("boxfilter3x3SP1", boxfilter3x3SP1);
    imwrite("boxfilter3x3SP1.bmp", boxfilter3x3SP1);
    
    Mat boxfilter5x5GN10;
    Mat boxfilter5x5GN30;
    Mat boxfilter5x5SP05;
    Mat boxfilter5x5SP1;
    boxfilter5x5(image,boxfilter5x5GN10,GaussianNoise10);
    namedWindow("boxfilter5x5GN10", WINDOW_AUTOSIZE);
    imshow("boxfilter5x5GN10", boxfilter5x5GN10);
    imwrite("boxfilter5x5GN10.bmp", boxfilter5x5GN10);
    
    boxfilter5x5(image,boxfilter5x5GN30,GaussianNoise30);
    namedWindow("boxfilter5x5GN30", WINDOW_AUTOSIZE);
    imshow("boxfilter5x5GN30", boxfilter5x5GN30);
    imwrite("boxfilter5x5GN30.bmp", boxfilter5x5GN30);
    
    boxfilter5x5(image,boxfilter5x5SP05,SaltandPepper05);
    namedWindow("boxfilter5x5SP05", WINDOW_AUTOSIZE);
    imshow("boxfilter5x5SP05", boxfilter5x5SP05);
    imwrite("boxfilter5x5SP05.bmp", boxfilter5x5SP05);
    
    boxfilter5x5(image,boxfilter5x5SP1,SaltandPepper1);
    namedWindow("boxfilter5x5SP1", WINDOW_AUTOSIZE);
    imshow("boxfilter5x5SP1", boxfilter5x5SP1);
    imwrite("boxfilter5x5SP1.bmp", boxfilter5x5SP1);
    
    
    
    
    //
    //Run median filter (3X3, 5X5) on all noisy images
    Mat medianfilter3x3GN10;
    Mat medianfilter3x3GN30;
    Mat medianfilter3x3SP05;
    Mat medianfilter3x3SP1;
    medianfilter3x3(image,medianfilter3x3GN10,GaussianNoise10);
    namedWindow("medianfilter3x3GN10", WINDOW_AUTOSIZE);
    imshow("medianfilter3x3GN10", medianfilter3x3GN10);
    imwrite("medianfilter3x3GN10.bmp", medianfilter3x3GN10);
    
    medianfilter3x3(image,medianfilter3x3GN30,GaussianNoise30);
    namedWindow("medianfilter3x3GN30", WINDOW_AUTOSIZE);
    imshow("medianfilter3x3GN30", medianfilter3x3GN30);
    imwrite("medianfilter3x3GN30.bmp", medianfilter3x3GN30);
    
    medianfilter3x3(image,medianfilter3x3SP05,SaltandPepper05);
    namedWindow("medianfilter3x3SP05", WINDOW_AUTOSIZE);
    imshow("medianfilter3x3SP05", medianfilter3x3SP05);
    imwrite("medianfilter3x3SP05.bmp", medianfilter3x3SP05);
    
    medianfilter3x3(image,medianfilter3x3SP1,SaltandPepper1);
    namedWindow("medianfilter3x3SP1", WINDOW_AUTOSIZE);
    imshow("medianfilter3x3SP1", medianfilter3x3SP1);
    imwrite("medianfilter3x3SP1.bmp", medianfilter3x3SP1);
    
    Mat medianfilter5x5GN10;
    Mat medianfilter5x5GN30;
    Mat medianfilter5x5SP05;
    Mat medianfilter5x5SP1;
    medianfilter5x5(image,medianfilter5x5GN10,GaussianNoise10);
    namedWindow("medianfilter5x5GN10", WINDOW_AUTOSIZE);
    imshow("medianfilter5x5GN10", medianfilter5x5GN10);
    imwrite("medianfilter5x5GN10.bmp", medianfilter5x5GN10);
    
    medianfilter5x5(image,medianfilter5x5GN30,GaussianNoise30);
    namedWindow("medianfilter5x5GN30", WINDOW_AUTOSIZE);
    imshow("medianfilter5x5GN30", medianfilter5x5GN30);
    imwrite("medianfilter5x5GN30.bmp", medianfilter5x5GN30);
    
    medianfilter5x5(image,medianfilter5x5SP05,SaltandPepper05);
    namedWindow("medianfilter5x5SP05", WINDOW_AUTOSIZE);
    imshow("medianfilter5x5SP05", medianfilter5x5SP05);
    imwrite("medianfilter5x5SP05.bmp", medianfilter5x5SP05);
    
    medianfilter5x5(image,medianfilter5x5SP1,SaltandPepper1);
    namedWindow("medianfilter5x5SP1", WINDOW_AUTOSIZE);
    imshow("medianfilter5x5SP1", medianfilter5x5SP1);
    imwrite("medianfilter5x5SP1.bmp", medianfilter5x5SP1);
    
    //Run opening followed by closing or closing followed by opening
    Mat openingClosingGN10;
    Mat openingClosingGN30;
    Mat openingClosingSP05;
    Mat openingClosingSP1;
    
    openingClosing(image,openingClosingGN10,GaussianNoise10);
    namedWindow("openingClosingGN10", WINDOW_AUTOSIZE);
    imshow("openingClosingGN10", openingClosingGN10);
    imwrite("openingClosingGN10.bmp", openingClosingGN10);
    
    openingClosing(image,openingClosingGN30,GaussianNoise30);
    namedWindow("openingClosingGN30", WINDOW_AUTOSIZE);
    imshow("openingClosingGN30", openingClosingGN30);
    imwrite("openingClosingGN30.bmp", openingClosingGN30);
    
    openingClosing(image,openingClosingSP05,SaltandPepper05);
    namedWindow("openingClosingSP05", WINDOW_AUTOSIZE);
    imshow("openingClosingSP05", openingClosingSP05);
    imwrite("openingClosingSP05.bmp", openingClosingSP05);
    
    openingClosing(image,openingClosingSP1,SaltandPepper1);
    namedWindow("openingClosingSP1", WINDOW_AUTOSIZE);
    imshow("openingClosingSP1", openingClosingSP1);
    imwrite("openingClosingSP1.bmp", openingClosingSP1);
    
    
    Mat closingOpeningGN10;
    Mat closingOpeningGN30;
    Mat closingOpeningSP05;
    Mat closingOpeningSP1;
    
    closingOpening(image,closingOpeningGN10,GaussianNoise10);
    namedWindow("closingOpeningGN10", WINDOW_AUTOSIZE);
    imshow("closingOpeningGN10", closingOpeningGN10);
    imwrite("closingOpeningGN10.bmp", closingOpeningGN10);
    
    closingOpening(image,closingOpeningGN30,GaussianNoise30);
    namedWindow("closingOpeningGN30", WINDOW_AUTOSIZE);
    imshow("closingOpeningGN30", closingOpeningGN30);
    imwrite("closingOpeningGN30.bmp", closingOpeningGN30);
    
    closingOpening(image,closingOpeningSP05,SaltandPepper05);
    namedWindow("closingOpeningSP05", WINDOW_AUTOSIZE);
    imshow("closingOpeningSP05", closingOpeningSP05);
    imwrite("closingOpeningSP05.bmp", closingOpeningSP05);
    
    closingOpening(image,closingOpeningSP1,SaltandPepper1);
    namedWindow("closingOpeningSP1", WINDOW_AUTOSIZE);
    imshow("closingOpeningSP1", closingOpeningSP1);
    imwrite("closingOpeningSP1.bmp", closingOpeningSP1);
    
    
    
    waitKey(0);
    
    return 0;
}

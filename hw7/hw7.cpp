#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
using namespace cv;
using namespace std;

//lena64 array
char thinningArray[64][64] = { 0 };
char thinningOp[64][64] = { 0 };
//lena64 array
char shrinkArray[64][64] = { 0 };
int yokoiArray[64][64] = { 0 };

//讀取lena圖
Mat image = imread("lena.bmp");
//讀取lena圖 的寬高
cv::Size s = image.size();
int rows = s.height;
int cols = s.width;
//2值化 畫布
Mat image2 = image.clone();
Mat lena64(64, 64, CV_8UC3);
Mat thinning(64, 64, CV_8UC3);


//fuction getNewValue
//input pixel內的灰階值
//output 取2值化thresholding後的直
//取2值化
int getNewValue(int value) {
    int newValue = 0;
    int thresholding = 128;
    
    if (value >= thresholding)
        newValue = 255;
    
    return newValue;
}





char yokoi_h(int b,int c,int d,int e){
    
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



int yokoi_f(int a1,int a2,int a3,int a4){
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


int h(int b, int c, int d, int e) {
    
    if (b == c && (d != b || e != b)) {
        return 1;
    } else {
        return 0;
    }
    
}



char f(int a1, int a2, int a3, int a4, int x) {
    if (a1 == 1 || a2 == 1 || a3 == 1 || a4 == 1) {
        int count = 0;
        if (a1 == 1) count++;
        if (a2 == 1) count++;
        if (a3 == 1) count++;
        if (a4 == 1) count++;
        if (count == 1)
            return 's';
        else
            return '1';
    } else {
        if (x == 255)
            return '1';
        else
            return '0';
        
    }
}

bool check_if_4(int x,int y){
    int up=0;
    int right=0;
    int left=0;
    int bottom=0;
    
    if(y>0)
        up=yokoiArray[x][y-1];
    else
        up=0;
    if(x<63)
        right=yokoiArray[x+1][y];
    else
        right=0;
    if(x>0)
        left=yokoiArray[x-1][y];
    else
        left=0;
    if(y<63)
        bottom=yokoiArray[x][y+1];
    else
        bottom=0;
    
    if(up==1||
       right==1||
       left==1||
       bottom==1)
        return true;
    else
        return false;
}

bool isShrink(int x,int y,Mat image){
      int x0, x1, x2, x3, x4, x5, x6, x7, x8;
    x0=image.at<Vec3b>(x,y)[0];
    if(y<63)
        x1=image.at<Vec3b>(x+1,y)[0];
    else
        x1=0;
    if(y!=0)
        x2=image.at<Vec3b>(x,y-1)[0];
    else
        x2=0;
    if(x!=0)
        x3=image.at<Vec3b>(x-1,y)[0];
    else
        x3=0;
    if(x<63)
        x4=image.at<Vec3b>(x,y+1)[0];
    else
        x4=0;
    if(x<63&&y<63)
        x5=image.at<Vec3b>(x+1,y+1)[0];
    else
        x5=0;
    if(y!=0&&x<63)
        x6=image.at<Vec3b>(x+1,y-1)[0];
    else
        x6=0;
    if(y!=0&&x!=0)
        x7=image.at<Vec3b>(x-1,y-1)[0];
    else
        x7=0;
    if(x!=0&&y<63)
        x8=image.at<Vec3b>(x-1,y+1)[0];
    else
        x8=0;
    
    char a1 = h(x0, x1, x6, x2);
    char a2 = h(x0, x2, x7, x3);
    char a3 = h(x0, x3, x8, x4);
    char a4 = h(x0, x4, x5, x1);
    if(f(a1, a2, a3, a4, x0)=='s')
        return true;
    else
        return false;

}

//主函式
int main(int argc,
         const char * argv[]) {
    cout << "R04525092 工科 鄭力文" << endl;
    
    //取2值化
    for (int y = 0; y < cols; y++) {
        for (int x = 0; x < rows; x++) {
            for (int z = 0; z < 3; z++) {
                image2.at < Vec3b > (x, y)[z] = getNewValue(image2.at < Vec3b > (x, y)[z]);
            }
        }
    }
    
    //縮成64*64
    
    for (int y = 0; y < 64; y++) {
        for (int x = 0; x < 64; x++) {
            for (int z = 0; z < 3; z++) {
                lena64.at < Vec3b > (x, y)[z] = image2.at < Vec3b > (x * 8, y * 8)[z];
            }
        }
    }
    thinning=lena64.clone();
    
    int isChanged = 0;
    while (isChanged<5) {
        isChanged++;
        


        
        int y0,y1,y2,y3,y4,y5,y6,y7,y8;
        
        //yokoi
        for (int y=0;y<64;y++){
            for(int x=0;x<64;x++){
                if(thinning.at<Vec3b>(x,y)[0]==255){
                    y0=thinning.at<Vec3b>(x,y)[0];
                    if(y<63)
                        y1=thinning.at<Vec3b>(x+1,y)[0];
                    else
                        y1=0;
                    if(y!=0)
                        y2=thinning.at<Vec3b>(x,y-1)[0];
                    else
                        y2=0;
                    if(x!=0)
                        y3=thinning.at<Vec3b>(x-1,y)[0];
                    else
                        y3=0;
                    if(x<63)
                        y4=thinning.at<Vec3b>(x,y+1)[0];
                    else
                        y4=0;
                    if(x<63&&y<63)
                        y5=thinning.at<Vec3b>(x+1,y+1)[0];
                    else
                        y5=0;
                    if(y!=0&&x<63)
                        y6=thinning.at<Vec3b>(x+1,y-1)[0];
                    else
                        y6=0;
                    if(y!=0&&x!=0)
                        y7=thinning.at<Vec3b>(x-1,y-1)[0];
                    else
                        y7=0;
                    if(x!=0&&y<63)
                        y8=thinning.at<Vec3b>(x-1,y+1)[0];
                    else
                        y8=0;
                    
                    char a1=yokoi_h(y0,y1,y6,y2);
                    char a2=yokoi_h(y0,y2,y7,y3);
                    char a3=yokoi_h(y0,y3,y8,y4);
                    char a4=yokoi_h(y0,y4,y5,y1);
                    yokoiArray[x][y]=yokoi_f(a1,a2,a3,a4);
                }
                else{
                    yokoiArray[x][y]=8;
                }
            }
        }
        
        
        

        
        
        
        
        //shrink marked pixels that are deletable
        for (int y = 0; y < 64; y++) {
            for (int x = 0; x < 64; x++) {
                for (int z = 0; z < 3; z++) {
                    //lena64.at<Vec3b>(x,y)[z]
                    if (yokoiArray[x][y] == 1 && check_if_4(x, y) && isShrink(x,y,thinning))
                        thinning.at < Vec3b > (x, y)[z] = 0;
                    else if (int(thinning.at < Vec3b > (x, y)[0]) == 0)
                        thinning.at < Vec3b > (x, y)[z] = 0;
                    else
                        thinning.at < Vec3b > (x, y)[z] = 255;
                    
                    
                }
            }
        }
        
        
        for (int r = 0; r < 64; r++)
            cout << "  ";
        cout << endl;
        cout << "iteration "<<isChanged<< endl;
        
        //結果檢查
        for (int y = 0; y < 64; y++) {
            for (int x = 0; x < 64; x++) {
                if (int(thinning.at < Vec3b > (y, x)[0]) == 255)
                    cout <<  "* ";
                else
                    cout<< "  ";
            }
            cout << endl;
            
        }
        
        
    }
    
    ofstream fsOutput("lena.txt", ios::out);
    
    for (int y=0;y<64;y++){
        for(int x=0;x<64;x++){
            if (int(thinning.at < Vec3b > (y, x)[0]) == 255){
                cout <<  "* ";
                fsOutput<<"* ";
            }
            else{
                fsOutput<<"  " ;
                 cout<< "  ";
            }
        }
        cout<<endl;
        fsOutput<<endl;
    }
    
    fsOutput.close();
    
    //顯示結果
    namedWindow("thinning", WINDOW_AUTOSIZE);
    imshow("thinning", thinning);
    imwrite("thinning.jpg", thinning);
    
    
    waitKey(0);
    return 0;
}

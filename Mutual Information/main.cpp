//
//  main.cpp
//  Mutual Information
//
//  Created by zhoushiwei on 16/5/13.
//  Copyright © 2016年 zhoushiwei. All rights reserved.
//

#include <iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    Mat limg=imread("/Users/zhoushiwei/Desktop/male1-15/manhair/man-03.png",0);
    Mat rimg=imread("/Users/zhoushiwei/Desktop/male1-15/manhair/man-11.png",0);
    static float *H1;/////概率直方图
    static float *H2;
    static float **H12;
    static int **d;
    d=new  int *[limg.rows];
    for(int i=0;i<limg.rows;i++)
    {
        d[i]=new int[limg.cols];
        for(int j=0;j<limg.cols;j++)
        {
            d[i][j]=0;
        }
    }
    H1=new  float [256];
    H2=new  float [256];
    H12=new  float *[256];
    
    for(int i=0;i<256;i++)
    {
        H1[i]=0;
        H2[i]=0;;
        H12[i]=new  float[256];
        for(int j=0;j<256;j++)
        {
            H12[i][j]=0;
        }
    }
    int IniMptc=0;
    for(int i=0;i<limg.rows;i++)
    {
        for(int j=0;j<limg.cols;j++)
        {
            if(d[i][j]!=-1&&(j-d[i][j])>=0)
            {
                int grayv1=(int)limg.at<uchar>(i,j);
                int grayv2=(int)rimg.at<uchar>(i,j-d[i][j]);
                H1[grayv1]=H1[grayv1]+1;
                H2[grayv2]=H1[grayv2]+1;
                H12[grayv1][grayv2]=H12[grayv1][grayv2]+1;///////////////频率直方图
                IniMptc++;
            }
        }
    }
    for(int i=0;i<256;i++)
    {
        H1[i]=H1[i]/IniMptc;
        H2[i]=H2[i]/IniMptc;
        for(int j=0;j<256;j++)
        {
            H12[i][j]=H12[i][j]/IniMptc;
        }
    }
    float HA,HB,HAB;
    HA=HB=HAB=0;
    for(int i=0;i<256;i++)
    {
        if(H1[i]!=0)
        {
            HA=HA+(-H1[i]*log(H1[i]));
        }
        if(H2[i]!=0)
        {
            HB=HB+(-H2[i]*log(H2[i]));
        }
        for(int j=0;j<256;j++)
        {
            if(H12[i][j]!=0)
            {
                HAB=HAB+(-H12[i][j]*log(H12[i][j]));
            }
        }
    }
    float IAB=HA+HB-HAB;
    cout<<IAB<<endl;
    return 0;
}

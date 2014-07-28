//
//  main.cpp
//  PI
//
//  Created by PeterChoi on 2014. 7. 22..
//  Copyright (c) 2014년 PeterChoi. All rights reserved.
//

// 1 2 3 4 5 / 6 7 8 9 10 11 12 13

#include <iostream>
#include <string.h>

#define TEST_MODE true
#if TEST_MODE
#include <fstream>
#endif

char strIn[10000+1];
int  strMin[10000];
int strSize;

int ms; //minimum score
int ts; //temp score

enum {c1=1,c2=2,c3=4,c4=5,c5=10}; //part case

int findCase(const int ii, int nl)
{
    int rr = c5;
    
    if(strIn[ii] == strIn[ii+1] && strIn[ii] == strIn[ii+2])
    {
        for(int i=3 ; i<nl ; i++)
            if(strIn[ii] != strIn[ii+i])
                return c5;
        
        rr = c1;
        
    }
    else if(strIn[ii+1] - strIn[ii] == strIn[ii+2] - strIn[ii+1])
    {
        int gap = strIn[ii+1] - strIn[ii];
        
        for(int i=3 ; i<nl ; i++)
            if(strIn[ii+i] - strIn[ii+i-1] != gap)
                return c5;
        
        if(gap == 1 || gap == -1)
            rr = c2;
        else
            rr = c4;
    }
    else if(strIn[ii] == strIn[ii+2])
    {
        // 아오 모르겠다
        if(nl >= 4 && strIn[ii+1] != strIn[ii+3]) return c5;
        if(nl == 5 && strIn[ii+2] != strIn[ii+4]) return c5;
        rr = c3;
    }
    
    return rr;
}


int find(const int ii)
{
    if(ii >= strSize) return 0;
    
    if(strMin[ii] != -1) return strMin[ii];
    
    int nMinSize = 987654321;
    int nTemp;
    
    for(int i=3 ; i<= 5 ; i++)
    {
        if(ii+i<=strSize)
        {
            nTemp = find(ii+i) + findCase(ii, i);
            nMinSize = (nMinSize > nTemp)?nTemp:nMinSize;
        }
    }
    strMin[ii] = nMinSize;
    return nMinSize;
}


int main(int argc, const char * argv[])
{
    int c = 0;
    
#if TEST_MODE
    std::ifstream myFile ("input.txt");
    std::ifstream myFile2 ("output.txt");
    
    int r;
    
    if (myFile.is_open())
        myFile>>c;
    else
        return -1;
#else
    std::cin>>c;
#endif
    for(int i=0 ; i<c ; i++)
    {
        ms = 10000*10 + 1;
        ts = 0;
#if TEST_MODE
        myFile>>strIn;
        myFile2>>r;
#else
        std::cin>>strIn;
#endif
        strSize = (int)strlen(strIn);
        //find(0);
        for(int i=0 ; i<strSize ; i++)
            strMin[i] = -1;
        
        ms = find(0);
        
        std::cout<<ms<<std::endl;
        
#if TEST_MODE
        if(r != ms)
            std::cout<<"false"<<std::endl;
#endif
    }
#if TEST_MODE
    myFile.close();
    myFile2.close();
#endif
    
    return 0;
}


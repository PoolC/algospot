//
//  main.cpp
//  QUADTREE
//
//  Created by PeterChoi on 2014. 7. 11..
//  Copyright (c) 2014년 PeterChoi. All rights reserved.
//

/* 1차 제출
 submission.cpp: In function ‘int swaptree(int)’:
 submission.cpp:42:17: warning: converting to non-pointer type ‘char’ from NULL [-Wconversion-null]
 strT[i] = NULL;
 ^
 submission.cpp:44:51: error: ‘strncpy’ was not declared in this scope
 strncpy(strT, &MT[ii+sz[0]+sz[1]], sz[2]+sz[3]);
 ^
 submission.cpp:45:39: error: ‘strncat’ was not declared in this scope
 strncat(strT, &MT[ii], sz[0]+sz[1]);
 ^
 submission.cpp: In function ‘int main(int, const char**)’:
 submission.cpp:84:28: error: ‘strlen’ was not declared in this scope
 sl = (int)strlen(MT);
 */


#include <iostream>

#define TEST_MODE false
#if TEST_MODE
#include <fstream>
#endif

char MT[1000+1]; // Map tree
//char RT[1000+1]; // Result tree

//int sl; // =strlen

char strT[1000+1]; // string temp -> for swap

int swaptree(const int ii)
{
    int sz[4]; //swap을 위해 변경해야 하는 size 저장
    int iid=ii; // inner index
    
    for(int i=0 ; i<4 ; i++)
    {
        sz[i] = 1;
        if(MT[iid+i] == 'x')
        {
            int a = swaptree(iid+i+1);
            sz[i] += a;
            iid += a;
        }
    }
    //int nn = sz[0] + sz[1] + sz[2] + sz[3]; // strlen(strT)
    
//    for(int i=0 ; i<1000+1 ; i++)
//        strT[i] = NULL;
//    
//    strncpy(strT, &MT[ii+sz[0]+sz[1]], sz[2]+sz[3]);
//    strncat(strT, &MT[ii], sz[0]+sz[1]);
    
//    for(int i = 0 ; i<nn ; i++)
//    {
//        MT[ii+i] = strT[i];
//    }
    int n01 = sz[0] + sz[1];
    int n23 = sz[2] + sz[3];
    int nn = n01 + n23;
    for(int i=0 ; i<n23 ; i++)
    {
        strT[i] = MT[ii+n01+i];
    }
    for(int i=0 ; i<n01 ; i++)
    {
        strT[n23+i] = MT[ii+i];
    }
    for(int i = 0 ; i<nn ; i++)
    {
        MT[ii+i] = strT[i];
    }
    
    
    return nn;
}

int main(int argc, const char * argv[])
{
    int c = 0;
    
#if TEST_MODE
    std::ifstream myFile ("input.txt");
    std::ifstream myFile2 ("result.txt");
    
    char strResult[1000+1];
    
    if (myFile.is_open())
        myFile>>c;
    else
        return -1;
#else
    std::cin>>c;
#endif
    for(int i=0 ; i<c ; i++)
    {
    
#if TEST_MODE
        myFile>>MT;
        myFile2>>strResult;
        std::cout<<MT<<std::endl;
#else
        std::cin>>MT;
#endif
        
        //sl = (int)strlen(MT);
    
        if(MT[0] == 'x')
        {
            swaptree(1);
        }
        
#if TEST_MODE
        char rr;
        
        if(strcmp(MT, strResult) == 0)
            rr = 'T';
        else
        {
            rr = 'F';
            std::cout<<strResult<<std::endl;
        }
        std::cout<<MT<<"("<<rr<<")"<<std::endl;
#else
        std::cout<<MT<<std::endl;
#endif
    
    }
#if TEST_MODE
    myFile.close();
#endif
    
    return 0;
}


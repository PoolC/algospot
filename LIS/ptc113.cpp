//
//  main.cpp
//  LIS
//
//  Created by PeterChoi on 2014. 7. 22..
//  Copyright (c) 2014년 PeterChoi. All rights reserved.
//

#include <iostream>

#define TEST_MODE false
#if TEST_MODE
#include <fstream>
#endif

int n;
int in[500];
int nEachMax[500];

int cu; //count
int mc; //max count

// 2차 시도에서 시간 복잡도가 order n! 으로 하니 시간 초과 ㅋㅋㅋㅋ
//void find(int nHead, int index)
//{
//    if(cu > mc)
//        mc = cu;
//
////    if( n - index - 1 < mc - cu)
////        return;
//
//    for(int i=index ; i<n ; i++)
//    {
//        if(n - i - 1 < mc - cu)
//            break;
//        if(in[i] > nHead)
//        {
//            cu++;
//            find(in[i],i+1);
//            cu--;
//        }
//    }
//}


int main(int argc, const char * argv[])
{
    int c = 0;
    
    
    
#if TEST_MODE
    std::ifstream myFile ("LIS_input.txt");
    std::ifstream myFile2 ("LIS_output.txt");
    
    
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
        int rr;
        myFile>>n;
        myFile2>>rr;
#else
        std::cin>>n;
#endif
        for(int i=0 ; i<n ; i++)
        {
#if TEST_MODE
            myFile>>in[i];
#else
            std::cin>>in[i];
#endif
            nEachMax[i] = 1;
        }
        
        
        mc = 0;
        for(int i=n-1 ; i>=0 ; i--)
        {
            cu = 1;
            
            for(int j=i+1 ; j<n ; j++)
            {
                if(in[i]<in[j])
                {
                    if(nEachMax[i] + nEachMax[j] > cu)
                    {
                        cu = nEachMax[i] + nEachMax[j];
                    }
                }
            }
            nEachMax[i] = cu;
            
            if(cu > mc)
                mc = cu;
        }
        
        
        std::cout<<mc<<std::endl;
        
#if TEST_MODE
        if(rr != mc)
            std::cout<<"false"<<std::endl;
#endif
    }
#if TEST_MODE
    myFile.close();
    myFile2.close();
#endif
    
    return 0;
}



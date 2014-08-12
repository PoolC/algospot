//
//  main.cpp
//  WORDCHAIN
//
//  Created by PeterChoi on 2014. 8. 11..
//  Copyright (c) 2014년 PeterChoi. All rights reserved.
//

//1차 제출 : 시간초과

#include <iostream>
#include <string.h>
#include <list>

#define TEST_MODE false
#if TEST_MODE
#include <fstream>
#endif

int n;

char strInput[100][10+1];
int  nInputSize[100];
bool isUsed[100];

std::list<char*> strResult;

bool AllUsed()
{
    for(int i=0 ; i<n ; i++)
        if(isUsed[i] == false)
            return false;
    
    return true;
}

bool find(char c)
{
    if(AllUsed()) return true;
    
    for(int i=0 ; i<n ; i++)
    {
        if(isUsed[i] == false && strInput[i][0] == c)
        {
            isUsed[i] = true;
            
            if(find(strInput[i][nInputSize[i]-1]))
            {
                strResult.push_front(strInput[i]);
                return true;
            }
            
            isUsed[i] = false;
        }
    }
    
    return false;
}


int main(int argc, const char * argv[])
{
    int c = 0;
    
#if TEST_MODE
    std::ifstream myFile ("input_WORDCHAIN.txt");
    
    
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
        myFile>>n;
#else
        std::cin>>n;
#endif
        char strTemp[11];
        for(int j=0 ; j<n ; j++)
        {
#if TEST_MODE
            myFile>>strTemp;
#else
            std::cin>>strTemp;
#endif
            nInputSize[j] = (int)strlen(strTemp);
            isUsed[j] = false;
            strcpy(strInput[j], strTemp);
        }
        strResult.clear();
        
        for(int j=0 ; j<n ; j++)
        {
            isUsed[j] = true;
            if(find(strInput[j][nInputSize[j]-1]))
            {
                strResult.push_front(strInput[j]);
                break;
            }
            isUsed[j] = false;
        }
        
        if(strResult.empty())
        {
            std::cout<<"IMPOSSIBLE"<<std::endl;
        }
        else
        {
            for(std::list<char*>::iterator iter = strResult.begin() ; iter != strResult.end() ; iter++)
            {
                std::cout<<*iter<<" ";
            }
            std::cout<<std::endl;
        }
        
    }
#if TEST_MODE
    myFile.close();
#endif
    
    return 0;
}
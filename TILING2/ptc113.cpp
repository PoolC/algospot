//
//  main.cpp
//  TILING2
//
//  Created by PeterChoi on 2014. 7. 29..
//  Copyright (c) 2014년 PeterChoi. All rights reserved.
//

#include <iostream>

#define TEST_MODE false
#if TEST_MODE
#include <fstream>
#endif

int n;
unsigned int nMemory[101];

unsigned int find(int nColumnSize)
{
    if(nMemory[nColumnSize] != 0)
        return nMemory[nColumnSize];
    
    if(nColumnSize > 2)
    {
        nMemory[nColumnSize] = (find(nColumnSize -1) + find(nColumnSize -2)) % 1000000007;
        return nMemory[nColumnSize];
    }
    else if(nColumnSize > 1) // 2
    {
        return 2;
    }
    else // 1 or 0
    {
        return nColumnSize;
    }
}

int main(int argc, const char * argv[])
{
    int c = 0;
    
#if TEST_MODE
    std::ifstream myFile ("tiling2_input.txt");
    std::ifstream myFile2 ("tiling2_output.txt");
    
    
    if (myFile.is_open())
        myFile>>c;
    else
        return -1;
#else
    std::cin>>c;
#endif
    
    for(int i=0 ; i<=100 ; i++)
    {
        nMemory[i] = 0;
    }
    
    for(int i=0 ; i<c ; i++)
    {
#if TEST_MODE
        myFile>>n;
#else
        std::cin>>n;
#endif
        unsigned int nResult = find(n);
        
        std::cout<<nResult<<std::endl;
        
#if TEST_MODE
        int nOutput;
        myFile2>>nOutput;
        if(nResult != nOutput)
            std::cout<<"false"<<std::endl;
#endif
        
    }
#if TEST_MODE
    myFile.close();
    myFile2.close();
#endif
    
    return 0;
}


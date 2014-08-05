//
//  main.cpp
//  ITES
//
//  Created by PeterChoi on 2014. 8. 5..
//  Copyright (c) 2014년 PeterChoi. All rights reserved.
//

#include <iostream>
#include <list>
#include <math.h>

#define TEST_MODE true
#if TEST_MODE
#include <fstream>
#endif

//1차 제출 시간초과
// 큐를 하나 만들어서 시간을 줄여야 겠음



int main(int argc, const char * argv[])
{
    int c = 0;
    unsigned int k;
    unsigned int n;
    unsigned int nResult;
    
    unsigned long long llAValue;
    unsigned int nAValue;
    unsigned int nTemp;
    
    //unsigned int lastN = 0;
    //unsigned long long llAValueLast = 0;
    //short nMemory[50000000];
    
    const unsigned long long MOD = pow(2, 32);
    
    std::list<int> listInput;
    
#if TEST_MODE
    std::ifstream myFile ("input_Ites.txt");
    
    
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
        myFile>>k;
        myFile>>n;
#else
        std::cin>>k;
        std::cin>>n;
#endif
        llAValue = 1983;
        nTemp = 0;
        nResult = 0;
        listInput.clear();
        for(int j=0 ; j<n ; j++)
        {
//            if(lastN > j)
//            {
//                nAValue = nMemory[j];
//                
//                llAValue = llAValueLast;
//            }
//            else
            {
                nAValue = llAValue % 10000 +1;
                nTemp += nAValue;
                //nMemory[lastN] = nAValue;
                //lastN++;
                
                llAValue = (llAValue * 214013 + 2531011) % MOD;
            }
            
            listInput.push_back(nAValue);
            while(nTemp > k)
            {
                nTemp -= listInput.front();
                listInput.pop_front();
            }

            if(nTemp == k)
                nResult++;
        }
        
        std::cout<<nResult<<std::endl;
        
    }
#if TEST_MODE
    myFile.close();
#endif
    
    return 0;
}


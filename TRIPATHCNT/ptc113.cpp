//
//  main.cpp
//  TRIPATHCNT
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
int nResultMap[100][100];

int find(int row, int col)
{
    if( row != n-1 -1)
    {
        if(nResultMap[row+1][col] > nResultMap[row+1][col+1])
        {
            return find(row+1, col);
        }
        else if(nResultMap[row+1][col] < nResultMap[row+1][col+1])
        {
            return find(row+1, col+1);
        }
        else
        {
            return find(row+1,col) + find(row+1, col+1);
        }
    }
    else
    {
        if(nResultMap[row+1][col] == nResultMap[row+1][col+1])
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }
}


int main(int argc, const char * argv[])
{
    int c;
    int nMap[100][100];
    
#if TEST_MODE
    std::ifstream myFile ("TRIPATHCNT_input.txt");
    std::ifstream myFile2 ("TRIPATHCNT_output.txt");
    
    
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
        for(int j=0 ; j<n ; j++)
            for(int k=0 ; k<j+1 ; k++)
            {
#if TEST_MODE
                myFile>>nMap[j][k];
#else
                std::cin>>nMap[j][k];
#endif
            }
        //가장 아래층!
        for(int j=0 ; j<n ; j++)
            nResultMap[n-1][j] = nMap[n-1][j];
        
        for(int j=n-1 ; j>0 ; j--)
            for(int k=0 ; k<j ; k++)
            {
                nResultMap[j-1][k] = nMap[j-1][k] + ((nResultMap[j][k] > nResultMap[j][k+1])?nResultMap[j][k]:nResultMap[j][k+1]);
            }

        
        std::cout<<find(0, 0)<<std::endl;
        
    }
#if TEST_MODE
    myFile.close();
    myFile2.close();
#endif
    
    return 0;
}


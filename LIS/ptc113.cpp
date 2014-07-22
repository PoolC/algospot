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

int cu; //count
int mc; //max count


int main(int argc, const char * argv[])
{
    int c = 0;
    
    int nt=0; //num temp
    int de=987654321; //degree
    
    
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
        }
        
        mc = 0;
        for(int i=0 ; i<n ; i++)
        {
            nt = in[i];
            cu = 1;
            for(int j=i+1 ; j<n ; j++)
            {
                if( in[j] > nt)
                {
                    nt = in[j];
                    cu++;
                }
            }
            if(mc < cu)
                mc = cu;
            if( i + mc > n - i)
                break;
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



//
//  main.cpp
//  BOARDCOVER
//
//  Created by PeterChoi on 2014. 7. 7..
//  Copyright (c) 2014년 PeterChoi. All rights reserved.
//

#include <iostream>

#define TEST_MODE false
#if TEST_MODE
#include <fstream>
#include <string>
#endif


int h,w; // input
bool map[20][20];
int n; // result

void find(int x, int y)
{
    //draw map
//    for(int i=0 ; i<h ; i++)
//    {
//        for(int j=0 ; j<w ; j++)
//        {
//            if(i==x && j==y)
//                std::cout<<"2";
//            else if(map[i][j])
//                std::cout<<"0";
//            else
//                std::cout<<"1";
//        }
//        std::cout<<std::endl;
//    }
//    std::cout<<std::endl;
    
    if(y >= w)
    {
        x++;
        y = 0;
        if(x==h-1)
        {
            for(int i=x ; i<h ; i++) // -1 인이유는 가장 아랫줄 까지 않가도 마무리 되기 때문
                for(int j=y ; j<w ; j++)
                    if(map[i][j])
                        return;
            
            n++; // success!!
            return;
        }
    }
    
    bool isRool = false;
    for(int i=x ; i<h - 1 ; i++) // -1 인이유는 가장 아랫줄 까지 않가도 마무리 되기 때문
    {
        for(int j= (isRool)?0:y ; j<w ; j++)
        {
            if(map[i][j])
            {
                map[i][j] = false;
                // ㄱ
                if(j<w-1 && map[i][j+1] && map[i+1][j+1])
                {
                    map[i][j+1] = false;
                    map[i+1][j+1] = false;
                    find(i, j+2);
                    map[i][j+1] = true;
                    map[i+1][j+1] = true;
                }
                // ㄱ 반대
                if(j<w-1 && map[i][j+1] && map[i+1][j])
                {
                    map[i][j+1] = false;
                    map[i+1][j] = false;
                    find(i, j+2);
                    map[i][j+1] = true;
                    map[i+1][j] = true;
                }
                // ㄴ
                if(j<w-1 && map[i+1][j] && map[i+1][j+1])
                {
                    map[i+1][j] = false;
                    map[i+1][j+1] = false;
                    find(i, j+1);
                    map[i+1][j] = true;
                    map[i+1][j+1] = true;
                }
                // ㄴ 반대
                if(j<w && j>0 && map[i+1][j-1] && map[i+1][j])
                {
                    map[i+1][j-1] = false;
                    map[i+1][j] = false;
                    find(i, j+1);
                    map[i+1][j-1] = true;
                    map[i+1][j] = true;
                }
                map[i][j] = true;
                
                return; // 더 전진 하면 뒤에 구멍 생김
            }
        }
        isRool = true;
    }
    find(x, y+1);
    
}


int main(int argc, const char * argv[])
{
    int c = 0;
    char temp;
    int n3; //빈공간이 3의 배수인지 체크
    
#if TEST_MODE
    //std::string strTemp;
    //std::string line;
    std::ifstream myFile ("test.txt");
    
    
    if (myFile.is_open())
        myFile>>c;
    else
        return -1;
#else
    std::cin>>c;
#endif
    
    for(int i=0 ; i<c ; i++)
    {
        n = 0;
        n3 = 0;
#if TEST_MODE
        myFile>>h>>w;
#else
        std::cin>>h>>w;
#endif
        
        for(int j=0 ; j<h ; j++)
            for(int k=0 ; k<w ; k++)
            {
#if TEST_MODE
                myFile>>temp;
#else
                std::cin>>temp;
#endif
                if(temp == '#')
                    map[j][k] = false;
                else
                {
                    map[j][k] = true;
                    n3++;
                }
            }
        
        if(n3 % 3 == 0)
            find(0, 0);
        
        std::cout<<n<<std::endl;
    }
    
#if TEST_MODE
     myFile.close();
#endif

    return 0;
}


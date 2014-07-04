//
//  main.cpp
//  PICNIC
//
//  Created by PeterChoi on 2014. 7. 4..
//  Copyright (c) 2014년 PeterChoi. All rights reserved.
//

#include <iostream>

int nn; //방법의 수
int n; //학생수

bool ff[10][10]; //친구쌍
bool bf[10]; //각회마다 선택된 사람


bool isAllTrue()
{
    for(int i=0 ; i<n ; i++)
    {
        if(bf[i] == false)
            return false;
    }
    
    return true;
}

void find(int index)
{
    for(int i=index+1 ; i<n ; i++)
    {
        if(ff[index][i] && bf[i] == false)
        {
            bf[index] = true;
            bf[i] = true;
            
            if(isAllTrue())
            {
                nn++;
            
                bf[index] = false;
                bf[i] = false;
                
                return;
            }
            else
            {
                for(int j=index+1 ; j<n ; j++)
                {
                    if(bf[j] == false)
                        find(j);
                }
            }
            
            bf[index] = false;
            bf[i] = false;
        }
    }
}


int main(int argc, const char * argv[])
{
    int c; //테스트 케이스
    //int n; //학생수
    int m; //친구 쌍의 수
    
    int f1,f2; //친구쌍 입력값
    
    //bool ff[10][10]; //친구쌍
    //bool bf[10]; //각회마다 선택된 사람수
    
    std::cin>>c;
    
    for(int i=0 ; i<c ; i++)
    {
        std::cin>>n>>m;
        
        nn=0;
        //memset(ff, false, sizeof(bool)*100);
        //memset(bf, false, sizeof(bool)*10);
        for(int j=0 ; j<n ; j++)
        {
            bf[j] = false;
            for(int k=0 ; k<n ; k++)
                ff[j][k] = false;
        }
        
        
        for(int j=0 ; j<m ; j++)
        {
            std::cin>>f1>>f2;
            ff[f1][f2] = true;
            ff[f2][f1] = true;
        }
        
        bf[0] = true;
        for(int j=1 ; j<n ; j++)
        {
            if(ff[0][j])
            {
                bf[j] = true;
             
                if(isAllTrue())
                {
                    nn++;
                    break;
                }
                for(int k=1 ; k<n ; k++)
                {
                    if(bf[k] == false)
                        find(k);
                }
                
                bf[j] = false;
            }
        }
        
        std::cout<<nn<<std::endl;
        
    }
    
    
    return 0;
}


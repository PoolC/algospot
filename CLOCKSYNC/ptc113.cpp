//
//  main.cpp
//  SynchronizingClocks
//
//  Created by PeterChoi on 2014. 7. 8..
//  Copyright (c) 2014년 PeterChoi. All rights reserved.
//

#include <iostream>
#include <list>

int cs[16]; //clock state
int cc[10];  //case call 해당 case가 몇번 불렸는지 저장

int cn; //call num  불린 횟수
int mn; //minimum num

bool found;

bool isEnd()
{
    for(int i=0 ; i<16 ; i++)
        if(cs[i] % 12 != 0)
            return false;
    return true;
}

void ChangeNum(int ncase, bool bPlus = true)
{
    int pp = (bPlus)? 3 : -3;
    
    switch (ncase) {
        case 0:
            cs[0]+=pp;
            cs[1]+=pp;
            cs[2]+=pp;
            break;
        case 1:
            cs[3]+=pp;
            cs[7]+=pp;
            cs[9]+=pp;
            cs[11]+=pp;
            break;
        case 2:
            cs[4]+=pp;
            cs[10]+=pp;
            cs[14]+=pp;
            cs[15]+=pp;
            break;
        case 3:
            cs[0]+=pp;
            cs[4]+=pp;
            cs[5]+=pp;
            cs[6]+=pp;
            cs[7]+=pp;
            break;
        case 4:
            cs[6]+=pp;
            cs[7]+=pp;
            cs[8]+=pp;
            cs[10]+=pp;
            cs[12]+=pp;
            break;
        case 5:
            cs[0]+=pp;
            cs[2]+=pp;
            cs[14]+=pp;
            cs[15]+=pp;
            break;
        case 6:
            cs[3]+=pp;
            cs[14]+=pp;
            cs[15]+=pp;
            break;
        case 7:
            cs[4]+=pp;
            cs[5]+=pp;
            cs[7]+=pp;
            cs[14]+=pp;
            cs[15]+=pp;
            break;
        case 8:
            cs[1]+=pp;
            cs[2]+=pp;
            cs[3]+=pp;
            cs[4]+=pp;
            cs[5]+=pp;
            break;
        case 9:
            cs[3]+=pp;
            cs[4]+=pp;
            cs[5]+=pp;
            cs[9]+=pp;
            cs[13]+=pp;
            break;
    }
}

void findM2(int ii)
{
    if( cn > mn)
        return;
    if(isEnd())
    {
        mn = cn;
        found = true;
        return;
    }
    
    for( int i=0 ; i<4 ; i++)
    {
        
        for(int j=0 ; j<i ; j++)
            ChangeNum(ii);
        //cc[ii] = i;
        cn += i;
        if(isEnd())
        {
            mn = cn;
            found = true;
            return;
        }
        else if(ii < 9)
        {
            findM2(ii+1);
        }
        for(int j=0 ; j<i ; j++)
            ChangeNum(ii,false);
        cn -= i;
        
        if(found)
            return;
    }
}

int main(int argc, const char * argv[])
{
    int c;
    
    std::cin>>c;
    
    for(int i=0 ; i<c ; i++)
    {
        for(int j=0 ; j<16 ; j++)
            std::cin>>cs[j];
        for(int j=0 ; j<10 ; j++)
            cc[j] = 0;
        cn=0;
        mn = 3*10 + 1;
        found = false;
        
        findM2(0);
        
        //        for(int j=1 ; j<30 ; j++)
        //        {
        //            mn = j;
        //            findM2(0);
        //            if(found)
        //                break;
        //        }
        
        if(found == false)
        {
            for(int j=0 ; j<10; j++)
            {
                for(int k=0 ; k<3 ; k++)
                    ChangeNum(j);
            }
            found = isEnd();
        }
        
        if(found)
            std::cout<<mn<<std::endl;
        else
            std::cout<<"-1"<<std::endl;
        
    }
    
    return 0;
}


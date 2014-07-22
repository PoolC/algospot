//
//  main.cpp
//  PI
//
//  Created by PeterChoi on 2014. 7. 22..
//  Copyright (c) 2014년 PeterChoi. All rights reserved.
//

#include <iostream>

#define TEST_MODE false
#if TEST_MODE
#include <fstream>
#include <string.h>
#endif

char strIn[10000+1];
int ms; //minimum score
int ts; //temp score

enum pc{c1,c2,c3,c4,c5}; //part case

pc findCase(const int ii)
{
    pc rr = c5;
    
    if(strIn[ii+1] && strIn[ii+2])
    {
        if(strIn[ii] == strIn[ii+1] && strIn[ii] == strIn[ii+2])
        {
            rr = c1;
        }
        else if(strIn[ii+1] - strIn[ii] == strIn[ii+2] - strIn[ii+1])
        {
            if(strIn[ii+1] - strIn[ii] == 1 || strIn[ii+1] - strIn[ii] == -1)
                rr = c2;
            else
                rr = c4;
        }
        else if(strIn[ii] == strIn[ii+2])
        {
            rr = c3;
        }
    }
    return rr;
}


void find(const int ii)
{
    int t;
    int tt;
    
    if(ms <= ts) return;
    
    if(strIn[ii] == '\0')
    {
        if( ms > ts)
            ms = ts;
        return;
    }
    
    if(strIn[ii+1])
    {
        switch(findCase(ii))
        {
            case c1:
                t = 1;
                for(int i=1 ; i<5 + 3 ; i++)
                {
                    if(strIn[ii+i] && (strIn[ii] == strIn[ii+i])) t++;
                    else break;
                }
                if( t >= 6)
                {
                    ts += 1;
                    find(ii + t - 3); //6번 이상 페턴이 반복되면 n + 3 개로 나누는 것이 더 유리하기 때문
                    ts -= 1;
                }
                else if( t >= 3)
                {
                    ts += 1;
                    find(ii+t);
                    ts -= 1;
                }
                break;
            case c2:
                t = 0;
                tt = strIn[ii+1] - strIn[ii]; //속도를 위해 strIn[ii] - '0' 생략
                
                if(tt == 1 || tt == -1)
                {
                    t += 2;
                    for(int i=1 ; i<4 + 3 ; i++)
                    {
                        if(strIn[ii+1+i] && (strIn[ii+1+i] - strIn[ii+i]) == tt) t++;
                        else break;
                    }
                }
                
                //마지막에 한자리 때문에 다음 페턴이 어려워 지는 경우
                if( t >= 4)
                {
                    if(findCase(ii + t - 1) < c2)
                        t--;
                }
                
                if( t >= 6)
                {
                    ts += 2;
                    find(ii + t - 3); //6번 이상 페턴이 반복되면 n + 3 개로 나누는 것이 더 유리하기 때문
                    ts -= 2;
                }
                else if(t >= 3)
                {
                    ts += 2;
                    find(ii+t);
                    ts -= 2;
                }
                break;
            case c3:
            {
                t = 2;
                char c1 = strIn[ii];
                char c2 = strIn[ii+1];
                
                for(int i=2 ; i<5 + 3 ; i++)
                {
                    if( i % 2 == 0)
                    {
                        if(strIn[ii+i]&&strIn[ii+i] == c1) t++;
                        else break;
                    }
                    else
                    {
                        if(strIn[ii+i]&&strIn[ii+i] == c2) t++;
                        else break;
                    }
                }
                //마지막에 한자리 때문에 다음 페턴이 어려워 지는 경우
                if( t >= 4)
                {
                    if(findCase(ii + t - 1) < c3)
                        t--;
                }
                if( t >= 6)
                {
                    ts += 4;
                    find(ii + t - 3); //6번 이상 페턴이 반복되면 n + 3 개로 나누는 것이 더 유리하기 때문
                    ts -= 4;
                }
                else if(t>=3)
                {
                    ts += 4;
                    find(ii+t);
                    ts -= 4;
                }
                break;
            }
            case c4:
                t = 0;
                tt = strIn[ii+1] - strIn[ii]; //속도를 위해 strIn[ii] - '0' 생략
                //if(tt == 1 || tt == -1)
                {
                    t += 2;
                    for(int i=1 ; i<4 + 3 ; i++)
                    {
                        if(strIn[ii+1+i]&&(strIn[ii+1+i] - strIn[ii+i]) == tt) t++;
                        else break;
                    }
                }
                //마지막에 한자리 때문에 다음 페턴이 어려워 지는 경우
                if( t >= 4)
                {
                    if(findCase(ii + t - 1) < c4)
                        t--;
                }
                if( t >= 6)
                {
                    ts += 5;
                    find(ii + t - 3); //6번 이상 페턴이 반복되면 n + 3 개로 나누는 것이 더 유리하기 때문
                    ts -= 5;
                }
                else if(t >= 3)
                {
                    ts += 5;
                    find(ii+t);
                    ts -= 5;
                }
                break;
            case c5:
                t = 1;
                for(int i=1 ; i<5+3 ; i++)
                {
                    if(strIn[ii+i] && findCase(ii+i) == c5) t++;
                    else break;
                }
                if( t>= 6)
                {
                    ts += 10;
                    find(ii+t-3);
                    ts -= 10;
                }
                else if( t>= 3)
                {
                    ts += 10;
                    find(ii+t);
                    ts -= 10;
                }
                else
                {
                    //이 케이스가 있는가?
                    ts += 10;
                    find(ii+t);
                    ts -= 10;
                }
                break;
        }
    }
}


int main(int argc, const char * argv[])
{
    int c = 0;
    
#if TEST_MODE
    std::ifstream myFile ("input.txt");
    std::ifstream myFile2 ("output.txt");
    
    int r;
    
    if (myFile.is_open())
        myFile>>c;
    else
        return -1;
#else
    std::cin>>c;
#endif
    for(int i=0 ; i<c ; i++)
    {
        ms = 10000*10 + 1;
        ts = 0;
#if TEST_MODE
        myFile>>strIn;
        myFile2>>r;
#else
        std::cin>>strIn;
#endif
        
        find(0);
        
        
        std::cout<<ms<<std::endl;
        
#if TEST_MODE
      if(r != ms)
          std::cout<<"false"<<std::endl;
#endif
    }
#if TEST_MODE
    myFile.close();
    myFile2.close();
#endif
    
    return 0;
}


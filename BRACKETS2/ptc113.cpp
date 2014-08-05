//
//  main.cpp
//  BRACKETS2
//
//  Created by PeterChoi on 2014. 8. 5..
//  Copyright (c) 2014년 PeterChoi. All rights reserved.
//

/* 1 차 제출
 submission.cpp: In function ‘int main(int, const char**)’:
 submission.cpp:46:39: error: ‘strlen’ was not declared in this scope
 nLength = (int)strlen(strInput);
 */
/* 2 차 제출
 RTE (SIGSEGV: segmentation fault, probably incorrect memory access)
 */

#include <iostream>
#include <string.h>
#include <stack>

#define TEST_MODE false
#if TEST_MODE
#include <fstream>
#endif

struct likeStack{
    char strStack[10000+1];
    int nTopIndex;
    likeStack()
    {
        nTopIndex = -1; // -1이 빈거
    }
    char top()
    {
        if(nTopIndex != -1)
            return strStack[nTopIndex];
        else
            return '0';
    }
    void pop() { nTopIndex--;}
    void push(char cInput)
    {
        nTopIndex++;
        strStack[nTopIndex] = cInput;
    }
};

int main(int argc, const char * argv[])
{
    int c = 0;
    int nLength;
    char strInput[10000+1];
    char cTemp;
    bool bResult;
    
    //std::stack<char> cStack;
    likeStack cStack2;
    
#if TEST_MODE
    std::ifstream myFile ("input_Brackets2.txt");
    
    
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
        myFile>>strInput;
#else
        std::cin>>strInput;
#endif
        nLength = (int)strlen(strInput);
        bResult = true;
        //while(cStack.empty() == false)
        //    cStack.pop();
        cStack2.nTopIndex = -1;
        
        for(int j=0 ; bResult && (j<nLength) ; j++)
        {
            cTemp = strInput[j];
            switch(cTemp)
            {
                case '(': case '{': case '[':
                    //cStack.push(cTemp);
                    //cStack2.nTopIndex++;
                    cStack2.push(cTemp);
                    break;
                case ')':
                    if(cStack2.top() == '(') cStack2.pop();
                    else bResult = false;
                    break;
                case '}':
                    if(cStack2.top() == '{') cStack2.pop();
                    else bResult = false;
                    break;
                case ']':
                    if(cStack2.top() == '[') cStack2.pop();
                    else bResult = false;
                    break;
//                    switch(cStack.top())
//                {
//                    case '(':
//                        if(cTemp == ')')
//                            cStack.pop();
//                        else
//                            bResult = false;
//                        break;
//                    case '{':
//                        if(cTemp == '}')
//                            cStack.pop();
//                        else
//                            bResult = false;
//                        break;
//                        
//                    case '[':
//                        if(cTemp == ']')
//                            cStack.pop();
//                        else
//                            bResult = false;
//                        break;
//                }
//                    break;
            }
        }
        if(bResult && cStack2.top() == '0')
            std::cout<<"YES"<<std::endl;
        else
            std::cout<<"NO"<<std::endl;
        
    }
#if TEST_MODE
    myFile.close();
#endif
    
    return 0;
}
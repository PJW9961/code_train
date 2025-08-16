#include<iostream>
#include<string>
using namespace std;
int maximum69Number (int num) 
    {
        string s=to_string(num);
        int i=s.find('6');
        //没找到6
        if(i==string::npos)
        {
            return num;
        }

        //替换高位6
        s[i]='9';
        return stoi(s);
    }
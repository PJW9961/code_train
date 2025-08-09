#include<iostream>
#include<windows.h>
using namespace std;
bool isPowerOfTwo(int n) 
{
  return n>0&&(n&(n-1))==0;
}

int main()
{
  int a=16;
  cout<<isPowerOfTwo(a);
  system("pause");
  return 0;
}
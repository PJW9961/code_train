#include<iostream>
#include<cmath>
using namespace std;
bool isPowerOfThree(int n) 
{
    int power=1;
    while(power<(pow(2,31)-1)/3)
    {
      power*=3;
    }

    return n>0&&power%n==0;
}
int main()
{
  return 0;
}
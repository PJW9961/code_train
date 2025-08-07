#include<iostream>
#include<vector>
#include<windows.h>
#include<iomanip>
#include<cmath>
using namespace std;


double dfs(int a,int b, vector<vector<double> >& memo)
{
  if (a <= 0 && b <= 0) return 0.5;  // 同时耗尽
    if (a <= 0) return 1.0;             // A先耗尽
    if (b <= 0) return 0.0;             // B先耗尽
    
    // 记忆化
    if (memo[a][b] != -1) return memo[a][b];
    
    // 状态转移：四种操作的期望
    double result = 0.25 * (
        dfs(a-4, b, memo) +      // 操作1
        dfs(a-3, b-1, memo) +    // 操作2  
        dfs(a-2, b-2, memo) +    // 操作3
        dfs(a-1, b-3, memo)      // 操作4
    );
    
    return memo[a][b] = result;
}

double soupServings(int n)
{
  n=ceil(n/25.0);
  if(n>=179) return 1;//防止大数大量占用空间
  vector<vector<double> > memo(n+1, vector<double>(n+1, -1));
  return dfs(n,n,memo);
}
int main()
{
  cout<<fixed<<setprecision(5);
  int n;
  cin>>n;
  cout<<soupServings(n);
  system("pause");
  return 0;
}
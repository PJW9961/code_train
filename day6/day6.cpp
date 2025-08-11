#include<iostream>
#include<vector>
#include<windows.h>
using namespace std;

vector<int> productQueries(int n, vector<vector<int>>& queries) 
{
  vector<int> powers, answer;
  const int MOD = 1000000007;
  
  // 位运算更快得到分解幂集
  int bit = 0;
  while(n > 0) {
    if(n & 1) //最后一位是1则加入powers进行分解
    {  
      powers.push_back(1 << bit);  
    }
    n >>= 1;
    bit++;
  }

  for(int i = 0; i < queries.size(); i++) {
    int left = queries[i][0];
    int right = queries[i][1];
    
    int product = 1;  
    for(int j = left; j <= right; j++) {
      product = (product * (powers[j]) % MOD)%MOD;
    }
    answer.push_back(product);
  }
  return answer;
}

int main()
{
  
  system("pause");
  return 0;
}

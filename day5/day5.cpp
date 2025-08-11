#include<iostream>
#include<string>
#include<map>  // 使用map替代unordered_map，兼容C++98
#include<vector>
#include<windows.h>
using namespace std;

map<long long, map<int,int> > powerOf2Counts;  // 注意空格，兼容旧编译器

void initPowerOf2Counts() {
  for(int i = 0; i <= 30; ++i) {  // 增加到30，覆盖更多情况
    long long powerKey = 1<< i;  // 使用long long避免溢出
    long long temp = powerKey;      // 临时变量用于计算
    cout<<powerKey<<endl;
    map<int,int> digitCount;
    
    // 初始化所有数字0-9的计数为0
    for(int j = 0; j <= 9; ++j) {
      digitCount[j] = 0;
    }
    
    // 统计这个2的幂的每个数字出现次数
    while(temp > 0) {
      digitCount[temp % 10]++;
      temp /= 10;
    }
    
    powerOf2Counts[powerKey] = digitCount;
  }
}

// 检查给定数字是否能重排列成2的幂
bool reorderedPowerOf2(int n) {
  if(n <= 0) return false;  // 边界条件
  initPowerOf2Counts();
  map<int,int> numCount;
  
  // 初始化数字计数
  for(int j = 0; j <= 9; ++j) {
    numCount[j] = 0;
  }
  
  // 统计输入数字的每个数字出现次数
  int temp = n;
  while(temp > 0) {
    numCount[temp % 10]++;
    temp /= 10;
  }
  
  // 检查是否与任何2的幂的数字频次匹配
  for(map<long long, map<int,int> >::iterator it = powerOf2Counts.begin(); 
      it != powerOf2Counts.end(); ++it) {
    if(numCount == it->second) {
      return true;
    }
  }
  return false;
}

int main() {
  cout<<reorderedPowerOf2(1)<<endl;
  system("pause");
  return 0;
}
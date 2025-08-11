# LeetCode Day 5 - 重新排序得到2的幂

> **题目链接**: [869. 重新排序得到2的幂 - LeetCode](https://leetcode.cn/problems/reordered-power-of-2/)  
> **难度**: 中等  
> **标签**: 数学, 计数, 枚举, 排序

## 题目描述

给定正整数 n ，我们按任何顺序（包括原始顺序）将数字重新排序，注意其前导数字不能为零。

如果我们可以通过上述方式得到 2 的幂，返回 `true`；否则，返回 `false`。

## 示例

### 示例 1：
```
输入：n = 1
输出：true
解释：1 可以重新排序得到 1，而 1 是 2 的幂（2^0 = 1）
```

### 示例 2：
```
输入：n = 10
输出：false
解释：10 的数字是 1 和 0，无论怎么重新排序都不能得到 2 的幂
```

## 解题思路

### 算法：数字频次统计 + 哈希表匹配

1. **核心思想**：将问题转化为数字频次匹配问题
2. **预处理**：统计所有可能的2的幂的数字频次
3. **匹配策略**：检查输入数字的频次是否与某个2的幂匹配

### 关键观察

#### 1. 数字重排的本质
- 重排数字不改变各个数字的出现次数
- 两个数字能互相重排当且仅当它们的数字频次完全相同

#### 2. 2的幂的范围
- 32位整数范围内：2^0 到 2^30
- 最大的2的幂：2^30 = 1,073,741,824

#### 3. 频次匹配
```
例如：46 → 频次统计：{4:1, 6:1}
     64 → 频次统计：{4:1, 6:1}
     两者频次相同，所以46可以重排成64
```

### 算法步骤

1. **预处理阶段**：
   - 生成所有32位范围内的2的幂
   - 统计每个2的幂的数字频次
   - 存储在哈希表中供后续查询

2. **查询阶段**：
   - 统计输入数字n的数字频次
   - 与预处理的2的幂频次进行匹配
   - 找到匹配则返回true，否则false

## 代码实现

### 完整解法

```cpp
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<windows.h>
using namespace std;

map<long long, map<int,int> > powerOf2Counts;

void initPowerOf2Counts() {
  for(int i = 0; i <= 30; ++i) {
    long long powerKey = 1LL << i;  // 修复：使用LL避免溢出
    long long temp = powerKey;
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
  if(n <= 0) return false;
  
  // 只需要初始化一次
  static bool initialized = false;
  if(!initialized) {
    initPowerOf2Counts();
    initialized = true;
  }
  
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

// 辅助函数：打印数字频次（调试用）
void printDigitCount(int n) {
  map<int,int> count;
  for(int j = 0; j <= 9; ++j) {
    count[j] = 0;
  }
  
  int temp = n;
  while(temp > 0) {
    count[temp % 10]++;
    temp /= 10;
  }
  
  cout << "数字 " << n << " 的频次: ";
  for(int i = 0; i <= 9; i++) {
    if(count[i] > 0) {
      cout << "[" << i << ":" << count[i] << "] ";
    }
  }
  cout << endl;
}

int main() {
  // 测试用例
  vector<int> testCases;
  testCases.push_back(1);
  testCases.push_back(10);
  testCases.push_back(16);
  testCases.push_back(24);
  testCases.push_back(46);
  testCases.push_back(125);
  testCases.push_back(128);
  
  cout << "=== 重新排序得到2的幂测试 ===" << endl;
  cout << "数字\t结果\t\t说明" << endl;
  cout << "----------------------------------------" << endl;
  
  for(size_t i = 0; i < testCases.size(); i++) {
    int num = testCases[i];
    bool result = reorderedPowerOf2(num);
    cout << num << "\t" << (result ? "true" : "false") << "\t\t";
    
    if(result) {
      cout << "可以重排成2的幂";
    } else {
      cout << "无法重排成2的幂";
    }
    cout << endl;
  }
  
  // 显示前10个2的幂
  cout << "\n=== 前10个2的幂 ===" << endl;
  for(int i = 0; i < 10; i++) {
    long long power = 1LL << i;
    cout << "2^" << i << " = " << power << endl;
  }
  
  system("pause");
  return 0;
}
```

## 算法分析

### 时间复杂度
- **预处理**: O(31 × log(2^30)) = O(31 × 30) = O(930) ≈ O(1)
- **单次查询**: O(log n + 31) = O(log n)
- **总体**: O(log n)

### 空间复杂度
- **存储31个2的幂**: O(31 × 10) = O(310) ≈ O(1)
- **临时频次统计**: O(10) = O(1)
- **总体**: O(1)

### 算法优势

| 特点 | 说明 |
|------|------|
| **高效查询** | 预处理后每次查询只需O(log n)时间 |
| **空间优化** | 只存储必要的频次信息 |
| **逻辑清晰** | 将重排问题转化为频次匹配 |
| **易于扩展** | 可以轻松适配其他数字重排问题 |

## 运行示例

### 测试输出
```
=== 重新排序得到2的幂测试 ===
数字    结果        说明
----------------------------------------
1       true        可以重排成2的幂
10      false       无法重排成2的幂
16      true        可以重排成2的幂
24      false       无法重排成2的幂
46      true        可以重排成2的幂
125     true        可以重排成2的幂
128     true        可以重排成2的幂

=== 前10个2的幂 ===
2^0 = 1
2^1 = 2
2^2 = 4
2^3 = 8
2^4 = 16
2^5 = 32
2^6 = 64
2^7 = 128
2^8 = 256
2^9 = 512
```

### 详细分析（46的例子）

```
输入: n = 46
步骤1: 统计46的数字频次
       4出现1次，6出现1次
       频次：{4:1, 6:1}

步骤2: 检查与2的幂匹配
       2^6 = 64的频次：{4:1, 6:1}
       
步骤3: 频次匹配成功！
       46可以重排成64，返回true
```

## 关键技巧总结

### 1. **数字频次统计**
```cpp
while(temp > 0) {
    digitCount[temp % 10]++;  // 统计每位数字
    temp /= 10;
}
```

### 2. **位运算生成2的幂**
```cpp
long long power = 1LL << i;  // 高效计算2^i
```

### 3. **频次比较**
```cpp
if(numCount == it->second) {  // map可以直接比较
    return true;
}
```

### 4. **静态初始化优化**
```cpp
static bool initialized = false;
if(!initialized) {
    initPowerOf2Counts();
    initialized = true;
}
```

## 扩展思考

### 1. **如果允许前导零怎么办？**
当前算法已经正确处理，因为我们比较的是数字频次，不考虑顺序。

### 2. **能否进一步优化？**
- 可以使用字符串哈希代替map比较
- 可以预计算所有可能的频次签名

### 3. **类似问题**
- 判断两个字符串是否为字母异位词
- 检查数字是否可以重排成回文数

## 学习收获

- 掌握了**频次统计**在字符串/数字重排问题中的应用
- 理解了**预处理 + 查询**的算法设计模式
- 学会了用**哈希表匹配**解决组合问题
- 体验了**位运算**在生成数学序列中的高效性

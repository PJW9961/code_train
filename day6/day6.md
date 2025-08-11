# Day 6: 二的幂数组中查询范围内的乘积

> **题目链接**: [2438.二的幂数组中查询范围内的乘积](https://leetcode.cn/problems/range-product-queries-of-powers/description/)
> **难度**: 中等  
> **标签**: 位运算,数组,前缀和

## 示例

```
输入：n = 15, queries = [[0,1],[2,2],[0,3]]
输出：[2,4,64]
解释：
对于 n = 15，得到 powers = [1,2,4,8]。没法得到元素数目更少的数组。
第 1 个查询的答案：powers[0] * powers[1] = 1 * 2 = 2。
第 2 个查询的答案：powers[2] = 4。
第 3 个查询的答案：powers[0] * powers[1] * powers[2] * powers[3] = 1 * 2 * 4 * 8 = 64。
```

## 约束条件
- `1 <= n <= 10^9`
- `1 <= queries.length <= 10^5`
- `0 <= lefti <= righti < powers.length`

## 算法思路

### 核心思想
1. **二进制分解**: 任何正整数都可以唯一地表示为2的幂的和
2. **位运算优化**: 使用位运算快速提取每个2的幂
3. **区间乘积**: 计算指定范围内powers数组元素的乘积

### 详细步骤

#### 第一步：构造powers数组
利用二进制表示，将 `n` 分解为2的幂的和：
- 使用 `n & 1` 检查最低位是否为1
- 如果是1，则 `2^bit` 是分解的一部分
- 使用 `n >>= 1` 右移一位，继续检查下一位
- 使用 `1 << bit` 计算 `2^bit`

#### 第二步：处理查询
对每个查询 `[left, right]`：
- 计算 `powers[left] * powers[left+1] * ... * powers[right]`
- 对结果取模 `10^9 + 7`

### 位运算详解

#### `n & 1` 的作用
```
示例：n = 15 (二进制: 1111)
15 & 1 = 1111 & 0001 = 0001 = 1  ✓ 包含2^0 = 1
7 & 1  = 0111 & 0001 = 0001 = 1  ✓ 包含2^1 = 2  
3 & 1  = 0011 & 0001 = 0001 = 1  ✓ 包含2^2 = 4
1 & 1  = 0001 & 0001 = 0001 = 1  ✓ 包含2^3 = 8
```

#### 分解过程
```
n = 15 = 8 + 4 + 2 + 1 = 2^3 + 2^2 + 2^1 + 2^0
二进制：1111
位置：  3210
powers = [1, 2, 4, 8]  // 按升序排列
```

## 代码实现

```cpp
#include<iostream>
#include<vector>
#include<windows.h>
using namespace std;

vector<int> productQueries(int n, vector<vector<int>>& queries) 
{
    vector<int> powers, answer;
    const int MOD = 1000000007;
    
    // 位运算快速分解n为2的幂的和
    int bit = 0;
    while(n > 0) {
        if(n & 1) {  // 检查最低位是否为1
            powers.push_back(1 << bit);  // 添加2^bit
        }
        n >>= 1;  // 右移一位
        bit++;
    }
    
    // 处理每个查询
    for(int i = 0; i < queries.size(); i++) {
        int left = queries[i][0];
        int right = queries[i][1];
        
        long long product = 1;  // 使用long long防止溢出
        for(int j = left; j <= right; j++) {
            product = (product * powers[j]) % MOD;
        }
        answer.push_back(product);
    }
    return answer;
}
```


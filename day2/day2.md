# LeetCode Day 2 - 分汤

> **题目链接**: [808. 分汤 - LeetCode](https://leetcode.cn/problems/soup-servings/)  
> **难度**: 中等  
> **标签**: 数学, 动态规划, 概率与统计

## 解题思路

### 算法：DFS

1. **核心思想**：将问题建模为马尔可夫链，每个状态表示两种汤的剩余量
2. **状态定义**：`memo[a][b]` 表示汤A剩余i毫升，汤B剩余j毫升时满足条件的概率
3. **状态转移**：当前状态的概率等于四种操作概率的加权平均

### 马尔可夫链分析

这是一个典型的**吸收马尔可夫链**问题：

- **状态空间**：(剩余汤A, 剩余汤B)
- **转移概率**：每种操作均为0.25
- **吸收状态**：任一汤耗尽时停止
- **目标概率**：P(A先耗尽) + 0.5 × P(同时耗尽)

#### 状态转移方程

```
memo[a][b] = 0.25 × (memo[a-100][b] + memo[a-75][b-25] + memo[a-50][b-50] + memo[a-25][b-75])
```

#### 边界条件

- 如果 `a ≤ 0 && b ≤ 0`：同时耗尽，返回 0.5
- 如果 `a ≤ 0`：A先耗尽，返回 1.0  
- 如果 `b ≤ 0`：B先耗尽，返回 0.0

### 算法优化

#### 1. 记忆化递归
避免重复计算相同状态，将时间复杂度从指数级降到多项式级。

#### 2. 大数值优化
当n足够大时，由于每次操作A汤的平均消耗量（62.5ml）大于B汤（37.5ml），A先耗尽的概率趋近于1。

```cpp
if (n >= 4475) return 1.0;  // 数学分析得出的阈值
```

#### 3. 状态空间缩放
将所有值除以25，减少状态数量：

```cpp
  n = ceil(n/25.0);  // 向上取整
```


## 代码实现

### 方法1：记忆化递归

```cpp
#include<iostream>
#include<vector>
#include<iomanip>
#include<algorithm>
using namespace std;

double dfs(int a, int b, vector<vector<double>>& memo) {
    // 边界条件
    if (a <= 0 && b <= 0) return 0.5;  // 同时耗尽
    if (a <= 0) return 1.0;             // A先耗尽
    if (b <= 0) return 0.0;             // B先耗尽
    
    // 记忆化检查
    if (memo[a][b] != -1) return memo[a][b];
    
    // 状态转移：四种操作的期望值
    double result = 0.25 * (
        dfs(max(0, a-100), b, memo) +           // 操作1: A-100, B-0
        dfs(max(0, a-75), max(0, b-25), memo) + // 操作2: A-75,  B-25
        dfs(max(0, a-50), max(0, b-50), memo) + // 操作3: A-50,  B-50
        dfs(max(0, a-25), max(0, b-75), memo)   // 操作4: A-25,  B-75
    );
    
    return memo[a][b] = result;
}

double soupServings(int n) {
    // 大数值优化：当n很大时概率趋近于1
    if (n >= 4475) return 1.0;
    
    // 初始化记忆化数组
    vector<vector<double>> memo(n+1, vector<double>(n+1, -1));
    
    return dfs(n, n, memo);
}

int main() {
    cout << fixed << setprecision(5);
    int n;
    cout << "请输入汤的初始量: ";
    cin >> n;
    cout << "概率结果: " << soupServings(n) << endl;
    return 0;
}
```

### 方法2：状态压缩优化版本（推荐解法）

```cpp
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
```

## 算法分析

### 复杂度分析

| 方法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 记忆化递归 | O(n²) | O(n²) | 实现简单，只计算需要的状态 |
| 动态规划 | O(n²) | O(n²) | 自底向上，状态转移清晰 |
| 状态压缩版 | O((n/25)²) | O((n/25)²) | 空间优化，适合大数值 |

### 数学原理

这个问题的关键在于观察到：
- A汤的期望消耗：(100+75+50+25)/4 = 62.5ml
- B汤的期望消耗：(0+25+50+75)/4 = 37.5ml
- A汤消耗更快，当n很大时P(A先耗尽)趋近于1

### 优化技巧

1. **阈值优化**：n≥4475时直接返回1.0
2. **状态缩放**：所有值除以25，减少了空间利用以及后续算法的递归消耗时间
3. **记忆化**：避免重复计算，显著提升效率

## 运行示例

### 测试用例

### 输入格式
```
n=50
```

### 输出
```
0.62500
```

## 关键点总结

1. **状态建模**：将随机过程建模为马尔可夫链
2. **记忆化优化**：避免重复计算，提升效率
3. **边界处理**：正确处理各种终止条件
4. **数学洞察**：利用期望值分析进行大数优化

## 学习收获

- **概率动态规划**
- **马尔可夫链**
- **数学分析**


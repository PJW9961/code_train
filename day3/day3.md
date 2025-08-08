# LeetCode Day 3 - 两数相加

> **题目链接**: [2. 两数相加 - LeetCode](https://leetcode.cn/problems/add-two-numbers/)  
> **难度**: 中等  
> **标签**: 链表, 数学, 递归


## 解题思路

### 算法：模拟加法 + 链表操作

1. **核心思想**：模拟小学数学的竖式加法过程
2. **逐位相加**：从最低位开始，逐位计算两数之和
3. **进位处理**：当位数和≥10时，需要向高位进位
4. **链表构建**：为每个结果位创建新的链表节点

### 关键点分析

#### 1. 逆序存储的优势
由于链表按逆序存储（低位在前），这正好符合加法运算从低位开始的特点，无需额外的数据结构。

#### 2. 进位机制
```
当前位 = (数字1当前位 + 数字2当前位 + 进位) % 10
新进位 = (数字1当前位 + 数字2当前位 + 进位) / 10
```

#### 3. 不同长度处理
- 短链表结束后，将对应位视为0
- 继续处理长链表的剩余部分
- 最后处理可能存在的进位

#### 4. 哑节点技巧
使用哑节点(dummy node)简化链表头部的边界处理。

## 代码实现

### 方法：一次遍历 + 哑节点

```cpp
#include<iostream>
using namespace std;

struct ListNode 
{
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
{
  ListNode* l3=new ListNode(0);
  ListNode* current=l3;
  int c=0;
  while(l1||l2) //两个中有一个不空时继续循环
  {
    int n1,n2;
    if(l1)
    {
      n1=l1->val;
      l1=l1->next;
    }
    else
    {
      n1=0;
    }

    if(l2)
    {
      n2=l2->val;
      l2=l2->next;
    }
    else
    {
      n2=0;
    }
    int sum = c+n1+n2;
    c=sum/10;
    sum=sum%10;
    current->next=new ListNode(sum);
    current=current->next;
  }
  if(c>0)
  {
    current->next=new ListNode(c);
    current=current->next;
  }
  ListNode* result=l3->next;
  delete l3;
  return result;
}

```

## 算法分析

### 时间复杂度
- **O(max(m, n))** - 其中m和n分别是两个链表的长度
- 需要遍历较长链表的所有节点

### 空间复杂度
- **O(max(m, n))** - 结果链表的长度最多为max(m, n) + 1
- 除了结果链表外，只使用了常数级别的额外空间

### 边界情况处理

| 情况 | 处理方式 | 示例 |
|------|----------|------|
| 链表长度不同 | 短链表结束后视为0 | [1,2] + [3,4,5] |
| 最高位有进位 | 循环条件包含carry | [9,9] + [1] = [0,0,1] |
| 其中一个为空 | 输入验证确保非空 | - |
| 全为0 | 正常处理 | [0] + [0] = [0] |

## 运行示例

### 测试用例

### 输入格式
```
输入：l1 = [2,4,3], l2 = [5,6,4]
```

### 输出
```
输出：[7,0,8]
```

## 学习收获

- **链表操作**
- **哑节点**
- **进位处理**

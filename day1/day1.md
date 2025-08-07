# LeetCode Day 1 - 盛最多水的容器

> **题目链接**: [11. 盛最多水的容器 - LeetCode](https://leetcode.cn/problems/container-with-most-water/)  
> **难度**: 中等  
> **标签**: 贪心算法, 双指针

## 解题思路

### 算法：双指针

1. **核心思想**：使用双指针从数组两端向中间移动
2. **面积计算**：面积 = 两指针间距离 × min(左指针高度, 右指针高度)
3. **指针移动策略**：总是移动高度较小的一边，因为移动较长的一边不可能得到更大的面积（后续进行证明）

### 为什么移动较短的指针？

#### 数学证明（反证法）

**要证明的命题：** 假设 `height[left] ≤ height[right]`，那么 `(left, right)` 是所有以 `left` 为左边界的组合中的最优解。

**证明过程：**

1. **假设条件**
   - 设 `height[left] < height[right]`
   - 假设存在 `k` 满足 `left < k < right`，使得 `Area(left, k) > Area(left, right)`

2. **建立不等式**
   
   根据假设，需要满足：
   ```
   (k - left) × min(height[k], height[left]) > (right - left) × min(height[right], height[left])
   ```
   
   由于 `height[left] < height[right]`，上式简化为：
   ```
   (k - left) × min(height[k], height[left]) > (right - left) × height[left]
   ```

3. **分情况讨论**

   **已知条件：** `k - left < right - left`（因为 `k < right`）

   **情况1：** `height[k] < height[left]`
   ```
   Area(left, k) = (k - left) × height[k]
                 < (k - left) × height[left]    [因为 height[k] < height[left]]
                 < (right - left) × height[left]  [因为 k - left < right - left]
                 = Area(left, right)
   ```
   
   **情况2：** `height[k] ≥ height[left]`
   ```
   Area(left, k) = (k - left) × height[left]    [因为 min(height[k], height[left]) = height[left]]
                 < (right - left) × height[left]  [因为 k - left < right - left]
                 = Area(left, right)
   ```

4. **得出矛盾**
   
   无论哪种情况，都有 `Area(left, k) < Area(left, right)`，与假设矛盾。

5. **结论**
   
   因此假设不成立，`(left, right)` 确实是所有以 `left` 为左边界的组合中的最优解。
   
   **推论：** 我们可以安全地移动左指针而不会错过最优解。同理可证移动右指针的情况。

---


## 代码实现

### 方法1：暴力算法（时间复杂度 O(n²)）

```cpp
// 暴力解法：枚举所有可能的两条线
int maxArea(vector<int>& height) {
    int max_area = 0;
    int length = height.size();
    
    for(int i = 0; i <= length-1; i++)
    {
        for(int j = i+1; j <= length-1; j++)
        {
            int area = min(height[i], height[j]) * (j-i);
            max_area = max(max_area, area);
        }
    }
    
    return max_area;
}
```

**暴力算法思路：**
- 枚举所有可能的两条线的组合
- 对于每一对 (i, j)，计算面积 = min(height[i], height[j]) × (j-i)
- 保留最大的面积值

### 方法2：双指针算法（时间复杂度 O(n)）

```cpp
// 优化解法：双指针
int maxArea(vector<int>& height) {
    int max_area = 0;
    int length = height.size();
    int left = 0, right = length - 1;
    
    while(left < right)
    {
        // 计算当前面积
        int current_area = (right - left) * min(height[left], height[right]);
        max_area = max(max_area, current_area);
        
        // 移动较短的指针
        if(height[left] < height[right]) 
            left++;
        else 
            right--;
    }
    
    return max_area;
}
```

**双指针算法思路：**
- 使用两个指针从数组两端开始
- 每次移动较短的指针，因为移动较长的指针不可能得到更大面积
- 只需要遍历一次数组，大大提高了效率

## 算法分析

### 暴力算法复杂度
- **时间复杂度：O(n²)** - 需要两层嵌套循环枚举所有可能的组合
- **空间复杂度：O(1)** - 只使用了常数级别的额外空间

### 双指针算法复杂度
- **时间复杂度：O(n)** - 每个元素最多被访问一次
- **空间复杂度：O(1)** - 只使用了常数级别的额外空间

### 算法对比
| 算法 | 时间复杂度 | 空间复杂度 | 优缺点 |
|------|------------|------------|--------|
| 暴力算法 | O(n²) | O(1) | 思路直观，但效率低 |
| 双指针 | O(n) | O(1) | 效率高，是最优解 |

## 运行示例

### 输入格式
```
[1,8,6,2,5,4,8,3,7]
```

### 输出
```
49
```

## 关键点总结

1. **双指针技巧**：从两端向中间移动，避免了 O(n²) 的暴力解法
2. **贪心策略**：始终移动较短的指针，在减少遍历范围的同时，确保了最优解不被掠过。
3. **数学思维**：面积 = 宽度 × 高度，高度由较短边决定

## 学习收获

- **双指针算法**
- **贪心策略**
-


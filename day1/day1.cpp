//11.盛最多水的容器
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <windows.h>
using namespace std;
vector<int> ArrayInput(string input)
{
    vector<int> result={} ;
    if(input[0]=='[')
        input.erase(0,1);
    if(input[input.size()-1]==']')
        input.pop_back();
    stringstream array(input);
    string token;
    while(getline(array,token,','))
    {
        if(!token.empty())
        {
            result.push_back(stoi(token));
        }
    }
    return result;
}

// int maxArea(vector<int>& height) {
//           int max_area = 0;
//     int length=height.size();
//     for(int i=0;i<=length-1;i++)
//     {
//         for(int j=i+1;j<=length-1;j++)
//         {
//             int area=min(height[i],height[j])*(j-i);
//             int new_max_area=max(max_area,area);
//             max_area=new_max_area;
//         }
//     }
//     return max_area;
//     }

int maxArea(vector<int>& height) {
    int max_area = 0;
    int length=height.size();
    int left=0,right=length-1;
    while(left<right)
    {
      max_area=max(max_area,((right-left)*min(height[left],height[right])));
      if(height[left]<height[right]) left++;
      else right--;
    }
    return max_area;
}
int main()
{
    string input;
    cin>>input;
    vector<int> height=ArrayInput(input);
    int max_Area=maxArea(height);
    cout<<max_Area;
    system("pause");
    return 0;
}
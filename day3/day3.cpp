#include<iostream>
using namespace std;

struct ListNode 
{
  int val;
  ListNode *next;
  ListNode() : val(0), next(NULL) {}
  ListNode(int x) : val(x), next(NULL) {}
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

int main()
{
  
}
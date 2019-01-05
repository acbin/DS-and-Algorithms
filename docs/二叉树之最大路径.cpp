/*
给定一颗二叉树的逻辑结构（先序遍历的结果，空树用字符‘0’表示，例如AB0C00D00），建立该二叉树的二叉链式存储结构
二叉树的每个结点都有一个权值，从根结点到每个叶子结点将形成一条路径，每条路径的权值等于路径上所有结点的权值和。编程求出二叉树的最大路径权值。如下图所示，共有4个叶子即有4条路径，
路径1权值=5 + 4 + 11 + 7 = 27          路径2权值=5 + 4 + 11 + 2 = 22
路径3权值=5 + 8 + 13 = 26                路径4权值=5 + 8 + 4 + 1 = 18
可计算出最大路径权值是27。
该树输入的先序遍历结果为ABCD00E000FG00H0I00，各结点权值为：
A-5，B-4，C-11，D-7，E-2，F-8，G-13，H-4，I-1


输入

第一行输入一个整数t，表示有t个测试数据
第二行输入一棵二叉树的先序遍历，每个结点用字母表示
第三行先输入n表示二叉树的结点数量，然后输入每个结点的权值，权值顺序与前面结点输入顺序对应
以此类推输入下一棵二叉树
输出

每行输出每棵二叉树的最大路径权值，如果最大路径权值有重复，只输出1个

样例输入

2
AB0C00D00
4 5 3 2 6
ABCD00E000FG00H0I00
9 5 4 11 7 2 8 13 4 1
样例输出

11
27
*/
#include <iostream>
#define ok 0
#define error -1
using namespace std;

//链表结点类定义
class ListNode
{
  public:
    int data;
    ListNode *next;
    ListNode() { next = NULL; }
};

class LinkList
{
  public:
    ListNode *head;
    int len;
    LinkList();
    ~LinkList();
    ListNode *LL_index(int i);
    int LL_get(int i);
    int LL_insert(int i, int item);
    int LL_del(int i);
    void LL_display();
};

LinkList::LinkList()
{
    head = new ListNode();
    len = 0;
}
LinkList::~LinkList()
{
    ListNode *p, *q;
    p = head;
    while (p != NULL)
    {
        q = p;
        p = p->next;
        delete q;
    }
    len = 0;
    head = NULL;
}

ListNode *LinkList::LL_index(int i)
{
    ListNode *p;
    p = head;
    if (i < 0 || i > len + 1)
    {
        return NULL;
    }
    while (i--)
    {
        p = p->next;
    }
    return p;
}

int LinkList::LL_insert(int i, int item)
{
    if (i < 1 || i > len + 1)
    {
        return error;
    }
    ListNode *p;
    p = LL_index(i - 1);
    ListNode *pNew;
    pNew = new ListNode();
    pNew->data = item;
    pNew->next = p->next;
    p->next = pNew;
    len++;
    return ok;
}

int LinkList::LL_del(int i)
{
    if (i < 1 || i > len + 1)
    {
        return error;
    }
    ListNode *p, *tmp;
    p = LL_index(i - 1);
    tmp = p->next;
    p->next = tmp->next;
    delete tmp;
    --len;
    return ok;
}

int LinkList::LL_get(int i)
{
    if (i < 1 || i > len + 1)
    {
        return error;
    }
    ListNode *p;
    p = LL_index(i);
    return p->data;
}

void LinkList::LL_display()
{
    ListNode *p;
    p = head->next;
    while (p)
    {
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}

int main()
{

    int n, i, j = 2, data, ret;
    LinkList list;
    cin >> n;
    for (i = 0; i < n; ++i)
    {
        cin >> data;
        list.LL_insert(i + 1, data);
    }
    list.LL_display();

    //插入两次
    while (j--)
    {
        cin >> i >> data;
        ret = list.LL_insert(i, data);
        if (ret == error)
        {
            cout << "error" << endl;
        }
        else
        {
            list.LL_display();
        }
    }

    //删除两次
    j = 2;
    while (j--)
    {
        cin >> i;
        ret = list.LL_del(i);
        if (ret == error)
        {
            cout << "error" << endl;
        }
        else
        {
            list.LL_display();
        }
    }

    //查找两次
    j = 2;
    while (j--)
    {
        cin >> i;
        ret = list.LL_get(i);
        if (ret == error)
        {
            cout << "error" << endl;
        }
        else
        {
            cout << ret << endl;
        }
    }
    return 0;
}
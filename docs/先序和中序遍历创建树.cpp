/*
二叉树结点用A、B、C、a、b、+、-等单字符表示，且结点各不相同。根据二叉树的先序和中序遍历创建二叉树，并输出二叉树的后序遍历和树高度。

提示:递归。

输入

测试次数t

每组测试数据含2行数据(假设遍历正确，没有空树):

树的先序遍历

树的中序遍历

输出

对每组测试数据，输出树的后序遍历顺序和树的高度。

样例输入

3
ABC
BAC
ABCDEF
BCAEDF
ABCDF
ADFCB

样例输出

B C A 2
C B E F D A 3
F D C B A 5

*/

#include <iostream>
#include <string>
#include <math.h>
using namespace std;
struct Node
{
    char val;
    Node *rc, *lc;
};
Node *rebuild(string pre, string mid)
{
    int i, len;
    Node *head = new Node();
    head->val = pre[0];
    //cout << pre<< "  " << mid << endl ;
    len = mid.length();
    for (i = 0; i < len; i++)
    {
        if (pre[0] == mid[i])
        {
            if (i != 0)
            {
                head->lc = rebuild(pre.substr(1, i), mid.substr(0, i)); //左子树
            }
            else
            {
                head->lc = NULL;
            }
            if (i != len - 1)
            {
                head->rc = rebuild(pre.substr(i + 1, len - 1 - i), mid.substr(i + 1, len - 1 - i)); //右子树
            }
            else
            {
                head->rc = NULL;
            }
        }
    }
    return head;
}
void after(Node *head)
{
    if (head == NULL)
    {
        return;
    }
    else
    {
        if (head->lc != NULL)
            after(head->lc);
        if (head->rc != NULL)
            after(head->rc);
        cout << head->val << " ";
    }
}
int high(Node *T)
{
    if (T == NULL)
        return 0;
    else
        return max(high(T->lc), high(T->rc)) + 1;
}
int main()
{
    int n;
    cin >> n;
    string pre, mid;
    Node *head = NULL;
    for (int i = 0; i < n; ++i)
    {
        Node *head;
        cin >> pre >> mid;
        head = rebuild(pre, mid);
        after(head);
        cout << high(head);
        cout << endl;
    }
    return 0;
}
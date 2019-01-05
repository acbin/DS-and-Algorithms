/*
题目描述

 给出一个数据序列，建立哈希表，采用求余法作为哈希函数，模数为11，哈希冲突用链地址法和表头插入

如果首次查找失败，就把数据插入到相应的位置中

实现哈希查找功能

输入

第一行输入n，表示有n个数据
第二行输入n个数据，都是自然数且互不相同，数据之间用空格隔开
第三行输入t，表示要查找t个数据
从第四行起，每行输入一个要查找的数据，都是正整数

输出

每行输出对应数据的查找结果

样例输入

6
11 23 39 48 75 62
6
39
52
52
63
63
52
样例输出

6 1
error
8 1
error
8 1
8 2
提示

注意，当两次输入要相同的查找数据，如果第一次查找不成功就会执行插入，那么第二次查找必然成功，且查找次数为1次（因为做表头插入）


例如示例数据中输入两次52，第一次查找失败就把52插入到位置8，第二次查找就成功了，所以第一次输出error，第二次就输出8 1


为什么第三次输入52会输出8 2

*/
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <math.h>
using namespace std;
class TNode //节点类
{
  public:
    char oper;
    TNode *left;
    TNode *right;
    int s, t;
    TNode()
    {
        left = right = NULL;
        oper = 0;
    }
    TNode(char op)
    {
        left = right = NULL;
        oper = op;
    }
};
bool isOper(char op) //判断是否为运算符
{
    char oper[] = {'(', ')', '+', '-', '*', '/', '^'};
    for (int i = 0; i < sizeof(oper); i++)
    {
        if (op == oper[i])
        {
            return true;
        }
    }
    return false;
}

int getOperOrder(char op) //返回运算符op所对应的优先级
{
    switch (op)
    {
    case '(':
        return 1;
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 3;
    case '^':
        return 4;
    default:
        //定义在栈中的右括号和栈底字符的优先级最低
        return 0;
    }
}

void freeTree(TNode *&p) //释放树
{
    if (p->left != NULL)
        freeTree(p->left);
    if (p->right != NULL)
    {
        freeTree(p->right);
    }
    delete (p);
}
void preOrder(TNode *p)
{
    if (p)
    {
        cout << p->oper;
        preOrder(p->left);
        preOrder(p->right);
    }
}

void ExpTree1(TNode *&p, string str) //后缀表达式生成二叉树
{
    stack<TNode *> nodeStack;
    char temp;
    int i = 0;
    temp = str[i++];
    while (temp != '\0')
    {
        if (temp != '\0' && !isOper(temp)) //不是运算符，则进栈
        {
            p = new TNode(temp); //以temp为结点值构造二叉树结点
            nodeStack.push(p);
            temp = str[i++];
        }
        else
        {
            p = new TNode(temp);
            if (nodeStack.size())
            {
                p->right = nodeStack.top(); //若非空则弹栈并设为结点的右孩子
                nodeStack.pop();
            }
            if (nodeStack.size())
            {
                p->left = nodeStack.top(); //若非空则弹栈并设为结点的左孩子
                nodeStack.pop();
            }
            nodeStack.push(p);
            temp = str[i++];
        }
    }
}

void count(TNode *p, int &height, int n) //求值函数
{
    if (p->left == NULL && p->right == NULL)
    {
        if (n > height)
            height = n;
    }
    if (p->left != NULL)
    {
        count(p->left, height, n + 1);
    }
    if (p->right != NULL)
    {
        count(p->right, height, n + 1);
    }
}
int main()
{
    string expression;
    TNode *tree;
    while (cin >> expression)
    {
        ExpTree1(tree, expression);
        preOrder(tree);
        freeTree(tree);
        cout << endl;
    }
    return 0;
}
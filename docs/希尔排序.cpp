/*
给出一个数据序列，使用希尔排序算法进行从小到大的排序
间隔gap使用序列长度循环除2直到1
Input
第一行输入t，表示有t个测试示例(完成)
第二行输入n，表示第一个示例有n个数据(完成)
第三行输入n个数据，都是正整数，数据之间用空格隔开(完成)
以此类推
Output
每行输出每个示例排序后，从小到大的结果(完成)

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
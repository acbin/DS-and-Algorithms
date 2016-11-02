
/*
任意二叉树可以根据完全二叉树性质保存在一个数组中。已知二叉树的数组存储，用程序构建该二叉树。

提示：用递归方法或非递归都可以

递归方法的代码框架如下：

 



输入

第一行输入一个整数t，表示有t个测试数据

第二行起输入二叉树的数组存储结果，空树用字符‘0’表示，输入t行

数组的数据由大写字母和0表示

输出

逐行输出每个二叉树的先序结果

样例输入

3
ABC0D
ABCDEF000G
ABEC0F0D0
样例输出

ABDC
ABDEGCF
ABCDEF
*/
#include<queue>  
#include <iostream>
using namespace std;   

     

class BiTreeNode{   

public:   

    char data;   

    BiTreeNode *LeftChild;   

    BiTreeNode *RightChild;   

    BiTreeNode():LeftChild(NULL),RightChild(NULL){}   

    ~BiTreeNode(){}   

};   

     

class BiTree{   

private:   

    BiTreeNode *Root;   

    int pos;   

    int len;  

    string strTree;   

    BiTreeNode* CreateBiTree();   

    void PreOrder(BiTreeNode* t);   

    void InOrder(BiTreeNode* t);   

    void PostOrder(BiTreeNode* t);   

public:   

    BiTree(){};   

    ~BiTree(){};   

    void CreateTree(string TreeArray);   

    BiTreeNode* CreateBiTree(int pos);  

    void PreOrder();   

    void InOrder();   

    void PostOrder();   

    void LevelOrder();  

    void LevelOrder(BiTreeNode *t);  

};   

     

void BiTree::CreateTree(string TreeArray)   

{   

    len=TreeArray.length();  

    strTree.assign(TreeArray);  

    Root=CreateBiTree(0);  

}   

     

BiTreeNode* BiTree::CreateBiTree(int pos)   

{       BiTreeNode* T;   

    int ch;  

    if(pos>strTree.length())return NULL;  

    ch=strTree[pos];  

    if(ch=='0')T=NULL;  

    else 

    {  

        T=new BiTreeNode();  

        T->data=ch;  

        if(2*(pos+1)<=len)T->LeftChild=CreateBiTree(2*(pos+1)-1);  

        if(2*(pos+1)+1<=len)T->RightChild=CreateBiTree(2*(pos+1));  

    }  

    return T;  

}   

     

void BiTree::PreOrder()   

{   

    PreOrder(Root);   

}   

     

void BiTree::PreOrder(BiTreeNode* t)   

{   

    if(t)   

    {   

        cout<<t->data;   

        PreOrder(t->LeftChild);   

        PreOrder(t->RightChild);   

    }   

}   

     

void BiTree::InOrder()   

{   

    InOrder(Root);   

}   

     

void BiTree::InOrder(BiTreeNode* t)   

{   

    if(t)   

    {   

        InOrder(t->LeftChild);   

        cout<<t->data;   

        InOrder(t->RightChild);   

    }   

}        

void BiTree::PostOrder()   

{   

    PostOrder(Root);   

}   

     

void BiTree::PostOrder(BiTreeNode*t)   

{   

    if(t)   

    {   

        PostOrder(t->LeftChild);   

        PostOrder(t->RightChild);   

        cout<<t->data;   

    }   

}   

void BiTree::LevelOrder()  

{  

    LevelOrder(Root);  

}//LevelOrder()  

   

void BiTree::LevelOrder(BiTreeNode *t)  

{  

    queue<BiTreeNode*> tq;  

    BiTreeNode*p=t;  

    if(p)  

    {  

        tq.push(p);  

        while(!tq.empty())  

        {  

            p=tq.front();  

            tq.pop();  

            if(p)  

            {  

                cout<<p->data;  

                tq.push(p->LeftChild);  

                tq.push(p->RightChild);  

            }  

        }  

    }  

}//LevelOrder(BiTreeNode *t)  

int main()   

{   

    int t;   

    string str;       BiTree BT;   

    BiTreeNode BTN;   

    cin>>t;   

    while(t--)   

    {   

        cin>>str;   

        BT.CreateTree(str);   

        BT.PreOrder();  

        cout<<endl;  

    }   

    return 0;   

} 

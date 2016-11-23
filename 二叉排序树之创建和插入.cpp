/*
题目描述

给出一个数据序列，建立二叉排序树，并实现插入功能

对二叉排序树进行中序遍历，可以得到有序的数据序列

输入

第一行输入t，表示有t个数据序列

第二行输入n，表示首个序列包含n个数据

第三行输入n个数据，都是自然数且互不相同，数据之间用空格隔开

第四行输入m，表示要插入m个数据

从第五行起，输入m行，每行一个要插入的数据，都是自然数且和前面的数据不等

以此类推输入下一个示例

输出

第一行输出有序的数据序列，对二叉排序树进行中序遍历可以得到

从第二行起，输出插入第m个数据后的有序序列，输出m行

以此类推输出下一个示例的结果

 

样例输入

1
6
22 33 55 66 11 44
3
77
50
10
样例输出

11 22 33 44 55 66 
11 22 33 44 55 66 77 
11 22 33 44 50 55 66 77 
10 11 22 33 44 50 55 66 77 
*/
#include <iostream> 
using namespace std; 
  
#define OK 1 
#define ERROR 0 
  
class TreeNode{ 
public: 
    int data; 
    TreeNode *LeftChild; 
    TreeNode *RightChild; 
    TreeNode(){LeftChild=NULL;RightChild=NULL;data=0;} 
}; 
  
class Tree{ 
public: 
    TreeNode* Root; 
    void CreateBinary(int *a,int size) 
    { 
        if(size==0)return; 
        Root=NULL; 
        TreeNode *t; 
        int length=0; 
        t=new TreeNode(); 
        t->data=a[length]; 
        Root=t; 
        for(;++length<size;){ 
            t=new TreeNode(); 
            t->data=a[length]; 
            InsertElem(Root,t); 
        }//for 
    }//CreateBinary 
      
    void InsertElem(TreeNode *F,TreeNode *t){ 
        if(F->data < t->data){ 
            if(F->RightChild){ 
                InsertElem(F->RightChild,t); 
            }//if 
            else F->RightChild=t; 
        }//if 
        else{ 
            if(F->LeftChild) 
                InsertElem(F->LeftChild,t); 
            else F->LeftChild=t; 
        }//else 
    }//InsertElem 
  
    void InOrder(){ 
        InOrder(Root); 
    } 
  
    void InOrder(TreeNode *t){ 
        if(t){ 
            InOrder(t->LeftChild); 
            cout<<t->data<<" "; 
            InOrder(t->RightChild); 
        }//if 
    }//InSearch 
}; 
  
int main(){ 
    int t,n,i,num,N; 
    Tree T; 
    cin>>t; 
    while(t--){ 
        cin>>n; 
        int *a=new int[n]; 
        for(i=-1;++i<n;){ 
            cin>>a[i]; 
        }//for 
        T.CreateBinary(a,n); 
        T.InOrder(); 
        cout<<endl; 
        cin>>num; 
        while(num--){ 
            cin>>N; 
            TreeNode *tr=new TreeNode(); 
            tr->data=N; 
            T.InsertElem(T.Root,tr); 
            T.InOrder(); 
            cout<<endl; 
        }//while 
    }//while 
    return 0; 
}

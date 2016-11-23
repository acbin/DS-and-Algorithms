/*
给出一个数据序列，建立二叉排序树，并实现查找功能(完成)
对二叉排序树进行中序遍历，可以得到有序的数据序列(完成)
Input
第一行输入t，表示有t个数据序列(完成)
第二行输入n，表示首个序列包含n个数据(完成)
第三行输入n个数据，都是自然数且互不相同，数据之间用空格隔开(完成)
第四行输入m，表示要查找m个数据(完成)
从第五行起，输入m行，每行一个要查找的数据，都是自然数(完成)
以此类推输入下一个示例(完成)
Output
第一行输出有序的数据序列，对二叉排序树进行中序遍历可以得到(完成)
从第二行起，输出查找结果，如果查找成功输出查找次数，如果查找失败输出-1(完成)
以此类推输出下一个示例的结果(完成)
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
    bool Find; 
    int times; 
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
  
    void Searchfordata(TreeNode *t,int data){ 
        if(Find && t){ 
            times++; 
            if(t->data==data){ 
                Find=false; 
            } 
            else if(t->data > data){ 
                Searchfordata(t->LeftChild,data); 
            } 
            else{ 
                Searchfordata(t->RightChild,data); 
            } 
        } 
    } 
  
    int Searchfordata(int data){ 
        Find=true; 
        times=0; 
        Searchfordata(Root,data); 
        if(Find)return -1; 
        else return times; 
    } 
  
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
            cout<<T.Searchfordata(N)<<endl; 
        }//while 
    }//while 
    return 0; 
}

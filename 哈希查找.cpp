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
#include<iostream> 
using namespace std; 
  
#define SUCCESS 1 
#define UNSUCCESS 0 
#define DUPLICATE -1 
#define OK 1 
#define Status int 
  
class Link{ 
public: 
    Link*next; 
    int data; 
    Link(){next=NULL;} 
}; 
  
class HashTable{ 
public: 
    Link *elem;//数据元素存储基址，动态分配数组 
    int count;//当前数据元素个数 
    int sizeindex;//hashsize[sizeindex]为当前容量 
    Status NewElem(int size){ 
        elem=new Link[size]; 
        count=0; 
        sizeindex=size; 
        for(int i=-1;++i<sizeindex;){ 
            elem[i].data=NULL; 
        } 
        return SUCCESS; 
    }//NewElem 
    int Hash(int data){ 
        return data%11; 
    }//Hash 
    Status InsertHash(int data){ 
        int c=0; 
        int p; 
        if(SearchHash(data,p,c))return DUPLICATE; 
        else if(p<sizeindex-1){ 
            if(elem[p].next==NULL){ 
                Link *temp=new Link(); 
                temp->data=data; 
                count++; 
                elem[p].next=temp; 
                return OK; 
            } 
            else{ 
                Link *temp=new Link(); 
                temp->data=data; 
                Link *q=elem[p].next; 
                temp->next=q; 
                elem[p].next=temp; 
                return OK; 
            } 
        } 
    }//InsertHash 
  
    Status SearchHash(int data,int &p,int &c){ 
            p=Hash(data); 
            Link *q=elem[p].next; 
            while(q!=NULL && data!=q->data){ 
                if(q->next!=NULL){ 
                    q=q->next; 
                    c++; 
                } 
                else break; 
            }    
            if(q!=NULL && data==q->data){ 
                return SUCCESS; 
            } 
            else{ 
                return UNSUCCESS; 
            } 
    }//SearchHash 
}; 
  
int main(){ 
    HashTable HT; 
    int n,Data,t,p,c; 
    cin>>n; 
    HT.NewElem(11); 
    for(int i=-1;++i<n;){ 
        cin>>Data; 
        HT.InsertHash(Data); 
    }//for 
    cin>>t; 
    while(t--){ 
        cin>>Data; 
        c=1; 
        if(HT.SearchHash(Data,p,c)){ 
            cout<<p<<" "<<c<<endl; 
        } 
        else{ 
            cout<<"error"<<endl; 
            HT.InsertHash(Data); 
        } 
    } 
    return 0; 
}

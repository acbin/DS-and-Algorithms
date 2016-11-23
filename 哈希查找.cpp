/*
给出一个数据序列，建立哈希表，采用求余法作为哈希函数，模数为11，哈希冲突用链地址法和表头插入
如果首次查找失败，就把数据插入到相应的位置中
实现哈希查找功能
Input
第一行输入n，表示有n个数据(完成)
第二行输入n个数据，都是自然数且互不相同，数据之间用空格隔开(完成)
第三行输入t，表示要查找t个数据(完成)
从第四行起，每行输入一个要查找的数据，都是正整数(完成)
Output
每行输出对应数据的查找结果(完成)

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

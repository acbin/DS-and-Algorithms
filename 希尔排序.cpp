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
using namespace std;  
    
class ShellSort{  
public:  
    void display(int *a,int length){ 
        int i; 
        for(i=-1;++i<length-1;){ 
            cout<<a[i]<<" "; 
        }cout<<a[i]<<endl; 
    } 
    void swap(int *a,int *b){  
        (*a)^=(*b)^=(*a)^=(*b);  
    }  
    void Shell_Sort(int *a,int length){  
        int gap=length/2,temp,i,j,start;  
        while(gap>1){  
//          cout<<gap<<endl; 
            for(start=-1;++start<gap;){ 
              for(i=gap+start;i<length;i+=gap){  
                  temp=i;  
                  for(j=i-gap;j>=0;j-=gap){  
                     if(a[j]<=a[temp])break;  
                     swap(&a[j],&a[temp]);  
                     temp=j;  
                  }//for  
               }//for 
//            display(a,length); 
            }//for 
            gap/=2;  
        }//while  
//      cout<<"最后进行一次直接插入排序"<<endl; 
        //最后进行一次直接插入排序  
        for(i=0;++i<length;){  
            temp=i;  
            for(j=i-1;j>=0;--j){  
                if(a[j]<=a[temp])break;  
                swap(&a[j],&a[temp]);  
                temp=j;  
            } 
//          display(a,length); 
        }  
    }  
};  
    
int main(){  
    int t,n;  
    int i;  
    ShellSort SS;  
    cin>>t;  
    while(t--){  
        cin>>n;  
        int *data=new int[n];  
        for(i=-1;++i<n;){  
            cin>>data[i];  
        }//for  
        SS.Shell_Sort(data,n);  
        for(i=-1;++i<n;){  
            cout<<data[i]<<" ";  
        }//for  
        cout<<endl;  
    }//while  
    return 0;  
}//int

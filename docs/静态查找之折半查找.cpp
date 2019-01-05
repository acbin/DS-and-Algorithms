/*
题目描述

给出一个队列和要查找的数值，找出数值在队列中的位置，队列位置从1开始

要求使用折半查找算法

输入

第一行输入n，表示队列有n个数据
第二行输入n个数据，都是正整数，用空格隔开
第三行输入t，表示有t个要查找的数值
第四行起，输入t个数值，输入t行

输出

每行输出一个要查找的数值在队列的位置，如果查找不成功，输出字符串error

样例输入

8
11 22 33 44 55 66 77 88
3
22
88
99
样例输出

2
8
error
*/
#include <iostream>
using namespace std;

int Search(int *ArraySize, int S, int n)
{
    int low = 1;
    int high = n;
    int mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (ArraySize[mid] == S)
            return mid;
        else if (ArraySize[mid] > S)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return 0;
}

int main()
{
    int n, i, t, S, num;
    cin >> n;
    int *ArraySize = new int[n + 1];
    for (i = 0; ++i < n + 1;)
    {
        cin >> ArraySize[i];
    } //for
    cin >> t;
    while (t--)
    {
        cin >> S;
        num = Search(ArraySize, S, n);
        if (num)
        {
            cout << num << endl;
        } //if
        else
        {
            cout << "error" << endl;
        } //else
    }     //while
    return 0;
} //main
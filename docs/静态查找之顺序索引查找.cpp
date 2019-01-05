/*
题目描述

给出一个队列和要查找的数值，找出数值在队列中的位置，队列位置从1开始

要求使用顺序索引查找算法，其中索引表查找和块内查找都采用不带哨兵、从头开始的顺序查找方法。

输入

第一行输入n，表示主表有n个数据
第二行输入n个数据，都是正整数，用空格隔开
第三行输入k，表示主表划分为k个块，k也是索引表的长度
第四行输入k个数据，表示索引表中每个块的最大值
第五行输入t，表示有t个要查找的数值
第六行起，输入t个数值，输入t行

输出

每行输出一个要查找的数值在队列的位置和查找次数，数据之间用短划线隔开，如果查找不成功，输出字符串error

样例输入

18
22 12 13 8 9 20 33 42 44 38 24 48 60 58 74 57 86 53
3
22 48 86
6
13
5
48
40
53
90
样例输出

3-4
error
12-8
error
18-9
error
*/
#include <iostream>
using namespace std;

int Search(int *ArraySize, int *max, int S, int n, int k, int &l)
{
    int num;
    int SS;
    for (num = -1; num < k && !(S <= max[++num]); l++)
        ;
    if (num == k)
        return 0;
    SS = (n / k) * (num);
    for (int i = SS - 1; ++i < SS + 6;)
    {
        l++;
        if (ArraySize[i] == S)
        {
            return i + 1;
        }
    } //for
    return 0;
}

int main()
{
    int n, i, t, S, num, k, l;
    cin >> n;
    int *ArraySize = new int[n];
    for (i = -1; ++i < n;)
    {
        cin >> ArraySize[i];
    } //for
    cin >> k;
    int *max = new int[k];
    for (i = -1; ++i < k;)
    {
        cin >> max[i];
    } //for
    cin >> t;
    while (t--)
    {
        cin >> S;
        l = 1;
        num = Search(ArraySize, max, S, n, k, l);
        if (num)
        {
            cout << num << "-" << l << endl;
        } //if
        else
        {
            cout << "error" << endl;
        } //else
    }     //while
    return 0;
} //main
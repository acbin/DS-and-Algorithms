/*
给出一个数据序列，使用快速排序算法进行从小到大的排序
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

class QuickSort
{
  public:
    int Partition(int *a, int low, int high)
    {
        int temp = a[low];
        int pivotkey = a[low];
        while (low < high)
        {
            while (low < high && a[high] >= pivotkey)
                --high;
            if (low != high)
                a[low] = a[high];
            while (low < high && a[low] <= pivotkey)
                ++low;
            if (low != high)
                a[high] = a[low];
        } //while
        a[low] = temp;
        return low;
    }
    void QSort(int *a, int low, int high)
    {
        int pivotloc;
        if (low < high)
        {
            pivotloc = Partition(a, low, high);
            QSort(a, low, pivotloc - 1);
            QSort(a, pivotloc + 1, high);
        }
    }
};

int main()
{
    int t, n;
    int i;
    QuickSort QS;
    cin >> t;
    while (t--)
    {
        cin >> n;
        int *data = new int[n];
        for (i = -1; ++i < n;)
        {
            cin >> data[i];
        } //for
        QS.QSort(data, 0, n - 1);
        for (i = -1; ++i < n;)
        {
            cout << data[i] << " ";
        } //for
        cout << endl;
    } //while
    return 0;
} //int
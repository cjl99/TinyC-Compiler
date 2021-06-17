extern int printf(char* format);
void display(int array[], int maxlen)
{
    int i;

    for(i = 0; i < maxlen; i++)
    {
        printf("%-3d", array[i]);
    }
    printf("\n");

    return ;
}

void QuickSort(int *arr, int low, int high)
{
    if (low < high)
    {
        int i = low;
        int j = high;
        int k = arr[low];
        while (i < j)
        {
            while(i < j && arr[j] >= k)     // 从右向左找第一个小于k的数
            {
                j--;
            }

            if(i < j)
            {
                arr[i++] = arr[j];
            }

            while(i < j && arr[i] < k)      // 从左向右找第一个大于等于k的数
            {
                i++;
            }

            if(i < j)
            {
                arr[j--] = arr[i];
            }
        }

        arr[i] = k;

        // 递归调用
        QuickSort(arr, low, i - 1);     // 排序k左边
        QuickSort(arr, i + 1, high);    // 排序k右边
    }
}

// 主函数
int main()
{
    int array[5];
    int maxlen = 5;

    array[0] = 1;
    array[1] = 10;
    array[2] = 3;
    array[3] = 5;
    array[4] = 7;

    printf("排序前的数组\n");
    display(array, maxlen);

    QuickSort(array, 0, maxlen-1);  // 快速排序

    printf("排序后的数组\n");
    display(array, maxlen);

    return 0;
}
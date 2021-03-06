extern int printf(char* format);
int display(int *array, int maxlen)
{

    int i;

    for(i = 0; i < maxlen; i++)
    {
        printf("%-3d ", array[i]);
    }
    printf("\n");

    return 0;
}

int swap(int* a, int* b)
{
    int t = *a;
    if(a==b) return 0;
    *a = *b;
    *b = t;

    return 0;
}

int QuickSort(int *arr, int low, int high)
{
    if (low <= high)
    {
        int pivot = arr[high];
        int pi;
        int i = low-1;
        int j = low;

        for (j = low; j <= high - 1; j++)
        {
            // If current element is smaller than the pivot
            if (arr[j] < pivot)
            {
                i++; // increment index of smaller element
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[i + 1], &arr[high]);
        pi = i+1;
        // 递归调用
        QuickSort(arr, low, pi - 1);     // 排序k左边
        QuickSort(arr, pi + 1, high);    // 排序k右边
    }
    return 1;
}

// 主函数
int main()
{
    int array[15] = {15,2,3,4,5,
                    6,7,8,9,10,
                    11,12,13,14,1};
    int maxlen = 15;

    printf("排序前的数组\n");
    display(array, maxlen);

    QuickSort(array, 0, maxlen-1);  // 快速排序
    printf("排序后的数组\n");
    display(array, maxlen);

    return 0;
}
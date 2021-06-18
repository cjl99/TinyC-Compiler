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
    *a = *b;
    *b = t;

    return 0;
}

int QuickSort(int *arr, int low, int high)
{
    if (low < high)
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
    int array[10];
    int maxlen = 10;

    array[0] = 1;
    array[1] = 10;
    array[2] = 3;
    array[3] = 5;
    array[4] = 7;
    array[5] = 9;
    array[6] = 15;
    array[7] = 4;
    array[8] = 13;
    array[9] = 2;

    printf("排序前的数组\n");
    display(array, maxlen);

    QuickSort(array, 0, maxlen-1);  // 快速排序
//
    printf("排序后的数组\n");
    display(array, maxlen);

    return 0;
}
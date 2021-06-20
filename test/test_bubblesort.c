extern int printf(char *format);
int bubble_sort(int *arr, int len) {
    int i, j, temp;
    for (i = 0; i < len - 1; i++) {
        for (j = 0; j < len - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return 0;
}
int main() {
    int arr[14] = { 22, 34, 3, 32,
                    82, 55, 89, 50, 37,
                    5, 64, 35, 9, 70 };
    int len = 14;
    int i;

    bubble_sort(arr, len);
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);
    return 0;
}
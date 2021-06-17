extern int printf(char* format);
int display(int *array, int maxlen)
{
    int i;
    printf("maxlen=%d ",maxlen);
    for(i = 0; i < maxlen; i++)
    {
        printf("%-3d", array[i]);
    }
    printf("\n");

    return 1;
}

int main(){
    int a[10];
    int i;
    int maxlen = 5;
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    a[3] = 7;
    a[4] = 2;

    display(a,5);

    return 0;
}

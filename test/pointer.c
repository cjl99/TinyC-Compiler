extern int printf(char* format);

int main(){
    int a = 222;
    int *pa = &a;
    int array[10];
    char *str = "abc";
    int array2[10];
    int *parr = array2;

    // test pointer
    printf("test pointer>>\n");
    printf("%d %d\n",a, *pa);

    // test array
    printf("test array>>\n");
    array[0] = 111;
    array[1] = 222;
    printf("%d %d\n",array[0], array[1]);

    // test pointer to array
    printf("test pointer to array>>\n");
    printf("%d %c\n",str, str[1]);

    printf("test pointer to array>>\n");
    array2[1] = 3;
    parr[1] = 2;
    printf("%d %d", array2[1], parr[1]);

    return 0;
}
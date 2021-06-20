extern int printf(char* format);
int main(){
    // test pointer
    int a = -1;
    int *pa = &a;
    int **ppa = &pa;
    int array[10];
    int *parr = array;
    printf("%d %d %d    ",a, *pa, **ppa);
    // test array
    array[0] = 111;
    array[1] = 222;
    printf("%d %d   ",array[0], array[1]);
    // test pointer to array
    parr[2] = 333;
    printf("%d %d   ", parr[0], array[2]);
    // test dereference array
    parr = &array[5];
    printf("%d %d   ", *array, *parr);
    array[5] = 555;
    printf("%d %d   ", *array, *parr);
    return 0;
}
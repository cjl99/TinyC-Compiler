extern int printf(char* format);
//int display(int *array){
//    printf("%d", array[0]);
//    return 1;
//}

int main(){
    int a[10];
    int *pa;

    a[0] = 11;

    pa = &a[0];

    *pa = 2;

//    printf("%d ", pa[1]);
    printf("%d ", a[0]);
    printf("%d ", pa[0]);

    return 0;
}

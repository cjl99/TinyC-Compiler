extern int printf(char* format);
//int display(int *array){
//    printf("%d", array[0]);
//    return 1;
//}

int main(){
//    int a[10];
//
//    int *pa;
//
//    pa = a;
//
//    *pa = 1;

        int *a;
        int **a2;
        int b;
        b = 11;
        a = &b;
        a2 = &a;



//    printf("%d ", pa[1]);
    printf("%d ", *a);
    *a = 2;
    printf("%d", **a2);
//    printf("%d ", *pa);

    return 0;
}

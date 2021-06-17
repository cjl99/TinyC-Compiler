extern int printf(char* format);
//int display(int *array){
//    printf("%d", array[0]);
//    return 1;
//}

int main(){
    int a[10];
    int *b = a;
    a[0] = 3;
    b[0] = 2;
    printf("%p %p", a, b);

    return 0;
}

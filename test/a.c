extern int printf(char* format);
//int display(int *array){
//    printf("%d", array[0]);
//    return 1;
//}

int main(){
    int a[10];
    int *b = a;
//    a[0] = 1;

//    if(k==a[0]) {
//        printf("%d", a[0]);
//    }
//a = 2;
    a[0] = 3;
    printf("%d", b[0]);

    return 0;
}

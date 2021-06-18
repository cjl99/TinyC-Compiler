extern int printf(char* format);
//int display(int *array){
//    printf("%d", array[0]);
//    return 1;
//}
//int addf(int a, int b) {
//    a = a+b;
//    return a;
//}

int main(){
    int a[10];
    int *b;

    a[0] = 111;
    a[1] = 222;
//
    b = a;
    b[1] = 333;
    a[1] = 444;
//
    printf("%d %d", b[0], a[1]) ;

    return 0;
}

extern int printf(char* format);
int addf(int a, int b) {
    return a+b;
}

int main(){
    printf("%d", addf(1,2));
    return 0;
}

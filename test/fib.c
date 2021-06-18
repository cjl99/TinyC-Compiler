extern int printf(char* format);
int fib(int n) {
    int res;

    if(n<2) {
        res = n;
    }
    else{
        res = fib(n-1)+fib(n-2);
    }
    // printf("fib: %d   ", res);
    return res;
}

// 主函数
int main()
{
    int a0 = 0;
    a0 = fib(6);
    printf("%d", a0);

    return 0;
}
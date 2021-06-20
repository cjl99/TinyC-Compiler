extern int printf(char* format);
int fib(int n) {
    if(n<2)
        return n;
    return fib(n-1)+fib(n-2);
}

// 主函数
int main()
{
    //fib-index   0 1 2 3 4 5 6
    //fib-result  0 1 1 2 3 5 8
    printf("%d ", fib(4)); // suppose 3
    printf("%d ", fib(5)); // suppose 5
    printf("%d ", fib(6)); // suppose 8

    return 0;
}
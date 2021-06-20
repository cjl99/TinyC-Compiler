extern int printf(char *format);

int add(int a, int b) {
    return a+b;
}

int sub(int a, int b) {
    return a-b;
}

int main() {
    int a = 1;
    int b = 4;

    printf("add result: %d   ", add(b, a));
    printf("sub result: %d ", sub(b, a))
}


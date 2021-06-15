int f(int a, int b) {
    return 3;
}
int fadd(int a1, int a2) {
    return a1+a2;
}

int main(){
    int a = 1;
    int b = 2;
    int c = 4;

    c = fadd(a, b);
    c = f(a,b);

    return c;
}

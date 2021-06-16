extern int printf(char* format);

int main(){

    int s = 0;
    int i;
    int j;

    if(i==0) {
        printf("%d", ++s);
    }
    else {
        s = s+10;
        printf("%d", s);
    }

    for(i=0; i<=5; ++i) {
        for(j=0; j<=5; ++j) {
            printf("%d %d\n",i, j);
            if(j==2) break;
        }

    }

    return 0;
}
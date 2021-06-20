extern int printf(char *format);

int main() {
    int i, j;
    for (i = 0; i < 100; ++i) {
        if (i >= 4) continue;
        j = 0;
        while(++j) {
            if (j == 2) break;
            else printf("%-3d %-3d", i, j);

        }
    }

    return 0;
}
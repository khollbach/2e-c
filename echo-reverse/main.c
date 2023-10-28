#include <stdio.h>
#include <string.h>

void print_reverse(char *s);

char buf[256];

int main() {
    int ret;

    while (1) {
        printf("> ");
        ret = scanf("%255s", buf);
        if (ret == EOF) {
            break;
        } else if (ret == 0) {
            perror("scanf");
            return 1;
        }

        print_reverse(buf);
        printf("\n");
    }

    return 0;
}

void print_reverse(char *s) {
    int len = strlen(s);
    int i;
    for (i = len - 1; i >= 0; i--) {
        putchar(s[i]);
    }
}

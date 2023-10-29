#include <stdio.h>
#include <conio.h>

int main() {
    unsigned char x, y;
    int i;

    clrscr();
    screensize(&x, &y); // 40, 24
    cprintf("screen dimensions: (%d, %d)\r\n", x, y);
    cprintf("(press any key to continue)\r\n");
    cgetc();

    // Ok. So this just prints a bunch of dashes.
    // Not what I wanted.
    for (i = y / 2; i < y; i++) {
        chlinexy(0, i, x);
    }
    cgetc();

    return 0;
}

#include <stdio.h>
#include <conio.h>

char _read_val; // needed so the compiler doesn't optimize away the read
#define ADDR(a) ((char*)a)
#define READ(a) (_read_val = *ADDR(a))
#define WRITE(a, x) (*ADDR(a) = x)

int main() {
    unsigned char x, y;

    clrscr();
    screensize(&x, &y); // 40, 24
    cprintf("screen dimensions: (%d, %d)\r\n", x, y);
    cprintf("(press any key to continue)\r\n");
    cgetc();

    WRITE(0xC050, 0); // graphics mode
    cgetc();

    READ(0xC051); // back to text mode

    return 0;
}

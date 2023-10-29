#include <stdio.h>
#include <conio.h>

char _read_val; // needed so the compiler doesn't optimize away the read
#define ADDR(a) ((char*)a)
#define READ(a) (_read_val = *ADDR(a))
#define WRITE(a, x) (*ADDR(a) = x)

enum low_res_color {
    black = 0,
    magenta = 1,
    dark_blue = 2,
    purple = 3,
    dark_green = 4,
    grey_1 = 5,
    medium_blue = 6,
    light_blue = 7,
    brown = 8,
    orange = 9,
    grey_2 = 10,
    pink = 11,
    green = 12,
    yellow = 13,
    aqua = 14,
    white = 15,
};

int main() {
    int x, y;

    cgetc();
    WRITE(0xC050, 0); // graphics mode
    cgetc();
    clrscr();
    cgetc();
    for (y = 0; y < 8; y++) {
        for (x = 0; x < 8; x++) {
            if ((x + y) % 2 == 0) {
                WRITE(0x0400 + y * 40 + x, white);

                //WRITE(0x0600 + y*2 * 40 + x, white);
                //WRITE(0x0600 + (y*2+1) * 40 + x, white);
            }
        }
        cgetc();
    }
    //cgetc();

    return 0;
}

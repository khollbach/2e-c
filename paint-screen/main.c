#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

typedef uint8_t u8;
typedef uint16_t u16;

void gr();
void gr_clear();
void paint(int color);

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
    int i;
    cgetc();

    gr();
    cgetc();

    for (i = 0; i < 16; i++) {
        gr_clear();
        cgetc();

        paint(i);
        cgetc();
    }

    return 0;
}

// Activate graphics mode.
void gr() {
    WRITE(0xC050, 0);
}

void gr_clear() {
    // Note that this clobbers screen holes.
    memset(ADDR(0x400), 0, 0x400);
}

void paint(int color) {
    memset(ADDR(0x400), color << 4 | color, 0x400);
}

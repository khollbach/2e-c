#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

typedef uint8_t u8;
typedef uint16_t u16;

void gr();
void gr_clear();
void draw_chessboard();
u16 gr_coord_to_addr(u8 x, u8 y);

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
    cgetc();

    gr();
    cgetc();

    gr_clear();
    cgetc();

    draw_chessboard();
    cgetc();

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

void draw_chessboard() {
    int x, y;
    for (y = 0; y < 8; y++) {
        for (x = 0; x < 8; x++) {
            if ((x + y) % 2 == 0) {
                WRITE(gr_coord_to_addr(x, y), white << 4 | white);
            }
        }
    }
}

u16 gr_coord_to_addr(u8 x, u8 y) {
    u8 group;
    u16 base, offset;
    assert(x < 40);
    assert(y < 24);

    group = y / 8;
    switch (group) {
    case 0:
        base = 0x400;
        break;
    case 1:
        base = 0x428;
        break;
    case 2:
        base = 0x450;
        break;
    }

    offset = y % 8 * 0x80;

    return base + offset + x;
}

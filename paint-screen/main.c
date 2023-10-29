#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>

typedef uint8_t u8;
typedef uint16_t u16;

void gr();
void select(bool page2);
void clear(bool page2);
void paint(bool page2, int color);

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
    bool screen;

    gr();
    clear(0);
    clear(1);
    cgetc();

    // Switch display buffer, *then* paint.
    for (i = 0; i < 16; i++) {
        screen = i % 2;

        select(screen);
        paint(screen, i);
        cgetc();
    }

    clear(0);
    clear(1);
    select(1);
    cgetc();

    // Pre-paint, before switching display buffers.
    // Will this look any smooth-er / more instant?
    // (update: a little less flicker, I think; but they're both pretty decent)
    for (i = 0; i < 16; i++) {
        screen = i % 2;

        paint(screen, i);
        select(screen);
        cgetc();
    }

    select(0);

    return 0;
}

// Activate graphics mode.
void gr() {
    WRITE(0xC050, 0);
}

void select(bool page2) {
    READ(0xC054 + page2);
}

void clear(bool page2) {
    // Note that this clobbers screen holes.
    u16 base = page2 ? 0x800 : 0x400;
    memset(ADDR(base), 0, 0x400);
}

void paint(bool page2, int color) {
    u16 base = page2 ? 0x800 : 0x400;
    memset(ADDR(base), color << 4 | color, 0x400);
}

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>

typedef uint8_t u8;
typedef uint16_t u16;

char _read_val; // needed so the compiler doesn't optimize away the read
#define ADDR(a) ((char*)a)
#define READ(a) (_read_val = *ADDR(a))
#define WRITE(a, x) (*ADDR(a) = x)

enum hi_res_color {
    // todo
};

const int logo_x = 12;
const int logo_y = 15;
const bool rc_logo[][] = {
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1],
    [1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1],
    [1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1],
    [1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1],
    [1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1],
    [1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0],
    [0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
    [1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1],
    [1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
};

int main() {
    hgr();
    hgr_clear();
    draw_logo();
    cgetc();
    return 0;
}

// Activate high-res graphics mode.
void hgr() {
    WRITE(0xC050, 0); // text mode off
    WRITE(0xC057, 0); // hires mode on
}

void hgr_clear() {
    // Note that this clobbers screen holes.
    memset(ADDR(0x2000), 0, 0x400);

    // Also note that we've changed program code loads (see Makefile).
    // Since 0x2000-0x5FFF are hi-res graphics pages 1 and 2,
    // we're now storing the program at 0x6000.
}

void draw_logo() {
    int x, y;
    for (y = 0; y < logo_y; y++) {
        for (x = 0; x < logo_x; x++) {
            color = rc_logo[x][y] ? todo : todo:
            a = hgr_coord_to_addr(x, y);
            WRITE(a, color);
        }
    }
}

u16 hgr_coord_to_addr(int x, int y) {
    assert(x < 280);
    assert(y < 192);

    todo
}

/*

*/

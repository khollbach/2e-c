#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>

typedef uint8_t u8;
typedef uint16_t u16;

void hgr();
void hgr_clear();

char _read_val; // needed so the compiler doesn't optimize away the read
#define ADDR(a) ((char*)a)
#define READ(a) (_read_val = *ADDR(a))
#define WRITE(a, x) (*ADDR(a) = x)

int main() {
    u8 byte_value;
    u16 x, y, third, base, offset, cell, row;

    cgetc();
    hgr();
    hgr_clear();
    cgetc();

    byte_value = 0;

    for (y = 0; y < 24; y++) {
        third = y / 8;
        switch (third) {
        case 0:
            base = 0x2000;
            break;
        case 1:
            base = 0x2028;
            break;
        case 2:
            base = 0x2050;
            break;
        }
        offset = y % 8 * 0x80;

        for (x = 0; x < 40; x++) {
            cell = base + offset + x;

            // A cell consists of 8 rows of 7 pixels each.
            // See page 35 of the Technical Reference Manual for a great diagram.
            for (row = 0; row < 8; row++) {
                WRITE(cell + row * 0x400, byte_value++);
            }
        }

        // Pause after every third of the screen.
        if (y % 8 == 7) {
            cgetc();
        }
    }

    return 0;
}

// Activate high-res graphics mode.
void hgr() {
    WRITE(0xC050, 0); // text mode off
    WRITE(0xC057, 0); // hires mode on
}

void hgr_clear() {
    // Note that this clobbers screen holes.

    // todo: this doesn't seem to clear the screen. debug!
    // first of all, why did we think length 0x400 is enough; shouldn't it be 0x2000?
    memset(ADDR(0x2000), 0, 0x400);

    // Note that we've changed where the program code loads (see Makefile).
    // Since 0x2000-0x5FFF are hi-res graphics pages 1 and 2,
    // we're now storing the program at 0x6000.
}

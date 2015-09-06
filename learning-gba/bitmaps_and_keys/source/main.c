
#include "toolbox.h"
#include "input.h"
#include "mountain.h"

/**
 * Program displays a bitmap on the screen. The colors are inverted when the A button is pressed.
 * Note that this program requires the files "toolbox.h", "input.h", and "toolbox.c" from the TONC
 * demo "key_demo" in the "basic" section.
 */

int main(void) {

    REG_DISPCNT = DCNT_MODE4 | DCNT_BG2;

    memcpy(vid_mem, mountainBitmap, mountainBitmapLen);
    memcpy(pal_bg_mem, mountainPal, mountainPalLen);

	while (1) {
        vid_vsync();
        key_poll();

        if (key_hit(KEY_A)) {
            pal_bg_mem[0] = ~pal_bg_mem[0] & 0x7FFF;
            pal_bg_mem[1] = ~pal_bg_mem[1] & 0x7FFF;
            pal_bg_mem[2] = ~pal_bg_mem[2] & 0x7FFF;
        }
	}
}

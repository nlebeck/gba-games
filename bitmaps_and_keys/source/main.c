
#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <stdio.h>
#include <stdlib.h>

#include "toolbox.h"
#include "mountain.h"

/**
 * Program will display a picture on screen. Some colors will change when the A button is pressed.
 */

int main(void) {

    REG_DISPCNT = DCNT_MODE4 | DCNT_BG2;

	while (1) {
        vid_vsync();

        memcpy(vid_mem, mountainBitmap, mountainBitmapLen);
        memcpy(pal_bg_mem, mountainPal, mountainPalLen);
	}
}

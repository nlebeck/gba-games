#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <stdio.h>
#include <stdlib.h>

#include "toolbox.h"

#define REG_VCOUNT *(vu16*)0x04000006

void vid_vsync();

//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

    int startx = 20;

    int ya = 20;
    int yb = 22;

	while (1) {
        vid_vsync();

        ya++;
        yb++;

        if (yb == 160) {
            ya = 0;
            yb = 2;
        }

        int i;
        for (i = 0; i < 100; i++) {
            int x = i + startx;
            vid_mem[SCREEN_WIDTH * ya + x] = CLR_RED;
            vid_mem[SCREEN_WIDTH * yb + x] = CLR_LIME;
        }
    }
}

void vid_vsync() {
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

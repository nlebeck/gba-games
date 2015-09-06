#include <tonc.h>
#include <brin.h>

/*
 * Code for experimenting with regular tiled backgrounds. Uses Brinstar tileset
 * from TONC brin_demo.
 *
 * Niel Lebeck
 */

void setTilemap(int sbb) {
    se_mem[sbb][0] = 0x0000;
    se_mem[sbb][1] = 0x0001;
    se_mem[sbb][2] = 0x0002;
    se_mem[sbb][3] = 0x0003;
}

int main() {

    // copy the background tile palette into the right place in memory
    memcpy(pal_bg_mem, brinPal, brinPalLen);

    // copy the background tileset into char-base-block (CBB) 0
    memcpy(&tile_mem[0][0], brinTiles, brinTilesLen);

    // manually write to the tilemap in screen-base-block (SBB) 30
    setTilemap(30);

    // set background 0 control and display control registers
    REG_BG0CNT = BG_CBB(0) | BG_4BPP | BG_SBB(30) | BG_REG_64x32;
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;

    int posX = 0;
    int posY = 0;

    while(1) {
        key_poll();

        if (key_is_down(KEY_RIGHT)) {
            posX++;
        }
        else if (key_is_down(KEY_LEFT)) {
            posX--;
        }

        if (key_is_down(KEY_UP)) {
            posY--;
        }
        else if (key_is_down(KEY_DOWN)) {
            posY++;
        }

        // update background offset position based on key press
        REG_BG0HOFS = posX;
        REG_BG0VOFS = posY;

        vid_vsync();
    }

    return 0;
}

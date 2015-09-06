#include <tonc.h>
#include <brin.h>

/*
 * Code that experiments with regular tiled backgrounds. Uses the Brinstar tileset
 * from the TONC demo brin_demo.
 *
 * Niel Lebeck
 */

void setTilemap() {

    int sbb = 30;

    // the pipe tiles are 25 and 26 (top) and 17 and 18 (bottom)
    se_mem[sbb][0] = 0x3019;
    se_mem[sbb][1] = 0x301A;
    se_mem[sbb][1 * 32 + 0] = 0x3011;
    se_mem[sbb][1 * 32 + 1] = 0x3012;

    // using palette 4 instead of 3 changes the color of the pipe
    se_mem[sbb][10] = 0x4019;
    se_mem[sbb][11] = 0x401A;
    se_mem[sbb][1 * 32 + 10] = 0x4011;
    se_mem[sbb][1 * 32 + 11] = 0x4012;

    // put a pipe in the other screenblock
    se_mem[sbb + 1][0] = 0x5019;
    se_mem[sbb + 1][1] = 0x501A;
    se_mem[sbb + 1][1 * 32 + 0] = 0x5011;
    se_mem[sbb + 1][1 * 32 + 1] = 0x5012;

    // put another pipe below it but indexing off the screen base block
    se_mem[sbb][1024 + 6 * 32 + 0] = 0x6019;
    se_mem[sbb][1024 + 6 * 32 + 1] = 0x601A;
    se_mem[sbb][1024 + 7 * 32 + 0] = 0x6011;
    se_mem[sbb][1024 + 7 * 32 + 1] = 0x6012;
}

int main() {

    // copy the background tile palette into the right place in memory
    memcpy(pal_bg_mem, brinPal, brinPalLen);

    // copy the background tileset into char-base-block (CBB) 0
    memcpy(&tile_mem[0][0], brinTiles, brinTilesLen);

    // manually write the tilemap
    setTilemap();

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

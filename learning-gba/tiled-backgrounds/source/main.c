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

    // The pipe tiles are 25 and 26 (top) and 17 and 18 (bottom), or in hex,
    // 0x19 and 0x1A (top) and 0x11 and 0x12 (bottom). Each screenblock is
    // 32x32 tiles, so the tile at position (x,y) within the screenblock is set
    // by writing to the memory at offset (y * 32 + x).
    se_mem[sbb][0] = 0x0019;
    se_mem[sbb][1] = 0x001A;
    se_mem[sbb][1 * 32 + 0] = 0x0011;
    se_mem[sbb][1 * 32 + 1] = 0x0012;

    // Using palette 3 instead of 0 changes the color of the pipe. For 4bpp
    // tilesets, the upper nybble of the tilemap value is the palbank number,
    // which indicates which 16-color palette is used.
    //
    // TODO: Figure out why the palbank number is 30 instead of 03 for palette 3.
    se_mem[sbb][10] = 0x3019;
    se_mem[sbb][11] = 0x301A;
    se_mem[sbb][1 * 32 + 10] = 0x3011;
    se_mem[sbb][1 * 32 + 11] = 0x3012;

    // Put a pipe in the other screenblock
    se_mem[sbb + 1][0] = 0x4019;
    se_mem[sbb + 1][1] = 0x401A;
    se_mem[sbb + 1][1 * 32 + 0] = 0x4011;
    se_mem[sbb + 1][1 * 32 + 1] = 0x4012;

    // Put another pipe below it but indexing off of the screen base block
    se_mem[sbb][1024 + 6 * 32 + 0] = 0x6019;
    se_mem[sbb][1024 + 6 * 32 + 1] = 0x601A;
    se_mem[sbb][1024 + 7 * 32 + 0] = 0x6011;
    se_mem[sbb][1024 + 7 * 32 + 1] = 0x6012;
}

int main() {

    // Copy the background tile palette into the right place in memory
    memcpy(pal_bg_mem, brinPal, brinPalLen);

    // Copy the background tileset into char-base-block (CBB) 0
    memcpy(&tile_mem[0][0], brinTiles, brinTilesLen);

    // Manually write the tilemap
    setTilemap();

    // Set background 0 control and display control registers
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

        // Update background offset position based on key press
        REG_BG0HOFS = posX;
        REG_BG0VOFS = posY;

        vid_vsync();
    }

    return 0;
}

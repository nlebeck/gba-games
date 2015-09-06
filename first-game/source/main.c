#include <tonc.h>

#include <brin.h>
#include <metr.h>

/*
 * Typedefs and structs
 */

typedef enum {
    SPLASH,
    PLAYING,
    DONE
} state_type;

/*
 * Global game state variables
 */

state_type gameState = SPLASH;
int posX = 0;
int posY = 0;

/*
 * Methods
 */
void setTilemap() {

    int sbb = 30;

    se_mem[sbb][0] = 0x0019;
    se_mem[sbb][1] = 0x001A;
    se_mem[sbb][1 * 32 + 0] = 0x0011;
    se_mem[sbb][1 * 32 + 1] = 0x0012;

    se_mem[sbb][10] = 0x3019;
    se_mem[sbb][11] = 0x301A;
    se_mem[sbb][1 * 32 + 10] = 0x3011;
    se_mem[sbb][1 * 32 + 11] = 0x3012;
}

void drawSplash() {
    tte_write("#{P:40,60}");
    tte_write("Niel's first game");
    tte_write("#{P:40,100}");
    tte_write("Press A to begin");
}

void doPlaying() {
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
    REG_BG0HOFS = posX;
    REG_BG0VOFS = posY;

    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
}

void doSplash() {
    drawSplash();
    if (key_released(KEY_A)) {
        gameState = PLAYING;
    }

    REG_DISPCNT = DCNT_MODE0 | DCNT_BG1;
}

int main() {

    // Set up background
    memcpy(pal_bg_mem, brinPal, brinPalLen);
    memcpy(&tile_mem[0][0], brinTiles, brinTilesLen);
    setTilemap();

    // Set up background 0 (game background) and background 1 (text)
    REG_BG0CNT = BG_CBB(0) | BG_4BPP | BG_SBB(30) | BG_REG_64x32;
    tte_init_se_default(1, BG_CBB(1) | BG_SBB(24));

    // Set up display control register
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;

    while(1) {
        key_poll();

        if (gameState == PLAYING) {
            doPlaying();
        }
        else if (gameState == SPLASH) {
            doSplash();
        }

        vid_vsync();
    }
    
    while(1);

    return 0;
}

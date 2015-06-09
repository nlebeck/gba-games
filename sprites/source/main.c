
#include "stdio.h"

#include "toolbox.h"
#include "memmap.h"
#include "memdef.h"
#include "types.h"
#include "input.h"

#include "blobLarge.h"

OBJ_ATTR obj_buffer[128];

int main(void) {
    memcpy(&tile_mem[4][0], blobLargeTiles, blobLargeTilesLen);
    memcpy(pal_obj_mem, blobLargePal, blobLargePalLen);
    oam_init(obj_buffer, 128);
    REG_DISPCNT = DCNT_OBJ | DCNT_OBJ_1D;

    OBJ_ATTR * blob = &obj_buffer[0];
    u32 blobTileIndex = 0;
    u32 blobPalBank = 0;

    //two different ways of setting OAM values: by hand and using TONC macros

    blob->attr0 = (blob->attr0 & ~ATTR0_SHAPE_MASK) | ATTR0_SQUARE;
    blob->attr1 = (blob->attr1 & ~ATTR1_SIZE_MASK) | ATTR1_SIZE_64;
    blob->attr2 = (blob->attr2 & ~ATTR2_ID_MASK) | (blobTileIndex << ATTR2_ID_SHIFT);
    blob->attr2 = (blob->attr2 & ~ATTR2_PALBANK_MASK) | (blobPalBank << ATTR2_PALBANK_SHIFT);

    /*
    BFN_SET2(blob->attr0, ATTR0_SQUARE, ATTR0_SHAPE);
    BFN_SET2(blob->attr1, ATTR1_SIZE_64, ATTR1_SIZE);
    BFN_SET(blob->attr2, blobTileIndex, ATTR2_ID);
    BFN_SET(blob->attr2, blobPalBank, ATTR2_PALBANK);
    */

	while (1) {
        vid_vsync();

        obj_unhide(blob, 0);

        oam_copy(oam_mem, obj_buffer, 1);
	}
}



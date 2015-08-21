#include <tonc.h>

/*
 * To build this template program, you need the DEVKITPRO, DEVKITARM, and
 * TONCLIB environment variables set. You should have a devkitPro folder with
 * devkitARM and libgba subfolders. Set DEVKITPRO to the path of the base
 * devkitPro folder, and set DEVKITARM to the devkitARM subfolder. Set TONCLIB
 * to the tonclib folder. This template program uses the makefile from the
 * devkitPro GBA example template.
 */

int main() {
    
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;

    tte_init_se_default(0, BG_CBB(0) | BG_SBB(31));
    tte_write("#{P:20,60}");
    tte_write("Niel's devkitPro/tonclib");
    tte_write("#{P:20,80}");
    tte_write("template: use these files");
    tte_write("#{P:20,100}");
    tte_write("as a starting point.");

    while(1);

    return 0;
}

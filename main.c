#include <genesis.h>
#include "resources.h"

#define SCREEN_W 320
#define SCREEN_H 224
#define PLAYER_W 32
#define PLAYER_H 32

static Sprite* diver;
static s16 playerX = 72;
static s16 playerY = 112;
static u16 score = 0;
static u16 oxygen = 100;
static u16 frameTick = 0;
static bool treasureTaken = FALSE;
static const s16 treasureX = 250;
static const s16 treasureY = 112;

static void drawHUD(void)
{
    char line[32];
    sprintf(line, "SCORE %04d", score);
    VDP_drawText(line, 1, 1);
    sprintf(line, "AIR %03d", oxygen);
    VDP_drawText(line, 25, 1);
}

static void resetGame(void)
{
    playerX = 72;
    playerY = 112;
    score = 0;
    oxygen = 100;
    frameTick = 0;
    treasureTaken = FALSE;
}

int main(bool hardReset)
{
    u16 joy;
    Sprite* treasure;

    (void) hardReset;
    VDP_setScreenWidth320();
    VDP_setPlaneSize(64, 32, TRUE);
    VDP_setTextPalette(PAL1);

    VDP_drawImageEx(BG_A, &background,
        TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USER_INDEX),
        0, 0, FALSE, TRUE);

    SPR_init();
    diver = SPR_addSprite(&player, playerX, playerY,
        TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
    treasure = SPR_addSprite(&treasure_item, treasureX, treasureY,
        TILE_ATTR(PAL1, TRUE, FALSE, FALSE));

    VDP_drawText("FREEDIVER'S ADVENTURES", 7, 2);
    VDP_drawText("THE DEEP BLUE CAVE", 10, 3);
    drawHUD();

    while (TRUE)
    {
        joy = JOY_readJoypad(JOY_1);

        if (joy & BUTTON_LEFT)  playerX -= 2;
        if (joy & BUTTON_RIGHT) playerX += 2;
        if (joy & BUTTON_UP)    playerY -= 2;
        if (joy & BUTTON_DOWN)  playerY += 2;

        if (playerX < 0) playerX = 0;
        if (playerX > SCREEN_W - PLAYER_W) playerX = SCREEN_W - PLAYER_W;
        if (playerY < 32) playerY = 32;
        if (playerY > SCREEN_H - PLAYER_H - 8) playerY = SCREEN_H - PLAYER_H - 8;

        SPR_setPosition(diver, playerX, playerY);

        if (!treasureTaken &&
            (playerX + PLAYER_W > treasureX + 6) &&
            (playerX < treasureX + 26) &&
            (playerY + PLAYER_H > treasureY + 6) &&
            (playerY < treasureY + 26))
        {
            treasureTaken = TRUE;
            score += 100;
            SPR_setVisibility(treasure, HIDDEN);
        }

        frameTick++;
        if ((frameTick % 60) == 0 && oxygen > 0) oxygen--;
        if (oxygen == 0)
        {
            VDP_drawText("AIR LOW! FIND THE EXIT!", 7, 25);
            if (joy & BUTTON_START) resetGame();
        }

        if ((frameTick % 8) == 0) drawHUD();

        SPR_update();
        SYS_doVBlankProcess();
    }

    return 0;
}

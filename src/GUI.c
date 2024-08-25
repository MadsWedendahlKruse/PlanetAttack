#include "GUI.h"

uint8_t GUI_init() {   //Initializes LCD SCREEN to get ready for use

    GPIO_initJoystick();
    lcd_init();

    char player1[9] = "1 PLAYER";
    char player2[9] = "2 PLAYER";
    char help[5] = "HELP";
    char blank[1] = "";
    char mark[3] = "> ";

    char fwd1[11] = "Forward: w";
    char fwd2[11] = "Forward: i";
    char right1[11] = "Right:   d";
    char right2[11] = "Right:   l";
    char left1[11] = "Left:    a";
    char left2[11] = "Left:    j";
    char shoot1[11] = "Shoot:   c";
    char shoot2[11] = "Shoot:   n";

    char play[11] = "Play: p";
    char boss[11] = "Boss: b";

    #define SIZE_X 2
    #define SIZE_Y 4
    char* guiElement[SIZE_X][SIZE_Y];

    #define GUI_START 0
    #define GUI_HELP1 1
    #define GUI_HELP2 2
    uint8_t guiState = GUI_START;

    int8_t activeX = 0;
    int8_t activeY = 0;

    uint8_t inputSample1;
    uint8_t inputSample2 = -1;

    while(1) {

        lcd_bClear();

        switch (guiState) {

            case GUI_START:
                guiElement[0][0] = player1;
                guiElement[1][0] = player2;
                guiElement[0][1] = blank;
                guiElement[1][1] = blank;
                guiElement[0][2] = help;
                guiElement[1][2] = blank;
                guiElement[0][3] = blank;
                guiElement[1][3] = blank;
            break;

            case GUI_HELP1:
                guiElement[0][0] = fwd1;
                guiElement[1][0] = fwd2;
                guiElement[0][1] = right1;
                guiElement[1][1] = right2;
                guiElement[0][2] = left1;
                guiElement[1][2] = left2;
                guiElement[0][3] = shoot1;
                guiElement[1][3] = shoot2;
            break;

            case GUI_HELP2:
                guiElement[0][0] = play;
                guiElement[1][0] = boss;
                guiElement[0][1] = blank;
                guiElement[1][1] = blank;
                guiElement[0][2] = blank;
                guiElement[1][2] = blank;
                guiElement[0][3] = blank;
                guiElement[1][3] = blank;
            break;
        }

        int i, j;
        for (i = 0; i < SIZE_Y; i++) {
            for (j = 0; j < SIZE_X; j++) {
                if (j == activeX && i == activeY && guiState == 0) {
                    lcd_bWriteString(mark, j * 64, i * 8);
                    lcd_bWriteString(guiElement[activeX][activeY], 8 + j * 64, i * 8);
                } else {
                    lcd_bWriteString(guiElement[j][i], 8 + j * 64, i * 8);
                }
            }
        }

        inputSample1 = GPIO_readJoystick();

        if (inputSample1 != inputSample2) {

            if (inputSample1 == JOYSTICK_UP) {

                activeY--;
                // skip "blank" areas
                for (i = 0; i < SIZE_Y; i++) {
                    if (guiElement[activeX][activeY] == blank) {
                    activeY--;
                    }
                    if (activeY < 0) {
                        activeY = SIZE_Y - 1;
                    }
                }

            } else if (inputSample1 == JOYSTICK_DOWN) {

                activeY++;
                // skip "blank" areas
                for (i = 0; i < SIZE_Y; i++) {
                    if (guiElement[activeX][activeY] == blank) {
                    activeY++;
                    }
                    if (activeY > SIZE_Y - 1) {
                        activeY = 0;
                    }
                }

            } else if (inputSample1 == JOYSTICK_LEFT || inputSample1 == JOYSTICK_RIGHT) {

                activeX = (activeX == 0) ? 1 : 0;
                // skip "blank" areas
                if (guiElement[activeX][activeY] == blank) {
                    activeX--;
                }

            } else if (inputSample1 == JOYSTICK_CENTER) {

                if (guiState == GUI_START) {

                    if (activeX == 0 && activeY == 0) {
                        // 1 PLAYER
                        return 1;
                        break;

                    } else if (activeX == 1 && activeY == 0) {
                        // 2 PLAYER
                        return 2;
                        break;

                    } else if (activeX == 0 && activeY == 2) {
                        // HELP
                        guiState = GUI_HELP1;

                    }

                } else if (guiState == GUI_HELP1) {

                    guiState = GUI_HELP2;

                } else {

                    guiState = GUI_START;
                }
            }
        }

        inputSample2 = GPIO_readJoystick();

        lcd_bShow();
    }
}

void GUI_update() {

    lcd_bClear();

    char player1[9] = "PLAYER 1";
    char player2[9] = "PLAYER 2";
    char hp[4] = "HP:";
    char score[7] = "SCORE:";
    char health1 = players[0].e.health + '0';
    char health2 = players[1].e.health + '0';

    char points1[4];
    points1[0] = (players[0].score / 100) + '0';
    points1[1] = ((players[0].score % 100) / 10) + '0';
    points1[2] = (players[0].score % 10) + '0';
    points1[3] = '\0';

    char points2[4];
    points2[0] = (players[1].score / 100) + '0';
    points2[1] = ((players[1].score % 100) / 10) + '0';
    points2[2] = (players[1].score % 10) + '0';
    points2[3] = '\0';

    // First line
    uint8_t y = 0;
    lcd_bWriteString(player1, 0, y);
    lcd_bWriteString(player2, 64, y);

    // Third line
    y = 16;
    lcd_bWriteString(hp, 0, y);
    lcd_bWriteChar(health1, 16, y);
    lcd_bWriteChar(health2, 80, y);
    lcd_bWriteString(hp, 64, y);

    // Fourth line
    y = 24;
    lcd_bWriteString(score, 0, y);
    lcd_bWriteString(points1, 32, y);
    lcd_bWriteString(score, 64, y);
    lcd_bWriteString(points2, 96, y);

    lcd_bShow();
}

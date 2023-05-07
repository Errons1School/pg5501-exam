#ifndef PG550_EXAM_ESP32_MAIN_H
#define PG550_EXAM_ESP32_MAIN_H

#include "snake/SnakeGame.h"
#include "modules/MTftScreen.h"
#include "modules/MGyroscope.h"
#include "modules/MPotentiometer.h"
#include "modules/MEeprom.h"

#include <Arduino.h>

enum GameState {
    MainMenu = 0,
    Playing = 1,
    HighScore = 2,
};

/* Prints out the main menu on the tft screen
 * PARA1        int value of what menu option to highlight */
void printOptionMainMenu(int iOption);

/* Takes the input from user and changes what menu option to highlight
 * PARA1        int pointer to value that is highlighted to user
 * RETURN       int value to change menu option highlight up or down*/
int changeOptionMainMenu(int *piMainMenuSelect);

/* Takes input from user to select highlighted option and change game state
 * PARA1        int value that indicate what game state to select
 * return       int value of what game state to continue in*/
int selectOptionMainMenu(int iMainMenuSelect);

#endif //PG550_EXAM_ESP32_MAIN_H

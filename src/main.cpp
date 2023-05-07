#include "main.h"
/*
 *  This exam is done using an ESP32.
 *  All pins are therefor used for an ESP32 and need change on other cards.
 *  Pin out: https://raw.githubusercontent.com/jenschr/LectureFeather/main/img/pinout.png
 * */

// I2C protocol
int8_t scl = 4;        // Serial Clock
int8_t sda = 3;        // Serial Data

// SPI protocol
int8_t sclk = 36;       // Serial Clock
int8_t miso = 37;       // Master In Slave Out
int8_t mosi = 35;       // Master Out Slave In
int8_t ss1 = 13;        // Slave Select Adafruit 240x135 Color TFT LCD ST7789
int8_t dcTft = 12;      // Data control Adafruit 240x135 Color TFT LCD ST7789
int8_t dcSd = 11;       // Data control Adafruit 240x135 Color TFT LCD ST7789 SD-card

// Other pins
int8_t potentiometerReader = 18;

// objects for modules
MTftScreen *pMTftScreen = nullptr;
MGyroscope *pMGyroscope = nullptr;
MPotentiometer *pPotentiometer = nullptr;
MEeprom *pEprom = nullptr;


// object for the game
SnakeGame *pSnakeGame = nullptr;
GameState gameState = MainMenu;


void setup() {
    Serial.begin(9600);
    delay(5000); // makes time to connect serial monitor
    Wire.begin(sda, scl); // initiate I2C

//    Initiate modules
//    Minor timers between each to make sure every object had time to complete
    pMTftScreen = new MTftScreen(ss1, dcTft, dcSd);
    Serial.println("Screen added");
    delay(50);

    pMGyroscope = new MGyroscope();
    Serial.println("Gyroscope added");
    delay(50);

    pPotentiometer = new MPotentiometer(potentiometerReader);
    Serial.println("Potentiometer added");
    delay(50);

    pEprom = new MEeprom();
    Serial.println("EEprom memory added");
    delay(50);

//    Test of screen and texture
//    This is boot up test to check tft and sd card is connected
//    Optional to have this on boot

    pMTftScreen->screenTest();
    Serial.println("Screen test");
    delay(1000);

    pMTftScreen->testTexture();
    Serial.println("Texture test");
    delay(1000);

    pMTftScreen->clearScreen();
    Serial.println("Clear Screen");
    delay(1000);

    pEprom->clearMemory();
}

void loop() {
    int iMainMenuSelect = GameState::MainMenu;
    int iChangeMainMenu = -10;

    switch (gameState) {
        case GameState::MainMenu : {
            while (gameState == GameState::MainMenu) {
                printOptionMainMenu(iChangeMainMenu);
                iChangeMainMenu = changeOptionMainMenu(&iMainMenuSelect);
                gameState = (GameState) selectOptionMainMenu(iMainMenuSelect);
            }
            break;
        }

        case GameState::Playing : {
            pMTftScreen->clearScreen();
            pSnakeGame = new SnakeGame(pMGyroscope, pMTftScreen, pEprom);
            pSnakeGame->startGame();
            pSnakeGame->freeSnakeGame();

            pMTftScreen->clearScreen();
            gameState = GameState::MainMenu;
            iMainMenuSelect = 0;
            break;
        }

        case GameState::HighScore : {
            int *aiScores = pEprom->getHighScoreTable();
            pMTftScreen->printHighScore(aiScores);

            delay(10000);
            free(aiScores);
            gameState = GameState::MainMenu;
            break;
        }

        default: {
            gameState = GameState::MainMenu;
        }
    }

}

void printOptionMainMenu(int iOption) {
    pMTftScreen->printMainMenu(iOption);
}

int changeOptionMainMenu(int *piMainMenuSelect) {
    //This is static to "remember" what game state keep
    static int iMainMenuSelect = 0;
    iMainMenuSelect = pPotentiometer->getUpOrDown();

    if (iMainMenuSelect == 1 && *piMainMenuSelect != 1) {
        *piMainMenuSelect = GameState::Playing;
    }
    else if (iMainMenuSelect == -1 && *piMainMenuSelect != 2) {
        *piMainMenuSelect = GameState::HighScore;
    }

    return iMainMenuSelect;
}

int selectOptionMainMenu(int iMainMenuSelect) {
    if (pMGyroscope->getSelect() == 1) {
        return iMainMenuSelect;
    }
    return GameState::MainMenu;
}
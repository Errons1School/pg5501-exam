#include "MTftScreen.h"

#define USE_SD_CARD

MTftScreen::MTftScreen(int slaveSelect, int dataControllerTft, int dataControllerSD) {
//    Setup tft screen
    pTft = new Adafruit_ST7789((int8_t) slaveSelect, (int8_t) dataControllerTft, -1);
    pTft->init(135, 240);
    pTft->setRotation(3);
    pTft->fillScreen(ST77XX_BLACK);

//    Setup SD-card
    pSD = new SdFat;
    pReader = new Adafruit_ImageReader(*pSD);
    while (!pSD->begin(dataControllerSD, SD_SCK_MHZ(20))) {
        delay(1000);
        Serial.println("Failed to read SD");
    }

    Serial.println("Success to read SD");
}

void MTftScreen::screenTest() {
    pTft->fillScreen(ST77XX_WHITE);
    pTft->setTextColor(ST77XX_BLACK);
    pTft->setTextSize(2);
    pTft->setCursor(10, 10);
    pTft->println("ESP3do GameBoy");
}

void MTftScreen::testTexture() {
    pTft->fillScreen(ST77XX_BLACK);

    for (int y = 0; y < 135; y += INT_GAME_PIXEL) {
        for (int x = 0; x < INT_GRID_SIZE_Y; x += INT_GAME_PIXEL) {
            pReader->drawBMP("/grass1.bmp", *pTft, (short) x, (short) y);
        }
    }

    pReader->drawBMP("/food.bmp", *pTft, 30, 15);
    pReader->drawBMP("/head0.bmp", *pTft, 30, 30);
    pReader->drawBMP("/body.bmp", *pTft, 30, 45);
    pReader->drawBMP("/tail0.bmp", *pTft, 30, 60);
}

void MTftScreen::clearScreen() {
    pTft->fillScreen(ST77XX_BLACK);
}

void MTftScreen::printTexture(int iWhatToPrint, int iX, int iY, int iDirection) {
    const char *sPicture;

    if (iWhatToPrint == SnakeGamePixel::HEAD) {
        switch (iDirection) {
            case SnakeGameDirection::UP:
                sPicture = "/head0.bmp";
                break;

            case SnakeGameDirection::LEFT:
                sPicture = "/head1.bmp";
                break;

            case SnakeGameDirection::DOWN:
                sPicture = "/head2.bmp";
                break;

            case SnakeGameDirection::RIGHT:
                sPicture = "/head3.bmp";
                break;

            default:
                break;
        }

    } else if (iWhatToPrint == SnakeGamePixel::BODY) {
        sPicture = "/body.bmp";

    } else if (iWhatToPrint == SnakeGamePixel::TAIL) {
        switch (iDirection) {
            case SnakeGameDirection::UP:
                sPicture = "/tail0.bmp";
                break;

            case SnakeGameDirection::LEFT:
                sPicture = "/tail1.bmp";
                break;

            case SnakeGameDirection::DOWN:
                sPicture = "/tail2.bmp";
                break;

            case SnakeGameDirection::RIGHT:
                sPicture = "/tail3.bmp";
                break;

            default:
                break;
        }

    } else if (iWhatToPrint == SnakeGamePixel::FOOD) {
        sPicture = "/food.bmp";

    } else {
        sPicture = "/grass1.bmp";
    }

    pReader->drawBMP(sPicture, *pTft, (short) iX, (short) iY);
}

void MTftScreen::printMainMenu(int iOption) {
    static int iPrintGrass = 0;

    if (iPrintGrass != iOption && iOption != 0 || iOption == -10) {
        Serial.println(iPrintGrass);
        Serial.println(iOption);

        printBackgroundGrass();

        if (iOption == -10) {
            pTft->setTextColor(ST77XX_WHITE);
            pTft->setTextSize(3);
            pTft->setCursor(10, 10);
            pTft->write("Play");

            pTft->setTextSize(3);
            pTft->setCursor(10, 68);
            pTft->write("HighScore");
        }
        iPrintGrass = iOption;
    }

//    Upper option to highlight
    if (iOption == 1) {
        pTft->setTextColor(ST77XX_BLUE);
        pTft->setTextSize(4);
        pTft->setCursor(10, 10);
        pTft->write("Play");

        pTft->setTextColor(ST77XX_WHITE);
        pTft->setTextSize(3);
        pTft->setCursor(10, 68);
        pTft->write("HighScore");

//        Latter option to highlight
    } else if (iOption == -1) {
        pTft->setTextColor(ST77XX_WHITE);
        pTft->setTextSize(3);
        pTft->setCursor(10, 10);
        pTft->write("Play");

        pTft->setTextColor(ST77XX_BLUE);
        pTft->setTextSize(4);
        pTft->setCursor(10, 68);
        pTft->write("HighScore");
    }
}

void MTftScreen::printScore(int iScore) {
    printBackgroundGrass();

    pTft->setTextColor(ST77XX_WHITE);
    pTft->setTextSize(2);
    pTft->setCursor(10, 10);
    pTft->print("Your score is: ");
    pTft->print(iScore);
    delay(5000);
}

void MTftScreen::printHighScore(int *aiScores) {
    printBackgroundGrass();

    pTft->setTextColor(ST77XX_WHITE);
    pTft->setTextSize(2);
    pTft->setCursor(10, 10);
    pTft->println("High scores!");

    for (int i = 0; i < INT_HIGH_SCORE_SIZE; ++i) {
        pTft->print(i + 1);
        pTft->print(". ");
        pTft->println(aiScores[i]);
    }
}

void MTftScreen::printBackgroundGrass() {
    for (int y = 0; (y * INT_GAME_PIXEL) < INT_GRID_SIZE_Y; ++y) {
        for (int x = 0; (x * INT_GAME_PIXEL) < INT_GRID_SIZE_X; ++x) {
            pReader->drawBMP("/grass1.bmp", *pTft, (short) (x * INT_GAME_PIXEL), (short) (y * INT_GAME_PIXEL));
        }
    }
}
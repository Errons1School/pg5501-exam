#include "MPotentiometer.h"
#include <Arduino.h>

MPotentiometer::MPotentiometer(int iPinPotentiometerReader) {
    this->iPinPotentiometerReader = iPinPotentiometerReader;
    pinMode(iPinPotentiometerReader, INPUT);
    iPotentiometerValue = analogRead(iPinPotentiometerReader);
}

int MPotentiometer::getUpOrDown() {
    int iValuePlusMinus = 150;
    int iNewValue = analogRead(iPinPotentiometerReader);
    int iValueMinus = iPotentiometerValue - iValuePlusMinus;
    int iValuePlus = iPotentiometerValue + iValuePlusMinus;

    if (iNewValue >= iValuePlus) {
        iPotentiometerValue = iNewValue;
        return 1;

    } else if (iNewValue <= iValueMinus) {
        iPotentiometerValue = iNewValue;
        return -1;

    } else {
        return 0;
    }
}

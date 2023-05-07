#include "MGyroscope.h"

// Documentation for lib: https://github.com/RobTillaart/GY521?utm_source=platformio&utm_medium=piohome

MGyroscope::MGyroscope() {
    pGyro = new GY521(0x69, &Wire);
    pGyro->setAccelSensitivity(2);
    pGyro->setGyroSensitivity(0);

    while (!pGyro->wakeup()) {
        Serial.println("Gyro not added");
        delay(1000);
    }

}

void MGyroscope::serialPrintTest() {
    pGyro->read();

    float xAcc = pGyro->getAccelX();
    float yAcc = pGyro->getAccelY();
    float zAcc = pGyro->getAccelZ();
    float xGyro = pGyro->getGyroX();
    float yGyro = pGyro->getGyroY();
    float zGyro = pGyro->getGyroZ();

    Serial.print("Acc: x ");
    Serial.print(xAcc, 2);
    Serial.print("\t y ");
    Serial.print(yAcc, 2);
    Serial.print("\t z ");
    Serial.print(zAcc, 2);
    Serial.println();

    Serial.print("Gyr: x ");
    Serial.print(xGyro, 2);
    Serial.print("\t y ");
    Serial.print(yGyro, 2);
    Serial.print("\t z ");
    Serial.print(zGyro, 2);
    Serial.println();
}

int MGyroscope::getSelect() {
    float fValuePlusMinus = 0.30;
    pGyro->read();
    float fNewValue = pGyro->getAccelX();
    float iValueMinus = fAccX - fValuePlusMinus;
    float iValuePlus = fAccX + fValuePlusMinus;

    if (fNewValue <= iValueMinus || fNewValue >= iValuePlus) {
        fAccX = fNewValue;
        return 1;

    } else {
        return 0;
    }
}

int MGyroscope::getLeftOrRight() {
    float fValuePlusMinus = 40;

    pGyro->read();
    fGyroZ = pGyro->getGyroZ();

    // gyroX returns +number to left and -number to the right
    // check left
    if (fGyroZ >= +fValuePlusMinus) {
        return 1;

//        Check right
    } else if (fGyroZ <= -fValuePlusMinus) {
        return -1;

    } else {
        return 0;
    }
}



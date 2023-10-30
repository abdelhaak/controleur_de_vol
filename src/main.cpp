#include <Arduino.h>
#include <Wire.h> 
#include "my_library.h"


void setup()
{
    Wire.begin(); // ouverture de la ligne I2C en maître
    TWBR = 24; // horloge I2C en 400kHz
    init_MPU6050();
    calibrer_MPU6050();
}

void loop()
{
    lire_MPU6050();

    // Calcul des vitesses angulaires BRUTES:
    gyro[ROLL] = gyro_raw[ROLL] - gyro_offset[ROLL];
    gyro[PITCH] = gyro_raw[PITCH] - gyro_offset[PITCH];
    gyro[YAW] = gyro_raw[YAW] - gyro_offset[YAW];

    // Calcul des accelérations BRUTES:
    accel[X] = accel_raw[X] - accel_offset[X];
    accel[Y] = accel_raw[Y] - accel_offset[Y];
    accel[Z] = accel_raw[Z] - accel_offset[Z];
}
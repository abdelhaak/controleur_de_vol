#include "my_library.h"
#include <Wire.h>


void init_MPU6050()
{
    // Configuration horloge interne
Wire.beginTransmission (MPU_adress); // Debut de communication
Wire.write (0x6B) ;                  // Registre  PWR_MGMT_1 
Wire.write (0x00) ;                  // Hotloge interne de 8 MHz
Wire.endTransmission();            // Fin de transmission

// Configuration échelle gyroscope
Wire.beginTransmission (MPU_adress) ;
Wire.write(0x1B) ;                   // Registre  GYRO_CONFIG
Wire.write (0x08) ;                  // Plage de  +- 500 º/s
Wire.endTransmission();

// Configuration échelle accéléromètre
Wire.beginTransmission (MPU_adress) ;
Wire.write (0x1C) ;                 // Registre  ACCEL_CONFIG
Wire.write(0x10) ;                  // plage +- 8g
Wire.endTransmission () ;

// Configuration filtre passe-bas
Wire.beginTransmission (MPU_adress) ;
Wire.write (0x1A) ;                 // Registre  CONFIG
Wire.write (0x03) ;                 // Frequence de coupure de environ 40 Hz
Wire.endTransmission () ;

}

void lire_MPU6050()
{
    Wire.beginTransmission (MPU_adress) ;
    Wire.write(0x3B);        // adresse de début
    Wire.endTransmission () ;
    Wire.requestFrom(MPU_adress, 14);     // requête lecture 14 octets

    // Attente jusqu'à ce que les 14 octets soient reçus

    while (Wire.available() < 14);

    accel_raw[X] = Wire.read() << 8 | Wire.read();      // accél. x
    accel_raw[Y] = Wire.read() << 8 | Wire.read();      // accél. Y
    accel_raw[Z] = Wire.read() << 8 | Wire.read();      // accél. z

    temperature = Wire.read() << 8 | Wire.read();

    gyro_raw[ROLL] = Wire.read() << 8 | Wire.read();        // gyro roll
    gyro_raw[PITCH] = Wire.read() << 8 | Wire.read();       //gyro pitch
    gyro_raw[YAW] = Wire.read() << 8 | Wire.read();         // gyro yaw
}

void calibrer_MPU6050()
{
    int nb_mesures = 2000;

    for (int i = 0; i < nb_mesures; i++)
    {
        lire_MPU6050();     // fonction de lecture du MPU6050

        // somme des échantillons de mesures
        gyro_offset[ROLL] += gyro_raw[ROLL];
        gyro_offset[PITCH] += gyro_raw[PITCH];
        gyro_offset[YAW] += gyro_raw[YAW];

        accel_offset[X] += accel_raw[X];
        accel_offset[Y] += accel_raw[Y];
        accel_offset[Z] += accel_raw[Z];
    }

    // Calcul de la moyenne des offsets pour le gyroscope
    gyro_offset[ROLL] /= nb_mesures;
    gyro_offset[PITCH] /= nb_mesures;
    gyro_offset[YAW] /= nb_mesures;

    // Calcul de la moyenne des offsets
    accel_offset[X] /= nb_mesures;
    accel_offset[Y] /= nb_mesures;

    // pour les axes X et Y, on retranche la valeur de l'offset
    // à la valeur brute pour la recentrer sur zéro car au
    // repos et horizontal le MPU a des accélérations nulles en X et Y

    // pour l'axe Z, la rectification des mesures brutes est
    // différente de celle des axes X et Y
    // au repos et à l'horizontal le MPU subit une accéleration de 1g
    // pour une accel de 1g, la valeur renvoyée doit être de 4096 donc
    // l'offset à retrancher á la valeur brute pour la rencontrer sur 4096 
    // est : moyenne - 4096

    accel_offset[Z] = (accel_offset[Z]/nb_mesures) - 4096;

}
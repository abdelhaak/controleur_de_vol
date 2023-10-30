//#ifndef MY_LIBRARY55
#define MY_LIBRARY

#define MPU_adress 0x68 // adresse du MPU-6050

#define ROLL 0      // indice 0 : axe roll
#define PITCH 1     // indice 1 : axe pitch
#define YAW 2       // indice 2 : axe yaw
#define X 0         // indice 0 : axe x
#define Y 1         // indice 1 : axe Y
#define Z 2         // indice 2 : axe Z

int accel_raw[3] = {0,0,0};     // tableau des accélérations brutes
int gyro_raw[3] = {0,0,0};      // tableau des vitesses angulaires brutes

float gyro[3] = {0,0,0};        // tableau des accélérations brutes et sans l'offset
float accel[3] = {0,0,0};       // tableau des vitesses angulaires brutes et sans l'offsets

float gyro_offset[3] = {0,0,0};        // tableau des offsets des accélérations
float accel_offset[3] = {0,0,0};       // tableau des offsets des vitesses angulaires

int temperature = 0;

// Initilalisation de MPU6050 
void init_MPU6050();

// Lire les valeurs de MPU6050
void lire_MPU6050();

// Calibration de capteur en suppriment les offsets
void calibrer_MPU6050();
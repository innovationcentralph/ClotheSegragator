#define S2 19 /*Define S2 Pin Number of ESP32*/
#define S3 18 /*Define S3 Pin Number of ESP32*/
#define sensorOut 23 /*Define Sensor Output Pin Number of ESP32*/
#define sensorVCC 36 /*Define Sensor Output Pin Number of ESP32*/

/*Define int variables*/
int Red = 0;
int Green = 0;
int Blue = 0;
int Frequency = 0;
float colorValue;


const int trigPin = 4;  // Trig pin of the ultrasonic sensor
const int echoPin = 5; // Echo pin of the ultrasonic sensor
unsigned long int checkMillis=0;

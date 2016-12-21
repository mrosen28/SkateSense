#include <Adafruit_Sensor.h>; // Libraries for Gyroscope
#include <Adafruit_L3GD20_U.h>;
#include <Wire.h>; // Library for Serial Communication
#include <SD.h>; //Library for SD Card
#define USE_I2C // Defines Gyroscope Connection Type
Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);
const int chipSelect = 2;
static AccelerationReading a = { 0 , 0 , 0 };

void setup() {
  static bool startup = true;
  bool startupBluetoothConnectionState = false;
  Wire.begin();
  Serial.begin(57600);

  //Allows Bean to Detect Motion Events
  gyro.enableAutoRange(true);

  if (!gyro.begin()){
    Serial.println("Unable to Initialize Gyro.");
    delay (1000);
  }

  Bean.enableMotionEvent(ANY_MOTION_EVENT);
  Bean.setAccelerometerPowerMode(VALUE_NORMAL_MODE);
  Bean.setAccelerationRange(4);

  /* Check Battery Level on Startup */
  float startUpBatteryLevel = batteryCheck(startup);

  /* Get Connection State */

  do {
    startupBluetoothConnectionState = Bean.getConnectionState();
    delay(10);
  } while(!startupBluetoothConnectionState);

   // Check if the card is present and can be initialized
  if (!SD.begin(chipSelect)) { Serial.println("SD fail"); }

   //If the file is available, write to it:
   File dataFile = SD.open("datalog.txt", FILE_WRITE);
   if (dataFile) {
     dataFile.println("Battery Voltage on Startup: ");
     dataFile.print(startUpBatteryLevel);
     dataFile.println("Bluetooth Connection:");
     dataFile.print(startupBluetoothConnectionState);
     dataFile.println("Startup Complete.");
     dataFile.println(" ");
     dataFile.close();
   }

}

void loop() {

    /* MAKE LOG - One Blink = One Update*/
    Bean.setLed(0,0,0); //Sets LED OFF
    struct values { int gyrox; int gyroy; int gyroz; uint16_t accelx; uint16_t accely; uint16_t accelz; };
    static values data;
    struct gyroValue{ int x; int y; int z; };


    //Update Data Values
    sensors_event_t event;
    gyro.getEvent(&event);
    gyroValue g = { event.gyro.x, event.gyro.y, event.gyro.z };
    a = Bean.getAcceleration();
    data = { g.x, g.y, g.z, a.xAxis, a.yAxis, a.zAxis };

    //Save Data and Set LED to Red
    saveData(data.gyrox, data.gyroy, data.gyroz, data.accelx, data.accely, data.accelz);
    Bean.setLed(255,0,0);

}

float batteryCheck(bool startUp) {
    int batteryPercentage = Bean.getBatteryLevel(); //Returns Level of Battery in Percent
    float actualBatteryVoltage = (Bean.getBatteryVoltage() / 100); // Finds Voltage Between 1.91V and 3.53V

    if(startUp == true){
      /* Sets LED According to Battery Level */
         if (batteryPercentage > 80) {
        Bean.setLed(0,255,0);
        }
        else if (batteryPercentage > 60) {
          Bean.setLed(255,255,0);
        }
        else if (batteryPercentage > 40) {
          Bean.setLed(255,150,0);
        }
        else if (batteryPercentage > 20) {
          Bean.setLed(255,75,0);
        }
        else {
          Bean.setLed(255,0,15);
        }

      /* Shows PowerState LED for 2s and then Turns off LED */
      delay(2000);
      Bean.setLed(0,0,0);
    }

    return actualBatteryVoltage;
}

void saveData(int gyrox, int gyroy, int gyroz, uint16_t accelx, uint16_t accely, uint16_t accelz){
   //If the file is available, write to it:
   if (!SD.begin(chipSelect)) { Serial.println("SD fail"); }
   File dataFile = SD.open("datalog.txt", FILE_WRITE);
   if (dataFile) {
      dataFile.print("Gyro: X =  ");
      dataFile.print(gyrox);
      dataFile.print(" Y =  ");
      dataFile.print(gyroy);
      dataFile.print(" Z =  ");
      dataFile.print(gyroz);
      dataFile.print(" Accel: X =  ");
      dataFile.print(accelx);
      dataFile.print(" Y =  ");
      dataFile.print(accely);
      dataFile.print(" Z =  ");
      dataFile.print(accelz);
      dataFile.println();
      dataFile.close();
    }

}

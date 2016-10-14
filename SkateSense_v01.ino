#include <Adafruit_L3GD20.h>; // Library for Gyroscope
#include <Wire.h>;

#define USE_I2C
  Adafruit_L3GD20 gyro;


void setup() {
  bool startup = true;
  Wire.begin();
  Serial.begin(57600);
  
  //Allows Bean to Detect Motion Events
  gyro.begin(gyro.L3DS20_RANGE_250DPS);
  if (!gyro.begin(gyro.L3DS20_RANGE_250DPS)){
    Serial.println("Oops ... unable to initialize the L3GD20. Check your wiring!");
    delay (1000);
  }
  Bean.enableMotionEvent(ANY_MOTION_EVENT);
  if(Bean.getAccelerometerPowerMode() != VALUE_NORMAL_MODE){
    Bean.setAccelerometerPowerMode(VALUE_NORMAL_MODE);
  }

  /* Check Battery Level on Startup */
  batteryCheck();

  //Print "Initilize Complete"
  Serial.println("Initialize Complete");
  delay(100);

  /* Get Connection State */
  bool bluetoothConnectionState;
  do {
    bluetoothConnectionState = Bean.getConnectionState();
    delay(10);
  } while(!bluetoothConnectionState);
  
  Bean.setLed(0,0,255);
  startup = false;
}

void loop() {
    bool startup = false;
    
    /* MAKE LOG - One Blink = One Update*/
    Bean.setLed(0,0,0); //Sets LED OFF
    
      gyro.read(); //Update Gyroscope Values
      int batteryLevel = Bean.getBatteryLevel(); 
        int xvalue1 = gyro.data.x;
        int yvalue1 = gyro.data.y;
        int zvalue1 = gyro.data.z;

      //Transmit Data within 200ms
      Bean.setLed(255,0,0); //Sets LED RED
      Serial.print("Gyro X = ");
      Serial.print(xvalue1);
      delay(50);
      Serial.print(" Gyro Y = ");
      Serial.print(yvalue1);
      delay(50);
      Serial.print(" Gyro Z = ");
      Serial.print(zvalue1);
      delay(50);
      Serial.print(" Battery Level = ");
      Serial.print(batteryLevel);
      Serial.println("");
      delay(50);
}
  
void batteryCheck() {
    //Declaring Variables
    int batteryPercentage = Bean.getBatteryLevel(); //Returns Level of Battery in Percent
    int batteryVoltage = Bean.getBatteryVoltage();
    float actualBatteryVoltage = (batteryVoltage / 100); // Creates Value Between 1.91V and 3.53V)
    
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
      /* Shows PowerState LED for 2s, Turns off LED and Moves On */
      delay(2000); 
      Bean.setLed(0,0,0);
      }


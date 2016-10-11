#include <Adafruit_L3GD20.h> // Library for Gyroscope

bool bluetoothConnectionState;
bool motionDetected;

Adafruit_L3GD20 gyro();

void setup(){
	//Allows Bean to Detect Motion Events
	Bean.enableMotionEvent(ANY_MOTION_EVENT);
	if(Bean.getAccelerometerPowerMode() != VALUE_NORMAL_MODE){
		Bean.setAccelerometerPowerMode(VALUE_NORMAL_MODE);
	}
	/* Check Battery Level on Startup */
	batteryCheck(int batteryPercentage, int batteryVoltage,float actualBatteryVoltage, int batteryCheckButtonStatus);

	/* Get Connection State */
	bluetoothConnectionState = Bean.getConnectionState();

	/* Wait for Bluetooth Connection */
	while(!bluetoothState){
		delay(1000)//Wait 1s
		bluetoothConnectionState = Bean.getConnectionState();
	}
		
}

void loop(){
	/* If Motion is Detected Start Log */
	detectMotion();
		if(!motionDetected){
			Bean.sleep(1000);
		}
	while(motionDetected){
		/* MAKE LOG */
			gyro.read(); //Updates Gyroscope Values

			/* Updates Data Array (MotionDetected,X,Y,Z) */
			logValues = {Bean.checkMotionEvent(ANY_MOTION_EVENT), gyro.data.x, gyro.data.y, gyro.data.z};

			/* Transmit Data */
			Serial.print(logValues)
			delay(100);

		/* After Log Update: Check if Board is Still Moving */
			detectMotion();

		/* If motion is not detected, wait 1s before checking again for 5s. */
				if(!motionDetected){
				Bean.sleep(1000);
				detectMotion() 

					if(!motionDetected){
					Bean.sleep(1000);
					detectMotion();

						if(!motionDetected){
						Bean.sleep(1000);
						detectMotion();

							if(!motionDetected){
							Bean.sleep(1000);
							detectMotion();

								if(!motionDetected){
								Bean.sleep(1000);
								detectMotion();
				}}}}}
				
			}
		}
	


void detectMotion(){
		if(Bean.checkMotionEvent(ANY_MOTION_EVENT)){
			motionDetected = true;
		}
		else if (!Bean.checkMotionEvent(ANY_MOTION_EVENT)){
			motionDetected = false;
		}
}
void batteryCheck(int batteryPercentage, int batteryVoltage,float actualBatteryVoltage, int batteryCheckButtonStatus){
		//Declaring Variables
		int batteryPercentage = Bean.getBatteryLevel; //Returns Level of Battery in Percent
		int batteryVoltage = Bean.getBatteryVoltage; //Returns Battery Voltage (191 - 353)
		float actualBatteryVoltage = batteryVoltage / 100; // Creates Value Between 1.91V and 3.53V)
		
			/* Checks Battery Level Range and Sets LED Accordingly */
			if (batteryPercentage > 80){
				Bean.setLed(0,255,0);
			}
				else if (batteryPercentage > 60){
					Bean.setLed(255,255,0)
				}
				else if (batteryPercentage > 40){
					Bean.setLed(255,150,0)
				}
				else if (batteryPercentage > 20){
					Bean.setLed(255,75,0)
				}
				else {
					Bean.setLed(255,0,15)
				}
			/* Shows PowerState LED for 2.5s, Turns off LED and Moves On */
			Bean.sleep(2500); 
			Bean.setLed(0,0,0);
}
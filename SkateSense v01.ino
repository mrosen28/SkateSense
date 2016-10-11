#include <Adafruit_L3GD20.h> // Library for Gyroscope

bool bluetoothState;
bool motionDetected;

void setup(){
	//Allows Bean to Detect Motion Events
	Bean.enableMotionEvent(ANY_MOTION_EVENT);
	if(Bean.getAccelerometerPowerMode() != VALUE_NORMAL_MODE){
		Bean.setAccelerometerPowerMode(VALUE_NORMAL_MODE);
	}


	//Serial Port Initialized Automatically
}

void loop(){
	/* Check Battery Level on Startup */
	batteryCheck(int batteryPercentage, int batteryVoltage,float actualBatteryVoltage, int batteryCheckButtonStatus);

	if(!bluetoothState){
		/* START ADVERTISING */
	}

	record();
		while(motionDetected){
			/* MAKE LOG */
			//After Log Update: Check if Board is Still Moving
			detectMotion();

			//If motion is not detected, wait 10s before checking again.
			if(!motionDetected){
				Bean.sleep(10000);
				detectMotion();

				//If motion isn't detected after second check, turn off SkateSense
				if(!motionDetected){
					/* Power Off */
				}
			}
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


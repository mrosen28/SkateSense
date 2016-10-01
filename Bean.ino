bool motionDetected = false;
void setup(){
	//Sets Pin 1 to an Input Pin
	const int batteryCheckButton = 1
	pinMode(batteryCheckButton, INPUT_PULLUP);
	batteryCheckButtonStatus = digitalRead(batteryCheckButton);

	//Allows Bean to Detect Motion Events
	Bean.enableMotionEvent(ANY_MOTION_EVENT);
	if(Bean.getAccelerometerPowerMode() != VALUE_NORMAL_MODE){
		Bean.setAccelerometerPowerMode(VALUE_NORMAL_MODE);
	}


	//Serial Port Initialized Automatically
}
void loop(){

	Record();
		while(motionDetected){
			/* INSERT CODE TO MAKE LOG */
		}

	void detectMotion(){
		if(Bean.checkMotionEvent(ANY_MOTION_EVENT) && !motionDetected){
			motionDetected = true;
		}
		else if (!Bean.checkMotionEvent && !motionDetected){
			motionDetected = false;
		}

	}

	battery(int batteryPercentage, int batteryVoltage,float actualBatteryVoltage, int batteryCheckButtonStatus);

}
	void battery(int batteryPercentage, int batteryVoltage,float actualBatteryVoltage, int batteryCheckButtonStatus){
		//Declaring Variables
		int batteryPercentage = Bean.getBatteryLevel; //Returns Level of Battery in Percent
		int batteryVoltage = Bean.getBatteryVoltage; //Returns Battery Voltage (191 - 353)
		float actualBatteryVoltage = batteryVoltage / 100; // Creates Value Between 1.91V and 3.53V)
	
		//When Battery Check Button Is Pressed Invoke Battery Blink Function
		while (batteryCheckButtonStatus == 1){
		batteryBlink(batteryPercentage);
		}
	}

		void batteryBlink (int batteryPercentage){
			//Checks Which Battery Range and Sets LED Accordingly
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

			Bean.sleep(2500); //Delays Bean+ for 2500ms (2.5s)
			Bean.setLed(0,0,0); //Turns off Led
}

#include <wiringARTIK.h>

#define ANALOG_PIN 0
#define PWM_PIN         2
#define PWM_ENABLE      1
#define PWM_DISABLE     0
#define PERIOD          1000000000

int main() {
	int SenVal;
	while(1) {
		SenVal=analogRead(ANALOG_PIN);
		if(SenVal>3000){
			pwmPin(PWM_PIN, PERIOD, 0, PWM_DISABLE);
		}
		else{
			pwmPin(PWM_PIN,PERIOD, 1000000000,PWM_ENABLE);
		}
	}
	return 0;
}

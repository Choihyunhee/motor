#include <wiringARTIK.h>

#define ANALOG_PIN 0
#define PWM_PIN         2
#define PWM_ENABLE      1
#define PWM_DISABLE     0
#define PERIOD          1000000000

int main(void) {
	float SenVal=0;
	float voltage=0;
	float temperature=0;
	while(1){
		SenVal= analogRead(ANALOG_PIN);
		voltage= SenVal/1000;
		temperature= -66.875+218.75*(voltage/5);
		if(temperature>20)
			pwmPin(PWM_PIN, PERIOD, 1000000000, PWM_ENABLE);
		else
			pwmPin(PWM_PIN, PERIOD, 0, PWM_DISABLE);

	}
	return 0;
}

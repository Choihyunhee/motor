#include <wiringARTIK.h>
#include "kbhit.h"

#define DIRECTION_PIN   128
#define ENABLE_PIN      129

//===== pin number ======
#define PWM_PIN         2
//=======================

#define PWM_ENABLE      1
#define PWM_DISABLE     0

#define INC_DEC         100000000  // increase or decrease
#define PERIOD          1000000000
 //nsec, 1ms

static int index=0;

int setup() {
    digitalPinMode(DIRECTION_PIN, OUTPUT);
    digitalPinMode(ENABLE_PIN, OUTPUT);

    digitalWrite(ENABLE_PIN, LOW);
}

void print_monitor(int duty_value) {
    int duty_ratio = 0;

    duty_ratio = (duty_value * 100) / PERIOD;

    printf("duty_value : %d\n", duty_value);
    printf("duty ratio : %d\n\n", duty_ratio);
    printf("====== PWM Test =======\n");
    printf("Please keyboard hit!!!!\n\n");

    if((index == 0) || (index == 1)) {
        printf("F : Forward Direction\n");
        printf("R : Reverse Direction\n");
        printf("Q : Exit\n");
    }

    else {
        printf("E : PWM Enable  & init\n");
        printf("Q : PWM Disable & exit\n");
        printf("I : PWM Increase\n");
        printf("D : PWM Decrease\n\n");
        printf("Duty Ratio (now) : %d\n", duty_ratio);
    }

    printf("=======================\n");
}

int main() {
    int loop=1;
    int ch=0;
    int pin_dir=0;
    int duty_cycle = 500000000;
    int direction = 2;

    setup();

    print_monitor(0);

	while(loop) {
        if(index == 0) {
            if(kbhit()) {
                pin_dir = getchar();
                index = 1;
            }
        }

        if(index == 1) {
            switch (pin_dir) {
                case 'f' :  // f : forward direction
                    direction = 1;
                    index = 2;

                    print_monitor(0);
                    break;

				case 'r' :  // r : reverse direction
                    direction = 0;
                    index = 2;

                    print_monitor(0);
                    break;

				case 'q' :  // q : exit
                    loop = 0;
                    break;
            }

            if(!pin_dir)    print_monitor(0);
        }

        if(index == 2) {
            if(kbhit())     ch = getchar();

            switch (ch) {
                case 'e' :  // e : enable & init
                    duty_cycle = 500000000;

                    digitalWrite(DIRECTION_PIN, direction);
                    pwmPin(PWM_PIN, PERIOD, duty_cycle, PWM_ENABLE);
                    printf("Pressed '%c'!\n", ch);
                    printf("PWM Enable\n");

                    index = 2;
                    print_monitor(duty_cycle);
                    break;

                case 'i' :  // i : inc
                    duty_cycle += INC_DEC;  // Max = 1000000

                    if(duty_cycle > PERIOD) duty_cycle = PERIOD;

                    digitalWrite(DIRECTION_PIN, direction);
                    pwmPin(PWM_PIN, PERIOD, duty_cycle, PWM_ENABLE);
                    printf("Pressed '%c'!\n", ch);
                    printf("PWM Increase\n");

                    index = 2;
                    print_monitor(duty_cycle);
                    break;

                case 'd' :  // d : dec
                    duty_cycle -= INC_DEC;  // Min = 200000

                    if(duty_cycle < (PERIOD / 5))   duty_cycle = (PERIOD / 5);

                    digitalWrite(DIRECTION_PIN, direction);
                    pwmPin(PWM_PIN, PERIOD, duty_cycle, PWM_ENABLE);
                    printf("Pressed '%c'!\n", ch);
                    printf("PWM Decrease\n");

                    index = 2;
                    print_monitor(duty_cycle);
                    break;

                case 'q' :  // q : disable & exit
                    pwmPin(PWM_PIN, PERIOD, 0, PWM_DISABLE);
                    printf("Pressed '%c'!\n", ch);
                    printf("PWM Disable & Exit\n");

                    index = 0;
                    print_monitor(0);
                    break;
            }

            ch = 0;
        }
    }

    return 0;
}

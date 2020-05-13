/******************************************************************************
 * The Mechatronics Revolution: Fundamentals and Core Concepts
 * Lab Assignment 3: MSP432 LaunchPad Example Project
 *
 * Description: An example project that uses DriverLib to
 * read LaunchPad's pushbuttons and turn on LEDs
 *
 * Revision: 1.0
 * Date: March 2020
*******************************************************************************/

/* DriverLib Include */
#include "driverlib.h"

/* Macros (could be moved to a header file) */
#define LED1_PIN            GPIO_PORT_P1,GPIO_PIN0
#define LEDR_PIN            GPIO_PORT_P2,GPIO_PIN0
#define LEDG_PIN            GPIO_PORT_P2,GPIO_PIN1
#define LEDB_PIN            GPIO_PORT_P2,GPIO_PIN2
#define BTN1_PIN            GPIO_PORT_P1,GPIO_PIN1
#define BTN2_PIN            GPIO_PORT_P1,GPIO_PIN4

/* Function prototype */
void lab3_initialization(void);


void main(void)
{
    int i;
    uint32_t counter = 0;
    bool flag = 0;

    WDT_A_holdTimer(); // stop watchdog timer

    /* GPIO initialization */
    lab3_initialization();

    while(1)
    {
        // Pushbutton 1 and LED 1
        if (MAP_GPIO_getInputPinValue(BTN1_PIN) == GPIO_INPUT_PIN_LOW)
        {
            MAP_GPIO_setOutputHighOnPin(LED1_PIN);

            for (i=0; i<10000; i++); // switch debouncing
        }
        else
        {
            MAP_GPIO_setOutputLowOnPin(LED1_PIN);
        }

        // Pushbutton 2 and LED 2
        if (MAP_GPIO_getInputPinValue(BTN2_PIN) == GPIO_INPUT_PIN_LOW)
        {
            if (counter % 3 == 0)
            {
                MAP_GPIO_setOutputHighOnPin(LEDR_PIN);
            }
            else if(counter % 3 == 1)
            {
                MAP_GPIO_setOutputHighOnPin(LEDG_PIN);
            }
            else if (counter % 3 == 2)
            {
                MAP_GPIO_setOutputHighOnPin(LEDB_PIN);
            }

            flag = 1;

            for (i=0; i<10000; i++); // switch debouncing
        }
        else
        {
            MAP_GPIO_setOutputLowOnPin(LEDR_PIN);
            MAP_GPIO_setOutputLowOnPin(LEDG_PIN);
            MAP_GPIO_setOutputLowOnPin(LEDB_PIN);

            if (flag == 1)
            {
                counter++;
                flag = 0;
            }
        }
    }
}

void lab3_initialization(void)
{
    /* GPIO configuration */
    MAP_GPIO_setAsInputPinWithPullUpResistor(BTN1_PIN);
    MAP_GPIO_setAsInputPinWithPullUpResistor(BTN2_PIN);

    MAP_GPIO_setAsOutputPin(LED1_PIN);
    MAP_GPIO_setAsOutputPin(LEDR_PIN);
    MAP_GPIO_setAsOutputPin(LEDG_PIN);
    MAP_GPIO_setAsOutputPin(LEDB_PIN);

    MAP_GPIO_setOutputLowOnPin(LED1_PIN);
    MAP_GPIO_setOutputLowOnPin(LEDR_PIN);
    MAP_GPIO_setOutputLowOnPin(LEDG_PIN);
    MAP_GPIO_setOutputLowOnPin(LEDB_PIN);
}

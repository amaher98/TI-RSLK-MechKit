/******************************************************************************
 * The Mechatronics Revolution: Fundamentals and Core Concepts
 * Lab Assignment 3: MSP432
 *
 * Description: The code uses DriverLib to
 * read LaunchPad's pushbuttons and turn on LEDs, and to use DriverLib
 * to turn on LED2 when any of the bump sensors is clicked.
 *
 * Author: Ahmed Ali (amaher98)
 * Revision: 1.0
 * Date: 13th May 2020
*******************************************************************************/

/* DriverLib Include */
#include "driverlib.h"
/* mechrev Include */ //AAli
#include "mechrev.h" //AAli

/* Macros (could be moved to a header file) */
#define LED1_PIN            GPIO_PORT_P1,GPIO_PIN0
#define LEDR_PIN            GPIO_PORT_P2,GPIO_PIN0
#define LEDG_PIN            GPIO_PORT_P2,GPIO_PIN1
#define LEDB_PIN            GPIO_PORT_P2,GPIO_PIN2
#define BTN1_PIN            GPIO_PORT_P1,GPIO_PIN1
#define BTN2_PIN            GPIO_PORT_P1,GPIO_PIN4

/* Function prototype */
void lab3_initialization(void);

volatile uint32_t counter = 0;

void main(void)
{
//    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN0 & GPIO_PIN2 & GPIO_PIN3 & GPIO_PIN4 & GPIO_PIN5 & GPIO_PIN6 & GPIO_PIN7);
//    GPIO_interruptEdgeSelect(GPIO_PORT_P4,GPIO_PIN0 & GPIO_PIN2 & GPIO_PIN3 & GPIO_PIN4 & GPIO_PIN5 & GPIO_PIN6 & GPIO_PIN7, GPIO_HIGH_TO_LOW_TRANSITION);
//    Interrupt_enableInterrupt(INT_PORT4);

    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN0);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4,GPIO_PIN0, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4,GPIO_PIN2, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN3);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4,GPIO_PIN3, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4,GPIO_PIN4, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4,GPIO_PIN5, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN6);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4,GPIO_PIN6, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN7);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4,GPIO_PIN7, GPIO_HIGH_TO_LOW_TRANSITION);

    Interrupt_enableInterrupt(INT_PORT4);


    int i;
//    bool flag = 0;

    WDT_A_holdTimer(); // stop watchdog timer

    mechrev_setup(); //AAli


    /* GPIO initialization */
    lab3_initialization();


    while(1)
    {
        // Pushbutton 1 or Pushbutton 2 and LED 1
        if ((MAP_GPIO_getInputPinValue(BTN1_PIN) == GPIO_INPUT_PIN_LOW) | (MAP_GPIO_getInputPinValue(BTN2_PIN) == GPIO_INPUT_PIN_LOW))
        {
            MAP_GPIO_setOutputHighOnPin(LED1_PIN);

            for (i=0; i<10000; i++); // switch debouncing
        }
        else
        {
            MAP_GPIO_setOutputLowOnPin(LED1_PIN);
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

// The code has an issue that the bump sensors connected to pins
// 4.5, 4.6, 4.7 do not trigger Interrupt more than one

void PORT4_IRQHandler(void)
{
    uint32_t status;
    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P4);
    //Verify that the interrupt is triggered by P4.0

    if (status & GPIO_PIN0)
    {
        counter++;
        MAP_GPIO_setOutputHighOnPin(LEDR_PIN);
    }
    if (status & GPIO_PIN7)
    {
        counter++;
        MAP_GPIO_setOutputHighOnPin(LEDR_PIN);
    }
    if (status & GPIO_PIN2)
    {
        counter++;
        MAP_GPIO_setOutputHighOnPin(LEDG_PIN);
    }
    if (status & GPIO_PIN6)
    {
        counter++;
        MAP_GPIO_setOutputHighOnPin(LEDG_PIN);
    }
    if (status & GPIO_PIN3)
    {
        counter++;
        MAP_GPIO_setOutputHighOnPin(LEDB_PIN);
    }
    if (status & GPIO_PIN5)
    {
        counter++;
        MAP_GPIO_setOutputHighOnPin(LEDB_PIN);
    }

    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P4, status);

}



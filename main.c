#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "Switch_Driver.h"

int main(void)
{

    volatile uint32_t ui32Loop;

    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //
    // Check if the peripheral access is enabled.
    //
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    /*intalize Buttons*/
    Switch_init();
    switch2_init();

    /*Make The Three Leds As OUTPUT*/
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);

    /*define three variables that defines button state*/
    uint8_t Led0_State = 0;
    uint8_t Led1_State = 0;
    uint8_t Led2_State = 0;

    uint8_t Button0_First = 0;
    uint8_t Button1_First = 0;
    uint8_t Button2_First = 0;

    /*Loop Forever*/
    while (1)
    {
        /*Read Status Of Switch Zero*/
        if (Switch0_Read() == 1)
        {
            if ((Led1_State == 0) || (Led2_State == 0))
            {
                if ((Led1_State == 0) && (Led2_State == 0))
                {
                    Button0_First = 1;
                }
                Led0_State = 1;
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            }
            else
            {
                if (Button1_First == 1)
                {
                    Button1_First = 0;
                    Button2_First = 1;

                    /*Turn off Led 1*/
                    Led1_State = 0;
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
                }
                else if (Button2_First == 1)
                {
                    Button2_First = 0;
                    Button1_First = 1;

                    /*Turn Off led2*/
                    Led2_State = 0;
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x0);
                }
            }
        }
        /*Read Status OF Switch One*/
        if (Switch1_Read() == 1)
        {
            if ((Led0_State == 0) || (Led2_State == 0))
            {
                if ((Led0_State == 0) && (Led2_State == 0))
                {
                    Button1_First = 1;
                }
                Led1_State = 1;
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
            }
            else
            {
                if (Button0_First == 1)
                {
                    Button0_First = 0;
                    Button2_First = 1;
                    /*Turn Off Led 0*/
                    Led0_State = 0;
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x0);
                }
                else if (Button2_First == 1)
                {
                    Button2_First = 0;
                    Button0_First = 1;
                    /*Turn Off led 2*/
                    Led2_State = 0;
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x0);
                }
            }
        }
        /*Read Status Of Switch Two*/
        if (Switch2_Read() == 1)
        {
            if ((Led0_State == 0) || (Led1_State == 0))
            {
                if ((Led0_State == 0) && (Led1_State == 0))
                {
                    Button2_First = 1;
                }
                Led2_State = 1;
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
            }
            else
            {
                if (Button0_First == 1)
                {
                    Button0_First = 0;
                    Button1_First = 1;

                    /*Turn Off Led 0*/
                    Led0_State = 0;
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x0);
                }
                else if (Button1_First == 1)
                {
                    Button1_First = 0;
                    Button0_First = 1;
                    /*Turn Off Led1*/
                    Led1_State = 0;
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
                }

            }
        }

    }
}

#include "lib/include.h"

void Delay(unsigned long counter);
void UART5_Transmitter(unsigned char data);
void printstring(char *str);
void UART5_init(void)
{
    SYSCTL->RCGCUART |= 0x20;   //Paso 1 (RCGCUART) pag.344 UARTEnable/modulo0 0->Disable 1->Enable
    SYSCTL->RCGCGPIO |= 0x10;     //Paso 2 (RCGCGPIO) pag.340  clock port D
    //(GPIOAFSEL) pag.671 Enable alternate function
    Delay(1);

    /* UART0 initialization */
    UART5->CTL = 0;         /* desabilitar modulo  */
    UART5->IBRD = 104;      /* for 9600 baud rate, integer = 104 */
    UART5->FBRD = 11;       /* for 9600 baud rate, fractional = 11*/
    UART5->CC = 0;          /*Selecciona reloj del sistema*/
    UART5->LCRH = 0x60;     /* data lenght 8-bit, not parity bit, no FIFO */
    UART5->CTL = 0x301;     /* Enable UART5 module, Rx and Tx */

    /* UART5 TX5 and RX5 use PE4 and PE5. Configure them digital and enable alternate function */
    GPIOE->DEN = 0x30;      /* set PE4 and PE5 as digital */
    GPIOE->AFSEL = 0x30;    /* Use PE4,PE5 alternate function */
    GPIOE->AMSEL = 0;    /* Turn off analg function*/
    GPIOE->PCTL = 0x00110000;     /* configure PE4 and PE5 for UART */
}
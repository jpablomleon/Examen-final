#include "lib/include.h"
/* TM4C123G Tiva C Series ADC Example */
/* This Program measures analog voltage by using ADC0 via interrupt method*/
/* TM4C123G ADC Interrupt Example */
#include <stdio.h>
void UART5_Transmitter(unsigned char data);
void printstring(char *str);
char mesg[12];
volatile float voltage;
volatile unsigned int adc_value;
void ADC0SS3_Handler(void)
{
    //UART FR flag pag 911//
    //UART DR data 906//
    int v;
    char c;
    while((UART0->FR & (1<<4)) != 0 );
    v = UART0->DR & 0xFF;
    c = v;
    return c;
}
extern void printChar(char c)
{
    while((UART0->FR & (1<<5)) != 0 );
    UART0->DR = c;
}
extern void printString(char* string)
{
    while(*string)
    {
        printChar(*(string++));
    }
}

extern char * readString(char delimitador)
{
    int i=0;
    char *string = (char *)calloc(10,sizeof(char));
    char c = readChar();
    while(c != delimitador)
    {
           *(string+i) = c;
              i++;
              if(i%10==0)
              {
                string = realloc(string,(i+10)*sizeof(char));
                }
       c = readChar();
   }

   return string;
}
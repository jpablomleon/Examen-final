/*
 * ADC.c
 *
 *  Created on: 08/02/2023
 *      Author: Juan
 */
#include "lib/include.h"

void Delay(unsigned long counter);
char mesg[12];
volatile float voltage;
volatile unsigned int adc_value;
void ADC0SS3_Handler(void){

    adc_value = ADC0->SSFIFO3; /* Lee la conversión ADC/
	ADC0->ISC = 8;          /* clear coversion clear flag bit*/
  ADC0->PSSI |= (1<<3);        /* Enable SS3 conversion or start sampling data from AN0 */


     //Pag 396 para inicializar el modulo de reloj del adc RCGCADC
    SYSCTL->RCGCADC |= (1<<0); 
    //Pag 382 (RGCGPIO) Puertos base habilitación del reloj
    //                     F     E      D       C      B     A
    SYSCTL->RCGCGPIO |= (1<<4);
    //Pag 760 (GPIODIR) Habilta los pines como I/O un cero para entrada y un uno para salida


    GPIOE_AHB->AFSEL |=  (1<<3);
    //(GPIODEN) pag.781 desabilita el modo digital
    GPIOE_AHB->DEN &= ~(1<<3);
    //Pag 787 GPIOPCTL registro combinado con el GPIOAFSEL y la tabla pag 1808
    GPIOE_AHB->AMSEL |= (1<<3);
    //Pag 1159 El registro (ADCPC) establece la velocidad de conversión por segundo


    ADC0->ACTSS &=  ~(1<<3);
    //Pag 1091 Este registro (ADCEMUX) selecciona el evento que activa la conversión (trigger)
    ADC0->EMUX &= ~0xF000;
    //Pag 1129 Este registro (ADCSSMUX3) define las entradas analógicas con el canal y secuenciador seleccionado
    ADC0->SSMUX3 = 0;
    //pag 868 Este registro (ADCSSCTL3), configura el bit de control de muestreo y la interrupción
    ADC0->SSCTL3 |= (1<<1) | (1<<2) ;


    /* Enable ADC Interrupt */
    ADC0->IM |= (1<<3); /* Unmask ADC0 sequence 2 interrupt pag 1082*/
    NVIC->ISER[0] =  0x00020000;
    //NVIC_EN0_R = 0x00010000;
    //Pag 1077 (ADCACTSS) Este registro controla la activación de los secuenciadores
    ADC0->ACTSS |= (1<<3);
    ADC0->PSSI |= (1<<3);

    while(1)
    {
       
			  /*Convertir el valor digital a voltage */
			 voltage = (adc_value * 0.0008);
			 sprintf(mesg, "\r\nVoltage = %0.3f Volts", voltage);
			 printstring(mesg);
      Delay(2000);
    }
}
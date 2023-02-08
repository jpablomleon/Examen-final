# Examen-final
Usando el módulo de transmisión asíncrono serial UART n y el convertidor analógico digital ADC.  Usar la función de manejo de interrupciones NVIC del ADC para leer el valor de conversión. De tal Forma que el valor leído sirva para habilitar el PWM a un ciclo de trabajo en función de un  porcentaje dado por el profesor.

Consideraciones. 
1.- Se Configurará la tarjeta a X MHZ
2.- Se configurara el GPIO X pin X de tal forma que al cambiar de estado de bajo a alto, se llame a 
una función de interrupción.
3.- Se iniciará la cuenta del temporizador 0 subtimer b de tal forma que cuente en modo ascendente 
dos segundos para iniciar la 
captura de datos del ADC.
4.- El ADC capturara durante 100 milisegundos (para esto se puede usar TIMER o retardo por SYSTICK
para limpiar el ADC) en un arreglo.
5.- Los valores capturados se enviarán por el protocolo de comunicación asíncrono serial a una 
interfaz (python o matlab) para su captura y procesamiento.
6.- El valor Capturado debería ser procesado en un algoritmo que sea capaz de comparar si la medida 
del valor máximo del convertidor es el (X)%, de ser así se enviara un dato por el protocolo de 
transmisión serial que inicie el ciclo de trabajo de uno de los PWM con dicho valor.

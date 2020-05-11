/*
 * Hecho por bVill
 * 
 * 
 */

/*  Ejemplo de control de una caldera para el ESP32
    Entradas: Sensor de flama en la terminal 12, 0 hay flama
    Salidas : Valvula de gas 0 abierta
              Generador de chispa 1 encendido
    Comienza con la valvula cerrada y el generador de chispa apagado 
    esprando 10 segundos a que se despeje cualquier gas que pueda haber 
    en el quemador. Si durante este tiempo se presenta flama, reinicia
    el tiempo de espera. Despues enciende la valvula de gas  y el 
    generador de chispa y espera tres segundos. Apaga el generador de 
    chispas y espera otros tres segundos. Finalmente, mientras haya
    flama mantiene la valvula de gas encendida y si en algun momento 
    detecta que no hay flama, apaga la valvula de gas y regresa a 
    esperar que los gases se disipen.
    * 
    * Este programa puede compilarse en el archivo blink.c del proyecto
    * blink del ESP-IDF
    * 
    * Ejemplo didactico
    * Hecho por Miguelangel Fraga Aguilar
    * Marzo de 2020
   
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

/* Puedes usar el menu de configuracion (idf.py menuconfig) para escoger 
 * la terminal correspondiente al led de la tarjeta que corresponde a
 * la valvula de gas
*/
#define BLINK_GPIO CONFIG_BLINK_GPIO
//Cabecera de la funcion de la maquina de estados
void caldera(void);

void app_main(void)
{
    //Asigna la terminal a la funcion de GPIO
    gpio_pad_select_gpio(BLINK_GPIO);
    //la configura amo salida
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    
    //Asigna la terminal 14 a la funcion de GPIO
    gpio_pad_select_gpio(GPIO_NUM_14);
    //la configura amo salida
    gpio_set_direction(GPIO_NUM_14, GPIO_MODE_OUTPUT);
    
    //Asigna la terminal a la funcion de GPIO
    gpio_pad_select_gpio(GPIO_NUM_12);
    //Configura la terminal 12 como entrada
    gpio_set_direction(GPIO_NUM_12, GPIO_MODE_INPUT);
    //Configura el Pull-UP
    gpio_set_pull_mode(GPIO_NUM_12,GPIO_PULLUP_ONLY);
    //Configura el Pull-Down
    //gpio_set_pull_mode(GPIO_NUM_12,GPIO_PULLDOWN_ONLY);
    
   //Apaga la valvula de gas y el generador de chispa
    gpio_set_level(BLINK_GPIO, 1);
    gpio_set_level(GPIO_NUM_14, 0);
    
    while(1) {
        //Llama a la función que implementa la maquina de estados 
        //del control de la caldera
        caldera();
        //Retardo de 1S
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        
   
    }
}



void caldera(void){
    static unsigned llamadas=0,etapa=0;
    llamadas++;
    switch(etapa){
    case 0: if(0==gpio_get_level(GPIO_NUM_12)) //Si hay flama
                llamadas=0;//Reinicia la espera
            if(10<=llamadas){
                etapa=1;
                llamadas=0;
                //Enciende la valvula de gas y la chispa
                gpio_set_level(BLINK_GPIO, 1);
                gpio_set_level(GPIO_NUM_14, 1);
            }
            break;
    case 1: if(3<=llamadas){
                etapa=2;
                llamadas=0;
                //Apaga el generador de chispa
                gpio_set_level(GPIO_NUM_14, 0);
            }
            break;
    case 2: if(3<=llamadas){
                etapa=3;
                llamadas=0;
            }
            break;
    case 3: if(0!=gpio_get_level(GPIO_NUM_12)){ //Si no hay flama
                etapa=0;
                llamadas=0;
                //Cierra la valvula de gas  
                gpio_set_level(BLINK_GPIO, 0);
            }
            break;

    }
}

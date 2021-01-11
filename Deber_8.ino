/*
 *    UNIVERSIDAD TECNICA DEL NORTE
 *    SISTEMAS EMBEBIDOS
 *    STEVEN FLORES 
 *    DEBER 8
 */
 


#include<avr/power.h>       //Librerias
#include<avr/sleep.h>      //Librerias
#include<avr/wdt.h>       //Librerias
#include<EEPROM.h>       //Librerias

int dato;            //variable 1
int i;              //variable 2 
//reset por lineas de programación

void (* resetFunc)(void)=0;
void setup(){
  //EEPROM.write(0,0);           Escritura de dato inicial, se realiza una sola vez 
  dato=EEPROM.read(0);          //Lectura del dato 0, para activacion del sistema completo
  Serial.begin(9600);          //Velocidad del cx
  if(dato==0){              //Condicion de activacion de metodo
    sistema();              //Activacion de metodo  
    EEPROM.write(1,0);     //Actualizacion dato auxiliar
    i=EEPROM.read(1);     //Lectura de dato auxiliar
  }else{
    i=EEPROM.read(1);    //LEctura de dato auxiliar
    i=i+1;               //Aumento de dato auxiliar
    EEPROM.update(1,i);  //Actualizacion dato auxiliar
  }
  if(i<15){           //Condicion de activacion del modo sleep (15*4 = 60 segundos)
  delay(100);        
  modo();           //Metodo de activacion de modo sleep
  }else{
    EEPROM.update(0,0);       //Actualizacion dato principal para el sistema
    wdt_enable(WDTO_15MS);   //Condicion reinicio del sistema.
  }
}
  void loop(){     
   
  }
void modo(){
    wdt_enable(WDTO_4S);     // modo sleep por 4 segundos
    set_sleep_mode(SLEEP_MODE_PWR_SAVE);  //Seleccion modo sleep
    sleep_enable();     //Activacion modo sleep
    sleep_mode();      //Funcionamiento modo sleep 
    sleep_disable();   //Desactivar modo sleep 
    wdt_disable();    //Desactivar perro guiardian
}
void sistema(){
  Serial.println("Iniciando Lectura");    //Mensaje de confirmacion de lectura cada 60 segundos
  Serial.println("El dato obtenido es :");   //Mensaje de informacion
  EEPROM.update(0,1);           //Actualizacion dato principal del sistema
  Serial.println(analogRead(0));      // Lectura del dato mediante puerto analogo
  Serial.println("Volviendo a modo Sleep");     //Informacion activacion modo sleep
  delay(100);     
}
void encender(){
  resetFunc();       //Funcion reiniciar arduino
}

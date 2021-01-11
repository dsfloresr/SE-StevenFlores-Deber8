/*
 *    UNIVERSIDAD TECNICA DEL NORTE
 *    SISTEMAS EMBEBIDOS
 *    STEVEN FLORES 
 *    DEBER 8
 */
 


#include<avr/power.h>
#include<avr/sleep.h>
#include<avr/wdt.h>
#include<EEPROM.h>

int dato;
int dato1;
int i;
//reset por lineas de programación

void (* resetFunc)(void)=0;
void setup(){
  //EEPROM.write(0,0);
  dato=EEPROM.read(0);
  Serial.begin(9600);
  if(dato==0){
    sistema();
    EEPROM.write(1,0);
    i=EEPROM.read(1);
  }else{
    i=EEPROM.read(1);
    i=i+1;
    EEPROM.update(1,i);
  }
  if(i<15){
  delay(100);
  modo();
  }else{
    EEPROM.update(0,0);
    wdt_enable(WDTO_15MS);
  }
}
  void loop(){     
  }
void modo(){
    wdt_enable(WDTO_4S);
    set_sleep_mode(SLEEP_MODE_PWR_SAVE);
    sleep_enable();
    sleep_mode();
    sleep_disable();
    wdt_disable();
}
void sistema(){
  Serial.println("Iniciando Lectura");
  Serial.println("El dato obtenido es :");
  EEPROM.update(0,1);
  Serial.println(analogRead(0));
  Serial.println("Volviendo a modo Sleep");
  delay(100);
}
void encender(){
  resetFunc();
}

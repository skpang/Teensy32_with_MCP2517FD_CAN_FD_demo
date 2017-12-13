/*
 * Teensy 3.2 with MCP2517FD CAN FD demo
 * 
 * 
 * 
 * 
 * v1.0 December 2017
 * 
 * skpang.co.uk
 * 
 */


#include "drv_canfdspi_api.h"
#include "drv_canfdspi_register.h"
#include "drv_canfdspi_defines.h"
#include "drv_spi.h"


int i;
int led = 13;
extern uint8_t txd[MAX_DATA_BYTES];
extern CAN_TX_MSGOBJ txObj;


void setup() {
  
  pinMode(led, OUTPUT); 
  digitalWrite(led, HIGH); 
  
  delay(1000);
  Serial.println(F("CAN Bus Tx test"));
  APP_CANFDSPI_Init(CAN_500K_2M);
  //
  
  digitalWrite(led, LOW);      
}


void loop() {

  digitalWrite(led, HIGH); 
  
  txObj.bF.ctrl.IDE = 0;
  txObj.bF.id.SID = 0x7df;
  txObj.bF.ctrl.BRS = 0;
  txObj.bF.ctrl.FDF = 1;
  txObj.bF.ctrl.DLC = 8;
  APP_TransmitMessageQueue();
  txd[7]= i++;
  
  delay(1);
  digitalWrite(led, LOW); 

  delay(1);

  if(digitalRead(int1_pin) == 0)
  {
    APP_ReceiveMessage_Tasks();
    
  }
  

  
}







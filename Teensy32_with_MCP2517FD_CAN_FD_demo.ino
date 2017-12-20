/*
 * Teensy 3.2 with MCP2517FD CAN FD demo
 * http://skpang.co.uk/catalog/mcp2517fd-can-fd-breakout-with-teensy-include-teensy-32-p-1549.html
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
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int i;

extern uint8_t txd[MAX_DATA_BYTES];
extern CAN_TX_MSGOBJ txObj;

#define OLED_RESET 5
Adafruit_SSD1306 display(OLED_RESET);
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


void setup() {
  
  
  delay(1000);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
    display.display();
  display.clearDisplay();
  display.setTextSize(0);
  display.setTextColor(WHITE);
  display.setCursor(0,15);
  display.println(" Teensy FD Demo");
  display.println(" ");
  display.println(" skpang.co.uk");
  display.println(" ");
  display.println(" 121/17");
  display.display();
  
    
  Serial.println(F("CAN Bus Tx test"));
  APP_CANFDSPI_Init(CAN_500K_2M);
  //
  
   
}


void loop() {


  
  txObj.bF.ctrl.IDE = 0;
  txObj.bF.id.SID = 0x7df;
  txObj.bF.ctrl.BRS = 0;
  txObj.bF.ctrl.FDF = 1;
  txObj.bF.ctrl.DLC = 8;
  APP_TransmitMessageQueue();
  txd[7]= i++;
  
 

  delay(1);

  if(digitalRead(int1_pin) == 0)
  {
    APP_ReceiveMessage_Tasks();
    
  }
  

  
}







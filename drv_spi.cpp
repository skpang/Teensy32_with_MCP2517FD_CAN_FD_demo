
#include <SPI.h> 
#include "drv_spi.h"


#include "drv_canfdspi_api.h"
// Receive Channels
#define APP_RX_FIFO CAN_FIFO_CH1
const int test_pin = 23;
 
SPISettings settingsA(20000000, MSBFIRST, SPI_MODE0);

void DRV_SPI_Initialize()

{
   pinMode (int_pin, INPUT);
   pinMode (int0_pin, INPUT);
   pinMode (int1_pin, INPUT);
   pinMode (slaveSelectPin, OUTPUT);
   
   digitalWrite(slaveSelectPin,HIGH); 

   SPI.setMISO(MISO_PIN);       // SCK on pin 14
   SPI.setSCK(CLK_PIN);       // SCK on pin 13
   SPI.setMOSI(MOSI_PIN);
   
   SPI.begin();
  // SPI.setClockDivider(SPI_CLOCK_DIV2);  
   Serial.println(F("DRV_SPI_Initialize"));

   
   pinMode (test_pin, OUTPUT);
   digitalWriteFast(test_pin,HIGH);
}



int8_t DRV_SPI_TransferData(uint8_t spiSlaveDeviceIndex, uint8_t *SpiTxData, uint8_t *SpiRxData, uint16_t spiTransferSize)
{
  uint8_t i;
      
  SPI.beginTransaction(settingsA);
  digitalWriteFast(slaveSelectPin,LOW);
  
  for(i=0;i<spiTransferSize;i++)
  {
      SpiRxData[i] = SPI.transfer(SpiTxData[i]); 
  }
 
  digitalWriteFast(slaveSelectPin,HIGH);
  SPI.endTransaction();

  return 0;
 
}

CAN_RX_FIFO_EVENT rxFlags;
extern CAN_RX_MSGOBJ rxObj;
extern uint8_t rxd[MAX_DATA_BYTES];


void APP_ReceiveMessage_Tasks(void)
{

  uint8_t dlc,i,rxstep;
 
  DRV_CANFDSPI_ReceiveChannelEventGet(DRV_CANFDSPI_INDEX_0, APP_RX_FIFO, &rxFlags);
  
  if (rxFlags & CAN_RX_FIFO_NOT_EMPTY_EVENT)
    {
      // Read the message
      DRV_CANFDSPI_ReceiveMessageGet(DRV_CANFDSPI_INDEX_0, APP_RX_FIFO, &rxObj, rxd, MAX_DATA_BYTES);
      dlc = DRV_CANFDSPI_DlcToDataBytes( (CAN_DLC) rxObj.bF.ctrl.DLC);
      // out_usb();
      
      digitalWriteFast(test_pin,LOW);
      Serial.print(rxObj.bF.id.SID, HEX);
      Serial.print(' '); 
      for(i=0;i<dlc;i++)
      {
        Serial.print(rxd[i], HEX);
      }
      Serial.println(' '); 
      digitalWriteFast(test_pin,HIGH);
    }


}


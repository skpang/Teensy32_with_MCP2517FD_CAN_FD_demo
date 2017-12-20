
#include <SPI.h> 
#include "drv_spi.h"


#include "drv_canfdspi_api.h"
// Receive Channels
#define APP_RX_FIFO CAN_FIFO_CH1


void DRV_SPI_Initialize()

{
   pinMode (int_pin, INPUT);
   pinMode (int0_pin, INPUT);
   pinMode (int1_pin, INPUT);
   pinMode (slaveSelectPin, OUTPUT);
   
   digitalWrite(slaveSelectPin,HIGH); 

   SPI.setMISO(12);       // SCK on pin 14
   SPI.setSCK(13);       // SCK on pin 13
   SPI.setMOSI(11);


/*
       SPI.setMISO(8);       // SCK on pin 14
   SPI.setSCK(14);       // SCK on pin 13
   SPI.setMOSI(7);
  */
    
   SPI.begin();
   SPI.setClockDivider(SPI_CLOCK_DIV2);  
   Serial.println(F("DRV_SPI_Initialize"));

}

int8_t DRV_SPI_TransferData(uint8_t spiSlaveDeviceIndex, uint8_t *SpiTxData, uint8_t *SpiRxData, uint16_t spiTransferSize)
{
  uint8_t i;
  uint8_t out;
 
 // SPI.beginTransaction(settingsA);
 // digitalWrite(slaveSelectPin,LOW);
  digitalWriteFast(slaveSelectPin,LOW);
  for(i=0;i<spiTransferSize;i++)
  {
      out = SpiTxData[i];
      SpiRxData[i] = SPI.transfer(out);    
  }
  digitalWriteFast(slaveSelectPin,HIGH);
  //digitalWrite(slaveSelectPin,HIGH);
 // SPI.endTransaction()

   
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
     Serial.print(rxObj.bF.id.SID, HEX);
     Serial.print(' '); 
      for(i=0;i<dlc;i++)
      {
        Serial.print(rxd[i], HEX);
      }
       Serial.println(' '); 
    }


}


#include "SPI_setting.h"
#include "GPIO_setting.h"
#include "stpMtr_drive.h"
#include "stm32f10x_spi.h"

#include <stdint.h>



int main(void)
{
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA,DISABLE);
  
  GPIO_conf(GPIOA,GPIO_Pin_4,GPIO_Speed_50MHz,GPIO_Mode_Out_PP);   //SPI1_NSS
  GPIO_conf(GPIOA,GPIO_Pin_5,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);   //SPI1_SCK
  GPIO_conf(GPIOA,GPIO_Pin_6,Input_Mode,GPIO_Mode_IPU);           //SPI1_MISO
  GPIO_conf(GPIOA,GPIO_Pin_7,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);   //SPI1_MOSI

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,DISABLE);
  
  SPI_conf(SPI1,SPI_Mode_Master,SPI_DataSize_8b,SPI_BaudRatePrescaler_2,SPI_FirstBit_LSB,idle0_1Edge);
  SPI_SSOutputCmd(SPI1,ENABLE);
  enableSPI(SPI1,ENABLE);

  uint8_t Drive1 = stdMtr_drive_conf(StpMtr_Clockwise,StpMtr_Slp_Off,StpMtr_Sixteenth_step);
  uint8_t Drive2 = stdMtr_drive_conf(StpMtr_Clockwise,StpMtr_Slp_Off,StpMtr_Full_step);
  uint8_t Drive3 = stdMtr_drive_conf(StpMtr_Clockwise,StpMtr_Slp_Off,StpMtr_Eighth_step);

   while(1)
    {
	   while( !SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) );
    	  SPI_I2S_SendData(SPI1,Drive3);

       while( !SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) );
          SPI_I2S_SendData(SPI1,Drive2);

       while( !SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) );
          SPI_I2S_SendData(SPI1,Drive1);

      outputData();
    }
}

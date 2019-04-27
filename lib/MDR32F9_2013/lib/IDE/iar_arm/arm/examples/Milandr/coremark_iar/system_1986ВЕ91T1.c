/******************************************************************************

 ******************************************************************************/


#include "1986be91t1.h"

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemFrequency variable.
 */
void SystemInit (void)
{
// Настраиваем максимаотную частоту и соответсвующий ускоритель Flash
        RST_CLK->PER_CLOCK = 0xFFFFFFFF;  // Включаем все клоки

       RST_CLK->HS_CONTROL = 0x00001;    // Запускаем HSE генератор
       while (RST_CLK->CLOCK_STATUS == 0x00){}; // Ждем готовности генератора
       RST_CLK->CPU_CLOCK = 3;                                  // Даем на вход PLL HSE/2 = 4 МГц

       RST_CLK->CPU_CLOCK = 3  | 0x01<<8;          // Переходим на HSE/2, F_CPU=4 МГц

       RST_CLK->UART_CLOCK = 0x02000000;               // Enable UART 2 UARTCLK = F_CPU/2
  
        PORTF->ANALOG  = (0x03);
        PORTF->PWR     = (0x0F);
        PORTF->FUNC    = (0x0F);

        UART2->IBRD  = 0x11;
        UART2->FBRD  = 0x17;
        UART2->LCR_H = 0x3<<5 | 0<<4;
        UART2->IFLS  = 0x00;
        UART2->CR    = 0x00;
        UART2->CR    = 0x06 << 7 | 1;
        EEPROM->CMD  = 0x0<<3;
        EEPROM->CNTRL= 0x3;


        RST_CLK->TIM_CLOCK = 0x0100000F;
        TIMER1->ARR = 0xffff;
        TIMER1->PSG = 3125;
        TIMER1->CNTRL = 0x001;




}


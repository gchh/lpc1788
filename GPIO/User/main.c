#include "system_LPC177x_8x.h"
#include "lpc177x_8x_gpio.h"
#include "lpc177x_8x_systick.h"

void delay(__IO uint32_t delay_cnt);

int main(void)
{
    uint8_t value;
    
    //SysTick_Config(SystemCoreClock/1000);
    SYSTICK_InternalInit(1); //1ms
    NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1); //31最低优先级
    SYSTICK_IntCmd(ENABLE);
    SYSTICK_Cmd(ENABLE);
    
   
    GPIO_SetDir(0, 0x00000003, 1); //P0.0输出
    GPIO_SetValue(0, 0x00000003); //P0.0=1
    value=0;

    while(1)
    {
        GPIO_OutputValue(0, 0x00000003, value);
        value=!value;
        delay(500);
    }
}

__IO uint32_t uwTick;
void SysTick_Handler(void)
{
    uwTick++;
}

void delay(__IO uint32_t delay_cnt)//delay_cnt in 1ms
{
   uint32_t tickstart = uwTick;
   uint32_t wait = delay_cnt;

   /* Add a period to guarantee minimum wait */
   if (wait < 0xFFFFFFFF)
   {
      wait++;
   }
  
   while((uwTick-tickstart)<wait){}
}


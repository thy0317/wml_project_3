#include "stm32f10x.h"
#include "sys_time.h"
#include "led.h"
#include "key.h"
#include "uart.h"
#include "di.h"

int main(void)
{
    uint32_t index = 0;
    uint32_t host_time = 0;
    uint32_t current_ticks = 0;

    SysTickInit(1000); /* 1ms */
    Uart1Init();
    LedInit();
    KeyInit();
    DiInit();

    current_ticks = GetSysTick();
    while (1) {
        if (KeyTask() == kPressed) { // 按下复位键
            current_ticks = GetSysTick();
            host_time = 0;
            Uart1Send(11); // 发送11指令
        }

        if ((GetSysTick() - current_ticks) > host_time) {
            LedOff();
            if (DiScan(&index) == 1) { // 传感器有信号
                current_ticks = GetSysTick();
                host_time = time[index] * 1000;
                Uart1Send(index + 1); // 发送对应指令
                LedOn(); // led指示灯亮
            }
        }
    }
}

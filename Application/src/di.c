#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "di.h"

uint32_t RCC_APB2Periph[] = {DI1_CLK, DI2_CLK, DI3_CLK, DI4_CLK, DI5_CLK, DI6_CLK};
uint16_t GPIO_Pinx[] = {DI1_PIN, DI2_PIN, DI3_PIN, DI4_PIN, DI5_PIN, DI6_PIN};
GPIO_TypeDef *GPIOx[] = {DI1_PORT, DI2_PORT, DI3_PORT, DI4_PORT, DI5_PORT, DI6_PORT};
uint32_t time[] = {DI1_TIME, DI2_TIME, DI3_TIME, DI4_TIME, DI5_TIME, DI6_TIME};

void DiInit(void)
{
    GPIO_InitTypeDef di_init;

    for (int i = 0; i < 6; i++) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph[i], ENABLE);

        di_init.GPIO_Pin = GPIO_Pinx[i];
        di_init.GPIO_Mode = GPIO_Mode_IPU;
        di_init.GPIO_Speed = GPIO_Speed_10MHz;
        GPIO_Init(GPIOx[i], &di_init);
    }
}

uint32_t DiScan(uint32_t *index)
{
    for (int i = 0; i < 6; i++) {
        if (GPIO_ReadInputDataBit(GPIOx[i], GPIO_Pinx[i]) == RESET) {
            *index = i;
            return 1;
        }
    }

    return 0;
}

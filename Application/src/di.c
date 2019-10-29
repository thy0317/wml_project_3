#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "di.h"
#include "sys_time.h"

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

typedef struct {
    uint32_t ticks;
    uint8_t di_state;
    uint8_t state;
} di_t;

di_t di[6] = {0};

uint8_t ReadDi(uint32_t index)
{
    return GPIO_ReadInputDataBit(GPIOx[index], GPIO_Pinx[index]);
}

uint8_t DiState(uint32_t index)
{
    unsigned int current_tick = GetSysTick();
    uint8_t read_di = ReadDi(index);

    switch (di[index].state) {
        case 0: {
            if (read_di == Bit_RESET) {
                di[index].ticks = current_tick;
                di[index].state = 1;
            }
        } break;
        case 1: {
            if (read_di == Bit_RESET) {
                if ((current_tick - di[index].ticks) > (1000 * SCAN_TIME)) {
                    di[index].state = 2;
                    di[index].di_state = 1;
                }
            }
            else {
                di[index].state = 0;
            }
        } break;
        case 2: {
            if (read_di == Bit_SET) {
                di[index].state = 0;
                di[index].di_state = 0;
            }
        } break;
        default: {
            di[index].state = 0;
            di[index].di_state = 0;
        } break;
    }

    return di[index].di_state;
}

void DiReset(void)
{
    for (int i = 0; i < 6; i++) {
        di[i].state = 0;
        di[i].di_state = 0;
    }
}

uint32_t DiScan(uint32_t *index)
{
    for (int i = 0; i < 6; i++) {
        if (DiState(i) == 1) {
            *index = i;
            return 1;
        }
    }

    return 0;
}

#ifndef __DI_H
#define __DI_H

#define DI1_CLK     RCC_APB2Periph_GPIOB    // 传感器1所接引脚时钟
#define DI1_PORT    GPIOB                   // 传感器1所接引脚端口号
#define DI1_PIN     GPIO_Pin_1              // 传感器1所接引脚号
#define DI1_TIME    10                      // 传感器1保持时间 单位-秒

#define DI2_CLK     RCC_APB2Periph_GPIOB
#define DI2_PORT    GPIOB
#define DI2_PIN     GPIO_Pin_1
#define DI2_TIME    10

#define DI3_CLK     RCC_APB2Periph_GPIOB
#define DI3_PORT    GPIOB
#define DI3_PIN     GPIO_Pin_1
#define DI3_TIME    10

#define DI4_CLK     RCC_APB2Periph_GPIOB
#define DI4_PORT    GPIOB
#define DI4_PIN     GPIO_Pin_1
#define DI4_TIME    10

#define DI5_CLK     RCC_APB2Periph_GPIOB
#define DI5_PORT    GPIOB
#define DI5_PIN     GPIO_Pin_1
#define DI5_TIME    10

#define DI6_CLK     RCC_APB2Periph_GPIOB
#define DI6_PORT    GPIOB
#define DI6_PIN     GPIO_Pin_1
#define DI6_TIME    10

#define SCAN_TIME   1    // 检测时间 单位-秒

extern uint32_t time[];

void DiInit(void);
void DiReset(void);
uint32_t DiScan(uint32_t *index);

#endif

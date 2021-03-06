/**
 * @brief 实现DHT11温湿度传感器数据的读取
 * 
 * ***************************************************************************
 * @attention
 * 
 * DHT11应用说明：                                      
 * 1. 供电电压3-5.5V，传感器上电后要等待1s以越过不稳定状态，    
 * 在此期间无需发送任何指令
 * 
 * 2. 通信过程：总线空闲状态为高电平,主机把总线拉低等待DHT11响应,
 * 主机把总线拉低必须大于18毫秒,保证DHT11能检测到起始信号。
 * DHT11接收到主机的开始信号后,等待主机开始信号结束,然后发送80us低电平响应信号.
 * 主机发送开始信号结束后,延时等待20-40us后,读取DHT11的响应信号,
 * 主机发送开始信号后,可以切换到输入模式,或者输出高电平均可,总线由上拉电阻拉高。
 * 
 * 3. 读取到的数据格式：(一次完整的数据传输为40bit,高位先出。)
 * 8bit湿度整数数据 + 8bit湿度小数数据 + 8bit温度整数数据 +
 * 8bit温度小数数据 + 8bit校验和
 * 校验和： “ 8bit湿度整数数据 + 8bit湿度小数数据 +
 * 8bit温度整数数据 + 8bit温度小数数据 ” 所得结果的末8位。
 * 
 * 4. DHT11和MCU之间的接线：
 * 
 *               +5V  |  --->  | Pin1: VDD  
 *                A8  |  --->  | Pin2: DATA
 *  MCU Board         |        | Pin3: NC 悬空
 *               GND  |  --->  | Pin4: GND
 * 
 * ***************************************************************************
 **/

#include "main.h"
#include "dht11.h"

extern uint8_t temperature, humidity;
extern uint8_t frac_hum, frac_temp;
extern TIM_HandleTypeDef htim3;

// /**
//  * @brief 利用NOP进行微秒级延时
//  * @param nus
//  * 
//  */
// void DHT11Delayus(uint16_t nus)
// {
//     __IO uint32_t tmp = nus * HAL_RCC_GetHCLKFreq() / 1000000U;
//     do
//     {
//         __NOP();
//     } 
//     while (tmp--);
// }

/**
 * @brief 用定时器TIM3实现的微秒级延时
 * @param nus
 * @note nus不能超过49999
 */
void TIM3Delayus(uint16_t nus)
{
    __HAL_TIM_SET_COUNTER(&htim3, 0);
    while (__HAL_TIM_GET_COUNTER(&htim3) < nus);
}



/**
 * @brief 主机GPIO模式切换
 * @param mode 输入 or 输出模式
 * @arg MODE_INPUT, MODE_OUTPUT
 */
void DHT11GPIOModeSwitch(uint8_t mode)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = DHT11_DATA_Pin;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    if(mode == MODE_INPUT)
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    else if(mode == MODE_OUTPUT)
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    
    HAL_GPIO_Init(DHT11_DATA_GPIO_Port, &GPIO_InitStruct);
}

/**
 * @brief 启动传输
 * 主机发送低电平信号开始传输,维持20ms,
 * 随后主机切换至输入模式,DHT响应信号拉低后拉高,最后拉低代表数据传输开始
 * @retval DHT11State
 */
DHT11State DHT11Start(void)
{
    /* GPIO Output Push Pull Mode, 拉低作为开始信号 */
    if (HAL_GPIO_ReadPin(DHT11_DATA_GPIO_Port, DHT11_DATA_Pin) != GPIO_PIN_SET)
        return ERR_BUSBUSY;
    else
    {
        DHT11GPIOModeSwitch(MODE_OUTPUT);
        HAL_GPIO_WritePin(DHT11_DATA_GPIO_Port, DHT11_DATA_Pin, RESET);
        /* 延迟20ms保证DHT11能检测到起始信号 */
        TIM3Delayus(20000);
        DHT11GPIOModeSwitch(MODE_INPUT);
        /* 等待30us读DHT11的响应信号 */
        TIM3Delayus(30);
        if (HAL_GPIO_ReadPin(DHT11_DATA_GPIO_Port, DHT11_DATA_Pin) != GPIO_PIN_RESET)
            return ERR_NORESPONSE;

        while(HAL_GPIO_ReadPin(DHT11_DATA_GPIO_Port, DHT11_DATA_Pin) != GPIO_PIN_SET);
        TIM3Delayus(85);
        
        if (HAL_GPIO_ReadPin(DHT11_DATA_GPIO_Port, DHT11_DATA_Pin) != GPIO_PIN_RESET)
            return ERR_RESPONSETIMING;
        /* 此时数据传输开始 */
        else
            return OK_RESPONSE;   
    }
}

/**
 * @brief 接收数据并作校验
 * @attention 高位先出
 * @retval DHT11 transmition state
 * 
 */
DHT11State DHT11ReceiveAndCheck(void)
{
    uint8_t cnt, tmp[5] = {0, 0, 0, 0, 0};
    uint8_t status;

    for (cnt = 0; cnt < 40; cnt++)
    {
        /* 与上升沿对齐 */
        while(HAL_GPIO_ReadPin(DHT11_DATA_GPIO_Port, DHT11_DATA_Pin) != GPIO_PIN_SET);
        /* 延迟40us以后还是高电平说明接收到'1', 低电平说明接收到'0' */
        TIM3Delayus(40);
        status = HAL_GPIO_ReadPin(DHT11_DATA_GPIO_Port, DHT11_DATA_Pin) & 0X01;
        /* 湿度整数,湿度小数,温度整数,温度小数,校验和 */
        tmp[cnt / 8] |= (((uint8_t)status) << (7 - cnt % 8));
        if (HAL_GPIO_ReadPin(DHT11_DATA_GPIO_Port, DHT11_DATA_Pin) == GPIO_PIN_SET)
        {   
            /* 针对读到'1'的情况 */
            __HAL_TIM_SET_COUNTER(&htim3, 0);
            while(HAL_GPIO_ReadPin(DHT11_DATA_GPIO_Port, DHT11_DATA_Pin) != GPIO_PIN_RESET)
            {
                if (__HAL_TIM_GET_COUNTER(&htim3) >= MAX_WAIT_TIME)
                    return ERR_DATATIMEOUT;
            }   
        }
    }

    if (tmp[4] == tmp[0] + tmp[1] + tmp[2] + tmp[3])
    {
        humidity = tmp[0];
        frac_hum = tmp[1];
        temperature = tmp[2];
        frac_temp = tmp[3];
        return OK_CHECK;
    }
    else
        return ERR_CHECK;
}



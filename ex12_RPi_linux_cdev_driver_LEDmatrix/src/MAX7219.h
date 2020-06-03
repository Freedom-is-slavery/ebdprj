#define GPIO_DIN                1
#define GPIO_LOAD               4
#define GPIO_CLK                5

#define REG_NOOP                0X00
#define REG_DIGIT0              0X01
#define REG_DIGIT1              0X02
#define REG_DIGIT2              0X03
#define REG_DIGIT3              0X04
#define REG_DIGIT4              0X05
#define REG_DIGIT5              0X06
#define REG_DIGIT6              0X07
#define REG_DIGIT7              0X08
#define REG_DECODE_MODE         0X09
#define REG_INTENSITY           0X0A
#define REG_SCANLIMIT           0X0B
#define REG_SHUTDOWN            0X0C
#define REG_DISPLAYTEST         0X0F

#define LIGHT_MAX               0X0F
#define NORMAL_OPERATION        0X01
#define NO_DECODE               0X00
#define SCAN_8BIT               0X07
#define FORBID_TEST             0X00

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

void RPi_GPIO_Init(void);
void MAX7219_Init(void);
void MAX7219_Write(uint8_t addr, uint8_t data);
void MAX7219_WriteByte(uint8_t data);
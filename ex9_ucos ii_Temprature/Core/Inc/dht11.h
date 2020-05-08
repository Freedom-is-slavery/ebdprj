/**
 * @brief dht11.c所包含的头文件
 */

#define MODE_INPUT          1
#define MODE_OUTPUT         2

#define OK_RESPONSE         1
#define ERR_NORESPONSE      2
#define ERR_CHECK           3
#define OK_CHECK            4
#define ERR_DATATIMEOUT     5
#define ERR_BUSBUSY         6
#define ERR_RESPONSETIMING  7

#define MAX_WAIT_TIME       500       

typedef uint8_t DHT11State;

DHT11State DHT11Start(void);
void DHT11GPIOModeSwitch(uint8_t mode);
DHT11State DHT11ReceiveAndCheck(void);
void TIM3Delayus(uint16_t nus);

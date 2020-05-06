/**
 * @brief dht11.c所包含的头文件
 */

#define MODE_INPUT      1
#define MODE_OUTPUT     2

void DHT11Start(void);
void DHT11GPIOModeSwitch(uint8_t mode);
void DHT11ReceiveAndCheck(void);

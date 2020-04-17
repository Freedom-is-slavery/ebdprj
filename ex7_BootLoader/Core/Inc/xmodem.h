/*
 * xmodem.h
 */

#include "main.h"

void xmodem_receive(uint8_t *pbuf);
uint8_t calsum(const uint8_t *ptr, int16_t size);
uint16_t calcrc(const uint8_t *ptr, int16_t size);
void xmodem_delay200us(void);

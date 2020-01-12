/**
 * @file mcp.h
 * @author Erwin lejeune (erwin.lejeune15@gmail.com)
 * @brief Header file for API
 * @version 0.1
 * @date 2020-01-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef mcph
#define mcph

#define IODIRA 0x0
#define IODIRB 0x1
#define IPOLA  0x2
#define IPOLB  0x3
#define GPINTENA 0x4
#define GPINTENB 0x5
#define DEFVALA 0x6
#define DEFVALB 0x7
#define INTCONA 0x8
#define INTCONB 0x9
#define IOCONA 0xA
#define IOCONB 0xB
#define GPPUA 0xC
#define GPPUB 0xD
#define INTFA 0xE
#define INTFB 0xF
#define INTCAPA 0x10
#define INTCAPB 0x11
#define MCP_GPIOA 0x12
#define MCP_GPIOB 0x13
#define OLATA 0x14
#define OLATB 0x15

#include <stdint.h>
#include "spi.h"

typedef void (*mcpCallBack)();

class mcp23s17
{
    public:
    mcp23s17();

    enum port { PORTA, PORTB};
    enum mode { OUTPUT, INPUT, INPUT_PULLUP };
    enum itType { RISING , FALLING , BOTH };

    void writeReg(uint8_t reg , uint8_t val);
    uint8_t readReg (uint8_t reg);

    void setBitInReg ( uint8_t reg , uint8_t bitNum );
    void clearBitInReg ( uint8_t reg , uint8_t bitNum );

    void begin();
    int pinMode(port p, unsigned char bitNum, mode m);
    void digitalWrite(port p, unsigned char bitNum, bool value);
    uint8_t readBits(port p);

    void attachInterrupt(port p, uint8_t bitNum, itType type, mcpCallback callback);
};

extern mcp23s17 ioExt;

#endif
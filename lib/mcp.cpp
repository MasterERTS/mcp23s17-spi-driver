/**
 * @file mcp.cpp
 * @author Erwin lejeune (erwin.lejeune15@gmail.com)
 * @brief API class for the SPI driver
 * @version 0.1
 * @date 2020-01-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "mcp.h"

mcp23s17::mcp23s17() {}

void mcp23s17::writeReg(uint8_t reg , uint8_t val) {
    beginTransaction();
    transfer8(0x40);
    transfer8(reg);
    transfer8(val);
    endTransaction();
}

uint8_t mcp23s17::readReg(uint8_t reg) {
    beginTransaction();
    transfer8(0x41);
    transfer8(reg);
    uint8_t val = transfer8(0);
    endTransaction();
    return val;
}

void mcp23s17::setBitInReg(uint8_t reg, uint8_t bitNum) {
    uint8_t val = readReg(reg);
    val |= 1 << bitNum;
    writeReg(reg, val);
}

void mcp23s17::clearBitInReg(uint8_t reg , uint8_t bitNum) {
    uint8_t val = readReg(reg);
    val &= ~(1 << bitNum);
    writeReg(reg, val);
}

void mcp23s17::begin() {
    setupSPI();
}

int mcp23s17::pinMode(port p, unsigned char bitNum, mode m) {
    if (p == PORTA) {
        switch(m) {
            case INPUT :
                setBitInReg(IODIRA, bitNum);
                break;
            case OUTPUT :
                clearBitInReg(IODIRA, bitNum);
                break;
            case INPUT_PULLUP :
                setBitInReg(IODIRA, bitNum);
                setBitInReg(GPPUA, bitNum);
                break;
        }
    } else if (p == PORTB) {
        switch(m) {
            case INPUT :
                setBitInReg(IODIRB, bitNum);
                break;
            case OUTPUT :
                clearBitInReg(IODIRB, bitNum);
                break;
            case INPUT_PULLUP :
                setBitInReg(IODIRB, bitNum);
                setBitInReg(GPPUB, bitNum);
                break;
        }
    }

    return 0;
}

void mcp23s17::digitalWrite(port p, unsigned char bitNum, bool value) {
    if (p == PORTA) {
        if (value == 0) {
            clearBitInReg(MCP_GPIOA, bitNum);
        } else {
            setBitInReg(MCP_GPIOA, bitNum);
        }
    }
    else if (p == PORTB) {
        if(value == 0) {
            clearBitInReg(MCP_GPIOB, bitNum);
        } else {
            setBitInReg(MCP_GPIOB, bitNum);
        }
    }
}

uint8_t mcp23s17::readBits(port p) {
    uint8_t val;
    if (p == PORTA) {
        val = readReg(MCP_GPIOA);
    } else if (p == PORTB) {
        val = readReg(MCP_GPIOB);
    }
    return val;
}

// WIP
void attachInterrupt(port p, uint8_t bitNum, itType type, mcpCallback callback) {
    setBitInReg(GPINTENB, bitNum);
    setBitInReg(DEFVALB, bitNum);
    setBitInReg(INTCONB, bitNum);

    mcpCallback interruptTable[8];

    interruptTable[bitNum] = callback;
}
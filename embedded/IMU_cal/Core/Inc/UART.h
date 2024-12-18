#ifndef UART_H
#define UART_H

#include "main.h"
#include <cstdint>
#include <cstring> // For memcpy

class UART {
private:
	UART_HandleTypeDef *uartHandle;
    const uint8_t maxMessageSize = 0xFF; // Maximum message size

public:
    // Constructor to initialize the UART handle
    UART(UART_HandleTypeDef *huart);

    // Method to send raw data
    bool sendData(const uint8_t *data, uint16_t size);

    // Method to receive raw data (blocking)
    bool receiveData(uint8_t *data, uint16_t size, uint32_t timeout);

    // Method to send a structured message
    bool sendMessage(uint8_t address, const uint8_t *payload, uint8_t payloadSize);
};

#endif // UART_H

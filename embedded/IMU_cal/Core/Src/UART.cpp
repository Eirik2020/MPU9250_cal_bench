#include "UART.h"

// Constructor implementation
UART::UART(UART_HandleTypeDef *huart) : uartHandle(huart) {}

// Method to send raw data
bool UART::sendData(const uint8_t *data, uint16_t size) {
    // HAL_UART_Transmit returns HAL_OK on success
    return HAL_UART_Transmit(uartHandle, const_cast<uint8_t *>(data), size, HAL_MAX_DELAY) == HAL_OK;
}

// Method to receive raw data (blocking)
bool UART::receiveData(uint8_t *data, uint16_t size, uint32_t timeout) {
    // HAL_UART_Receive returns HAL_OK on success
    return HAL_UART_Receive(uartHandle, data, size, timeout) == HAL_OK;
}

// Method to send a structured message
bool UART::sendMessage(uint8_t address, const uint8_t *payload, uint8_t payloadSize) {
    // Ensure payload size does not exceed the limit
    if (payloadSize > (maxMessageSize - 4)) { // 4 bytes for start, address, size, end
        // Handle error: payload too large
        return false;
    }

    // Create a message buffer
    uint8_t message[maxMessageSize];

    // Populate the message
    message[0] = 0x7E;                   // Start byte
    message[1] = address;                 // Address byte
    message[2] = payloadSize;             // Number of payloads
    memcpy(&message[3], payload, payloadSize); // Copy payload into the buffer
    message[3 + payloadSize] = 0x7F;       // End byte

    // Use the sendData method to send the message
    return sendData(message, 4 + payloadSize);
}

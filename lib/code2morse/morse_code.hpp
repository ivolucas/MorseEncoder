#ifndef morse_code_h
#define morse_code_h

#include "Arduino.h"

const uint8_t CODE_DOT = 0b01;
const uint8_t CODE_DASH = 0b11;

#define MORSECODE_LETERS_START 0x20
#define MORSECODE_LETERS_END 0x7A
#define MORSECODE_BUFFER_SIZE 255
// morsecode
const uint16_t MORSECODE_LETERS[] = {
    0b00,             // SPACE
    0b111101110111,   // !
    0b011101011101,   // "
    0b00,             // #
    0b11010111010101, // $
    0b00,             // %
    0b00,             // &
    0b00,             // '
    0b00,             // (
    0b00,             // )
    0b00,             // *
    0b00,             // +
    0b111101011111,   // ,
    0b00,             // -
    0b110111011101,   // .
    0b00,             // /
    0b1111111111,     // 0
    0b1111111101,     // 1
    0b1111110101,     // 2
    0b1111010101,     // 3
    0b1101010101,     // 4
    0b0101010101,     // 5
    0b0101010111,     // 6
    0b0101011111,     // 7
    0b0101111111,     // 8
    0b0111111111,     // 9
    0b00,             // :
    0b00,             // ;
    0b00,             // <
    0b00,             // =
    0b00,             // >
    0b00,             // ?
    0b00,             // @
    0b00001101,       // A
    0b01010111,       // B
    0b01110111,       // C
    0b00010111,       // D
    0b00000001,       // E
    0b01110101,       // F
    0b00011111,       // G
    0b01010101,       // H
    0b00000101,       // I
    0b11111101,       // J
    0b00110111,       // K
    0b01011101,       // L
    0b00001111,       // M
    0b00000111,       // N
    0b00111111,       // O
    0b01111101,       // P
    0b11011111,       // Q
    0b00011101,       // R
    0b00010101,       // S
    0b00000011,       // T
    0b00110101,       // U
    0b11010101,       // V
    0b00111101,       // W
    0b11010111,       // X
    0b11110111,       // Y
    0b01011111,       // Z
    0b00,             // [
    0b00,             //
    0b00,             // ]
    0b00,             // ^
    0b00,             // _
    0b00,             // `
    0b00001101,       // A
    0b01010111,       // B
    0b01110111,       // C
    0b00010111,       // D
    0b00000001,       // E
    0b01110101,       // F
    0b00011111,       // G
    0b01010101,       // H
    0b00000101,       // I
    0b11111101,       // J
    0b00110111,       // K
    0b01011101,       // L
    0b00001111,       // M
    0b00000111,       // N
    0b00111111,       // O
    0b01111101,       // P
    0b11011111,       // Q
    0b00011101,       // R
    0b00010101,       // S
    0b00000011,       // T
    0b00110101,       // U
    0b11010101,       // V
    0b00111101,       // W
    0b11010111,       // X
    0b11110111,       // Y
    0b01011111,       // Z
};

class MorseCodeWriter
{
public:
    MorseCodeWriter(const uint8_t pin, const uint16_t did_lengt)
    {
        _pin = pin;
        _did_lengt = did_lengt;
        pinMode(_pin, OUTPUT);
        digitalWrite(_pin, LOW);
    }

    void queue(const char *str)
    {
        pointer = NULL;
        if (strlen(str) < MORSECODE_BUFFER_SIZE)
            strcpy(this->buffer, str);
        else
            strlcpy(this->buffer, str, MORSECODE_BUFFER_SIZE);
        pointer = this->buffer;
    }

    void writeLoop()
    {
        while (pointer != NULL && *pointer != '\0')
        {
            char leter = *pointer;
            pointer++; // set pointer to next leter now

            if (leter >= MORSECODE_LETERS_START && leter <= MORSECODE_LETERS_END)
            {
                current_simb = MORSECODE_LETERS[leter - MORSECODE_LETERS_START];
            }
            else
            {
                current_simb = 0b0; // Do an space
            }
            
            if (current_simb == 0b0) // if a space
            {
                delay(7 * _did_lengt);
            }
            else
            {
                while (current_simb > 0)
                {
                    u_int16_t duration = current_simb & 0b11;
                    digitalWrite(_pin, HIGH);
                    delay(duration * _did_lengt);
                    digitalWrite(_pin, LOW);
                    delay(_did_lengt);
                    current_simb = current_simb >> 2;
                }
                delay(2 * _did_lengt); // 1+2 did lenght
            }
        }
        pointer=NULL;
    }

protected:
    char buffer[MORSECODE_BUFFER_SIZE];
    char *pointer;
    uint8_t _pin;
    uint16_t _did_lengt;
    u_int16_t current_simb = 0;
};
#endif
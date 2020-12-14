#include <Arduino.h>

#include "Phy.h"

void inline send_bit(char bit)
{
    digitalWrite(12, bit);
    delay(1);
}

void send_frame(char payload[], int len)
{
    // Add preamble
    for (int i = 0; i < PREAMBLE_LEN; i += 2)
    {
        send_bit(0);
        send_bit(1);
    }

    // Start symbol
    int digit = 1 << (START_SYM_LEN - 1);
    while (digit)
    {
        send_bit(START_SYM & digit);
        digit >>= 1;
    }

    // Length
    digit = 1 << (PACKET_LENGTH_LEN - 1);
    while (digit)
    {
        send_bit(len & digit);
        digit >>= 1;
    }

    // Add payload
    for (int j = 0; j < len; j++)
    {
        int digit = 0x80;
        while (digit)
        {
            send_bit(payload[j] & digit);
            digit >>= 1;
        }
    }
    return;
}

int send(char payload[], int len)
{
    if (len > MAX_DATA_LEN)
        return -1;
    send_frame(payload, len);
    return 1;
}

static inline char read_char()
{
    char recv = 0;
    for (int i = 0; i < 8; i++)
    {
        recv = recv << 1;
        recv = recv | (digitalRead(12) & 0x1);
        delay(1);
    }
    return recv;
}

int recv(char message[])
{
    char curr = 0;

    while (curr != START_SYM)
    {
        curr = curr << 1;
        curr = curr | (digitalRead(12) & 0x1);
        delay(1);
    }

    int length = (int)read_char();
    for (int i = 0; i < length; i++)
    {
        message[i] = read_char();
    }

    return length;
}
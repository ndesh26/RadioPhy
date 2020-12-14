const int MAX_DATA_LEN = 255;
const int PREAMBLE_LEN = 12;
const int START_SYM_LEN = 8;
const int CRC_LEN = 8;
const int PACKET_LENGTH_LEN = 8;
const int START_SYM = 0x33;
const int MAX_FRAME_LEN = PREAMBLE_LEN + START_SYM_LEN + PACKET_LENGTH_LEN + 8*13 + CRC_LEN;

enum CurrState {
    Preamble,
    StartSym,
    Length,
    Payload,
    Crc,
};

int send(char payload[], int len);
int recv(char message[]);
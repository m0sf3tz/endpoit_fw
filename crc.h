#pragma once

unsigned crc8(unsigned crc, unsigned char *data, int len);
unsigned short crc16_ccitt(unsigned char *buf, int len);

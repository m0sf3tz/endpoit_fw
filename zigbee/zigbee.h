#include <stdbool.h>

bool ZIGBEE_DOZE(void);
bool ZIGBEE_WAKE(void);
bool initZigbeeGpioPins(void);

void zigbeeWrite(const char * dat, int len);
void zigbeeWriteDebug(const char * dat, int len);
//these guys de-init the pins for the zigbee - don't confuse w/ doze 
//called when power domain is turned off.
bool zigbeeWake(void);
bool zigbeeSleep(void);


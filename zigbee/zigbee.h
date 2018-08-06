#include <stdbool.h>

bool ZIGBEE_DOZE(void);
bool ZIGBEE_WAKE(void);
bool initZigbeeGpioPins(void);

void zigbeeWrite(const char * dat, int len);

/*
- To send one sectore will consume 1.28V
- VCAP reading from ADC of (0x213E == 5.96V)
- Current FW will begin sampling once we have     4.0V (0x164F) saved up
- Current FW will begin transmitting once we have 5.5V (0x1EAD) saved up
*/
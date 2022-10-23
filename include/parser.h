#ifndef _COMMANDPARSER
#define _COMMANDPARSER

#include <Arduino.h>

#define head1 0xAA
#define head2 0x55
#define receiveType_velocity 0x11
#define receiveType_pid      0x12
#define receiveType_params   0x13

#define rBUFFER_SIZE 11   // receive buffer 's length
#define sBUFFER_SIZE 27   // send buffer 's length

/*
 * parser command from master computer
 */
void parse_rvelcommnad(uint8_t* rcommand, float& vel, float& angular);

#endif // _COMMANDPARSER
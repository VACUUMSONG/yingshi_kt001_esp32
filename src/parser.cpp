#include "parser.h"

typedef union{
    uint8_t ivalue[2];
    int16_t i16value;
} uint_union;

/**
 * parse vel command received
 **/
void parse_rvelcommnad(uint8_t* rcommand, float& vel, float& angular)
{
    uint_union vel_, angular_;
    vel_.ivalue[0] = rcommand[5];
    vel_.ivalue[1] = rcommand[4];
    
    angular_.ivalue[0] = rcommand[9];
    angular_.ivalue[1] = rcommand[8];
    vel = (float)(vel_.i16value / 1000);
    angular = (float)(angular_.i16value / 1000);
}

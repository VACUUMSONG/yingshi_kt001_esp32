#include <Arduino.h>

void IsBig_Endian()
{
    unsigned short test = 0x1234;
    if(*( (unsigned char*) &test ) == 0x12)
      //  return True;
      Serial.println("Big end");
   else
      Serial.println("Small end");
}//IsBig_Endian()


void setup() {
    Serial.begin(115200);     
}
 
void loop() {
  IsBig_Endian();
}
 
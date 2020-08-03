// https://qiita.com/iigura/items/034ef2fcf12bdb57fd63
// https://qiita.com/UT-HACKs/items/540e9dddcd1d2d8b2be2

#include <Wire.h>

#define ADDR 0x04
#define Register 1

int potpin = 0; 
int val = 0;

void setup(void)
{
  Serial.begin(19200);
  
  Wire.begin(ADDR); //アドレスを8に設定
//  pinMode(PIN,OUTPUT);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop(void)
{
  //ここでは何もしない
}
int ind = 0;
int data[2] = {0};
void receiveEvent(int inNumOfRecvBytes)
{
//  data[0] = 0;
//  data[1] = 0;
  while(Wire.available())
  {
    data[ind] = Wire.read();
    ind++;
  }
  if(ind > 1)
  {
    Serial.print(data[0]); Serial.print(",");
    Serial.println(data[1]); // print the integer
    ind = 0;
  }
}

void requestEvent()
{
  val =  analogRead(potpin);
//  Serial.println(val);
  byte data[2];
  data[0] = byte(val);
  data[1] = byte(val>>8);
  
  Wire.write(data, 2);
}

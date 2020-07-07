// https://qiita.com/iigura/items/034ef2fcf12bdb57fd63
// https://qiita.com/UT-HACKs/items/540e9dddcd1d2d8b2be2

#include <Wire.h>

#define ADDR 0x04
#define PIN  13

void setup(void)
{
  Wire.begin(ADDR); //アドレスを8に設定
  pinMode(PIN,OUTPUT);
  Wire.onReceive(receiveEvent); // register event
//  Wire.onReceive(myReadLine); //割り込み関数の指定
}

void loop(void)
{
  //ここでは何もしない。
  delay(100);
}

void receiveEvent(int howMany)
{
  int c;
  if(Wire.available()) c = (int)Wire.read();
  if(c==1)
  {
    digitalWrite(13,HIGH);
//    Serial.println("HIGH"); // print the integer
  }
  else if(c==0)
  {
    digitalWrite(13,LOW);
//    Serial.println("LOW"); // print the integer
  }
}

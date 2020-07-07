#include <Wire.h>
// https://qiita.com/iigura/items/034ef2fcf12bdb57fd63

const int I2C_SLAVE_ADDRESS = 0x04;

void setup(void)
{
  Serial.begin(9600);  // Arduino IDE にあるシリアルモニタのデフォルト通信速度

  // I2C Inti
  Wire.begin(I2C_SLAVE_ADDRESS);
  Wire.onReceive(onRecv);

  Serial.print("STARTUP -- OUT\n");  // 正常に setup できたことを通知
}

void loop(void)
{
  // empty
}

static char gBuf[255];

void onRecv(int inNumOfRecvBytes)
{
  sprintf(gBuf,"NumOfBytes=%d : ",inNumOfRecvBytes);
  Serial.print(gBuf);

  while(Wire.available()>0) {
    unsigned char c=Wire.read();
    sprintf(gBuf,"%02X ",c);  // Serial には printf がないので、一度文字列に出力する
    Serial.print(gBuf);
  }
  Serial.print("\n");
}

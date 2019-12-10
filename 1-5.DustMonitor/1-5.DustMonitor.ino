#include <Arduino.h>
#include <pms.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
Pmsx003 pms(34, 32);

void setup(void) {
	Serial.begin(115200);
	while (!Serial) {};
	Serial.println("Pmsx003");

	pms.begin();
	pms.waitForData(Pmsx003::wakeupTime);
	pms.write(Pmsx003::cmdModeActive);

  u8g2.begin();
}

auto lastRead = millis();

void loop(void) {
  char pm1[4];
  char pm2_5[4];
  char pm10[4];
  const auto n = Pmsx003::Reserved;
  Pmsx003::pmsData data[n];
  Pmsx003::PmsStatus status = pms.read(data, n);

  itoa(data[3],pm1,10);
  itoa(data[4],pm2_5,10);
  itoa(data[5],pm10,10);
  
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.drawStr(25,10,"Dust Monitor");
  u8g2.drawStr(25,30,"PM1.0 : ");
  u8g2.drawStr(80,30,pm1);  // write something to the internal memory
  u8g2.drawStr(25,40,"PM2.5 : ");
  u8g2.drawStr(80,40,pm2_5);
  u8g2.drawStr(25,50,"PM10  : ");
  u8g2.drawStr(80,50,pm10);
  u8g2.sendBuffer();          // transfer internal memory to the display

  switch (status) {
    case Pmsx003::OK:
    {
      auto newRead = millis();
      Serial.print("Wait time ");
      Serial.println(newRead - lastRead);
      lastRead = newRead;

      // For loop starts from 3
      // Skip the first three data (PM1dot0CF1, PM2dot5CF1, PM10CF1)
      for (size_t i = Pmsx003::PM1dot0; i < n; ++i) { 
        Serial.print(data[i]);
        Serial.print("\t");
        Serial.print(Pmsx003::dataNames[i]);
        Serial.print(" [");
        Serial.print(Pmsx003::metrics[i]);
        Serial.print("]");
        Serial.println();
      }
      break;
    }
    case Pmsx003::noData:
      break;
    default:
      Serial.println(Pmsx003::errorMsg[status]);
  };
}

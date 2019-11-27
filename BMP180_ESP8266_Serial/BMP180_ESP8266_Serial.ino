/*
* author: lvdinh
* https://xcode.vn
* 2019/11/26
* v0.0.1
*
*	BMP180 SCL <-> D1 ESP8266
*	BMP180 SDA <-> D2 ESP8266
*/

#include <Adafruit_BMP085.h>
#define rate 0.010197162129779 //pa -> cm H2O

int32_t offset = 101284;	//áp suất trên mặt nước

Adafruit_BMP085 bmp;
int32_t pa;

void setup()
{
	Serial.begin(115200);
	Serial.println("begin");
	while (!bmp.begin())
	{
		Serial.println("Cannot start sensor!");
		delay(1000);
	}
}

void loop()
{
	if (Serial.available())
	{
		String str = Serial.readStringUntil('\n');
		if (str == "reset")
		{
			offset = pa;
			Serial.printf("Reset: %d\n", offset);
		}
	}

	pa = bmp.readPressure();
	float cm = (pa - offset) * rate;
	Serial.printf("Pressure: %d pa, Water level: %f cm\n", pa, cm);
	delay(500);
}
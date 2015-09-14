#include "SparkTime.h"

UDP UDPClient;
SparkTime rtc;
unsigned long currentTime;
unsigned long lastTime = 0UL;
String timeStr;

void sendData(String time) {
	int length = time.length();

	Serial1.write("t");
	Serial.print("t");
	for(int i = 0; i < length; i++) {
		Serial.print(time[i]);
		Serial1.write(time[i]);
	}
	Serial1.write("A");
	Serial.println("A");
}

void setup() {
	rtc.begin(&UDPClient, "north-america.pool.ntp.org");
	rtc.setTimeZone(-5);

	Serial.begin(9600);
	Serial1.begin(9600);
	delay(100);
}

void loop() {
	// Serial.println("work!");
	currentTime = rtc.now();
	String timeData = "";
	timeData += rtc.hourString(currentTime);
	timeData += rtc.minuteString(currentTime);
	Serial.println(timeData);
	sendData(timeData);

	Serial1.write("t");
	String hour = rtc.hourString(currentTime);
	for (int i = 0; i < hour.length(); i++) {
		Serial.println(hour[i]);
		Serial1.write(hour[i]);
	}
	String minute = rtc.minuteString(currentTime);
	for (int i = 0; i < minute.length(); i++) {
		Serial.println(minute[i]);
		Serial1.write(minute[i]);
	}
	Serial1.write("A");

	// sendData(rtc.hourString(currentTime));
	// timeData += rtc.minuteString(currentTime);
	// timeData += "A";

	delay(500);
	// sendData(timeData);
	Serial.println("work!");
	// Serial.println(timeData);

	// timeStr = "";
	// timeStr += rtc.minuteString(currentTime);
	// Serial.println(timeStr);
	// Serial.println("blah");

	// int x = Serial.available() - 1;
	//
	// if (x > 0) {
	// 	char inByte[x];
	// 	for (int i = 0; i < x; i++) {
	// 		inByte[i] = Serial.read();
	// 	}
	//
	// 	for(int i = 0; i < x; i++) {
	// 		Serial.print(inByte[i]);
	// 		Serial1.write(inByte[i]);
	// 	}
	//
	// 	Serial.println("");
	// 	Serial.read();
	// }

	// if (currentTime != lastTime) {
	// 	// sendData(timeStr);
	// 	// lastTime = currentTime;
	// }
	delay(100);
}

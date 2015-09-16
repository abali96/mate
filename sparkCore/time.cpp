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

void parseWeather(const char *name, const char *data) {
	Serial1.write("w");
	Serial.println("w");
	String json = String(data);
	int index = json.indexOf("\"id\":");
	String weather_code_str = json.substring(index+5, index+8);
	int weather_code = atoi(weather_code_str);
	if (weather_code <= 232) {
		Serial1.write("3");
		Serial.println("3");
	} else if (weather_code <= 522) {
		Serial1.write("2");
		Serial.println("2");
	} else if (weather_code <= 621) {
		Serial1.write("4");
		Serial.println("4");
	} else if (weather_code <= 801) {
		Serial1.write("0");
		Serial.println("0");
	} else if (weather_code <= 804) {
		Serial1.write("1");
		Serial.println("1");
	}
	Serial1.write("A");
	Serial.println("A");
	Serial.println("weather!");
}

void setup() {
	rtc.begin(&UDPClient, "north-america.pool.ntp.org");
	rtc.setTimeZone(-5);

	Spark.subscribe("hook-response/get_weather", parseWeather, MY_DEVICES);

	Serial.begin(9600);
	Serial1.begin(9600);
	delay(100);
}

void loop() {
	// Spark.publish("get_weather");
	// Serial.println("work!");
	// delay(5000);
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

	delay(500);
	Serial.println("work!");
	delay(100);
}

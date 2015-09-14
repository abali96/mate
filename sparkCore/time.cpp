#include "SparkTime.h"
#include "HttpClient.h"

UDP UDPClient;
SparkTime rtc;
unsigned long currentTime;
unsigned long lastTime = 0UL;
String timeStr;

HttpClient http;
http_header_t headers[] = {
	{"Accept", "*/*"},
	{"Accept", "*/*"}
};

http_request_t request;
http_response_t response;

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
	request.hostname = "www.timeapi.org";
	request.port = 80;
	request.path = "/utc/now";

	// The library also supports sending a body with your request:
	//request.body = "{\"key\":\"value\"}";

	// Get request
	http.get(request, response, headers);
	Serial.print("Application>\tResponse status: ");
	Serial.println(response.status);

	Serial.print("Application>\tHTTP Response Body: ");
	Serial.println(response.body);



	// currentTime = rtc.now();
	// String timeData = "";
	// timeData += rtc.hourString(currentTime);
	// timeData += rtc.minuteString(currentTime);
	// Serial.println(timeData);
	// sendData(timeData);
	//
	// Serial1.write("t");
	// String hour = rtc.hourString(currentTime);
	// for (int i = 0; i < hour.length(); i++) {
	// 	Serial.println(hour[i]);
	// 	Serial1.write(hour[i]);
	// }
	// String minute = rtc.minuteString(currentTime);
	// for (int i = 0; i < minute.length(); i++) {
	// 	Serial.println(minute[i]);
	// 	Serial1.write(minute[i]);
	// }
	// Serial1.write("A");
	//
	// delay(500);
	// Serial.println("work!");
	// delay(100);
}

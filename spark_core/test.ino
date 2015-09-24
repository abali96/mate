void setup() {
    Serial.begin(115200);
    Serial1.begin(9600);

    // Create our webhooks. These webhooks are pointed at our server.
    Spark.subscribe("hook-response/get_weather", gotWeatherData, MY_DEVICES);
    Spark.subscribe("hook-response/get_time", gotTimeData, MY_DEVICES);
    Spark.subscribe("hook-response/get_stocks", gotStocksData, MY_DEVICES);
    // On startup, we want to get these two things right away.
    Spark.publish("get_time");
    Spark.publish("get_weather");
    Spark.publish("get_stocks");
}


void loop() {
    // Get time data
    Spark.publish("get_time");
    delay(5000);

    // Get time data
    Spark.publish("get_weather");
    delay(5000);

    Spark.publish("get_stocks");
    delay(5000);
}

// This function will get called when weather data comes in
void gotWeatherData(const char *name, const char *data) {
    String str = String(data);
    for (int i = 0; i < str.length(); i++) {
      Serial.print(str[i]);
      Serial1.write(str[i]);
    }
    Serial.println("");
}

void gotTimeData(const char *name, const char*data) {
    String str = String(data);
    for (int i = 0; i < str.length(); i++) {
      Serial.print(str[i]);
      Serial1.write(str[i]);
    }
    Serial.println("");
}

void gotStocksData(const char *name, const char*data) {
  String str = String(data);
  for (int i = 0; i < str.length(); i++) {
    Serial.print(str[i]);
    Serial1.write(str[i]);
  }
  Serial.println("");
}

#include <WiFi.h>
#include "time.h"
#include "sntp.h"

#include "systemConfig.h"

#include <HTTPClient.h>
#include <ArduinoJson.h>

//Delete
#include "temporary.h"
const char* time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";

bool wifiConnection(){
    bool succeed = true;

    if(WiFi.status() != WL_CONNECTED){
        Serial.printf("Connecting to %s ", ssid);
        WiFi.begin(ssid, password);

        uint8_t connectionTry = 0;
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");

            if(connectionTry > maxConnectionRetry){
                succeed != succeed;
                break;
            }
        }
    }

    return succeed;
}

bool syncDateTime(){
    bool succeed = true;

    struct tm dateInfo;
    uint8_t NTPTry = 0;

    sntp_servermode_dhcp(1);

    configTzTime(time_zone, ntpServer1, ntpServer2);

    if(!wifiConnection()) return !succeed;

    Serial.println("Getting date from NTP server.");

    while(!getLocalTime(&dateInfo)){
        Serial.print(".");
        if(NTPTry > maxNTPTry){
            succeed != succeed;
            break;
        };
        delay(500);
    }

    return succeed;
}

void getDateTime(struct tm *dateInfo){
  sntp_servermode_dhcp(1);
  configTzTime(time_zone, ntpServer1, ntpServer2);
  getLocalTime(dateInfo);
}




void getCurrentWeather(struct currenWeatherData *data){
  WiFiClient client;
  HTTPClient http;

  JsonDocument doc;

  //Build API request
  std::string serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode +"&APPID=" + openWeatherMapApiKey + "&units=metric";
  String jsonBuffer = "{}";

  Serial.println("Requesting info");

  // Get data from API
  http.begin(client, serverPath.c_str());

  int httpResponseCode = http.GET();

  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    jsonBuffer = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);

    return;
  }
  // Free resources
  http.end();

  /////////////////////////////////////////////

  Serial.println(jsonBuffer);

  DeserializationError error = deserializeJson(doc, jsonBuffer);
  if (error) {
    Serial.println(F("jsonBuffer.parseObject() failed"));
    return;
  }

  const char * icon = doc["weather"][0]["icon"];
  Serial.println(icon);
  data->temperature = doc["main"][F("temp")];
  data->humidity = doc["main"]["humidity"];
  data->windSpeed = doc["wind"]["speed"];
  data->windDir = doc["wind"]["deg"];

}


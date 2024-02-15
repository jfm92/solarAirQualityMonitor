#include <WiFi.h>
#include "time.h"
#include "sntp.h"

#include "systemConfig.h"

//Delete
#include "temporary.h"

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
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);

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
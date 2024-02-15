#pragma once

/************************ Display pin config ************************/
#define EPD_CS 7
#define EPD_MOSI 6
#define EPD_SCK 4
#define EPD_BUSY 3
#define EPD_RES 2
#define EPD_DC 1

/************************ WiFi config ************************/

const uint8_t maxConnectionRetry = 10;


/************************ NTP config - Temporary ************************/
//This should be configured on web config 
const char* ntpServer1 = "pool.ntp.org"; 
const char* ntpServer2 = "time.nist.gov";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
const uint8_t maxNTPTry = 10;
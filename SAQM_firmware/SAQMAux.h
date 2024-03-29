#pragma once

#include <vector>
#include <map>
#include <string>

/************************ Hour and date config ************************/
std::vector<std::string> monthListEng = {"January", "February", "Mar", "Apr", "May","Jun","Jul","Aug","Sep","Oct", "Nov", "Dec"};
std::vector<std::string> monthListESP = {"Enero", "Febrero", "Mar", "Abr", "May","Jun","Jul","Ago","Sep","Oct", "Nov", "Dic"};

std::map<std::string, std::vector<std::string>> monthList = {{"ESP", monthListESP}, {"ENG", monthListEng}};

struct hourDateBox{
    uint16_t primaryFontSize = 24; //FreeSansBold24pt7b
    uint16_t secondaryFontSize = 9; //FreeSans9pt7b
    uint16_t X = 0;
    uint16_t Y = 0;
    uint16_t cursorY = Y + primaryFontSize + 15; //15 is a magic number to adapt to a specific place
    uint16_t dateXOffset = 5;
    uint16_t dateYOffset = primaryFontSize + secondaryFontSize - 15; // 15 is also magic number
    uint16_t Width = 150;
    uint16_t Height = (primaryFontSize * 2) + (secondaryFontSize * 2) - 5; //
} hourDateBox;

/************************ Envioromental config ************************/

struct envioromentalBox{
    uint16_t primaryFontSize = 9; //FreeSans9pt7b
    uint16_t X = 196;
    uint16_t Y = 0;
    uint16_t Width = 100;
    uint16_t Height = 128;
    uint16_t cursorY = Y + primaryFontSize + 6;
    
} envioromentalBox;

struct BME680readings{
    float temperature = 0.0;
    uint32_t pressure = 0;
    float humidity = 0.0;
    std::string airQualityLevel = "NoNe";
};


/************************ Forecast config ************************/

struct forecastBox{
    uint16_t primaryFontSize = 24; //FreeSansBold24pt7b
    uint16_t X = 0;
    uint16_t Y = 66;
    uint16_t Width = 150;
    uint16_t Height = 62;
    uint16_t cursorY = Y + primaryFontSize * 2;
    uint16_t cursorX = X;
    uint16_t offsetDataWind = 96;
    uint16_t iconOffsetX = 8;
    uint16_t iconOffsetY = 35;
    
} forecastBox;

struct currenWeatherData{
    int temperature = 0;
    uint32_t pressure = 0;
    uint8_t humidity = 0;
    uint16_t windDir = 0;
    uint8_t windSpeed = 0;
    uint8_t iconCode = 0;
};

std::vector<std::string> windDirectionENG = {"N", "NE", "E", "SE", "SE","S","SW","W","NW"};
std::vector<std::string> windDirectionESP = {"N", "NE", "E", "SE", "SE","S","SO","O","NO"};

std::map<std::string, std::vector<std::string>> windDirection = {{"ESP", windDirectionESP}, {"ENG", windDirectionENG}};
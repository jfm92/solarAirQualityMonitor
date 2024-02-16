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
    float temperature;
    uint32_t pressure;
    float humidity;
    std::string airQualityLevel;
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
    
} forecastBox;

struct forecastData{
    float temperature;
    uint32_t pressure;
    float humidity;
    std::string airQualityLevel;
};
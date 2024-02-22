#include <string>
#include <sstream> 
#include <map>

#include <GxEPD2_BW.h>
#include "systemConfig.h"
#include "SAQMAux.h"
#include "icons.h"

#include <Fonts/FreeSansBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>

#include "time.h"

GxEPD2_BW<GxEPD2_290_BS, GxEPD2_290_BS::HEIGHT> display(GxEPD2_290_BS(EPD_CS,  EPD_DC,  EPD_RES, EPD_BUSY));

void EPDInit(bool clearDisplay){
    display.init(115200,clearDisplay, clearDisplay ? 10 : 2,true);
    display.setRotation(1);

    if(!clearDisplay){
        //After deep sleep wake up, the first thing that you print will be blurry,
        //so to avoid on important data, we print a little dot on the corner
        display.setPartialWindow(0, 0, 1, 1);
        display.firstPage();
        display.drawCircle(0,0,1,GxEPD_BLACK);
        display.nextPage();
    }
}

void EPDUpdateDate(struct tm dateInfo, bool updateDate){
    
    display.setPartialWindow(hourDateBox.X, hourDateBox.Y, hourDateBox.Width, hourDateBox.Height);
    //display.setPartialWindow(0, 0, display.width(), display.height());
    display.setFont(&FreeSansBold24pt7b);
    display.setTextColor(GxEPD_BLACK);

    //Build hour
    std::string dateString = ((dateInfo.tm_hour < 10) ? ("0" + std::to_string(dateInfo.tm_hour)) : std::to_string(dateInfo.tm_hour)) + 
                            ":" + 
                            ((dateInfo.tm_min < 10) ? ("0" + std::to_string(dateInfo.tm_min)) : std::to_string(dateInfo.tm_min));
    display.firstPage();
    display.fillRect(hourDateBox.X, hourDateBox.Y, hourDateBox.Width, hourDateBox.Height, GxEPD_WHITE);
    display.setCursor(hourDateBox.X, hourDateBox.cursorY);
    display.print(dateString.c_str());

    if(updateDate){
        dateString.clear();
        //Build day, month and year text.
        dateString = ((dateInfo.tm_mday < 10) ? ("0" + std::to_string(dateInfo.tm_mday)) : std::to_string(dateInfo.tm_mday)) + //To keep constant size, we add a 0 for only digit numbers
                    " " + 
                    monthList["ENG"][dateInfo.tm_mon] + 
                    " " + 
                    std::to_string(dateInfo.tm_year + 1900); //Dates from this server start a 1900, we need to apply and offset

        display.setFont(&FreeSans9pt7b);
        display.setCursor(hourDateBox.X + hourDateBox.dateXOffset , hourDateBox.cursorY  + hourDateBox.dateYOffset);
        display.print(dateString.c_str());
    }
    display.nextPage();
}

void EPDUpdateForecast(struct currenWeatherData data){
    // Data preparation
    std::string tempForecast = std::to_string(data.temperature) + "C";
    std::string humidityForecast = std::to_string(data.humidity) + "%";
    std::string windSPeedForecast = std::to_string(data.windSpeed) + "m/s";

    display.setPartialWindow(forecastBox.X, forecastBox.Y, forecastBox.Width, forecastBox.Height);

    display.setFont(&FreeSansBold9pt7b);
    display.setTextColor(GxEPD_BLACK);

    display.firstPage();
    display.fillRect(forecastBox.X, forecastBox.Y, forecastBox.Width, forecastBox.Height, GxEPD_WHITE);

    display.drawFastHLine(forecastBox.X, forecastBox.Y + 5, forecastBox.Width, GxEPD_BLACK );

    display.setCursor(forecastBox.cursorX, forecastBox.cursorY - forecastBox.primaryFontSize);
    display.print(tempForecast.c_str());

    display.setCursor(forecastBox.cursorX, forecastBox.cursorY);
    display.print(humidityForecast.c_str());

    display.setCursor(forecastBox.cursorX + forecastBox.offsetDataWind, forecastBox.cursorY - forecastBox.primaryFontSize);
    display.print(getWindName(data.windDir).c_str());

    display.setCursor(forecastBox.cursorX + forecastBox.offsetDataWind, forecastBox.cursorY);
    display.print(windSPeedForecast.c_str());

    display.nextPage();

    //Print weather icon
    display.drawImage(iconMap[data.iconCode], forecastBox.X + forecastBox.iconOffsetX ,forecastBox.iconOffsetY, 48,48);
}

void EPDUpdateIndoorMeas(struct BME680readings readings){
    std::string measString;
    std::ostringstream stream;
    stream.precision(1);

    //Save original cursor position:
    uint16_t originalCursorY = envioromentalBox.cursorY;

    display.setPartialWindow(envioromentalBox.X, envioromentalBox.Y, envioromentalBox.Width, envioromentalBox.Height);
    display.setTextColor(GxEPD_WHITE);

    display.firstPage();
    display.fillRect(envioromentalBox.X, envioromentalBox.Y, envioromentalBox.Width, envioromentalBox.Height, GxEPD_BLACK);
    
    display.setFont(&FreeSansBold9pt7b);
    display.setCursor(envioromentalBox.X, envioromentalBox.cursorY);
    display.print("Indoor");

    display.setFont(&FreeSans9pt7b);
    //Print temperature
    envioromentalBox.cursorY += envioromentalBox.primaryFontSize * 2;
    display.setCursor(envioromentalBox.X, envioromentalBox.cursorY);
    stream << std::fixed << readings.temperature;
    measString = stream.str() + "C";
    display.print(measString.c_str());

    //Print humidity
    envioromentalBox.cursorY += envioromentalBox.primaryFontSize * 3;
    display.setCursor(envioromentalBox.X, envioromentalBox.cursorY);
    measString.clear();
    stream.str("");
    stream << std::fixed << readings.humidity;
    measString = stream.str() + "%";
    display.print(measString.c_str());

    //Print pressure
    envioromentalBox.cursorY += envioromentalBox.primaryFontSize * 3;
    display.setCursor(envioromentalBox.X, envioromentalBox.cursorY);
    measString.clear();
    measString = std::to_string(readings.pressure) + "hPa";
    display.print(measString.c_str());

    //Print Air quality
    envioromentalBox.cursorY += envioromentalBox.primaryFontSize * 3;
    display.setCursor(envioromentalBox.X, envioromentalBox.cursorY);
    measString.clear();
    measString = readings.airQualityLevel;
    display.print(measString.c_str());

    display.nextPage();

    envioromentalBox.cursorY = originalCursorY;
}

void EPDUpdateHWStatus(){

}

std::string getWindName(int degree) {
    // Normalize degree
    degree = degree % 360;
    if (degree < 0) {
        degree += 360;
    }

    const uint16_t degreePerDirection = 360 / windDirection["ENG"].size();

    uint8_t directionIndex = (degree + degreePerDirection / 2) / degreePerDirection;
    if (directionIndex == windDirection["ENG"].size()) {
        directionIndex = 0; 
    }

    return windDirection["ENG"][directionIndex];
}
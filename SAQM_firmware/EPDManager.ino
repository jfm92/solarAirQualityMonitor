#include <string>
#include <map>

#include <GxEPD2_BW.h>
#include "systemConfig.h"
#include "EPDManagerAux.h"

#include <Fonts/FreeSansBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>

#include "time.h"

GxEPD2_BW<GxEPD2_290_BS, GxEPD2_290_BS::HEIGHT> display(GxEPD2_290_BS(EPD_CS,  EPD_DC,  EPD_RES, EPD_BUSY));



void EPDInit(bool clearDisplay){
    display.init(115200,true,50,false);
    display.setRotation(1);

    if(clearDisplay) display.clearScreen();

    display.setPartialWindow(0, 0, display.width(), display.height());
}


void EPDUpdateDate(struct tm dateInfo, bool updateDate){
    
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


void EPDUpdateForecast(){

}

void EPDUpdateIndoorMeas(){

}

void EPDUpdateHWStatus(){

}
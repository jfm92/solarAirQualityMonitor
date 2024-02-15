//This is the entry point
#include "time.h"

// Save 
RTC_DATA_ATTR uint8_t bootCount = 0;


void setup(){
    Serial.begin(115200);

    bool startMode = (bootCount == 0) ? true : false;

    //If this is a fresh start we want a complete screen clear
    EPDInit(startMode);

    //If first start or one hour from last update we get NTP time
    if(startMode){
        struct tm dateInfo;
        syncDateTime();

        getLocalTime(&dateInfo);
        EPDUpdateDate(dateInfo, true);
    }

}

void loop(){
    
    struct tm dateInfo;
    getLocalTime(&dateInfo);
    EPDUpdateDate(dateInfo, true);
    delay(10*1000);
}
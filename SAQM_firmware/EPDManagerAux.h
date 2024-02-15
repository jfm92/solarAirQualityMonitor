#pragma once

#include <vector>
#include <map>

/************************ Hour and date config ************************/
std::vector<std::string> monthListEng = {"January", "February", "Mar", "Apr", "May","Jun","Jul","Aug","Sep","Oct", "Nov", "Dec"};
std::vector<std::string> monthListESP = {"Enero", "Febrero", "Mar", "Abr", "May","Jun","Jul","Ago","Sep","Oct", "Nov", "Dic"};

std::map<std::string, std::vector<std::string>> monthList = {{"ESP", monthListESP}, {"ENG", monthListEng}};

struct hourDateBox{
    uint16_t X = 0;
    uint16_t Y = 20;
    uint16_t Width = 70;
    uint16_t Height = 20;
    uint16_t cursorY = Y + Height - 6;
    uint16_t dateXOffset = 5;
    uint16_t dateYOffset = 20;
} hourDateBox;




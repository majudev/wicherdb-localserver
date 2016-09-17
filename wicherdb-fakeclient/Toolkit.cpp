#include "Toolkit.h"

void Wicher::Toolkit::log(std::string str){
    time_t rawtime;
    struct tm * timeinfo;

    std::time(&rawtime);
    timeinfo = localtime(&rawtime);

    char buffer[20];
    strftime(buffer, 20, "%H:%M:%S", timeinfo);
    std::cout << "[WICHER][" << buffer << "] " << str << std::endl;
}

std::string Wicher::Toolkit::itostr(int i){
    char ch[10];
    sprintf(ch, "%d", i);
    return std::string(ch);
}

int Wicher::Toolkit::strtoi(std::string str){
    int i;
    sscanf(str.c_str(), "%d", &i);
    return i;
}

std::string Wicher::Toolkit::time(){
    time_t rawtime;
    struct tm * timeinfo;

    std::time(&rawtime);
    timeinfo = localtime(&rawtime);

    char buffer[30];
    strftime(buffer, 20, "%d-%m-%Y %H:%M:%S", timeinfo);
    return std::string(buffer);
}

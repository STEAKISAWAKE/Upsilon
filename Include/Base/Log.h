
#ifndef __UPSILON_BASE_LOG_H__
#define __UPSILON_BASE_LOG_H__

#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <time.h>

inline std::string getCurrentDateTime( std::string s )
{
    time_t now = time(0);
    struct tm  tstruct;
    char  buf[80];
    tstruct = *localtime(&now);
    if(s=="now")
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    else if(s=="date")
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    return std::string(buf);
};

inline void ULog(std::string messageName, std::string message)
{
    printf("%s: %s\n", messageName.c_str(), message.c_str());
}

inline void ULogError(std::string messageName, std::string message)
{

    std::string fullMessage = messageName + ": " + message;

    std::string filePath = "C:\\Users\\Steak\\Documents\\GitHub\\Upsilon\\build\\Examples\\Render\\VulkanTests\\Debug\\Error" + getCurrentDateTime("date")+".txt";
    std::string now = getCurrentDateTime("now");
    std::ofstream ofs(filePath.c_str(), std::ios_base::out | std::ios_base::app );
    ofs << now << '\t' << fullMessage << '\n';
    ofs.close();

    printf("%s: %s\n", messageName.c_str(), message.c_str());
}

#endif // __UPSILON_BASE_LOG_H__
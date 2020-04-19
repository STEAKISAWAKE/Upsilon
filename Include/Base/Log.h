
#ifndef __UPSILON_BASE_LOG_H__
#define __UPSILON_BASE_LOG_H__

#include <iostream>
#include <string>

void Log(std::string messageName, std::string message)
{
    std::cout << messageName << ": " << message << std::endl;
}


#endif // __UPSILON_BASE_LOG_H__
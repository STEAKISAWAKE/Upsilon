
#ifndef __UPSILON_BASE_LOG_H__
#define __UPSILON_BASE_LOG_H__

#include <iostream>
#include <string>

inline void ULog(std::string messageName, std::string message)
{
    std::cout << messageName << ": " << message << std::endl;
}

inline void ULogError(std::string messageName, std::string message)
{
    std::cout << "\033[41m" << messageName << ": " << message << "\033[0m" << std::endl;
}

#endif // __UPSILON_BASE_LOG_H__
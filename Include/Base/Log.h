
#ifndef __UPSILON_BASE_LOG_H__
#define __UPSILON_BASE_LOG_H__

#include <iostream>
#include <string>
#include <cassert>

inline void ULog(std::string messageName, std::string message)
{
    printf("%s: %s\n", messageName.c_str(), message.c_str());
}

inline void ULogError(std::string messageName, std::string message)
{
    printf("%s: %s\n", messageName.c_str(), message.c_str());

}

#endif // __UPSILON_BASE_LOG_H__
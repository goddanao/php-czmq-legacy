#include "zutils.h"

std::string toUpper(const std::string& s)
{
    std::string result;

    std::locale loc;
    for (unsigned int i = 0; i < s.length(); ++i)
    {
        result += std::toupper(s.at(i), loc);
    }

    return result;
}

std::string toLower(const std::string& s)
{
    std::string result;

    std::locale loc;
    for (unsigned int i = 0; i < s.length(); ++i)
    {
        result += std::tolower(s.at(i), loc);
    }

    return result;
}
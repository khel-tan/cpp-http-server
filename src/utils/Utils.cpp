#include "Utils.hpp"
#include <algorithm>

void
ltrim(std::string &s)
{
    s.erase(s.begin(),
            std::find_if(s.begin(), s.end(),
                         [](const unsigned char c) {
                             return !std::isspace(c);
                         }));
}

void
rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](const unsigned char ch) {
                             return !std::isspace(ch);
                         })
                .base(),
            s.end());
}

void
trim(std::string &s)
{
    ltrim(s);
    rtrim(s);
}

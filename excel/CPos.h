#pragma once
#include <string>

class CPos {
public:
    CPos ( std::string_view str );

private:
    std::string m_str;
};
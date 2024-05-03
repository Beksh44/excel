#pragma once
#include <string>

class CPos {
public:
    CPos ( std::string_view str );
    std::string  getPos () const;

private:
    std::string m_str;
};
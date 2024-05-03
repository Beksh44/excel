#include "CPos.h"
#include <string>

CPos::CPos ( std::string_view str ) {

    auto it = str.begin();
    while ( std::isalpha ( *it ) ) {
        it++;
        m_str.push_back ( ::toupper( *it ) );
    }

    if ( it == str.begin() || it == str.end() || ! std::isdigit ( *it ) )
        throw std::invalid_argument ( "format of position isn't right" );//if we haven't moved from the beginning means that first element isn't a letter

    auto it2 = it;
    while ( std::isdigit ( *it ) && it != str.end() ) {
        it++;
        m_str.push_back( *it );
    }

    if ( it == it2 || it != str.end() )
        throw std::invalid_argument ( "format of position isn't right" );//if we haven't moved from the beginning
}

std::string CPos::getPos() const {
    return m_str;
}
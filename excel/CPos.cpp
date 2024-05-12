#include "CPos.h"
#include <iostream>
#include <string>


/*
 * Convert a string to an integer
 * @param pos - string
 * @param posInt - pair of integers
 */

void CPos::toInt ( const std::string & pos , std::pair<long long int , int> & posInt ) {
    int size = pos.size();
    posInt.first = 0;
    for ( int i = size - 1 , j = 0; i >= 0; i-- , j++ ) //convert the string to an integer
        posInt.first += ( ( pos [ j ] - 'A' + 1  ) * pow ( 26 , i ) );
}

/*
 * Convert integer to a string
 * @param posInt - integer
 * @return the string
 */

std::string CPos ::toStr ( long long int posInt ) {
    std::string pos = "";
    while ( posInt > 0 ) {
        int remainder = posInt % 26;
        char digit = 'A' + remainder - 1; // ('A'=1, 'B'=2, ..., 'Z'=26)
        pos = digit + pos;
        posInt /= 26;
    }
    return pos;
}

/*
 * Constructor
 * @param str - string
 */

CPos::CPos ( std::string_view str ) {

    m_fixedColumn = false;
    m_fixedRow = false;
    auto it = str.begin();
    if ( * it == '$') {//if the column is fixed
        m_fixedColumn = true;
        it++;//skipping
    }
    while ( std::isalpha ( *it ) ) {//while it's a letter
        m_str.push_back ( ::toupper( *it ) );
        it++;
    }

    if ( it == str.begin() || it == str.end() )
        throw std::invalid_argument ( "format of position isn't right" );//if we haven't moved from the beginning means that first element isn't a letter

    toInt ( m_str , m_int );//convert the string to a pair of integers
    auto it2 = it;
    if ( * it == '$' ) {//if the row is fixed
        m_fixedRow = true;
        it++;
    }

    std::string tmp;
    while ( std::isdigit ( *it ) && it != str.end() ) {//while it's a digit
        m_str.push_back( *it );
        tmp.push_back( * it );
        it++;
    }

    m_int.second = std::stoi( tmp );//convert the row to an integer

    if ( it == it2 || it != str.end() )
        throw std::invalid_argument ( "format of position isn't right" );//if we haven't moved from the beginning

}

/*
 * Get the position as a string
 * @return the position as a string
 */

std::string CPos::getPosStr() const {
    return m_str;
}

/*
 * Get the position as a pair of integers
 * @return the position as a pair of integers
 */

std::pair<long long int , int> CPos::getPosInt() const {
    return m_int;
}

/*
 * Check if the column is fixed
 * @return true if the column is fixed, false otherwise
 */

bool CPos::isFixedColumn() const {
    return m_fixedColumn;
}

/*
 * Check if the row is fixed
 * @return true if the row is fixed, false otherwise
 */

bool CPos::isFixedRow() const {
    return m_fixedRow;
}

/*
 * Set the fixed column
 * @param toSet - true if the column should be fixed, false otherwise
 */
void CPos::setFixedColumn ( bool toSet ) {
    m_fixedColumn = toSet;
}

/*
 * Set the fixed row
 * @param toSet - true if the row should be fixed, false otherwise
 */

void CPos::setFixedRow ( bool toSet ) {
    m_fixedRow = toSet;
}

/*
 * Serialize the object
 * @param out - output stream
 */

void CPos::serialize ( std::ostream & out ) const {
    size_t size = m_str.size();
    out.write ( reinterpret_cast< const char * > ( & size ) , sizeof ( size ) );
    out.write ( m_str.data() , m_str.size() );
    out.write ( reinterpret_cast< const char * > ( & m_fixedColumn ) , sizeof ( m_fixedColumn ) );
    out.write ( reinterpret_cast< const char * > ( & m_fixedRow ) , sizeof ( m_fixedRow ) );
    out.write ( reinterpret_cast< const char * > ( & m_int ) , sizeof ( m_int ) );
}

/*
 * Deserialize the object
 * @param in - input stream
 * @return true if the object was successfully deserialized, false otherwise
 */

bool CPos::deSerialize ( std::istream & in ) {
    size_t size;
    if ( ! in.read ( reinterpret_cast<char*> ( & size ), sizeof ( size ) ) ) {
        return false;
    }
    m_str.resize ( size );
    if ( ! in.read ( & m_str[0], size ) ) {
        return false;
    }

    if ( ! in.read ( reinterpret_cast< char * >( & m_fixedColumn ), sizeof ( m_fixedColumn ) ) )
        return false;
    if ( ! in.read ( reinterpret_cast< char * >( & m_fixedRow ), sizeof ( m_fixedRow ) ) )
        return false;
    if ( ! in.read ( reinterpret_cast< char * >( & m_int ), sizeof ( m_int ) ) )
        return false;
    return true;
}
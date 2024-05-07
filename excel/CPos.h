#include <string>
#ifndef CPOS_H
#define CPOS_H

class CPos {
public:
    CPos() = default;
    CPos ( std::string_view str );
    void toInt ( const std::string & pos , std::pair<long long int , int> & posInt );
    std::string toStr ( long long int posInt );
    std::string  getPosStr () const;
    std::pair<long long int , int> getPosInt () const;
    bool isFixedColumn() const;
    bool isFixedRow() const;
    void setFixedColumn ( bool toSet );
    void setVixedRow ( bool toSet );

private:
    std::string m_str;
    bool m_fixedColumn;
    bool m_fixedRow;
    std::pair< long long int , int> m_int;
};


#endif CPOS_H
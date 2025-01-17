#ifndef __PROGTEST__
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <climits>
#include <cfloat>
#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <array>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <variant>
#include <optional>
#include <compare>
#include <charconv>
#include <span>
#include <utility>
#include "expression.h"
using namespace std::literals;
using CValue = std::variant<std::monostate, double, std::string>;

constexpr unsigned                     SPREADSHEET_CYCLIC_DEPS                 = 0x01;
constexpr unsigned                     SPREADSHEET_FUNCTIONS                   = 0x02;
constexpr unsigned                     SPREADSHEET_FILE_IO                     = 0x04;
constexpr unsigned                     SPREADSHEET_SPEED                       = 0x08;
constexpr unsigned                     SPREADSHEET_PARSER                      = 0x10;
#endif /* __PROGTEST__ */


///////////////////////////////////////////////////////////////////////////////////CPos

class CPos {
public:
    CPos() = default;
    CPos ( std::string_view str );
    /*
     * Convert a string to an integer
     * @param pos - string
     * @param posInt - pair of integers
     */
    void toInt ( const std::string & pos , std::pair<long long int , int> & posInt );
    /*
     * Convert integer to a string
     * @param posInt - integer
     * @return the string
     */
    std::string toStr ( long long int posInt );
    /*
     * Get the position as a string
     * @return the string
     */
    std::string  getPosStr () const;
    /*
     * Get the position as an integer
     * @return the integer
     */
    std::pair<long long int , int> getPosInt () const;
    /*
     * Check if the column is fixed
     * @return true if the column is fixed, false otherwise
     */
    bool isFixedColumn() const;
    /*
     * Check if the row is fixed
     * @return true if the row is fixed, false otherwise
     */
    bool isFixedRow() const;
    /*
     * Set the fixed column
     * @param toSet - true if the column should be fixed, false otherwise
     */
    void setFixedColumn ( bool toSet );
    /*
     * Set the fixed row
     * @param toSet - true if the row should be fixed, false otherwise
     */
    void setFixedRow ( bool toSet );
    /*
     * Serialize the object
     * @param out - output stream
     */
    void serialize ( std::ostream & out ) const;
    /*
     * Deserialize the object
     * @param in - input stream
     * @return true if the object was deserialized, false otherwise
     */
    bool deSerialize ( std::istream & in );

private:
    std::string m_str;
    bool m_fixedColumn;
    bool m_fixedRow;
    std::pair< long long int , int> m_int;
};


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
//////////////////////////////////////////////////////////////////////////////CExpression

//CValue with position for the getValue of child class CPosition
using CValue2 = std::variant<std::monostate, double, std::string,CPos>;

class CExpression {
public:
    virtual std::shared_ptr<CExpression> clone() const = 0;


    /*
     * Print the expression
     */
    virtual void print () const = 0;

    /*
     * Get the value of the expression
     */
    virtual CValue2 getValue() = 0;

    /*
     * Check if the expression is a double
     */
    virtual bool isDouble() const = 0;

    /*
     * Check if the expression is a string
     */
    virtual bool isString() const = 0;

    /*
     * Check if the expression is a position
     */
    virtual bool isPos() const = 0;

    /*
     * Check if the expression is an operator
     */
    virtual bool isOperator() const = 0;

    /*
     * Serialize the expression
     */
    virtual void serialize ( std::ostream& os ) const = 0;

    /*
     * Deserialize the expression
     */
    virtual bool deSerialize ( std::istream& is ) = 0;

    /*
     * Get the type of the expression
     */
    virtual std::string getType() const = 0;
};

class COperator : public CExpression {
public:
    COperator();
    COperator ( const std::string & operaTor );

    std::shared_ptr<CExpression> clone() const override;

    CValue2 getValue() override;

    void print () const override;

    bool isDouble() const override;

    bool isString() const override;

    bool isPos() const override;

    bool isOperator() const override;

    void serialize ( std::ostream& os ) const override;

    bool deSerialize ( std::istream& is ) override;

    std::string getType() const override;

private:
    std::string m_oper;
};

class CPosition : public CExpression {

public:

    CPosition();

    CPosition ( CPos & pos );

    std::shared_ptr<CExpression> clone() const override;

    CValue2 getValue() override;

    void print () const override;

    bool isOperator() const override;

    bool isDouble() const override;

    bool isString() const override;

    bool isPos() const override;

    void serialize ( std::ostream& os ) const override;

    bool deSerialize ( std::istream& is ) override;

    std::string getType() const override;
private:
    CPos m_pos;
};

class CDouble : public CExpression {

public:

    CDouble();

    CDouble ( double value );

    CDouble ( const CDouble & other );

    std::shared_ptr<CExpression> clone() const override;

    CValue2 getValue() override;

    void print () const override;

    bool isOperator() const override;

    bool isDouble() const override;

    bool isString() const override;

    bool isPos() const override;

    void serialize ( std::ostream& os ) const override;

    bool deSerialize ( std::istream& is ) override;

    std::string getType() const override;
private:
    double m_number;
};

class CString : public CExpression {

public:
    CString();

    CString ( const std::string & str );

    std::shared_ptr<CExpression> clone() const override;

    CValue2 getValue() override;

    void print () const override;

    bool isOperator() const override;

    bool isDouble() const override;

    bool isString() const override;

    bool isPos() const override;

    void serialize ( std::ostream& os ) const override;

    bool deSerialize ( std::istream& is ) override;

    std::string getType() const override;
private:
    std::string m_str;
};


/////////////////////////////////////////////////COperator

COperator::COperator ( const std::string & operaTor ) : m_oper ( operaTor ) {}

COperator::COperator() = default;

std::shared_ptr<CExpression> COperator::clone() const {
    return std::make_shared<COperator>( *this );
}

void COperator::print() const {
    std::cout << "COperator" << std::endl;
}

CValue2 COperator::getValue() {
    return m_oper;
}

bool COperator::isOperator() const {
    return true;
}

bool COperator::isDouble() const {
    return false;
}

bool COperator::isPos() const {
    return false;
}

bool COperator::isString() const {
    return false;
}

std::string COperator::getType() const {
    return "COperator";
}

void COperator::serialize ( std::ostream & out ) const {
    size_t size = m_oper.size();
    out.write ( reinterpret_cast< const char * > ( & size ) , sizeof ( size ) );
    out.write ( m_oper.data() , size );
}

bool COperator::deSerialize ( std::istream & in ) {
    size_t size;
    if ( !in.read ( reinterpret_cast<char*> ( & size ), sizeof ( size ) ) ) {
        return false;
    }
    m_oper.resize ( size );
    in.read ( & m_oper [ 0 ], size );
    return true;
}

/////////////////////////////////////////////////CDouble

CDouble::CDouble() = default;

CDouble::CDouble ( double value ) : m_number ( value ) {}

CDouble::CDouble ( const CDouble & other ) {
    this->m_number = other.m_number;
}

void CDouble::print () const {
    std::cout << m_number << std::endl;
}

std::shared_ptr<CExpression> CDouble::clone ( ) const {
    return std::make_shared<CDouble>( *this );
}

CValue2 CDouble::getValue() {
    return m_number;
}

bool CDouble::isDouble() const {
    return true;
}

bool CDouble::isOperator() const {
    return false;
}

bool CDouble::isPos() const {
    return false;
}

bool CDouble::isString() const {
    return false;
}

std::string CDouble::getType() const {
    return "CDouble";
}

void CDouble::serialize ( std::ostream& out ) const {
    out.write ( reinterpret_cast< const char * > ( & m_number ), sizeof ( m_number ) );
}

bool CDouble::deSerialize ( std::istream & in ) {
    if ( ! in.read ( reinterpret_cast< char * > ( & m_number ) , sizeof ( m_number ) ) ) {
        return false;
    }
    return true;
}

/////////////////////////////////////////////////CString

CString::CString() = default;

CString::CString ( const std::string & str )  {
    m_str = str;
}

std::shared_ptr<CExpression> CString::clone() const {
    return std::make_shared<CString>( *this );
}

void CString::print () const {
    std::cout << "CString" << std::endl;
}

CValue2 CString::getValue() {
    return m_str;
}

bool CString::isString() const {
    return true;
}

bool CString::isPos() const {
    return false;
}

bool CString::isDouble() const {
    return false;
}

bool CString::isOperator() const {
    return false;
}

std::string CString::getType() const {
    return "CString";
}

void CString::serialize ( std::ostream & out ) const {
    size_t size = m_str.size();
    out.write ( reinterpret_cast< const char * > ( & size ) , sizeof ( size ) );
    out.write ( m_str.data(), size );
}

bool CString::deSerialize ( std::istream & in ) {
    size_t size;
    if ( ! in.read ( reinterpret_cast<char*> ( & size ), sizeof ( size ) ) ) {
        return false;
    }
    m_str.resize ( size );
    if ( ! in.read ( & m_str[0], size ) ) {
        return false;
    }
    return true;
}

/////////////////////////////////////////////////CPosition

CPosition::CPosition() = default;

CPosition::CPosition ( CPos & pos ) {
    m_pos = pos;
}

std::shared_ptr<CExpression> CPosition::clone() const {
    return std::make_shared<CPosition>( *this );
}

void CPosition::print () const {
    std::cout << "CPosition" << std::endl;
}

CValue2 CPosition::getValue() {
    return m_pos;
}

bool CPosition::isPos() const {
    return true;
}

bool CPosition::isDouble() const {
    return false;
}

bool CPosition::isOperator() const {
    return false;
}

bool CPosition::isString() const {
    return false;
}

std::string CPosition::getType() const {
    return "CPosition";
}

void CPosition::serialize ( std::ostream & out ) const {
    m_pos.serialize( out );
}

bool CPosition::deSerialize ( std::istream & in ) {
    return m_pos .deSerialize( in );
}

////////////////////////////////////////////////////////////////////////////////operator functions

CValue add ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double>( left ) && std::holds_alternative<double> ( right ) )
        return std::get<double> ( left ) + std::get<double> ( right );
    if ( std::holds_alternative<std::string> ( left ) && std::holds_alternative<std::string> ( right ) )
        return std::get<std::string>( left ) + std::get<std::string>( right );
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<std::string> ( right ) )
        return std::to_string ( std::get<double>( left ) ) + std::get<std::string>( right );
    if ( std::holds_alternative<std::string> ( left ) && std::holds_alternative<double> ( right ) )
        return std::get<std::string>( left ) + std::to_string( std::get<double>( right ) );

    return std::monostate();
}

CValue sub ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<double> ( right ) )
        return std::get<double> ( left ) - std::get<double> ( right );

    return std::monostate();
}

CValue div ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<double> ( right ) ) {
        double l = std::get<double> ( left );
        double r = std::get<double> ( right );
        if ( r == 0 )
            return std::monostate();
        else
            return l / r;
    }

    return std::monostate();
}

CValue mul ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<double> ( right ) )
        return std::get<double> ( left ) * std::get<double> ( right );

    return std::monostate();
}

CValue pow ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<double> ( right ) )
        return pow ( std::get<double> ( left ) , std::get<double> ( right ) );

    return std::monostate();
}

CValue unaryMinus ( const CValue & value ) {
    if ( std::holds_alternative<double> ( value ) )
        return ( -1 ) * std::get<double> ( value );

    return std::monostate();
}

CValue eq ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<double> ( right ) ) {
        if ( std::get<double> ( left ) == std::get<double> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    if ( std::holds_alternative<std::string> ( left ) && std::holds_alternative<std::string> ( right ) ) {
        if ( std::get<std::string> ( left ) == std::get<std::string> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    return std::monostate();
}

CValue ne ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative< double > ( left ) && std::holds_alternative< double > ( right ) ) {
        if ( std::get<double> ( left ) != std::get< double > ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    if ( std::holds_alternative<std::string> ( left ) && std::holds_alternative<std::string> ( right ) ) {
        if ( std::get<std::string> ( left ) != std::get<std::string> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    return std::monostate();
}

CValue lt ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<double> ( right ) ) {
        if ( std::get<double> ( left ) < std::get<double> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    if ( std::holds_alternative<std::string> ( left ) && std::holds_alternative<std::string> ( right ) ) {
        if ( std::get<std::string> ( left ) < std::get<std::string> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    return std::monostate();
}

CValue le ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<double> ( right ) ) {
        if ( std::get<double> ( left ) <= std::get<double> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    if ( std::holds_alternative<std::string> ( left ) && std::holds_alternative<std::string> ( right ) ) {
        if ( std::get<std::string> ( left ) <= std::get<std::string> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    return std::monostate();
}

CValue gt ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<double> ( right ) ) {
        if ( std::get<double> ( left ) > std::get<double> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    if ( std::holds_alternative<std::string> ( left ) && std::holds_alternative<std::string> ( right ) ) {
        if ( std::get<std::string> ( left ) > std::get<std::string> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    return std::monostate();
}

CValue ge ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<double> ( right ) ) {
        if ( std::get<double> ( left ) >= std::get<double> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    if ( std::holds_alternative<std::string> ( left ) && std::holds_alternative<std::string> ( right ) ) {
        if ( std::get<std::string> ( left ) >= std::get<std::string> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    return std::monostate();
}

/////////////////////////////////////////////////////////////////////////////////////////CMyBuilder

class CMyBuilder : public CExprBuilder {
private:
    std::shared_ptr<std::vector<std::shared_ptr<CExpression>>> ptrToPos;
    CPos m_pos;
public:

    CMyBuilder();

    void opAdd() override;

    void opSub() override;

    void opMul() override;

    void opDiv() override;

    void opPow() override;

    void opNeg() override;

    void opEq() override;

    void opNe() override;

    void opLt() override;

    void opLe() override;

    void opGt() override;

    void opGe() override;

    void valNumber ( double val ) override;

    void valString ( std::string val ) override;

    void valReference ( std::string val ) override;

    void valRange ( std::string val ) override;

    void funcCall ( std::string fnName,
                    int paramCount ) override;

    /*
     * Set the pointer to the vector of expressions
     */
    void setPtr ( std::shared_ptr<std::vector<std::shared_ptr<CExpression>>> & ptr );

};

CMyBuilder::CMyBuilder() = default;

void CMyBuilder::opAdd() {
    COperator toPush ( "+" );
    ptrToPos ->emplace_back( toPush.clone() );
}

void CMyBuilder::opDiv() {
    COperator toPush ( "/" );
    ptrToPos->emplace_back( toPush.clone() );
}

void CMyBuilder::opEq() {
    COperator toPush ( "==" );
    ptrToPos->emplace_back( toPush.clone() );
}

void CMyBuilder::opGe() {
    COperator toPush ( ">=" );
    ptrToPos->emplace_back( toPush.clone() );
}

void CMyBuilder::valNumber ( double val ) {
    CDouble toPush ( val );
    ptrToPos->emplace_back ( toPush.clone() );
}

void CMyBuilder::valString ( std::string val ) {
    CString toPush ( val );
    ptrToPos->emplace_back( toPush.clone() );
}

void CMyBuilder::valReference ( std::string val ) {
    CPos tmp ( val );
    CPosition toPush ( tmp );
    ptrToPos->emplace_back( toPush.clone() );
}

void CMyBuilder::opGt() {
    COperator toPush ( ">" );
    ptrToPos->emplace_back( toPush.clone() );
}

void CMyBuilder::opLe() {
    COperator toPush ( "<=" );// <=
    ptrToPos->emplace_back( toPush.clone() );
}

void CMyBuilder::opLt() {
    COperator toPush ( "<" );
    ptrToPos->emplace_back( toPush.clone() );
}

void CMyBuilder::opMul() {
    COperator toPush ( "*" );
    ptrToPos->emplace_back( toPush.clone() );
}

void CMyBuilder::opNe() {
    COperator toPush ( "!=" );
    ptrToPos->emplace_back( toPush.clone() );
}

void CMyBuilder::opNeg() {
    COperator toPush ( "unar" );
    ptrToPos->emplace_back( toPush.clone() );
}

void CMyBuilder::opPow() {
    COperator toPush ( "^" );
    ptrToPos->emplace_back( toPush.clone() );
}

void CMyBuilder::opSub() {
    COperator toPush ( "-" );
    ptrToPos->emplace_back( toPush.clone() );
}

void CMyBuilder::setPtr ( std::shared_ptr<std::vector<std::shared_ptr<CExpression>>> & ptr ) {
    ptrToPos = ptr;
}

void CMyBuilder::valRange ( std::string val ) {}

void CMyBuilder::funcCall ( std::string fnName, int paramCount ) {}

///////////////////////////////////////////////////////////////////////////////////recursive algorithm of dfs

/**
 *
 * @param graph
 * @param node
 * @param visited
 * @param currentlyVisiting
 *
 * @return true if there is a cycle
 * This function is a recursive algorithm of depth first search
 */

bool dfs ( const std::unordered_map <std::string , std::vector<std::shared_ptr<CExpression>>> & graph ,
           const std::string & node,
           std::unordered_set < std::string > & visited,
           std::unordered_set < std::string > & currentlyVisiting ) {

    if ( currentlyVisiting.find ( node ) != currentlyVisiting.end() )
        return true;


    if ( visited.find ( node ) != visited.end() )
        return false;


    visited.insert ( node );
    currentlyVisiting.insert ( node );

    if ( graph.contains ( node ) ) {
        for ( const auto & neighbor : graph.at ( node ) ) {
            if ( neighbor -> isPos () ) {
                if ( dfs ( graph, ( std::get < CPos > ( neighbor -> getValue () ) ).getPosStr(), visited, currentlyVisiting ) )
                    return true;
            }
        }
    }

    currentlyVisiting.erase ( node );

    return false;
}

////////////////////////////////////////////////////////////////////////////serializing functions

/**
 * @param os
 * @param str
 *
 * This function serializes a string to the output stream
 */
void serializeString ( std::ostream & os, const std::string & str ) {
    int length = str.size();
    os.write ( reinterpret_cast < const char * > ( & length ), sizeof ( length ) );
    os.write ( str.data() , length );
}


/**
 *
 * @param os
 * @param value
 *
 * This function serializes an integer to the output stream
 */
void serializeInt(std::ostream& os, int value ) {
    os.write ( reinterpret_cast < const char * > ( & value ), sizeof ( value ) );
}

/**
 *
 * @param os
 * @param value
 *
 * This function serializes a double to the output stream
 */

bool deserializeString( std::istream & is, std::string & str ) {
    int size;

    if ( ! is.read ( reinterpret_cast < char * > ( & size ) , sizeof ( size ) ) )
        return false;

    std::string str2 ( size , '\0' );
    is.read ( & str2 [ 0 ] , size );
    str = str2;

    return true;
}

/**
 *
 * @param is
 * @param value
 *
 * This function serializes an integer to the output stream
 */

bool deserializeInt ( std::istream & is, int & value ) {
    if ( ! is.read ( reinterpret_cast< char * > ( & value ), sizeof ( value ) ) ) {
        return false; // Error reading integer
    }
    return true;
}


////////////////////////////////////////////////CSpreadsheet
class CSpreadsheet {
public:
    static unsigned capabilities() {
        return SPREADSHEET_CYCLIC_DEPS | SPREADSHEET_FUNCTIONS | SPREADSHEET_FILE_IO | SPREADSHEET_SPEED;
        // | SPREADSHEET_PARSER
    }

    CSpreadsheet();

    CSpreadsheet( const CSpreadsheet & other );

    bool load ( std::istream & is );

    bool save ( std::ostream & os ) const;

    bool setCell ( CPos pos,
                   std::string contents );

    CValue getValue ( CPos pos );

    void copyRect ( CPos dst,
                    CPos src,
                    int w = 1,
                    int h = 1 );

private:
    std::unordered_map <std::string , std::vector<std::shared_ptr<CExpression>>> m_data;
};


//////////////////////////////////////////////CSpreadsheet implementation
CSpreadsheet::CSpreadsheet() = default;

CSpreadsheet::CSpreadsheet ( const CSpreadsheet & other ) {
    for ( const auto & pair : other.m_data ) {
        const std::string & key = pair.first;
        for ( const auto & expr : pair.second ) {
            m_data [ key ].push_back ( expr -> clone() );
        }
    }
}

bool CSpreadsheet::setCell ( CPos pos , std::string contents ) {
    CMyBuilder tmp;
    std::shared_ptr< std::vector<std::shared_ptr<CExpression>>> ptr = std::make_shared<std::vector<std::shared_ptr<CExpression>>>( m_data [ pos .getPosStr() ]);
    ptr->clear();
    tmp.setPtr ( ptr );
    parseExpression ( contents , tmp );
    m_data[ pos.getPosStr() ] = *ptr;
    return true;
}

CValue CSpreadsheet::getValue ( CPos pos ) {

    if ( ! m_data.contains ( pos.getPosStr() ) )//if there is nothing at this position
        return std::monostate();


    std::unordered_set < std::string > visited;
    std::unordered_set < std::string > currentlyVisiting;
    if ( dfs ( m_data , pos.getPosStr() , visited, currentlyVisiting ) )//if there is a cycle
        return std::monostate();

    std::vector<std::shared_ptr<CExpression>> * expression = & m_data [ pos.getPosStr() ];//getting the value at this position
    std::stack<CValue> myStack;
    CValue tmpVal;//temporary value to push to the stack
    for ( const auto & it : ( * expression ) ) {//going through the expression
        if ( ( it ) -> isPos() ) {//if it is a position
            if ( ! m_data.contains ( ( std::get< CPos >( it->getValue() ) ) .getPosStr() ) )//if there is nothing at this position
                return std::monostate();
        }
        if ( ( * it ).isOperator() ) {//if it is an operator
            std::string str = std::get<std::string>( ( * it ).getValue() );
            if ( str != "unar" ) {//if it is binary operator
                CValue right = myStack.top();
                myStack.pop();
                CValue left = myStack.top();
                myStack.pop();
                //checking every possible operator
                if ( str == "+" )
                    tmpVal = add ( left , right );
                else if ( str == "-" )
                    tmpVal = sub ( left , right );
                else if ( str == "*" )
                    tmpVal = mul ( left , right );
                else if ( str == "/" )
                    tmpVal = div ( left , right );
                else if ( str == "^" )
                    tmpVal = pow ( left , right );
                else if ( str == "==" )
                    tmpVal = eq ( left , right );
                else if ( str == "!=" )
                    tmpVal = ne ( left , right );
                else if ( str == "<" )
                    tmpVal = lt ( left , right );
                else if ( str == "<=" )
                    tmpVal = le ( left , right );
                else if ( str == ">" )
                    tmpVal = gt ( left , right );
                else if ( str == ">=" )
                    tmpVal = ge ( left , right );
            } else {//if it is a unary operator
                CValue value = myStack.top();
                myStack.pop();
                tmpVal = unaryMinus ( value );
            }
        } else {//if it is not an operator
            if ( ( * it ) . isPos() )//if it is a position
                tmpVal = getValue ( std::get<CPos>( ( * it ).getValue() ) );
            else {//if it is a value(double or string)
                if ( ( * it ) . isDouble() )
                    tmpVal = std::get<double> ( ( * it ) . getValue() );
                else if ( ( * it ) . isString() )
                    tmpVal = std::get<std::string> ( ( * it ) . getValue() );
            }
        }
        myStack.push ( tmpVal );//pushing the value to the stack
    }
    return myStack.top();//returning the top of the stack which is the final value
}

void CSpreadsheet::copyRect ( CPos dst , CPos src , int w , int h ) {

    long int diffWidth = dst.getPosInt().first - src.getPosInt().first;//difference in width
    int diffHeight = dst.getPosInt().second - src.getPosInt().second;//difference in height

    std::unordered_map< std::string , std::vector<std::shared_ptr<CExpression>>> tmpMap;//temporary map to store the values

    for ( int i = 0; i < h; ++i ) {//going through the height
        for ( int j = 0; j < w; ++j ) {//going through the width
            std::string tmpStr;
            tmpStr = src.toStr ( src.getPosInt().first + j ); // moving our position by width
            tmpStr += std::to_string( src.getPosInt().second + i );// moving our position by height

            if ( m_data.contains ( tmpStr ) ) {// if it's not a monostate
                std::vector< std::shared_ptr< CExpression > > * value = & m_data [ tmpStr ];//getting the value in that position
                std::vector< std::shared_ptr< CExpression > > toPush;
                for ( const auto & it : ( * value ) ) {//going through the value or expression
                    if ( it->isPos() ) {//if it is a position
                        CPos pos2 = std::get<CPos>( (* it ) . getValue() );//getting the position

                        tmpStr = pos2.toStr ( pos2.getPosInt().first + ( ( pos2.isFixedColumn() ) ? 0 : diffWidth ) );//moving the position by width
                        tmpStr += std::to_string ( pos2.getPosInt().second + ( ( pos2.isFixedRow() ) ? 0 : diffHeight ) );//moving the position by height
                        CPos tmpPos ( tmpStr );

                        if ( pos2.isFixedColumn() )//if the column is fixed
                            tmpPos.setFixedColumn ( true );
                        if ( pos2.isFixedRow() )//if the row is fixed
                            tmpPos.setFixedRow ( true );

                        CPosition posToPush ( tmpPos );//creating a new position to push
                        toPush . emplace_back ( posToPush . clone() );//pushing the new position
                    } else {
                        toPush . emplace_back ( it->clone() );//pushing the value that is not a position
                    }
                }
                tmpStr = dst.toStr ( dst.getPosInt().first + j ); // moving our position by width
                tmpStr += std::to_string( dst.getPosInt().second + i );//adding position in columns
                tmpMap [ tmpStr ] = toPush;//pushing the value to the map
            }
        }
    }

    for ( const auto & it : tmpMap ) {//going through the map
        if ( ! m_data.contains( it.first ) )
            m_data [ it.first ] = it.second;//if the position is not in the map, add it
        else {
            m_data . erase( it.first );//if the position is in the map, erase it
            m_data [ it.first ] = it.second;//add the new value
        }
    }
}

bool CSpreadsheet::save ( std::ostream & os ) const {
    int size = m_data.size();
    os.write ( reinterpret_cast < const char * > ( & size ), sizeof ( size ) );
    for ( const auto& pair : m_data ) {

        serializeString(os, pair.first);// Write position to stream

        int vecSize = pair.second.size();
        serializeInt(os, vecSize);

        for ( const auto & expr : pair.second ) {
            serializeString ( os, expr -> getType() );// Serialize expression type
            expr -> serialize ( os );
        }
    }
    return true;
}


bool CSpreadsheet::load(std::istream& is) {
    std::string position;
    int size;
    if ( ! deserializeInt( is , size ) )
        return false;

    for (int i = 0 ;i < size; i++ ) {
        if ( ! deserializeString ( is , position ) )
            return false;

        int vecSize;
        if ( ! deserializeInt ( is, vecSize ) )
            return false; // Error reading vector size


        m_data [ position ]. resize ( vecSize );

        for (int i = 0; i < vecSize; ++i) {
            std::string exprType;
            if (!deserializeString(is, exprType)) {
                return false; // Error reading expression type
            }
            // Create expression based on type
            if ( exprType == "CDouble" ) {//if it is a double
                CDouble tmp;
                if ( ! tmp.deSerialize ( is ) )
                    return false;
                m_data[position][i] = std::make_shared<CDouble> ( tmp );
            } else if ( exprType == "CString" ) {//if it is a string
                CString tmp;
                if ( ! tmp.deSerialize ( is ) )
                    return false;
                m_data[position][i] = std::make_shared<CString> ( tmp );
            } else if ( exprType == "CPosition" ) {//if it is a position
                CPosition tmp;
                if ( ! tmp.deSerialize ( is ) )
                    return false;
                m_data[position][i] = std::make_shared<CPosition> ( tmp );
            } else if ( exprType == "COperator" ) {//if it is an operator
                COperator tmp;
                if ( ! tmp.deSerialize ( is ) )
                    return false;
                m_data[position][i] = std::make_shared<COperator> ( tmp );
            } else {
                return false;
            }
        }
    }

    return true;
}


#ifndef __PROGTEST__

bool                                   valueMatch                              ( const CValue                        & r,
                                                                                 const CValue                        & s )

{
    if ( r . index () != s . index () )
        return false;
    if ( r . index () == 0 )
        return true;
    if ( r . index () == 2 )
        return std::get<std::string> ( r ) == std::get<std::string> ( s );
    if ( std::isnan ( std::get<double> ( r ) ) && std::isnan ( std::get<double> ( s ) ) )
        return true;
    if ( std::isinf ( std::get<double> ( r ) ) && std::isinf ( std::get<double> ( s ) ) )
        return ( std::get<double> ( r ) < 0 && std::get<double> ( s ) < 0 )
               || ( std::get<double> ( r ) > 0 && std::get<double> ( s ) > 0 );
    return fabs ( std::get<double> ( r ) - std::get<double> ( s ) ) <= 1e8 * DBL_EPSILON * fabs ( std::get<double> ( r ) );
}
int main ()
{
    CSpreadsheet x0, x1;
    std::ostringstream oss;
    std::istringstream iss;
    std::string data;

//    assert( x0 . setCell ( CPos ( "A1" ), "=A2" ) );
//    assert( x0 . setCell ( CPos ( "A2" ), "=A1" ) );
//    assert( valueMatch ( x0.getValue ( CPos ( "A1" ) ) , CValue() ) );
//    std::cout << "uraaaa" << std::endl;;


    assert ( x0 . setCell ( CPos ( "A1" ), "10" ) );
    assert ( x0 . setCell ( CPos ( "A2" ), "20.5" ) );
    assert ( x0 . setCell ( CPos ( "A3" ), "3e1" ) );
    assert ( x0 . setCell ( CPos ( "A4" ), "=40" ) );
    assert ( x0 . setCell ( CPos ( "A5" ), "=5e+1" ) );
    assert ( x0 . setCell ( CPos ( "A6" ), "raw text with any characters, including a quote \" or a newline\n" ) );
    assert ( x0 . setCell ( CPos ( "A7" ), "=\"quoted string, quotes must be doubled: \"\". Moreover, backslashes are needed for C++.\"" ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "A1" ) ), CValue ( 10.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "A2" ) ), CValue ( 20.5 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "A3" ) ), CValue ( 30.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "A4" ) ), CValue ( 40.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "A5" ) ), CValue ( 50.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "A6" ) ), CValue ( "raw text with any characters, including a quote \" or a newline\n" ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "A7" ) ), CValue ( "quoted string, quotes must be doubled: \". Moreover, backslashes are needed for C++." ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "A8" ) ), CValue() ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "AAAA9999" ) ), CValue() ) );
    assert ( x0 . setCell ( CPos ( "B1" ), "=A1+A2*A3" ) );
    assert ( x0 . setCell ( CPos ( "B2" ), "= -A1 ^ 2 - A2 / 2   " ) );
    assert ( x0 . setCell ( CPos ( "B3" ), "= 2 ^ $A$1" ) );
    assert ( x0 . setCell ( CPos ( "B4" ), "=($A1+A$2)^2" ) );
    assert ( x0 . setCell ( CPos ( "B5" ), "=B1+B2+B3+B4" ) );
    assert ( x0 . setCell ( CPos ( "B6" ), "=B1+B2+B3+B4+B5" ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "B1" ) ), CValue ( 625.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "B2" ) ), CValue ( -110.25 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "B3" ) ), CValue ( 1024.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "B4" ) ), CValue ( 930.25 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "B5" ) ), CValue ( 2469.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "B6" ) ), CValue ( 4938.0 ) ) );
    assert ( x0 . setCell ( CPos ( "A1" ), "12" ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "B1" ) ), CValue ( 627.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "B2" ) ), CValue ( -154.25 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "B3" ) ), CValue ( 4096.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "B4" ) ), CValue ( 1056.25 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "B5" ) ), CValue ( 5625.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "B6" ) ), CValue ( 11250.0 ) ) );
    x1 = x0;
    assert ( x0 . setCell ( CPos ( "A2" ), "100" ) );
    assert ( x1 . setCell ( CPos ( "A2" ), "=A3+A5+A4" ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "B1" ) ), CValue ( 3012.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "B2" ) ), CValue ( -194.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "B3" ) ), CValue ( 4096.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "B4" ) ), CValue ( 12544.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "B5" ) ), CValue ( 19458.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "B6" ) ), CValue ( 38916.0 ) ) );
    assert ( valueMatch ( x1 . getValue ( CPos ( "B1" ) ), CValue ( 3612.0 ) ) );
    assert ( valueMatch ( x1 . getValue ( CPos ( "B2" ) ), CValue ( -204.0 ) ) );
    assert ( valueMatch ( x1 . getValue ( CPos ( "B3" ) ), CValue ( 4096.0 ) ) );
    assert ( valueMatch ( x1 . getValue ( CPos ( "B4" ) ), CValue ( 17424.0 ) ) );
    assert ( valueMatch ( x1 . getValue ( CPos ( "B5" ) ), CValue ( 24928.0 ) ) );
    assert ( valueMatch ( x1 . getValue ( CPos ( "B6" ) ), CValue ( 49856.0 ) ) );
    oss . clear ();
    oss . str ( "" );
    assert ( x0 . save ( oss ) );
    data = oss . str ();
    iss . clear ();
    iss . str ( data );
    assert ( x1 . load ( iss ) );
    assert ( valueMatch ( x1 . getValue ( CPos ( "B1" ) ), CValue ( 3012.0 ) ) );
    assert ( valueMatch ( x1 . getValue ( CPos ( "B2" ) ), CValue ( -194.0 ) ) );
    assert ( valueMatch ( x1 . getValue ( CPos ( "B3" ) ), CValue ( 4096.0 ) ) );
    assert ( valueMatch ( x1 . getValue ( CPos ( "B4" ) ), CValue ( 12544.0 ) ) );
    assert ( valueMatch ( x1 . getValue ( CPos ( "B5" ) ), CValue ( 19458.0 ) ) );
    assert ( valueMatch ( x1 . getValue ( CPos ( "B6" ) ), CValue ( 38916.0 ) ) );
    assert ( x0 . setCell ( CPos ( "A3" ), "4e1" ) );
    assert ( valueMatch ( x1 . getValue ( CPos ( "B1" ) ), CValue ( 3012.0 ) ) );
    assert ( valueMatch ( x1 . getValue ( CPos ( "B2" ) ), CValue ( -194.0 ) ) );
    assert ( valueMatch ( x1 . getValue ( CPos ( "B3" ) ), CValue ( 4096.0 ) ) );
    assert ( valueMatch ( x1 . getValue ( CPos ( "B4" ) ), CValue ( 12544.0 ) ) );
    assert ( valueMatch ( x1 . getValue ( CPos ( "B5" ) ), CValue ( 19458.0 ) ) );
    assert ( valueMatch ( x1 . getValue ( CPos ( "B6" ) ), CValue ( 38916.0 ) ) );
    oss . clear ();
    oss . str ( "" );
    assert ( x0 . save ( oss ) );
    data = oss . str ();
    for ( size_t i = 0; i < std::min<size_t> ( data . length (), 10 ); i ++ )
        data[i] ^=0x5a;
    iss . clear ();
    iss . str ( data );
    assert ( ! x1 . load ( iss ) );
    assert ( x0 . setCell ( CPos ( "D0" ), "10" ) );
    assert ( x0 . setCell ( CPos ( "D1" ), "20" ) );
    assert ( x0 . setCell ( CPos ( "D2" ), "30" ) );
    assert ( x0 . setCell ( CPos ( "D3" ), "40" ) );
    assert ( x0 . setCell ( CPos ( "D4" ), "50" ) );
    assert ( x0 . setCell ( CPos ( "E0" ), "60" ) );
    assert ( x0 . setCell ( CPos ( "E1" ), "70" ) );
    assert ( x0 . setCell ( CPos ( "E2" ), "80" ) );
    assert ( x0 . setCell ( CPos ( "E3" ), "90" ) );
    assert ( x0 . setCell ( CPos ( "E4" ), "100" ) );
    assert ( x0 . setCell ( CPos ( "F10" ), "=D0+5" ) );
    assert ( x0 . setCell ( CPos ( "F11" ), "=$D0+5" ) );
    assert ( x0 . setCell ( CPos ( "F12" ), "=D$0+5" ) );
    assert ( x0 . setCell ( CPos ( "F13" ), "=$D$0+5" ) );
    x0 . copyRect ( CPos ( "G11" ), CPos ( "F10" ), 1, 4 );
    assert ( valueMatch ( x0 . getValue ( CPos ( "F10" ) ), CValue ( 15.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "F11" ) ), CValue ( 15.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "F12" ) ), CValue ( 15.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "F13" ) ), CValue ( 15.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "F14" ) ), CValue() ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "G10" ) ), CValue() ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "G11" ) ), CValue ( 75.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "G12" ) ), CValue ( 25.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "G13" ) ), CValue ( 65.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "G14" ) ), CValue ( 15.0 ) ) );
    x0 . copyRect ( CPos ( "G11" ), CPos ( "F10" ), 2, 4 );
    assert ( valueMatch ( x0 . getValue ( CPos ( "F10" ) ), CValue ( 15.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "F11" ) ), CValue ( 15.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "F12" ) ), CValue ( 15.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "F13" ) ), CValue ( 15.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "F14" ) ), CValue() ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "G10" ) ), CValue() ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "G11" ) ), CValue ( 75.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "G12" ) ), CValue ( 25.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "G13" ) ), CValue ( 65.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "G14" ) ), CValue ( 15.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "H10" ) ), CValue() ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "H11" ) ), CValue() ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "H12" ) ), CValue() ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "H13" ) ), CValue ( 35.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "H14" ) ), CValue() ) );
    assert ( x0 . setCell ( CPos ( "F0" ), "-27" ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "H14" ) ), CValue ( -22.0 ) ) );
    x0 . copyRect ( CPos ( "H12" ), CPos ( "H13" ), 1, 2 );
    assert ( valueMatch ( x0 . getValue ( CPos ( "H12" ) ), CValue ( 25.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "H13" ) ), CValue ( -22.0 ) ) );
    assert ( valueMatch ( x0 . getValue ( CPos ( "H14" ) ), CValue ( -22.0 ) ) );
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */

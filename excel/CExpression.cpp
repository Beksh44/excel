#include "CExpression.h"
#include <string>
#include <iostream>
#include "getValue.h"

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
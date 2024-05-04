#include "CExpression.h"
#include <string>
#include <iostream>


/////////////////////////////////////////////////COperator

COperator::COperator ( const char & operaTor ) : m_oper ( operaTor ) {}

COperator::COperator (  ) = default;

std::shared_ptr<CExpression> COperator::clone() const {
    return std::make_shared<COperator>( *this );
}

void COperator::print () const {
    std::cout << "jo" << std::endl;
}

/////////////////////////////////////////////////CDouble

CDouble::CDouble ( double value ) : number ( value ) {}

CDouble::CDouble ( const CDouble & other ) {
    this->number = other.number;
}

void CDouble::print () const {
    std::cout << number << std::endl;
}

std::shared_ptr<CExpression> CDouble::clone ( ) const {
    return std::make_shared<CDouble>( *this );
}

/////////////////////////////////////////////////CString

CString::CString ( const std::string & str )  {
    m_str = str;
}

std::shared_ptr<CExpression> CString::clone() const {
    return std::make_shared<CString>( *this );
}

void CString::print () const {
    std::cout << "jo2" << std::endl;
}

/////////////////////////////////////////////////CPosition

CPosition::CPosition ( CPos pos ) {
    m_pos = pos;
}

std::shared_ptr<CExpression> CPosition::clone() const {
    return std::make_shared<CPosition>( *this );
}

void CPosition::print () const {
    std::cout << "jo3" << std::endl;
}
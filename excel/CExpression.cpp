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
    std::cout << " operator " << std::endl;
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

bool COperator::isMonostate() const {
    return false;
}

/////////////////////////////////////////////////CDouble

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

bool CDouble::isMonostate() const {
    return false;
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

bool CString::isMonostate() const {
    return false;
}

/////////////////////////////////////////////////CPosition

CPosition::CPosition ( CPos & pos ) {
    m_pos = pos;
}

std::shared_ptr<CExpression> CPosition::clone() const {
    return std::make_shared<CPosition>( *this );
}

void CPosition::print () const {
    std::cout << "jo3" << std::endl;
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

bool CPosition::isMonostate() const {

}

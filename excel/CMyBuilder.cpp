#include <iostream>
#include <string>
#include "CMyBuilder.h"

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
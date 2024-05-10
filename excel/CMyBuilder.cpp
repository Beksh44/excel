#include <iostream>
#include <string>
#include "CMyBuilder.h"

CMyBuilder::CMyBuilder() = default;

void CMyBuilder::opAdd() {
    std::cout << " + " << std::endl;
    COperator toPush ( "+" );
    ptrToPos ->emplace_back( toPush.clone() );
}

void CMyBuilder::opDiv() {
    std::cout << " / " << std::endl;
    COperator toPush ( "/" );
    ptrToPos->emplace_back( toPush.clone() );
}

void CMyBuilder::opEq() {
    std::cout << " = " << std::endl;
    COperator toPush ( "==" );
    ptrToPos->emplace_back( toPush.clone() );
}

void CMyBuilder::opGe() {
    std::cout << " ge " << std::endl;
    COperator toPush ( ">=" ); // >=
    ptrToPos->emplace_back( toPush.clone() );
}

void CMyBuilder::valNumber ( double val ) {
    //std::cout << " the number is " << val << std::endl;
    CDouble toPush ( val );
    ptrToPos->emplace_back ( toPush.clone() );
    std::cout << "tmp second is ";
    (* ( *ptrToPos )[0] ).print();
    std::cout << std::endl;
}

void CMyBuilder::valString ( std::string val ) {
    CString toPush ( val );
    ptrToPos->emplace_back( toPush.clone() );
    std::cout << "tmp second is ";
    (* ( *ptrToPos )[0] ).print();
    std::cout << " the string is " << val << std::endl;
}

void CMyBuilder::valReference ( std::string val ) {
    CPos tmp ( val );
    CPosition toPush ( tmp );
    ptrToPos->emplace_back( toPush.clone() );
    std::cout << "tmp second is ";
    (* ( *ptrToPos )[0] ).print();
    std::cout << " our position is " << val << std::endl;
}

void CMyBuilder::opGt() {
    COperator toPush ( ">" );
    ptrToPos->emplace_back( toPush.clone() );
}

void CMyBuilder::valRange ( std::string val ) {

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

void CMyBuilder::funcCall ( std::string fnName, int paramCount ) {

}

void CMyBuilder::setPtr ( std::shared_ptr<std::vector<std::shared_ptr<CExpression>>> & ptr ) {
    ptrToPos = ptr;
}

void CMyBuilder::printDOuble() {
    //std::cout << std::endl;
}

void CMyBuilder::setTable ( std::unordered_map <std::string , std::vector<std::shared_ptr<CExpression>>> & data ) {
    m_table = data;
}
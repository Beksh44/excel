#include <iostream>
#include "COperator.h"

double CUnaryMinus::oneDouble ( double first ) {
    return first * (-1);
}

void CUnaryMinus::print() const {
    std::cout << "-" << std::endl;
}

std::shared_ptr<CExpression> CUnaryMinus::clone() const {

}
#ifndef EXCEL_COPERATOR_H
#define EXCEL_COPERATOR_H

#include "CExpression.h"

class CUnaryMinus : public COperation {
public:

    double oneDouble ( double first );

    std::shared_ptr<CExpression> clone() const override;

    void print() const override;

private:

};

class CPlus : public COperator {
public:

private:

};

class CSub : public COperator {

};

class


opAdd()
aplikace operátoru sčítání/zřetězení (+),
opSub()
aplikace operátoru odčítání (-),
opMul()
aplikace operátoru násobení (*),
opDiv()
aplikace operátoru dělení (/),
opPow()
aplikace operátoru umocnění (^),
opNeg()
aplikace operátoru unární mínus (-),
        opEq()
aplikace operátoru porovnání na rovnost (=),
opNe()
aplikace operátoru porovnání na nerovnost (<>),
opLt()
aplikace operátoru porovnání menší než (<),
opLe()
aplikace operátoru porovnání menší nebo rovno (<=),
opGt()
aplikace operátoru porovnání větší než (>),
opGe()

#endif //EXCEL_COPERATOR_H

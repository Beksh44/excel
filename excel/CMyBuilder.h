#ifndef EXCEL_CMYBUILDER_H
#define EXCEL_CMYBUILDER_H
#include <string>
#include <vector>

//x#include "CSpreadsheet.h"

#include "expression.h"
#include "CPos.h"
#include "CExpression.h"

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


#endif EXCEL_CMYBUILDER_H

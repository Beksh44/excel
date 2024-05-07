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
//    CPos position;
//    std::shared_ptr<std::unordered_map <std::string , std::vector<std::shared_ptr<CExpression>>>> ptrToTable;
    std::shared_ptr<std::vector<std::shared_ptr<CExpression>>> ptrToPos;
    std::unordered_map <std::string , std::vector<std::shared_ptr<CExpression>>> m_table;
    CPos m_pos;
public:

    CMyBuilder();

    virtual void opAdd() override;

    virtual void opSub() override;

    virtual void opMul() override;

    virtual void opDiv() override;

    virtual void opPow() override;

    virtual void opNeg() override;

    virtual void opEq() override;

    virtual void opNe() override;

    virtual void opLt() override;

    virtual void opLe() override;

    virtual void opGt() override;

    virtual void opGe() override;

    virtual void valNumber ( double val ) override;

    virtual void valString ( std::string val ) override;

    virtual void valReference ( std::string val ) override;

    virtual void valRange ( std::string val ) override;

    virtual void funcCall ( std::string fnName,
                            int paramCount ) override;

    void printDOuble ();

    void setPtr ( std::shared_ptr<std::vector<std::shared_ptr<CExpression>>> & ptr );

    void setTable ( std::unordered_map <std::string , std::vector<std::shared_ptr<CExpression>>> & data );
};


#endif EXCEL_CMYBUILDER_H

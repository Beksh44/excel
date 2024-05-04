//#include "expression.h"
#pragma once
#include <memory>
#include "CPos.h"

class CExpression {
public:
    virtual std::shared_ptr<CExpression> clone() const = 0;

    virtual void print () const = 0;
    
};

class COperator : public CExpression {

public:
    COperator();
    COperator ( const char & operaTor );

    std::shared_ptr<CExpression> clone() const override;

    void print () const override;

private:
    char m_oper;
};

class CPosition : public CExpression {

public:

    CPosition( CPos pos );

    std::shared_ptr<CExpression> clone() const override;

    void print () const override;
private:
    CPos m_pos;
};

class CDouble : public CExpression {

public:
    CDouble ( double value );

    CDouble ( const CDouble & other );

    std::shared_ptr<CExpression> clone() const override;

    void print () const override;

private:
    double number;
};

class CString : public CExpression {

public:
    CString ( const std::string & str );

    std::shared_ptr<CExpression> clone() const override;

    void print () const override;

private:
    std::string m_str;
};
#ifndef CEXPRESSION_H
#define CEXPRESSION_H
#include <memory>
#include <variant>
#include <string>
#include <unordered_map>
#include <vector>

#include "CPos.h"

using CValue = std::variant<std::monostate, double, std::string>;
using CValue2 = std::variant<std::monostate, double, std::string,CPos>;

class CExpression {
public:
    virtual std::shared_ptr<CExpression> clone() const = 0;

    virtual void print () const = 0;

    virtual CValue2 getValue() = 0;

    virtual bool isDouble() const = 0;

    virtual bool isString() const = 0;

    virtual bool isPos() const = 0;

    virtual bool isOperator() const = 0;

    virtual bool isMonostate() const = 0;

    virtual void serialize ( std::ostream& os ) const = 0;

    virtual bool deSerialize ( std::istream& is ) = 0;

    virtual std::string getType() const = 0;
};

class COperator : public CExpression {
public:
    COperator();
    COperator ( const std::string & operaTor );

    std::shared_ptr<CExpression> clone() const override;

    CValue2 getValue() override;

    void print () const override;

    bool isDouble() const override;

    bool isString() const override;

    bool isPos() const override;

    bool isOperator() const override;

    bool isMonostate() const override;

    void serialize ( std::ostream& os ) const override;

    bool deSerialize ( std::istream& is ) override;

    std::string getType() const;

private:
    std::string m_oper;
};

class CPosition : public CExpression {

public:

    CPosition();

    CPosition ( CPos & pos );

    std::shared_ptr<CExpression> clone() const override;

    CValue2 getValue() override;

    void print () const override;

    bool isOperator() const override;

    bool isDouble() const override;

    bool isString() const override;

    bool isPos() const override;

    bool isMonostate() const override;

    void serialize ( std::ostream& os ) const override;

    bool deSerialize ( std::istream& is ) override;

    std::string getType() const;
private:
    CPos m_pos;
};

class CDouble : public CExpression {

public:

    CDouble();

    CDouble ( double value );

    CDouble ( const CDouble & other );

    std::shared_ptr<CExpression> clone() const override;

    CValue2 getValue() override;

    void print () const override;

    bool isOperator() const override;

    bool isDouble() const override;

    bool isString() const override;

    bool isPos() const override;

    bool isMonostate() const override;

    void serialize ( std::ostream& os ) const override;

    bool deSerialize ( std::istream& is ) override;

    std::string getType() const;
private:
    double m_number;
};

class CString : public CExpression {

public:
    CString();

    CString ( const std::string & str );

    std::shared_ptr<CExpression> clone() const override;

    CValue2 getValue() override;

    void print () const override;

    bool isOperator() const override;

    bool isDouble() const override;

    bool isString() const override;

    bool isPos() const override;

    bool isMonostate() const override;

    void serialize ( std::ostream& os ) const override;

    bool deSerialize ( std::istream& is ) override;

    std::string getType() const;
private:
    std::string m_str;
};

#endif CEXPRESSION_H
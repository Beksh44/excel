#include "getValue.h"
#include "stack"

CValue add ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double>( left ) && std::holds_alternative<double> ( right ) )
        return std::get<double> ( left ) + std::get<double> ( right );
    if ( std::holds_alternative<double> ( left) && std::holds_alternative<double> ( right ) )
        return std::get<std::string>( left ) + std::get<std::string>( right );
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<std::string> ( right ) )
        return std::to_string ( std::get<double>( left ) ) + std::get<std::string>( right );
    if ( std::holds_alternative<std::string> ( left ) && std::holds_alternative<double> ( right ) )
        return std::get<std::string>( left ) + std::to_string( std::get<double>( right ) );

    return std::monostate();
}

//template<typename T, typename U, typename Op>
//std::variant<std::monostate, T> binaryOperation(const T& left, const U& right, Op operation) {
//    if constexpr (std::is_same_v<T, U>) {
//        return operation(left, right);
//    } else {
//        return std::monostate();
//    }
//}

//template<typename T, typename U>
//std::variant<std::monostate, T> sub ( const T & left, const U & right ) {
//    return binaryOperation(left, right, [] ( auto l, auto r) { return l - r; });
//}
//
//template<typename T, typename U>
//std::variant<std::monostate, T> div(const T& left, const U& right) {
//    return binaryOperation(left, right, [](auto l, auto r) { return l / r; });
//}

CValue sub ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<double> ( right ) )
        return std::get<double> ( left ) - std::get<double> ( right );

    return std::monostate();
}

CValue div ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<double> ( right ) ) {
        double l = std::get<double> ( left );
        double r = std::get<double> ( right );
            if ( r == 0 )
                return std::monostate();
            else
                return l / r;
    }

    return std::monostate();
}

CValue mul ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<double> ( right ) )
        return std::get<double> ( left ) * std::get<double> ( right );

    return std::monostate();
}

CValue pow ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<double> ( right ) )
        return pow ( std::get<double> ( left ) , std::get<double> ( right ) );

    return std::monostate();
}

CValue unaryMinus ( const CValue & value ) {
    if ( std::holds_alternative<double> ( value ) )
        return -std::get<double> ( value );

    return std::monostate();
}

CValue eq ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<double> ( right ) ) {
        if ( std::get<double> ( left ) == std::get<double> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    if ( std::holds_alternative<std::string> ( left ) && std::holds_alternative<std::string> ( right ) ) {
        if ( std::get<std::string> ( left ) == std::get<std::string> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    return std::monostate();
}

CValue ne ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<double> ( right ) ) {
        if ( std::get<double> ( left ) != std::get<double> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    if ( std::holds_alternative<std::string> ( left ) && std::holds_alternative<std::string> ( right ) ) {
        if ( std::get<std::string> ( left ) != std::get<std::string> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    return std::monostate();
}

CValue lt ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<double> ( right ) ) {
        if ( std::get<double> ( left ) < std::get<double> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    if ( std::holds_alternative<std::string> ( left ) && std::holds_alternative<std::string> ( right ) ) {
        if ( std::get<std::string> ( left ) < std::get<std::string> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    return std::monostate();
}

CValue le ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<double> ( right ) ) {
        if ( std::get<double> ( left ) <= std::get<double> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    if ( std::holds_alternative<std::string> ( left ) && std::holds_alternative<std::string> ( right ) ) {
        if ( std::get<std::string> ( left ) <= std::get<std::string> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    return std::monostate();
}

CValue gt ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<double> ( right ) ) {
        if ( std::get<double> ( left ) > std::get<double> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    if ( std::holds_alternative<std::string> ( left ) && std::holds_alternative<std::string> ( right ) ) {
        if ( std::get<std::string> ( left ) > std::get<std::string> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    return std::monostate();
}

CValue ge ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<double> ( right ) ) {
        if ( std::get<double> ( left ) >= std::get<double> ( right ) )
            return 1.0;
        else
            return 0.0;
    }
    if ( std::holds_alternative<std::string> ( left ) && std::holds_alternative<std::string> ( right ) ) {
        if ( std::get<std::string> ( left ) >= std::get<std::string> ( right ) )
             return 1.0;
        else
             return 0.0;
    }
    return std::monostate();
}
//скинуть гпт сказать сделать меньше


CValue getVal ( const CPos & pos , std::unordered_map <std::string , std::vector<std::shared_ptr<CExpression>>> & m_data ) {
    if ( ! m_data.contains ( pos.getPosStr() ) )//if there is nothing at this position
        return std::monostate();

    std::vector<std::shared_ptr<CExpression>> * expression = &m_data [ pos.getPosStr() ];
    std::stack<CValue> myStack;
    CValue tmpVal;
    for ( const auto & it : ( * expression ) ) {
        if ( ( * it ).isMonostate() )
            return std::monostate();
        else if ( ( * it ).isOperator() ) {
            std::string str = std::get<std::string>( ( * it ).getValue() );
            if ( str != "unar" ) {
                CValue right = myStack.top();
                myStack.pop();
                CValue left = myStack.top();
                myStack.pop();
                if ( str == "+" )
                    tmpVal = add ( left , right );
                else if ( str == "-" )
                    tmpVal = sub ( left , right );
                else if ( str == "*" )
                    tmpVal = mul ( left , right );
                else if ( str == "/" )
                    tmpVal = div ( left , right );
                else if ( str == "^" )
                    tmpVal = pow ( left , right );
                else if ( str == "==" )
                    tmpVal = eq ( left , right );
                else if ( str == "!=" )
                    tmpVal = ne ( left , right );
                else if ( str == "<" )
                    tmpVal = lt ( left , right );
                else if ( str == "<=" )
                    tmpVal = le ( left , right );
                else if ( str == ">" )
                    tmpVal = gt ( left , right );
                else if ( str == ">=" )
                    tmpVal = ge ( left , right );
            } else {
                CValue value = myStack.top();
                myStack.pop();
                tmpVal = unaryMinus ( value );
            }
        } else {
            if ( ( * it ) . isPos() )
                tmpVal = getVal ( std::get<CPos>( ( * it ).getValue() )  , m_data );
            else {
                if ( ( * it ) . isDouble() )
                    tmpVal = std::get<double> ( ( * it ) . getValue() );
                else if ( ( * it ) . isString() )
                    tmpVal = std::get<std::string> ( ( * it ) . getValue() );
            }
        }
        myStack.push ( tmpVal );
    }
    return myStack.top();
}
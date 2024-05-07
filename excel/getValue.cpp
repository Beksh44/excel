#include "getValue.h"

CValue Add ( const CExpression & left , const CExpression & right ) {
    if ( left.isMonostate() || right.isMonostate() )
        return std::monostate();
    if ( left.isDouble() && right.isDouble() )
        return std::get<double> ( left.getValue() ) + std::get<double> ( right.getValue() );
    if ( left.isString() && right.isString() )
        return std::get<std::string>( left.getValue() ) + std::get<std::string>( right.getValue() );
    if ( left.isDouble() && right.isString() )
        return std::to_string ( std::get<double>( left.getValue() ) ) + std::get<std::string>( right.getValue() );
    if ( left.isString() && right.isDouble() )
        return std::get<std::string>( left.getValue() ) + std::to_string( std::get<double>( right.getValue() ) );
    return std::monostate();
}

CValue Sub ( const CExpression & left , const CExpression & right ) {
    if ( left.isMonostate() || right.isMonostate() )
        return std::monostate();
    if ( left.isDouble() && right.isDouble() )
        return std::get<double> ( left.getValue() ) - std::get<double> ( right.getValue() );

    return std::monostate();
}

CValue Div ( const CExpression & left , const CExpression & right ) {
    if ( left.isMonostate() || right.isMonostate() )
        return std::monostate();
    if ( left.isDouble() && right.isDouble() )
        return std::get<double>(left.getValue()) / std::get<double>(right.getValue());

    return std::monostate();
}

CValue Mul ( const CExpression & left , const CExpression & right ) {
    if ( left.isMonostate() || right.isMonostate() )
        return std::monostate();
    if ( left.isDouble() && right.isDouble() )
        return std::get<double>( left.getValue() ) * std::get<double>( right.getValue() );

        return std::monostate();
}

CValue Pow ( const CExpression & left , const CExpression & right ) {
    if ( left.isMonostate() || right.isMonostate() )
        return std::monostate();
    if ( left.isDouble() && right.isDouble() )
        return std::get<double>( left.getValue() ) * std::get<double>( right.getValue() );

    return std::monostate();
}

CValue UnaryMinus ( const CExpression & left ) {
    if ( left.isMonostate() )
        return std::monostate();
    if ( left.isDouble() )
        return -std::get<double>(left.getValue());

    return std::monostate();
}

CValue getVal ( CPos & pos , std::unordered_map <std::string , std::vector<std::shared_ptr<CExpression>>> m_data ) {
    if ( m_data[ pos.getPosStr() ].size() == 0 )//if there is nothing at this position
        return std::monostate();

    if ( m_data[ pos.getPosStr() ].size() == 1 )//if there is only one value in vector at this position then it's not expression thus we just return what is stored there
        return ( m_data[ pos.getPosStr() ][0] )->getValue();

    for ( const auto & it : m_data[ pos.getPosStr() ] ) {
        if ( ( * it ).isMonostate() )
            return std::monostate();


    }
}
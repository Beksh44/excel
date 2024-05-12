#include "operators.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CValue add ( const CValue & left , const CValue & right ) {
    if ( std::holds_alternative<double>( left ) && std::holds_alternative<double> ( right ) )
        return std::get<double> ( left ) + std::get<double> ( right );
    if ( std::holds_alternative<std::string> ( left ) && std::holds_alternative<std::string> ( right ) )
        return std::get<std::string>( left ) + std::get<std::string>( right );
    if ( std::holds_alternative<double> ( left ) && std::holds_alternative<std::string> ( right ) )
        return std::to_string ( std::get<double>( left ) ) + std::get<std::string>( right );
    if ( std::holds_alternative<std::string> ( left ) && std::holds_alternative<double> ( right ) )
        return std::get<std::string>( left ) + std::to_string( std::get<double>( right ) );

    return std::monostate();
}

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
        return ( -1 ) * std::get<double> ( value );

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
    if ( std::holds_alternative< double > ( left ) && std::holds_alternative< double > ( right ) ) {
        if ( std::get<double> ( left ) != std::get< double > ( right ) )
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
#include <variant>
#include <string>

using CValue = std::variant<std::monostate, double, std::string>;

CValue add ( const CValue & left , const CValue & right );

CValue sub ( const CValue & left , const CValue & right );

CValue div ( const CValue & left , const CValue & right );

CValue mul ( const CValue & left , const CValue & right );

CValue pow ( const CValue & left , const CValue & right );

CValue unaryMinus ( const CValue & value );

CValue eq ( const CValue & left , const CValue & right );

CValue neq ( const CValue & left , const CValue & right );

CValue lt ( const CValue & left , const CValue & right );

CValue lte ( const CValue & left , const CValue & right );

CValue gt ( const CValue & left , const CValue & right );

CValue gte ( const CValue & left , const CValue & right );

CValue ne ( const CValue & left , const CValue & right );

CValue ge ( const CValue & left , const CValue & right );

CValue le ( const CValue & left , const CValue & right );

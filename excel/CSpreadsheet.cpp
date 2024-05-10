#include <variant>
#include <optional>
#include <compare>
#include <charconv>
#include <span>
#include <utility>
#include <iostream>

#include "CSpreadsheet.h"
#include "getValue.h"
#include "CMyBuilder.h"

CSpreadsheet::CSpreadsheet() = default;

CSpreadsheet::CSpreadsheet ( const CSpreadsheet & other ) {

}

bool CSpreadsheet::setCell ( CPos pos , std::string contents ) {
    CMyBuilder tmp;
    std::shared_ptr< std::vector<std::shared_ptr<CExpression>>> ptr = std::make_shared<std::vector<std::shared_ptr<CExpression>>>( m_data [ pos .getPosStr() ]);
    ptr->clear();
    tmp.setPtr ( ptr );
    tmp.setTable ( m_data );
    parseExpression ( contents , tmp );
    //std::cout << "tmp is " << tmp.
    m_data[ pos.getPosStr() ] = *ptr;
    return true;
}

CValue CSpreadsheet::getValue ( CPos pos ) {
    return getVal ( pos , m_data );
}

void CSpreadsheet::copyRect ( CPos dst , CPos src , int w , int h ) {
    long int diffWidth = dst.getPosInt().first - src.getPosInt().first;
    int diffHeight = dst.getPosInt().second - src.getPosInt().second;

    std::pair<long long int, int > offset = src.getPosInt();
    for ( int i = 0; i < h; ++i ) {
        for ( int j = 0; j < w; ++j ) {
            std::string tmpStr;
            tmpStr = src.toStr ( offset.first + j ); // moving our position by width
            tmpStr += std::to_string( offset.second + i );// moving our position by height

            if ( m_data.contains ( tmpStr ) ) {// if it's not a monostate
                std::vector< std::shared_ptr< CExpression > > * value = & m_data [ tmpStr ];//getting the value in that position
                std::vector< std::shared_ptr< CExpression > > toPush;
                for ( const auto & it : ( * value ) ) {//going through the value or expression
                    if ( it->isPos() ) {
                         CPos pos2 = std::get<CPos>( (* it ) . getValue() );

                         tmpStr = pos2.toStr ( pos2.getPosInt().first + ( ( pos2.isFixedColumn() ) ? 0 : diffWidth ) );
                         tmpStr += std::to_string ( pos2.getPosInt().second + ( ( pos2.isFixedRow() ) ? 0 : diffHeight ) );
                         CPos tmpPos ( tmpStr );

                         if ( pos2.isFixedColumn() )
                             tmpPos.setFixedColumn ( true );
                         if ( pos2.isFixedRow() )
                             tmpPos.setFixedRow ( true );

                         CPosition posToPush ( tmpPos );
                         toPush . emplace_back ( posToPush . clone() );
                    } else {
                        toPush . emplace_back ( it->clone() );
                    }
                }
                tmpStr = dst.toStr ( dst.getPosInt().first + j ); // moving our position by width
                tmpStr += std::to_string( dst.getPosInt().second + i );//adding position in columns
                m_data [ tmpStr ] = toPush;
            }
        }
    }

}


void serializeString ( std::ostream & os, const std::string & str ) {
    int length = str.size();
    os.write ( reinterpret_cast < const char * > ( & length ), sizeof ( length ) );
    os.write ( str.data() , length );
}


void serializeInt(std::ostream& os, int value ) {
    os.write ( reinterpret_cast < const char * > ( & value ), sizeof ( value ) );
}


bool deserializeString( std::istream & is, std::string & str ) {
    int size;

    if ( ! is.read ( reinterpret_cast < char * > ( & size ) , sizeof ( size ) ) )
        return false;

    std::string str2 ( size , '\0' );
    is.read ( & str2 [ 0 ] , size );
    str = str2;

    return true;
}

bool deserializeInt(std::istream& is, int & value) {
    if ( ! is.read ( reinterpret_cast< char * > ( & value ), sizeof ( value ) ) ) {
        return false; // Error reading integer
    }
    return true;
}


bool CSpreadsheet::save ( std::ostream & os ) const {
    int size = m_data.size();
    os.write ( reinterpret_cast < const char * > ( & size ), sizeof ( size ) );
    for (const auto& pair : m_data) {

        serializeString(os, pair.first);// Write position to stream

        int vecSize = pair.second.size();
        serializeInt(os, vecSize);

        for ( const auto & expr : pair.second ) {
            serializeString ( os, expr -> getType() );// Serialize expression type
            expr -> serialize ( os );
        }
    }
    return true;
}


//bool CSpreadsheet::load ( std::istream & is ) {
//    std::string position;
//    while ( is >> position ) {
//        size_t vecSize;
//        if ( ! is.read ( reinterpret_cast< char * > ( & vecSize ), sizeof ( vecSize ) ) ) {
//            return false; // Error reading vector size
//        }
//        m_data [ position ] .resize ( vecSize );
//
//        for ( size_t i = 0; i < vecSize; ++i) {
//            std::string exprType;
//            if ( ! ( is >> exprType ) ) {
//                return false; // Error reading expression type
//            }
//
//            // Create expression based on type
//            if (exprType == "CDouble") {
//                m_data [ position ] [ i ] = std::make_shared<CDouble>();
//            } else if (exprType == "CString") {
//                m_data [ position ] [ i ] = std::make_shared<CString>();
//            } else if (exprType == "CPosition") {
//                m_data [ position ] [ i ] = std::make_shared<CPosition>();
//            } else if (exprType == "COperator") {
//                m_data [ position ] [ i ] = std::make_shared<COperator>();
//            } else {
//                return false; // Unknown expression type
//            }
//
//            // Deserialize expression data
//            if ( ! m_data [ position ] [ i ] -> deSerialize ( is ) ) {
//                return false; // Error deserializing expression
//            }
//        }
//    }
//
//    return true;
//}


bool CSpreadsheet::load(std::istream& is) {
    std::string position;
    int size;
    if ( ! deserializeInt( is , size ) )
        return false;

    for (int i = 0 ;i < size; i++ ) {
        if ( ! deserializeString ( is , position ) )
            return false;

        int vecSize;
        if ( ! deserializeInt ( is, vecSize ) )
            return false; // Error reading vector size


        m_data [ position ]. resize ( vecSize );

        for (size_t i = 0; i < vecSize; ++i) {
            std::string exprType;
            if (!deserializeString(is, exprType)) {
                return false; // Error reading expression type
            }

            // Create expression based on type
            if (exprType == "CDouble") {
                CDouble tmp;
                if ( ! tmp.deSerialize ( is ) )
                    return false;
                m_data[position][i] = std::make_shared<CDouble> ( tmp );
            } else if (exprType == "CString") {
                CString tmp;
                if ( ! tmp.deSerialize ( is ) )
                    return false;
                m_data[position][i] = std::make_shared<CString> ( tmp );
            } else if (exprType == "CPosition") {
                CPosition tmp;
                if ( ! tmp.deSerialize ( is ) )
                    return false;
                m_data[position][i] = std::make_shared<CPosition> ( tmp );
            } else if ( exprType == "COperator") {
                COperator tmp;
                if ( ! tmp.deSerialize ( is ) )
                    return false;
                m_data[position][i] = std::make_shared<COperator> ( tmp );
            } else {
                return false;
            }

            // Deserialize expression data
//            if (!m_data[position][i]->deSerialize(is)) {
//                return false; // Error deserializing expression
//            }
        }
    }

    return true;
}

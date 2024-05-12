#include <variant>
#include <optional>
#include <compare>
#include <charconv>
#include <span>
#include <utility>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>

#include "CSpreadsheet.h"
#include "CMyBuilder.h"
#include "operators.h"

//serializing functions

/**
 * @param os
 * @param str
 *
 * This function serializes a string to the output stream
 */
void serializeString ( std::ostream & os, const std::string & str );


/**
 *
 * @param os
 * @param value
 *
 * This function serializes an integer to the output stream
 */

void serializeInt(std::ostream& os, int value );

/**
 *
 * @param is
 * @param str
 *
 * @return true if the string was deserialized successfully
 * This function deserializes a string of the input stream
 */

bool deserializeString( std::istream & is, std::string & str );

/**
 *
 * @param is
 * @param value
 * @return true if the integer was deserialized successfully
 *
 * This function deserializes an integer of the input stream
 */
bool deserializeInt ( std::istream & is, int & value );

/**
 *
 * @param graph
 * @param node
 * @param visited
 * @param currentlyVisiting
 * @return true if there is a cycle
 *
 * This function is a recursive algorithm of depth first search
 */

bool dfs ( const std::unordered_map <std::string , std::vector<std::shared_ptr<CExpression>>> & graph ,
           const std::string & node,
           std::unordered_set < std::string > & visited,
           std::unordered_set < std::string > & currentlyVisiting );

//////////////////////////////////////////////CSpreadsheet implementation
CSpreadsheet::CSpreadsheet() = default;

CSpreadsheet::CSpreadsheet ( const CSpreadsheet & other ) {
    for ( const auto & pair : other.m_data ) {
        const std::string & key = pair.first;
        for ( const auto & expr : pair.second ) {
            m_data [ key ].push_back ( expr -> clone() );
        }
    }
}

bool CSpreadsheet::setCell ( CPos pos , std::string contents ) {
    CMyBuilder tmp;
    std::shared_ptr< std::vector<std::shared_ptr<CExpression>>> ptr = std::make_shared<std::vector<std::shared_ptr<CExpression>>>( m_data [ pos .getPosStr() ]);
    ptr->clear();
    tmp.setPtr ( ptr );
    parseExpression ( contents , tmp );
    m_data[ pos.getPosStr() ] = *ptr;
    return true;
}

CValue CSpreadsheet::getValue ( CPos pos ) {

    if ( ! m_data.contains ( pos.getPosStr() ) )//if there is nothing at this position
        return std::monostate();


    std::unordered_set < std::string > visited;
    std::unordered_set < std::string > currentlyVisiting;
    if ( dfs ( m_data , pos.getPosStr() , visited, currentlyVisiting ) )//if there is a cycle
        return std::monostate();

    std::vector<std::shared_ptr<CExpression>> * expression = & m_data [ pos.getPosStr() ];//getting the value at this position
    std::stack<CValue> myStack;
    CValue tmpVal;//temporary value to push to the stack
    for ( const auto & it : ( * expression ) ) {//going through the expression
        if ( ( it ) -> isPos() ) {//if it is a position
            if ( ! m_data.contains ( ( std::get< CPos >( it->getValue() ) ) .getPosStr() ) )//if there is nothing at this position
                return std::monostate();
        }
        if ( ( * it ).isOperator() ) {//if it is an operator
            std::string str = std::get<std::string>( ( * it ).getValue() );
            if ( str != "unar" ) {//if it is binary operator
                CValue right = myStack.top();
                myStack.pop();
                CValue left = myStack.top();
                myStack.pop();
                //checking every possible operator
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
            } else {//if it is a unary operator
                CValue value = myStack.top();
                myStack.pop();
                tmpVal = unaryMinus ( value );
            }
        } else {//if it is not an operator
            if ( ( * it ) . isPos() )//if it is a position
                tmpVal = getValue ( std::get<CPos>( ( * it ).getValue() ) );
            else {//if it is a value(double or string)
                if ( ( * it ) . isDouble() )
                    tmpVal = std::get<double> ( ( * it ) . getValue() );
                else if ( ( * it ) . isString() )
                    tmpVal = std::get<std::string> ( ( * it ) . getValue() );
            }
        }
        myStack.push ( tmpVal );//pushing the value to the stack
    }
    return myStack.top();//returning the top of the stack which is the final value
}

void CSpreadsheet::copyRect ( CPos dst , CPos src , int w , int h ) {

    long int diffWidth = dst.getPosInt().first - src.getPosInt().first;//difference in width
    int diffHeight = dst.getPosInt().second - src.getPosInt().second;//difference in height

    std::unordered_map< std::string , std::vector<std::shared_ptr<CExpression>>> tmpMap;//temporary map to store the values

    for ( int i = 0; i < h; ++i ) {//going through the height
        for ( int j = 0; j < w; ++j ) {//going through the width
            std::string tmpStr;
            tmpStr = src.toStr ( src.getPosInt().first + j ); // moving our position by width
            tmpStr += std::to_string( src.getPosInt().second + i );// moving our position by height

            if ( m_data.contains ( tmpStr ) ) {// if it's not a monostate
                std::vector< std::shared_ptr< CExpression > > * value = & m_data [ tmpStr ];//getting the value in that position
                std::vector< std::shared_ptr< CExpression > > toPush;
                for ( const auto & it : ( * value ) ) {//going through the value or expression
                    if ( it->isPos() ) {//if it is a position
                        CPos pos2 = std::get<CPos>( (* it ) . getValue() );//getting the position

                        tmpStr = pos2.toStr ( pos2.getPosInt().first + ( ( pos2.isFixedColumn() ) ? 0 : diffWidth ) );//moving the position by width
                        tmpStr += std::to_string ( pos2.getPosInt().second + ( ( pos2.isFixedRow() ) ? 0 : diffHeight ) );//moving the position by height
                        CPos tmpPos ( tmpStr );

                        if ( pos2.isFixedColumn() )//if the column is fixed
                            tmpPos.setFixedColumn ( true );
                        if ( pos2.isFixedRow() )//if the row is fixed
                            tmpPos.setFixedRow ( true );

                        CPosition posToPush ( tmpPos );//creating a new position to push
                        toPush . emplace_back ( posToPush . clone() );//pushing the new position
                    } else {
                        toPush . emplace_back ( it->clone() );//pushing the value that is not a position
                    }
                }
                tmpStr = dst.toStr ( dst.getPosInt().first + j ); // moving our position by width
                tmpStr += std::to_string( dst.getPosInt().second + i );//adding position in columns
                tmpMap [ tmpStr ] = toPush;//pushing the value to the map
            }
        }
    }

    for ( const auto & it : tmpMap ) {//going through the map
        if ( ! m_data.contains( it.first ) )
            m_data [ it.first ] = it.second;//if the position is not in the map, add it
        else {
            m_data . erase( it.first );//if the position is in the map, erase it
            m_data [ it.first ] = it.second;//add the new value
        }
    }
}

bool CSpreadsheet::save ( std::ostream & os ) const {
    int size = m_data.size();
    os.write ( reinterpret_cast < const char * > ( & size ), sizeof ( size ) );
    for ( const auto& pair : m_data ) {

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

        for (int i = 0; i < vecSize; ++i) {
            std::string exprType;
            if (!deserializeString(is, exprType)) {
                return false; // Error reading expression type
            }
            // Create expression based on type
            if ( exprType == "CDouble" ) {//if it is a double
                CDouble tmp;
                if ( ! tmp.deSerialize ( is ) )
                    return false;
                m_data[position][i] = std::make_shared<CDouble> ( tmp );
            } else if ( exprType == "CString" ) {//if it is a string
                CString tmp;
                if ( ! tmp.deSerialize ( is ) )
                    return false;
                m_data[position][i] = std::make_shared<CString> ( tmp );
            } else if ( exprType == "CPosition" ) {//if it is a position
                CPosition tmp;
                if ( ! tmp.deSerialize ( is ) )
                    return false;
                m_data[position][i] = std::make_shared<CPosition> ( tmp );
            } else if ( exprType == "COperator" ) {//if it is an operator
                COperator tmp;
                if ( ! tmp.deSerialize ( is ) )
                    return false;
                m_data[position][i] = std::make_shared<COperator> ( tmp );
            } else {
                return false;
            }
        }
    }

    return true;
}


///////////////////////////////////////////////////////////////////////////////////recursive algorithm of dfs

/**
 *
 * @param graph
 * @param node
 * @param visited
 * @param currentlyVisiting
 *
 * @return true if there is a cycle
 * This function is a recursive algorithm of depth first search
 */

bool dfs ( const std::unordered_map <std::string , std::vector<std::shared_ptr<CExpression>>> & graph ,
           const std::string & node,
           std::unordered_set < std::string > & visited,
           std::unordered_set < std::string > & currentlyVisiting ) {

    if ( currentlyVisiting.find ( node ) != currentlyVisiting.end() )
        return true;


    if ( visited.find ( node ) != visited.end() )
        return false;


    visited.insert ( node );
    currentlyVisiting.insert ( node );

    if ( graph.contains ( node ) ) {
        for ( const auto & neighbor : graph.at ( node ) ) {
            if ( neighbor -> isPos () ) {
                if ( dfs ( graph, ( std::get < CPos > ( neighbor -> getValue () ) ).getPosStr(), visited, currentlyVisiting ) )
                    return true;
            }
        }
    }

    currentlyVisiting.erase ( node );

    return false;
}


////////////////////////////////////////////////////////////////////////////serializing functions

/**
 * @param os
 * @param str
 *
 * This function serializes a string to the output stream
 */
void serializeString ( std::ostream & os, const std::string & str ) {
    int length = str.size();
    os.write ( reinterpret_cast < const char * > ( & length ), sizeof ( length ) );
    os.write ( str.data() , length );
}

/**
 *
 * @param os
 * @param value
 *
 * This function serializes an integer to the output stream
 */
void serializeInt ( std::ostream & os, int value ) {
    os.write ( reinterpret_cast < const char * > ( & value ), sizeof ( value ) );
}

/**
 *
 * @param is
 * @param str
 *
 * This function deserializes a string of the input stream
 * @return true if the string was deserialized successfully
 */

bool deserializeString( std::istream & is, std::string & str ) {
    int size;

    if ( ! is.read ( reinterpret_cast < char * > ( & size ) , sizeof ( size ) ) )
        return false;

    std::string str2 ( size , '\0' );
    is.read ( & str2 [ 0 ] , size );
    str = str2;

    return true;
}

/**
 *
 * @param is
 * @param value
 *
 * This function deserializes an integer of the input stream
 * @return true if the integer was deserialized successfully
 */

bool deserializeInt ( std::istream & is, int & value ) {
    if ( ! is.read ( reinterpret_cast< char * > ( & value ), sizeof ( value ) ) ) {
        return false; // Error reading integer
    }
    return true;
}
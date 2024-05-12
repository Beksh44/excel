#include <string>
#include <iostream>
#ifndef CPOS_H
#define CPOS_H

class CPos {
public:
    CPos() = default;
    CPos ( std::string_view str );
    /*
     * Convert a string to an integer
     * @param pos - string
     * @param posInt - pair of integers
     */
    void toInt ( const std::string & pos , std::pair<long long int , int> & posInt );
    /*
     * Convert integer to a string
     * @param posInt - integer
     * @return the string
     */
    std::string toStr ( long long int posInt );
    /*
     * Get the position as a string
     * @return the string
     */
    std::string  getPosStr () const;
    /*
     * Get the position as an integer
     * @return the integer
     */
    std::pair<long long int , int> getPosInt () const;
    /*
     * Check if the column is fixed
     * @return true if the column is fixed, false otherwise
     */
    bool isFixedColumn() const;
    /*
     * Check if the row is fixed
     * @return true if the row is fixed, false otherwise
     */
    bool isFixedRow() const;
    /*
     * Set the fixed column
     * @param toSet - true if the column should be fixed, false otherwise
     */
    void setFixedColumn ( bool toSet );
    /*
     * Set the fixed row
     * @param toSet - true if the row should be fixed, false otherwise
     */
    void setFixedRow ( bool toSet );
    /*
     * Serialize the object
     * @param out - output stream
     */
    void serialize ( std::ostream & out ) const;
    /*
     * Deserialize the object
     * @param in - input stream
     * @return true if the object was deserialized, false otherwise
     */
    bool deSerialize ( std::istream & in );

private:
    std::string m_str;
    bool m_fixedColumn;
    bool m_fixedRow;
    std::pair< long long int , int> m_int;
};

#endif CPOS_H
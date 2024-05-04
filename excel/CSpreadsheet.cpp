#include <variant>
#include <optional>
#include <compare>
#include <charconv>
#include <span>
#include <utility>

using namespace std::literals;
using CValue = std::variant<std::monostate, double, std::string>;

constexpr unsigned SPREADSHEET_CYCLIC_DEPS = 0x01;
constexpr unsigned SPREADSHEET_FUNCTIONS = 0x02;
constexpr unsigned SPREADSHEET_FILE_IO = 0x04;
constexpr unsigned SPREADSHEET_SPEED = 0x08;
constexpr unsigned SPREADSHEET_PARSER = 0x10;

#include "CSpreadsheet.h"

bool CSpreadsheet::setCell ( CPos pos , std::string contents ) {
    if ( contents.empty() )
        m_data[ pos.getPos() ] = contents;

    try  {
        m_data[ pos.getPos() ] = std::stod ( contents );
    }
    catch ( const std::invalid_argument ) {
        m_data[ pos.getPos() ] = contents;
    }

    return true;
}
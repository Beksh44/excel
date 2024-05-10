#include <variant>
#include <optional>
#include <compare>
#include <charconv>
#include <span>
#include <utility>
#include <map>
#ifndef CSPREADSHEET_H
#define CSPREADSHEET_H
#pragma once


#include "CExpression.h"
#include "CPos.h"

constexpr unsigned SPREADSHEET_CYCLIC_DEPS = 0x01;
constexpr unsigned SPREADSHEET_FUNCTIONS = 0x02;
constexpr unsigned SPREADSHEET_FILE_IO = 0x04;
constexpr unsigned SPREADSHEET_SPEED = 0x08;
constexpr unsigned SPREADSHEET_PARSER = 0x10;

using CValue = std::variant<std::monostate, double, std::string>;


class CSpreadsheet {
public:
    static unsigned capabilities() {
        return SPREADSHEET_CYCLIC_DEPS | SPREADSHEET_FUNCTIONS | SPREADSHEET_FILE_IO | SPREADSHEET_SPEED ;
        // | SPREADSHEET_PARSER
    }

    CSpreadsheet();

    CSpreadsheet( const CSpreadsheet & other );

    bool load ( std::istream & is );

    bool save ( std::ostream & os ) const;

    bool setCell ( CPos pos,
                   std::string contents );

    CValue getValue ( CPos pos );

    void copyRect ( CPos dst,
                    CPos src,
                    int w = 1,
                    int h = 1 );

private:
    std::unordered_map <std::string , std::vector<std::shared_ptr<CExpression>>> m_data;
};

#endif CSPREADSHEET_H
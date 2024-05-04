#include <variant>
#include <optional>
#include <compare>
#include <charconv>
#include <span>
#include <utility>

using namespace std::literals;
using CValue = std::variant<std::monostate, double, std::string>;

#include "CPos.h"
#include "expression.h"
#include "CStore.h"

class CSpreadsheet {
public:
    static unsigned capabilities() {
        return SPREADSHEET_CYCLIC_DEPS | SPREADSHEET_FUNCTIONS | SPREADSHEET_FILE_IO | SPREADSHEET_SPEED ;
        // | SPREADSHEET_PARSER
    }

    CSpreadsheet() = default;

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
    std::unordered_map <std::string ,CStore> m_data;
};
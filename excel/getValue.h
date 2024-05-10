#include <variant>
#include <optional>
#include <compare>
#include <charconv>
#include <span>
#include <utility>
#include <map>
#include "CExpression.h"

CValue getVal ( const CPos & pos , std::unordered_map <std::string , std::vector<std::shared_ptr<CExpression>>> & m_data );
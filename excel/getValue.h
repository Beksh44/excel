#include <variant>
#include <optional>
#include <compare>
#include <charconv>
#include <span>
#include <utility>
#include <map>
#include "CExpression.h"

CValue Add ( const CExpression & first , const CExpression & second );

CValue getVal ( CPos & pos , std::unordered_map <std::string , std::vector<std::shared_ptr<CExpression>>> m_data );
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cctype>
#include <algorithm>
#include <string>
#include <list>

bool case_insensitive_cmp(char lhs, char rhs);
bool string_compare_ignorecase(const std::string& lhs, const std::string& rhs);
std::string toLowerCase(const std::string& str);
bool list_contains_ignorecase(const std::list<std::string>& lst, const std::string& value);

#endif
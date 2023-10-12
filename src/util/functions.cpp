#include "functions.h"
#include <cctype>
#include <algorithm>
#include <string>
#include <list>

bool case_insensitive_cmp(char lhs, char rhs)
{
    return std::toupper(lhs) < std::toupper(rhs);
}

bool string_compare_ignorecase(const std::string& lhs,
    const std::string& rhs)
{
    return std::lexicographical_compare(lhs.begin(),
        lhs.end(),
        rhs.begin(),
        rhs.end(),
        case_insensitive_cmp);
}

//// Function to convert a string to lower case
std::string toLowerCase(const std::string& str) {
   std::string lowerStr = str;
   std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
   return lowerStr;
}

//
//// Function to check if a list contains a string, case-insensitively
bool list_contains_ignorecase(const std::list<std::string>& lst, const std::string& value) {
   std::string lowerValue = toLowerCase(value);
   for (const auto& element : lst) {
       if (toLowerCase(element) == lowerValue) {
           return true;
       }
   }
   return false;
}

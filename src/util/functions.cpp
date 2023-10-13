#include "functions.h"
#include <cctype>
#include <algorithm>
#include <locale>
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
// trim from start (in place)
void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

// trim from start (copying)
std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
std::string trim_copy(std::string s) {
    trim(s);
    return s;
}
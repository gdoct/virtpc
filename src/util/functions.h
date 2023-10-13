#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cctype>
#include <algorithm>
#include <string>
#include <list>

inline bool case_insensitive_cmp(char lhs, char rhs) {
	return std::toupper(lhs) < std::toupper(rhs);
}

inline bool string_compare_ignorecase(const std::string& lhs, const std::string& rhs) {
    return std::lexicographical_compare(lhs.begin(),
        lhs.end(),
        rhs.begin(),
        rhs.end(),
        case_insensitive_cmp);
}

inline std::string to_lower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

//
//// Function to check if a list contains a string, case-insensitively
static bool list_contains_ignorecase(const std::list<std::string>& lst, const std::string& value) {
    std::string lowerValue = to_lower(value);
    for (const auto& element : lst) {
        if (to_lower(element) == lowerValue) {
            return true;
        }
    }
    return false;
}

// trim from start (in place)
inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));
}

// trim from end (in place)
inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}

// trim from both ends (in place)
inline void trim(std::string& s) {
    rtrim(s);
    ltrim(s);
}

// trim from start (copying)
inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

#endif
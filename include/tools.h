#ifndef TOOLS_H
#define TOOLS_H

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

std::vector<std::string> SplitString(const std::string& str, char delimiter);
std::vector<std::string> SplitString(const std::string& str);

template <typename T>
bool IsSmaller(const vector<T>& first, const vector<T>& second) {
    return lexicographical_compare(
        first.begin(), first.end(),
        second.begin(), second.end()
    );
}
#endif
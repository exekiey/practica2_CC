#pragma once
#include <string>

using namespace std;

class Symbol {
private:
    std::string name;
    
public:
    static Symbol emptySymbol;
    Symbol(const string& name);
    Symbol();
    string GetName() const;
    bool operator<(const Symbol& other) const;
    bool operator==(const Symbol& other) const;
    bool IsEmptySymbol() const;
    static void SetEmptySymbol(const string& epsilonName);
};
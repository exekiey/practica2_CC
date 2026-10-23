#include "symbol.h"
#include <string>

using namespace std;

Symbol Symbol::emptySymbol;

Symbol::Symbol(const std::string& name) : name(name) {}
Symbol::Symbol(){};
string Symbol::GetName() const { return name; }
bool Symbol::operator<(const Symbol& other) const {
    return name < other.name;
}
bool Symbol::operator==(const Symbol& other) const {
  return name == other.name;
}
bool Symbol::IsEmptySymbol() const {
  return *this == Symbol::emptySymbol;
}
void Symbol::SetEmptySymbol(const string& epsilonName) {
    emptySymbol = Symbol(epsilonName);
}

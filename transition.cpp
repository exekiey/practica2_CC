#include "transition.h"
#include "tools.h"
bool Transition::operator<(const Transition& other) const {
    if (currentState < other.currentState) return true;
    if (other.currentState < currentState) return false;

    if (IsSmaller(inputSymbols, other.inputSymbols)) return true;
    if (IsSmaller(other.inputSymbols, inputSymbols)) return false;

    if (transitionedState < other.transitionedState) return true;
    if (other.transitionedState < transitionedState) return false;

    if (IsSmaller(addedSymbols, other.addedSymbols)) return true;
    if (IsSmaller(other.addedSymbols, addedSymbols)) return false;

    return IsSmaller(movements, other.movements);
}
/*

bool Transition::MatchEpsilon(Symbol stackSymbol, State currentState) const {
    if ((this->stackTop == stackSymbol) &&
        (this->currentState == currentState) &&
        (this->inputSymbol.IsEpsilon())) {
        return true;
    }
    return false;
}
*/

bool Transition::Match(vector<Symbol> inputSymbols, State currentState) const {
    if ((this->inputSymbols == inputSymbols) &&
        (this->currentState == currentState))
    {
        return true;
    }
    return false;
}

#include "transition.h"

#include <iostream>

void Transition::Print() const {
    cout << "Transición: (" << currentState.GetName() << ", ";

    for (size_t i = 0; i < inputSymbols.size(); ++i) {
        cout << inputSymbols[i].GetName();
        if (i + 1 < inputSymbols.size()) {
            cout << ", ";
        }
    }

    cout << ") -> (" << transitionedState.GetName() << ", ";

    for (size_t i = 0; i < addedSymbols.size(); ++i) {
        cout << addedSymbols[i].GetName();
        if (i + 1 < addedSymbols.size()) {
            cout << ", ";
        }
    }

    cout << "; ";

    for (size_t i = 0; i < movements.size(); ++i) {
        cout << static_cast<char>(movements[i]);
        if (i + 1 < movements.size()) {
            cout << ", ";
        }
    }

    cout << ")" << endl;
}
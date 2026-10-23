#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "symbol.h"
#include "state.h"
#include "transition.h"

#include <set>
#include <vector>

struct TuringMachine {
    std::set<Symbol> inputSymbols;
    std::set<Symbol> tapeSymbols;
    std::set<State> states;
    State initialState;
    std::set<State> finalStates;
    int numberOfTapes;
    std::set<Transition> transitions;

    TuringMachine(
        const std::set<Symbol>& inputSymbols,
        const std::set<Symbol>& tapeSymbols,
        const std::set<State>& states,
        State initialState,
        const std::set<State>& finalStates,
        const int numberOfTapes,
        const std::set<Transition>& transitions
    );
};

#endif
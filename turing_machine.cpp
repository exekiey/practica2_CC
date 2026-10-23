#include "turing_machine.h"

#include <set>
#include <vector>

TuringMachine::TuringMachine(
    const std::set<Symbol>& inputSymbols,
    const std::set<Symbol>& tapeSymbols,
    const std::set<State>& states,
    State initialState,
    const std::set<State>& finalStates,
    const int numberOfTapes,
    const std::set<Transition>& transitions
) :
    inputSymbols(inputSymbols),
    tapeSymbols(tapeSymbols),
    states(states),
    initialState(initialState),
    finalStates(finalStates),
    numberOfTapes(numberOfTapes),
    transitions(transitions) {}
#ifndef TRANSITION_H
#define TRANSITION_H

#include <vector>

#include "state.h"
#include "symbol.h"
#include "movement.h"

struct Transition {
	State currentState;
	vector<Symbol> inputSymbols;
	State transitionedState;
    vector<Symbol> addedSymbols;
	vector<Movement> movements;

	bool operator<(const Transition& other) const;
    bool MatchEmpty(State currentState) const;
    bool Match(vector<Symbol> inputSymbol, State currentState) const;
    void Print() const;
};

#endif
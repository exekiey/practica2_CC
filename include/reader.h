#ifndef READER_H
#define READER_H

#include <fstream>
#include <set>
#include <string>
#include <vector>

#include "state.h"
#include "symbol.h"
#include "tools.h"
#include "transition.h"
#include "turing_machine.h"

using namespace std;

class Reader {
private:
	string emptySymbol = ".";
    char commentCharacter = '#';
	ifstream file;
    ifstream inputFile;
    TuringMachine turingMachine;
    vector<Symbol> inputSymbols;

	set<State> SplitStates(const string& line);
	bool SplitSymbols(const string& line, set<Symbol>& symbols);
	bool IsSubset(const set<State>& a, const set<State>& b) const;
	bool Contains(const set<State>& values, const State& value) const;
	bool Contains(const set<Symbol>& values, const Symbol& value) const;
    bool ContainsEmpty(const set<Symbol>& values) const;
	bool ValidateTransition(const Transition& transition);
    bool IsLineComment(const string& line) const;
    Movement ParseMovement(const string& movementString) const;

public:
	Reader(const string& automatonFilename, const string& inputFilename);
	bool ReadMachine();
    bool ReadInputFile(const set<Symbol>& inputSymbols, vector<vector<Symbol>>& inputSymbolsList);
	const TuringMachine GetTuringMachine() const;
};

#endif
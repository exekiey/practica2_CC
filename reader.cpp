#include "reader.h"

using namespace std;

Reader::Reader(const string& automatonFilename, const string& inputFilename) :
    file(automatonFilename),
    inputFile(inputFilename),
    turingMachine(set<Symbol>(), set<Symbol>(), set<State>(), State(), set<State>(), int(), set<Transition>()) {}

set<State> Reader::SplitStates(const string& line) {
	set<State> result;
	vector<string> tokens = SplitString(line, ' ');
	for (const string& token : tokens) {
		result.insert(State(token));
	}
	return result;
}

bool Reader::IsLineComment(const string& line) const {
	return line[0] == Reader::commentCharacter;
}

bool Reader::SplitSymbols(const string& line, set<Symbol>& symbols) {
	vector<string> tokens = SplitString(line, ' ');
	for (const string& token : tokens) {
		if (token.size() != 1) {
			std::cerr << "Error: el símbolo '" << token << "' no es de un único carácter." << endl;
			return false;
		}
		symbols.insert(Symbol(token));
	}
	return true;
}

bool Reader::IsSubset(const set<State>& a, const set<State>& b) const {
	for (const State& state : a) {
		if (b.find(state) == b.end()) return false;
	}
	return true;
}

bool Reader::Contains(const set<State>& values, const State& value) const {
	return values.find(value) != values.end();
}

bool Reader::Contains(const set<Symbol>& values, const Symbol& value) const {
	return values.find(value) != values.end();
}
bool Reader::ContainsEmpty(const set<Symbol>& values) const {
	for (Symbol symbol : values) {
        if (symbol.IsEmptySymbol()) {
            return true;
        }
    }
    return false;
}

bool Reader::ValidateTransition(const Transition& transition) {
	if (!Contains(turingMachine.states, transition.currentState)) {
		std::cerr << "Error: el estado origen '" << transition.currentState.GetName()
			<< "' no pertenece a Q." << endl;
		return false;
	}

	if (!Contains(turingMachine.states, transition.transitionedState)) {
		std::cerr << "Error: el estado destino '" << transition.transitionedState.GetName()
			<< "' no pertenece a Q." << endl;
		return false;
	}


    for (const Symbol& inputSymbol : transition.inputSymbols) {
        if (!Contains(turingMachine.tapeSymbols, inputSymbol) && !inputSymbol.IsEmptySymbol()) {
            std::cerr << "Error: el símbolo de entrada '" << inputSymbol.GetName()
                << "' no pertenece a Γ." << endl;
            return false;
        }
    }


    for (const Symbol& addedSymbol : transition.addedSymbols) {
        if (!Contains(turingMachine.tapeSymbols, addedSymbol) && !addedSymbol.IsEmptySymbol()) {
            std::cerr << "Error: el símbolo a escribir '" << addedSymbol.GetName()
                << "' no pertenece a Γ." << endl;
            return false;
        }
    }

	return true;
}

Movement Reader::ParseMovement(const string& movementString) const {
    if (movementString == "L") {
        return Movement::L;
    }
    if (movementString == "R") {
        return Movement::R;
    }
    if (movementString == "S") {
        return Movement::S;
    }
    cerr << "Error: movimiento inválido '" << movementString << "'." << endl;
    exit(1);
}

bool Reader::ReadMachine() {
	turingMachine = TuringMachine(set<Symbol>(), set<Symbol>(), set<State>(), State(), set<State>(), int(), set<Transition>());

	Symbol::SetEmptySymbol(emptySymbol);

	if (!file.is_open()) {
		cerr << "Error: no se pudo abrir el fichero." << endl;
		return false;
	}

	string line;

	while (getline(file, line)) {
		if (!IsLineComment(line)) {
			break;
		}
	}
	
	turingMachine.states = SplitStates(line);
	if (turingMachine.states.empty()) {
		cerr << "Error: Q está vacío." << endl;
		cerr << "Línea: " << line << endl;
		return false;
	}

	if (!getline(file, line)) {
		cerr << "Error: falta la sección del alfabeto de entrada (Σ)." << endl;
		return false;
	}
	if (!SplitSymbols(line, turingMachine.inputSymbols)) {
		cerr << "Error: Σ contiene un símbolo que no es de un único carácter." << endl;
		cerr << "Línea: " << line << endl;
		return false;
	}
    if (ContainsEmpty(turingMachine.inputSymbols)) {
        cerr << "Error: Σ contiene el símbolo vacío" << endl;;
		cerr << "Línea: " << line << endl;
        return false;
    }

	if (!getline(file, line)) {
		cerr << "Error: falta la sección del alfabeto de entrada (Σ)." << endl;
		return false;
	}
	if (!SplitSymbols(line, turingMachine.tapeSymbols)) {
		cerr << "Error: Γ contiene un símbolo que no es de un único carácter." << endl;
		cerr << "Línea: " << line << endl;
		return false;
	}
    if (ContainsEmpty(turingMachine.inputSymbols)) {
        cerr << "Error: Γ no contiene el símbolo vacío";
		cerr << "Línea: " << line << endl;
        return false;
    }

	if (!getline(file, line)) {
		cerr << "Error: falta el estado inicial (q0)." << endl;
		return false;
	}
	turingMachine.initialState = State(line);
	if (!Contains(turingMachine.states, turingMachine.initialState)) {
		cerr << "Error: el estado inicial '" << turingMachine.initialState.GetName()
			<< "' no pertenece a Q." << endl;
		cerr << "Línea: " << line << endl;
		return false;
	}

	if (!getline(file, line)) {
		cerr << "Error: falta el símbolo vacío." << endl;
		return false;
	}
    Symbol::SetEmptySymbol(line);

	if (!getline(file, line)) {
		cerr << "Error: falta la sección de estados finales (F)." << endl;
		return false;
	}
	turingMachine.finalStates = SplitStates(line);
	if (!IsSubset(turingMachine.finalStates, turingMachine.states)) {
		cerr << "Error: F no es subconjunto de Q." << endl;
		cerr << "Línea: " << line << endl;
		return false;
	}

	if (!getline(file, line)) {
		cerr << "Error: falta la sección de estados finales (F)." << endl;
		return false;
	}
    turingMachine.numberOfTapes = stoi(line);

	int lineNumber = 7;
    while (getline(file, line)) {
        lineNumber++;
        if (line.empty()) continue;

        vector<string> tokens = SplitString(line, ' ');
        int numberOfTapes = turingMachine.numberOfTapes;
        int expectedTokens = 2 + 3 * numberOfTapes;

        if (tokens.size() != expectedTokens) {
            cerr << "Error (línea " << lineNumber
                << "): una transición debe tener " << expectedTokens
                << " tokens para " << numberOfTapes << " cintas." << endl;
            cerr << "Línea: " << line << endl;
            return false;
        }

        State currentState = State(tokens[0]);
        
        
        vector<Symbol> inputSymbols;
        for (int i = 0; i < numberOfTapes; i++) {
            inputSymbols.push_back(Symbol(tokens[1 + i]));
        }
        
        State nextState = State(tokens[1 + numberOfTapes]);
        
        vector<Symbol> addedSymbols;
        for (int i = 0; i < numberOfTapes; i++) {
            addedSymbols.push_back(Symbol(tokens[1 + turingMachine.numberOfTapes + 1 + i]));
        }

        vector<Movement> movements;
        for (int i = 0; i < numberOfTapes; i++) {
            movements.push_back(ParseMovement(tokens[1 + turingMachine.numberOfTapes + 1 + turingMachine.numberOfTapes + i]));
        }

        Transition currentTransition = {
            currentState,
            inputSymbols,
            nextState,
            addedSymbols,
            movements
        };

        if (!ValidateTransition(currentTransition)) {
            cerr << "Error (línea " << lineNumber
                << "): transición inválida." << endl;
            cerr << "Línea: " << line << endl;
            return false;
        }

        turingMachine.transitions.insert(currentTransition);
	}

	return true;
}

bool Reader::ReadInputFile(const set<Symbol>& inputSymbols, vector<vector<Symbol>>& inputSymbolsList) {
    if (!inputFile.is_open()) {
        cerr << "Error: no se pudo abrir el fichero de entrada." << endl;
        return false;
    }

    string line;
    while (getline(inputFile, line)) {
        vector<string> tokens = SplitString(line);
        vector<Symbol> currentInputSymbols;
        for (const string& token : tokens) {
            Symbol symbol(token);
            if (!Contains(turingMachine.inputSymbols, symbol)) {
                cerr << "Error: el símbolo de entrada '" << symbol.GetName()
                    << "' no pertenece a Σ." << endl;
                cerr << "Línea: " << line << endl;
                return false;
            }
            currentInputSymbols.push_back(symbol);
        }
        inputSymbolsList.push_back(currentInputSymbols);
    }


    return true;
}

const TuringMachine Reader::GetTuringMachine() const {
	return turingMachine;
}
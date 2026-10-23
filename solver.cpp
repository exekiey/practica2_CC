#include "solver.h"

Solver::Solver(const TuringMachine& automaton)
    : turingMachine(automaton) {
}

bool Solver::Contains(
    const std::set<State>& values,
    const State& value
) const {
    for (const State& state : values) {
        if (state == value) {
            return true;
        }
    }

    return false;
}
/*
void Solver::PrintNode(const Node& node, const std::vector<Symbol>& input, const TuringMachine& automaton) {
    std::cout << "Estado: " << node.state.GetName() << std::endl;

    std::cout << "Input: ";
    for (int i = node.inputCounter; i < input.size(); ++i) {
        std::cout << input[i].GetName();
    }
    std::cout << std::endl;
    std::cout << "Stack: [";

    std::stack<Symbol> stackCopy = node.stack;
    while (!stackCopy.empty()) {
        Symbol symbol = stackCopy.top();
        stackCopy.pop();
        std::cout << symbol.GetName();
        if (!stackCopy.empty()) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
    std::cout << "Transiciones posibles: ";
    if (node.stack.empty()) {
        std::cout << std::endl;
        return;
    }
    std::cout << endl;
    for (const Transition& transition : automaton.transitions) {
        bool endOfInput = node.inputCounter == input.size();
        if (transition.MatchEpsilon(node.stack.top(), node.state)
            || (!endOfInput && transition.Match(input[node.inputCounter], node.stack.top(), node.state))) {
            std::cout << "(" << transition.currentState.GetName() << ", "
                << transition.inputSymbol.GetName() << ", "
                << transition.stackTop.GetName() << ") -> ("
                << transition.transitionedState.GetName() << ", [";
            for (const Symbol& symbol : transition.addedSymbols) {
                std::cout << symbol.GetName();
            }
            std::cout << "])";
            if (&transition != &(*automaton.transitions.rbegin())) {
                std::cout << ", ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << endl;
}
*/

void Solver::AppendVectorToStack(
    std::stack<Symbol>& stack,
    const std::vector<Symbol>& symbols
) {
    for (auto it = symbols.rbegin(); it != symbols.rend(); ++it) {
        stack.push(*it);
    }
}

bool Solver::DoTransitions(vector<Tape>& tapes, State& currentState) {
    vector<Symbol> symbols;
    for (Tape currentTape : tapes) {
        symbols.push_back(currentTape.GetSymbol());
    }
    for (const Transition& currentTransition : turingMachine.transitions) {
        if (currentTransition.Match(symbols, currentState)) {

            for (int i = 0; i < tapes.size(); i++) {
                tapes[i].Write(currentTransition.addedSymbols[i]);
                tapes[i].Move(currentTransition.movements[i]);
            }

            currentState = currentTransition.transitionedState;

            return true;
        }
    }
    return false;
}

bool Solver::Solve(const std::vector<Symbol>& input, string* result) {
    State currentState = turingMachine.initialState;
    
    vector<Tape> tapes;
    tapes.push_back(Tape(input));
    for (int _ = 1; _ < turingMachine.numberOfTapes; _++) {
        tapes.push_back(Tape(vector<Symbol>{}));
    }
    
    
    while (!Contains(turingMachine.finalStates, currentState)) {
        if (!DoTransitions(tapes, currentState)) {
            *result = tapes[0].ToString();
            return false;
        }
    }

    *result = tapes[0].ToString();
    return true;
}
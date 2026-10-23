#include <iostream>
#include <vector>
#include <string>

#include "reader.h"
#include "solver.h"
#include "state.h"

using namespace std;

bool ReadOptions(
    int argc,
    char* argv[],
    string& configFile,
    string& inputFile,
    bool& doTrace
) {
    bool hasConfigFile = false;
    bool hasInputFile = false;
    bool hasTraceOption = false;

    for (int i = 1; i < argc; ++i) {
        string argument = argv[i];

        if (argument[0] != '-') {
            cerr << "Argumento desconocido: " << argument << endl;
            return false;
        }

        switch (argument[1]) {
            case 'c':
                if (argument != "-config" || i + 1 >= argc) {
                    cerr << "Argumento inválido: " << argument << endl;
                    return false;
                }

                configFile = argv[++i];
                hasConfigFile = true;
                break;

            case 't': {
                if (argument != "-trace" || i + 1 >= argc) {
                    cerr << "Argumento inválido: " << argument << endl;
                    return false;
                }

                string traceOption = argv[++i];

                if (traceOption != "y" && traceOption != "n") {
                    cerr << "Error: -trace debe ser y o n." << endl;
                    return false;
                }

                doTrace = (traceOption == "y");
                hasTraceOption = true;
                break;
            }

            case 'i':
                if (argument != "-in" || i + 1 >= argc) {
                    cerr << "Argumento inválido: " << argument << endl;
                    return false;
                }

                inputFile = argv[++i];
                hasInputFile = true;
                break;

            default:
                cerr << "Argumento desconocido: " << argument << endl;
                return false;
        }
    }

    if (!hasConfigFile || !hasInputFile || !hasTraceOption) {
        cerr << "Uso: " << argv[0]
             << " -config <f> -trace <y|n> -in <f>"
             << endl;
        return false;
    }

    return true;
}

void PrintMachine(TuringMachine& automaton) {
    cout << "Estados:";
    for (const State& state : automaton.states) {
        cout << " " << state.GetName();
    }
    cout << endl;

    cout << "Símbolos de entrada:";
    for (const Symbol& symbol : automaton.inputSymbols) {
        cout << " " << symbol.GetName();
    }
    cout << endl;

    cout << "Símbolos de cinta:";
    for (const Symbol& symbol : automaton.tapeSymbols) {
        cout << " " << symbol.GetName();
    }
    cout << endl;

    cout << "Estado inicial: " << automaton.initialState.GetName() << endl;

    cout << "Estados finales:";
    for (const State& state : automaton.finalStates) {
        cout << " " << state.GetName();
    }
    cout << endl;

    for (const Transition& transition : automaton.transitions) {
        transition.Print();
    }
}

int main(int argc, char* argv[]) {
    string configFile;
    string inputFile;
    bool doTrace = false;

    if (!ReadOptions(argc, argv, configFile, inputFile, doTrace)) {
        return 1;
    }

    Reader reader(configFile, inputFile);

    if (!reader.ReadMachine()) {
        cerr << "Error al leer el archivo de la máquina de Turing." << endl;
        return 1;
    }

    TuringMachine turingMachine = reader.GetTuringMachine();

    if (doTrace) {
        PrintMachine(turingMachine);
    }

    vector<vector<Symbol>> inputSymbolsList;
    if (!reader.ReadInputFile(turingMachine.inputSymbols, inputSymbolsList)) {
        cerr << "Error al leer el archivo de entrada." << endl;
        return 1;
    }

    Solver solver = Solver(turingMachine);
    for (vector<Symbol> symbolList : inputSymbolsList) {
        for (Symbol symbol : symbolList) {
            cout << symbol.GetName();
        }
        string result;
        cout << (solver.Solve(symbolList, doTrace, &result) ? "Válida" : "Inválida");
        cout << result;
        cout << endl;
    }

    return 0;
}
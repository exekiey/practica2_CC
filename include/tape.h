#ifndef TAPE_H
#define TAPE_H

#include "symbol.h"
#include "movement.h"

#include <vector>

using namespace std;

class Tape {
    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;
        Symbol symbol;

        void SetSymbol(Symbol newSymbol);
        bool IsEmtpy();
    };

private:
    Node* head;

public:
    Tape(vector<Symbol> input);
    void Move(Movement movement);
    Symbol GetSymbol();
    void Write(Symbol symbol);
    string ToString();
};

#endif
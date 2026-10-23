#include "tape.h"

void Tape::Node::SetSymbol(Symbol newSymbol) {
    symbol = newSymbol;
}

bool Tape::Node::IsEmtpy() {
    return symbol.IsEmptySymbol();
}

Tape::Tape(vector<Symbol> input) {
    head = new Node();
    for (Symbol currentSymbol : input) {
        head->SetSymbol(currentSymbol);
        head->right = new Node();
        head->right->left = head;
        head = head->right;
    }
    head->SetSymbol(Symbol::emptySymbol);

    for (Symbol _ : input) {
        head = head->left;
    }
}

void Tape::Move(Movement movement) {
    if (movement == Movement::L) {
        if (head->left == nullptr || head->left->IsEmtpy()) {
            head->left = new Node();
            head->left->SetSymbol(Symbol::emptySymbol);
            head->left->right = head;
        }
        head = head->left;
        return;
    }

    if (movement == Movement::R) {
        if (head->right == nullptr || head->right->IsEmtpy()) {
            head->right = new Node();
            head->right->SetSymbol(Symbol::emptySymbol);
            head->right->left = head;
        }
        head = head->right;
        return;
    }

    if (movement == Movement::S) {
        return;
    }
}

void Tape::Write(Symbol symbol) {
    head->SetSymbol(symbol);
}

Symbol Tape::GetSymbol() {
    return head->symbol;
}

string Tape::ToString() {
    string result = "";
    Node* current = head;

    while (current->left != nullptr) {
        current = current->left;
    }

    while (current != nullptr) {
        result.append(current->symbol.GetName());
        current = current->right;
    }

    return result;
}
#include "interprete.cpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Uso: " << argv[0] << " <arquivo.bas>" << endl; // Alterado para .bas
        return 1;
    }

    Interpretador interprete;
    interprete.executar(argv[1]);

    return 0;
}

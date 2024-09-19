#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

//==============================================================

class Interpretador {
public:
    void executar(const string& nomeArquivo) {
        ifstream arquivo(nomeArquivo);
        if (!arquivo.is_open()) {
            cout << "Erro ao abrir o arquivo!" << endl;
            return;
        }

        vector<string> linhas;
        string linha;
        while (getline(arquivo, linha)) {
            linhas.push_back(linha);
        }

        arquivo.close();

        verificarComando(linhas);
    }

//==============================================================

private:
    unordered_map<string, int> variaveis;

    void verificarComando(const vector<string>& linhas) {
        int i = 0;
        while (i < linhas.size()) {
            string linha = linhas[i];
            removerEspaco(linha);

            if (linha.empty()) {
                ++i;
                continue;
            }

            istringstream fluxo(linha);
            int numeroLinha;
            fluxo >> numeroLinha; // Lê o número da linha

            string comando;
            fluxo >> comando; // Lê o comando 

            if (comando == "PRINT") {
                string expr;
                getline(fluxo, expr);
                removerEspaco(expr);
                try {
                    cout << avaliarExpressao(expr) << endl;
                } catch (const exception& e) {
                    cout << "Erro ao avaliar a expressão: " << e.what() << endl;
                }
            } else if (comando == "LET") {
                string var;
                string expr;
                fluxo >> var; // Lê a variável
                getline(fluxo, expr); // Lê " = 5"
                removerEspaco(expr);
                if (expr.empty() || expr[0] != '=') {
                    cout << "Formato inválido para LET: " << expr << endl;
                    ++i;
                    continue;
                }
                expr = expr.substr(1); // Remove "="
                try {
                    variaveis[var] = avaliarExpressao(expr);
                } catch (const exception& e) {
                    cout << "Erro ao atribuir valor: " << e.what() << endl;
                }
            } else if (comando == "GOTO") {
                int numeroLinha;
                fluxo >> numeroLinha;
                // Ajusta o índice para a linha correta
                int novaLinha = buscarLinha(linhas, numeroLinha);
                if (novaLinha != -1) {
                    i = novaLinha; // Ajuste correto para a linha
                    continue;
                } else {
                    cout << "Número da linha inválido para GOTO!" << endl;
                }
            } else if (comando == "HALT") {
                break;
            } else {
                cout << "Comando desconhecido: " << comando << endl;
            }

            ++i;
        }
    }

//==============================================================

    int avaliarExpressao(const string& expr) {
        istringstream fluxo(expr);
        string token;
        vector<int> valores;
        vector<char> operacoes;

        while (fluxo >> token) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                operacoes.push_back(token[0]);
            } else {
                int valor;
                try {
                    if (variaveis.find(token) != variaveis.end()) {
                        valor = variaveis[token];
                    } else {
                        valor = stoi(token);
                    }
                } catch (const invalid_argument& e) {
                    throw runtime_error("Valor inválido na expressão: " + token);
                }
                valores.push_back(valor);
            }
        }

        while (!operacoes.empty()) {
            int direita = valores.back(); valores.pop_back();
            int esquerda = valores.back(); valores.pop_back();
            char op = operacoes.back(); operacoes.pop_back();
            
            int resultado = 0;
            switch (op) {
                case '+': resultado = esquerda + direita; break;
                case '-': resultado = esquerda - direita; break;
                case '*': resultado = esquerda * direita; break;
                case '/': resultado = esquerda / direita; break;
                default: throw runtime_error("Operador inválido: " + string(1, op));
            }
            valores.push_back(resultado);
        }

        if (valores.empty()) {
            throw runtime_error("Nenhum valor para avaliar a expressão.");
        }

        return valores.back();
    }

//==============================================================

    void removerEspaco(string& str) {
        str.erase(0, str.find_first_not_of(" \t"));
        str.erase(str.find_last_not_of(" \t") + 1);
    }

//==============================================================

    int buscarLinha(const vector<string>& linhas, int numeroLinha) {
        for (size_t i = 0; i < linhas.size(); ++i) {
            istringstream fluxo(linhas[i]);
            int linhaAtual;
            fluxo >> linhaAtual;
            if (linhaAtual == numeroLinha) {
                return i;
            }
        }
        return -1; 
    }
};

//==============================================================


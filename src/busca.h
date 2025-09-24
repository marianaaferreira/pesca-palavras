#ifndef BUSCA_H
#define BUSCA_H

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <cctype>

using namespace std;

enum Direcao {
    DIREITA,
    ESQUERDA,
    CIMA,
    BAIXO,
    DIAGONAL_DIREITA_BAIXO,
    DIAGONAL_ESQUERDA_BAIXO,
    DIAGONAL_DIREITA_CIMA,
    DIAGONAL_ESQUERDA_CIMA,
    NENHUMA
};

struct Coordenada {
    int linha;
    int coluna;
};

struct Coordenadas {
    Coordenada inicial;
    Coordenada final;
    Direcao direcao;
};

std::mutex mtx;

// compara caracteres sem considerar maiúsculas e minúsculas
inline bool iguais(char a, char b) {
    return toupper(a) == toupper(b);
}

// enum para string
inline string direcaoToString(Direcao d) {
    switch (d) {
        case DIREITA: return "direita";
        case ESQUERDA: return "esquerda";
        case CIMA: return "cima";
        case BAIXO: return "baixo";
        case DIAGONAL_DIREITA_BAIXO: return "diagonal direita/baixo";
        case DIAGONAL_ESQUERDA_BAIXO: return "diagonal esquerda/baixo";
        case DIAGONAL_DIREITA_CIMA: return "diagonal direita/cima";
        case DIAGONAL_ESQUERDA_CIMA: return "diagonal esquerda/cima";
        default: return "nenhuma";
    }
}

void direita(const vector<vector<char>>& matriz, const string& palavra,
             Coordenadas& c, bool& encontrou) {
    int linhas = matriz.size();
    int colunas = matriz[0].size();

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j <= colunas - (int)palavra.size(); j++) {
            bool match = true;
            for (int k = 0; k < (int)palavra.size(); k++) {
                if (!iguais(matriz[i][j + k], palavra[k])) {
                    match = false;
                    break;
                }
            }
            if (match) {
                lock_guard<mutex> lock(mtx);
                if (!encontrou) {
                    encontrou = true;
                    c.inicial = {i, j};
                    c.final = {i, j + (int)palavra.size() - 1};
                    c.direcao = DIREITA;
                }
                return;
            }
        }
    }
}

void esquerda(const vector<vector<char>>& matriz, const string& palavra,
              Coordenadas& c, bool& encontrou) {
    int linhas = matriz.size();
    int colunas = matriz[0].size();

    for (int i = 0; i < linhas; i++) {
        for (int j = colunas - 1; j >= (int)palavra.size() - 1; j--) {
            bool match = true;
            for (int k = 0; k < (int)palavra.size(); k++) {
                if (!iguais(matriz[i][j - k], palavra[k])) {
                    match = false;
                    break;
                }
            }
            if (match) {
                lock_guard<mutex> lock(mtx);
                if (!encontrou) {
                    encontrou = true;
                    c.inicial = {i, j};
                    c.final = {i, j - (int)palavra.size() + 1};
                    c.direcao = ESQUERDA;
                }
                return;
            }
        }
    }
}

void baixo(const vector<vector<char>>& matriz, const string& palavra,
           Coordenadas& c, bool& encontrou) {
    int linhas = matriz.size();
    int colunas = matriz[0].size();

    for (int i = 0; i <= linhas - (int)palavra.size(); i++) {
        for (int j = 0; j < colunas; j++) {
            bool match = true;
            for (int k = 0; k < (int)palavra.size(); k++) {
                if (!iguais(matriz[i + k][j], palavra[k])) {
                    match = false;
                    break;
                }
            }
            if (match) {
                lock_guard<mutex> lock(mtx);
                if (!encontrou) {
                    encontrou = true;
                    c.inicial = {i, j};
                    c.final = {i + (int)palavra.size() - 1, j};
                    c.direcao = BAIXO;
                }
                return;
            }
        }
    }
}

void cima(const vector<vector<char>>& matriz, const string& palavra,
          Coordenadas& c, bool& encontrou) {
    int linhas = matriz.size();
    int colunas = matriz[0].size();

    for (int i = linhas - 1; i >= (int)palavra.size() - 1; i--) {
        for (int j = 0; j < colunas; j++) {
            bool match = true;
            for (int k = 0; k < (int)palavra.size(); k++) {
                if (!iguais(matriz[i - k][j], palavra[k])) {
                    match = false;
                    break;
                }
            }
            if (match) {
                lock_guard<mutex> lock(mtx);
                if (!encontrou) {
                    encontrou = true;
                    c.inicial = {i, j};
                    c.final = {i - (int)palavra.size() + 1, j};
                    c.direcao = CIMA;
                }
                return;
            }
        }
    }
}

void diagonalDireitaBaixo(const vector<vector<char>>& matriz, const string& palavra,
                          Coordenadas& c, bool& encontrou) {
    int linhas = matriz.size();
    int colunas = matriz[0].size();

    for (int i = 0; i <= linhas - (int)palavra.size(); i++) {
        for (int j = 0; j <= colunas - (int)palavra.size(); j++) {
            bool match = true;
            for (int k = 0; k < (int)palavra.size(); k++) {
                if (!iguais(matriz[i + k][j + k], palavra[k])) {
                    match = false;
                    break;
                }
            }
            if (match) {
                lock_guard<mutex> lock(mtx);
                if (!encontrou) {
                    encontrou = true;
                    c.inicial = {i, j};
                    c.final = {i + (int)palavra.size() - 1, j + (int)palavra.size() - 1};
                    c.direcao = DIAGONAL_DIREITA_BAIXO;
                }
                return;
            }
        }
    }
}

void diagonalEsquerdaBaixo(const vector<vector<char>>& matriz, const string& palavra,
                           Coordenadas& c, bool& encontrou) {
    int linhas = matriz.size();
    int colunas = matriz[0].size();

    for (int i = 0; i <= linhas - (int)palavra.size(); i++) {
        for (int j = (int)palavra.size() - 1; j < colunas; j++) {
            bool match = true;
            for (int k = 0; k < (int)palavra.size(); k++) {
                if (!iguais(matriz[i + k][j - k], palavra[k])) {
                    match = false;
                    break;
                }
            }
            if (match) {
                lock_guard<mutex> lock(mtx);
                if (!encontrou) {
                    encontrou = true;
                    c.inicial = {i, j};
                    c.final = {i + (int)palavra.size() - 1, j - (int)palavra.size() + 1};
                    c.direcao = DIAGONAL_ESQUERDA_BAIXO;
                }
                return;
            }
        }
    }
}

void diagonalDireitaCima(const vector<vector<char>>& matriz, const string& palavra,
                         Coordenadas& c, bool& encontrou) {
    int linhas = matriz.size();
    int colunas = matriz[0].size();

    for (int i = (int)palavra.size() - 1; i < linhas; i++) {
        for (int j = 0; j <= colunas - (int)palavra.size(); j++) {
            bool match = true;
            for (int k = 0; k < (int)palavra.size(); k++) {
                if (!iguais(matriz[i - k][j + k], palavra[k])) {
                    match = false;
                    break;
                }
            }
            if (match) {
                lock_guard<mutex> lock(mtx);
                if (!encontrou) {
                    encontrou = true;
                    c.inicial = {i, j};
                    c.final = {i - (int)palavra.size() + 1, j + (int)palavra.size() - 1};
                    c.direcao = DIAGONAL_DIREITA_CIMA;
                }
                return;
            }
        }
    }
}

void diagonalEsquerdaCima(const vector<vector<char>>& matriz, const string& palavra,
                          Coordenadas& c, bool& encontrou) {
    int linhas = matriz.size();
    int colunas = matriz[0].size();

    for (int i = (int)palavra.size() - 1; i < linhas; i++) {
        for (int j = (int)palavra.size() - 1; j < colunas; j++) {
            bool match = true;
            for (int k = 0; k < (int)palavra.size(); k++) {
                if (!iguais(matriz[i - k][j - k], palavra[k])) {
                    match = false;
                    break;
                }
            }
            if (match) {
                lock_guard<mutex> lock(mtx);
                if (!encontrou) {
                    encontrou = true;
                    c.inicial = {i, j};
                    c.final = {i - (int)palavra.size() + 1, j - (int)palavra.size() + 1};
                    c.direcao = DIAGONAL_ESQUERDA_CIMA;
                }
                return;
            }
        }
    }
}

#endif
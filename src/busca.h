#ifndef BUSCA_H
#define BUSCA_H

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <cctype>

using namespace std;

struct Coordenada {
    int linha;
    int coluna;
};

struct Coordenadas {
    Coordenada inicial;
    Coordenada final;
    string direcao; 
};

std::mutex mtx; 

// Função auxiliar para comparar caracteres sem considerar maiusculas e minusculas
bool iguais(char a, char b) {
    return toupper(a) == toupper(b);
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
                    c.direcao = "direita";
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
                    c.direcao = "esquerda";
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
                    c.direcao = "baixo";
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
                    c.direcao = "cima";
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
                    c.direcao = "diagonal direita/baixo";
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
                    c.direcao = "diagonal esquerda/baixo";
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
                    c.direcao = "diagonal direita/cima";
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
                    c.direcao = "diagonal esquerda/cima";
                }
                return;
            }
        }
    }
}

#endif

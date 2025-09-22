#ifndef BUSCA_H
#define BUSCA_H

#include <vector>
using namespace std;

struct Coordenada {
    int linha;
    int coluna;
};

struct Coordenadas {
    Coordenada inicial;
    Coordenada final;
    string direcao; //1- Diagonal 2- Horizontal 3- Vertical 4- DiagonalReverso 5- HorizontalReverso 6- VerticalReverso
};

void procuraDiagonal(vector<vector<char>> m, string palavra, bool &encontrou, Coordenadas &c);
void procuraHorizontal(vector<vector<char>> m, string palavra, bool &encontrou, Coordenadas &c);
void procuraVertical(vector<vector<char>> m, string palavra, bool &encontrou, Coordenadas &c);
void procuraDiagonalReverso(vector<vector<char>> m, string palavra, bool &encontrou, Coordenadas &c);
void procuraHorizontalReverso(vector<vector<char>> m, string palavra, bool &encontrou, Coordenadas &c);
void procuraVerticalReverso(vector<vector<char>> m, string palavra, bool &encontrou, Coordenadas &c);

// 1- Diagonal (para baixo e para a direita)
void procuraDiagonal(vector<vector<char>> m, string palavra, bool &encontrou, Coordenadas &c) {
    if (encontrou) return;

    int linhas = m.size();
    if (linhas == 0) return;
    int colunas = m[0].size();
    int tamanhoPalavra = palavra.size();

    for (int i = 0; i <= linhas - tamanhoPalavra; ++i) {
        for (int j = 0; j <= colunas - tamanhoPalavra; ++j) {
            bool match = true;
            for (int k = 0; k < tamanhoPalavra; ++k) {
                if (m[i + k][j + k] != palavra[k]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                encontrou = true;
                c.inicial = {i, j};
                c.final = {i + tamanhoPalavra - 1, j + tamanhoPalavra - 1};
                c.direcao = "direita/baixo";
                return;
            }
        }
    }
}

// 2- Horizontal (para a direita)
void procuraHorizontal(vector<vector<char>> m, string palavra, bool &encontrou, Coordenadas &c) {
    if (encontrou) return;

    int linhas = m.size();
    if (linhas == 0) return;
    int colunas = m[0].size();
    int tamanhoPalavra = palavra.size();

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j <= colunas - tamanhoPalavra; ++j) {
            bool match = true;
            for (int k = 0; k < tamanhoPalavra; ++k) {
                if (m[i][j + k] != palavra[k]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                encontrou = true;
                c.inicial = {i, j};
                c.final = {i, j + tamanhoPalavra - 1};
                c.direcao = "direita";
                return;
            }
        }
    }
}

// 3- Vertical (para baixo)
void procuraVertical(vector<vector<char>> m, string palavra, bool &encontrou, Coordenadas &c) {
    if (encontrou) {
        return; // sai da função se a palavra já foi encontrada por outra thread
    }

    int linhas = m.size();
    if (linhas == 0) {
        return;
    }
    int colunas = m[0].size();
    int tamanhoPalavra = palavra.size();

    for (int j = 0; j < colunas; ++j) {
        for (int i = 0; i <= linhas - tamanhoPalavra; ++i) {
            bool match = true;
            // Verifica a palavra de cima para baixo
            for (int k = 0; k < tamanhoPalavra; ++k) {
                if (m[i + k][j] != palavra[k]) {
                    match = false;
                    break;
                }
            }

            // Se a palavra foi encontrada atualiza as variáveis da struct e o retorno booleano
            if (match) {
                encontrou = true;

                c.inicial.linha = i;
                c.inicial.coluna = j;

                c.final.linha = i + tamanhoPalavra - 1;
                c.final.coluna = j;

                c.direcao = "baixo";
                return; 
            }
        }
    }
}

// 4- DiagonalReverso (para baixo e para a esquerda)
void procuraDiagonalReverso(vector<vector<char>> m, string palavra, bool &encontrou, Coordenadas &c) {
    if (encontrou) return;

    int linhas = m.size();
    if (linhas == 0) return;
    int colunas = m[0].size();
    int tamanhoPalavra = palavra.size();

    for (int i = 0; i <= linhas - tamanhoPalavra; ++i) {
        for (int j = tamanhoPalavra - 1; j < colunas; ++j) {
            bool match = true;
            for (int k = 0; k < tamanhoPalavra; ++k) {
                if (m[i + k][j - k] != palavra[k]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                encontrou = true;
                c.inicial = {i, j};
                c.final = {i + tamanhoPalavra - 1, j - tamanhoPalavra + 1};
                c.direcao = "baixo/esquerda";
                return;
            }
        }
    }
}

// 5- HorizontalReverso (para a esquerda)
void procuraHorizontalReverso(vector<vector<char>> m, string palavra, bool &encontrou, Coordenadas &c) {
    if (encontrou) return;

    int linhas = m.size();
    if (linhas == 0) return;
    int colunas = m[0].size();
    int tamanhoPalavra = palavra.size();

    for (int i = 0; i < linhas; ++i) {
        for (int j = tamanhoPalavra - 1; j < colunas; ++j) {
            bool match = true;
            for (int k = 0; k < tamanhoPalavra; ++k) {
                if (m[i][j - k] != palavra[k]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                encontrou = true;
                c.inicial = {i, j};
                c.final = {i, j - tamanhoPalavra + 1};
                c.direcao = "esquerda";
                return;
            }
        }
    }
}

// 6- VerticalReverso (para cima)
void procuraVerticalReverso(vector<vector<char>> m, string palavra, bool &encontrou, Coordenadas &c) {
    if (encontrou) return;

    int linhas = m.size();
    if (linhas == 0) return;
    int colunas = m[0].size();
    int tamanhoPalavra = palavra.size();

    for (int j = 0; j < colunas; ++j) {
        for (int i = tamanhoPalavra - 1; i < linhas; ++i) {
            bool match = true;
            for (int k = 0; k < tamanhoPalavra; ++k) {
                if (m[i - k][j] != palavra[k]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                encontrou = true;
                c.inicial = {i, j};
                c.final = {i - tamanhoPalavra + 1, j};
                c.direcao = "cima";
                return;
            }
        }
    }
}

#endif
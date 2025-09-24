#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <mutex>
#include "busca.h"
using namespace std;

struct ResultadoBusca {
    string palavra;
    bool encontrada;
    Coordenadas coordenadas;
};

bool buscaPalavra(vector<vector<char>> m, string palavra, Coordenadas &c){
    bool encontrou = false;
    thread tdireita(direita, ref(m), palavra, ref(c), ref(encontrou));
    thread tesquerda(esquerda, ref(m), palavra, ref(c), ref(encontrou));
    thread tbaixo(baixo, ref(m), palavra, ref(c), ref(encontrou));
    thread tcima(cima, ref(m), palavra, ref(c), ref(encontrou));
    thread tdiagonalDireitaBaixo(diagonalDireitaBaixo, ref(m), palavra, ref(c), ref(encontrou));
    thread tDiagonalDireitaCima(diagonalDireitaCima, ref(m), palavra, ref(c), ref(encontrou));
    thread tdiagonalEsquerdaBaixo(diagonalEsquerdaBaixo, ref(m), palavra, ref(c), ref(encontrou));
    thread tdiagonalEsquerdaCima(diagonalEsquerdaCima, ref(m), palavra, ref(c), ref(encontrou));

    tdireita.join();
    tesquerda.join();
    tbaixo.join();
    tcima.join();
    tdiagonalDireitaBaixo.join();
    tDiagonalDireitaCima.join();
    tdiagonalEsquerdaBaixo.join();
    tdiagonalEsquerdaCima.join();

    return encontrou;
}

int main() {
    ifstream fin("cacapalavras.txt");
    if (!fin) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    int linhas, colunas;
    fin >> linhas >> colunas; // leitura da dimensão da matriz
    vector<vector<char>> matriz(linhas, vector<char>(colunas));

    // leitura da matriz
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fin >> matriz[i][j];
        }
    }

    vector<string> palavras;
    string palavra;
    while (fin >> palavra) {
        palavras.push_back(palavra);
    }
    fin.close();

    vector<ResultadoBusca> resultadosEncontrados;

    for (const auto& p : palavras) {
        Coordenadas coordenadas;
        bool encontrada = buscaPalavra(matriz, p, coordenadas);
        resultadosEncontrados.push_back({p, encontrada, coordenadas});

        if (encontrada) {
            Coordenada inicial = coordenadas.inicial;
            Coordenada final = coordenadas.final;
            Direcao direcao = coordenadas.direcao;

            int linhaAtual = inicial.linha;
            int colunaAtual = inicial.coluna;

            while (true) {
                matriz[linhaAtual][colunaAtual] = toupper(matriz[linhaAtual][colunaAtual]);

                if (linhaAtual == final.linha && colunaAtual == final.coluna) break;

                switch (direcao) {
                    case DIREITA: colunaAtual++; break;
                    case ESQUERDA: colunaAtual--; break;
                    case BAIXO: linhaAtual++; break;
                    case CIMA: linhaAtual--; break;
                    case DIAGONAL_DIREITA_BAIXO: linhaAtual++; colunaAtual++; break;
                    case DIAGONAL_ESQUERDA_BAIXO: linhaAtual++; colunaAtual--; break;
                    case DIAGONAL_DIREITA_CIMA: linhaAtual--; colunaAtual++; break;
                    case DIAGONAL_ESQUERDA_CIMA: linhaAtual--; colunaAtual--; break;
                    default: break;
                }
            }
        }
    }

    ofstream fout("resultados.txt");
    if (!fout) {
        cerr << "Erro ao criar o arquivo de saída!" << endl;
        return 1;
    }

    // escreve matriz atualizada
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fout << matriz[i][j];
        }
        fout << endl;
    }
    fout << "------------------------------------------------------" << endl;

    // escreve resultados
    for (const auto& resultado : resultadosEncontrados) {
        if (resultado.encontrada) {
            fout << resultado.palavra << " - ("
                 << resultado.coordenadas.inicial.linha + 1 << ", "
                 << resultado.coordenadas.inicial.coluna + 1 << "): "
                 << direcaoToString(resultado.coordenadas.direcao) << endl;
        } else {
            fout << resultado.palavra << ": não encontrada" << endl;
        }
    }

    fout.close();
    return 0;
}
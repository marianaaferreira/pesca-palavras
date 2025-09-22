#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include "busca.h"
using namespace std;

struct ResultadoBusca {
    string palavra;
    Coordenadas coordenadas;
};

bool buscaPalavra(vector<vector<char>> m, string palavra, Coordenadas &c){
    bool encontrou = false;
    thread diagonal(procuraDiagonal, m, palavra, ref(encontrou), ref(c));
    thread horizontal(procuraHorizontal, m, palavra, ref(encontrou), ref(c));
    thread vertical(procuraVertical, m, palavra, ref(encontrou), ref(c));
    thread diagonalReverso(procuraDiagonalReverso, m, palavra, ref(encontrou), ref(c));
    thread horizontalReverso(procuraHorizontalReverso, m, palavra, ref(encontrou), ref(c));
    thread verticalReverso(procuraVerticalReverso, m, palavra, ref(encontrou), ref(c));

    diagonal.join();
    horizontal.join();
    vertical.join();
    diagonalReverso.join();
    horizontalReverso.join();
    verticalReverso.join();

    if(encontrou) return true; return false;
}

int main() {
    ifstream fin("cacapalavras.txt");
    if (!fin) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }
    int linhas, colunas;
    fin >> linhas >> colunas; //leitura da dimensao da matriz presente na primeira linha do arquivo
    vector<vector<char>> matriz(linhas, vector<char>(colunas));

    //leitura do arquivo e inserção dos caracteres em uma matriz
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
        if (buscaPalavra(matriz, p, coordenadas)) {
            resultadosEncontrados.push_back({p, coordenadas});
        }
    }

    for (const auto& resultado : resultadosEncontrados) {
        Coordenada inicial = resultado.coordenadas.inicial;
        Coordenada final = resultado.coordenadas.final;
        string direcao = resultado.coordenadas.direcao;

        int linhaAtual = inicial.linha;
        int colunaAtual = inicial.coluna;
        while (true) {
                matriz[linhaAtual][colunaAtual] = toupper(matriz[linhaAtual][colunaAtual]);
                
                if (linhaAtual == final.linha && colunaAtual == final.coluna) {
                    break;
                }

                if (direcao == "direita/baixo") {
                    linhaAtual++;
                    colunaAtual++;
                } else if (direcao == "direita") {
                    colunaAtual++;
                } else if (direcao == "baixo") {
                    linhaAtual++;
                } else if (direcao == "baixo/esquerda") {
                    linhaAtual++;
                    colunaAtual--;
                } else if (direcao == "esquerda") {
                    colunaAtual--;
                } else if (direcao == "cima") {
                    linhaAtual--;
                }
        }
    }

    ofstream fout("resultados.txt");
    if (!fout) {
        cerr << "Erro ao criar o arquivo de saída!" << endl;
        return 1;
    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fout << matriz[i][j];
        }
        fout << endl;
    }
    fout << "------------------------------------------------------" << endl;

    if (resultadosEncontrados.empty()) {
        fout << "Nenhuma palavra encontrada." << endl;
    } else {
        for (const auto& resultado : resultadosEncontrados) {
            fout << resultado.palavra << " - ("
                 << resultado.coordenadas.inicial.linha + 1 << ", "
                 << resultado.coordenadas.inicial.coluna + 1 << "): "
                 << resultado.coordenadas.direcao << endl;
        }
    }

    fout.close();

    return 0;
}
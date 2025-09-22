# Pesca Palavras
Projeto em C++ para implementar um algoritmo de **caça-palavras** usando **threads** para possibilitar buscas paralelas.
O programa lê uma matriz de caracteres a partir de um arquivo de texto e permite realizar buscas por palavras presentes no mesmo arquivo, armazenando e exibindo suas localizações.

## Estrutura do Projeto
├── src/                # Código-fonte
│   ├── main.cpp        # Ponto de entrada
│   └── busca.h         # Funções de busca
|              
├── cacapalavras.txt    # Arquivo de entrada
├── resultados.txt      # Arquivo de saída
│
├── README.md           # Documentação do projeto

## Formato do Arquivo de Entrada

O arquivo `cacapalavras.txt` deve conter:

1. Primeira linha: dimensões da matriz (`linhas colunas`).
2. Linhas seguintes: caracteres da matriz.
3. Linhas seguintes a matriz: palavras a serem buscadas.

## Como Compilar e Executar

No Linux ou no GitHub Codespaces:

```bash
g++ src/main.cpp -o build/app
./build/app

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "arvore.h"


using namespace std;

void menu(int);

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int iOpcao = 0;
    menu(iOpcao);

    return 0;
}


void printMenu()
{
    setlocale(LC_ALL, "Portuguese");
    cout << "01. Construir uma árvore binária de busca a partir de um arquivo texto\n"
            "02. Construir uma árvore binária de busca a partir de dados digitados pelo usuário\n"
            "03. Verificar a altura da árvore\n"
            "04. Verificar o tamanho da árvore\n"
            "05. Inserir um elemento\n"
            "06. Remover um elemento\n"
            "06. Buscar o endereço de memória de um elemento\n"
            "07. Verificar se a árvore é completa\n"
            "08. Verificar se a árvore é perfeita\n"
            "09. Exibir a árvore utilizando (BFS)\n"
            "10. Converter a árvore em uma lista e ordenar com Bubble Sort\n"
            "11. Converter a árvore em uma lista e ordenar com Selection Sort\n"
            "12. Converter a árvore em uma lista e ordenar com Insertion Sort\n"
            "13. Converter a árvore em uma lista e ordenar com Shell Sort" << endl;
    cout << "Digite: ";
}

void teste()
{
    struct Node *root = nullptr;

    for (int i = 0; i < 10; i++) {
        int j = 1 - 2 * (i % 2);
        root = insertNode(root, i * j);
    }

    traversePreOrder(root);
    cout << endl;


    cout << alturaArvore(root) << endl;

    cout << "Tamanho arvore: " << tamanhoArvore(root) << endl;
}

void menu(int iOpcao) {
    int iOpcaos = iOpcao;
    while (iOpcaos != -1){

        system("cls");

        printMenu();
        cin >> iOpcaos;

        switch (iOpcaos) {
            case 1:
                break;

            case -1:
                cout << "Tchau!" << endl;
                break;

            default:
                teste();
                break;

        }
    }
}
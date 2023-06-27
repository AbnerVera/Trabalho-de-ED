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
            "07. Buscar o endereço de memória de um elemento\n"
            "08. Verificar se a árvore é completa\n"
            "09. Verificar se a árvore é perfeita\n"
            "10. Exibir a árvore utilizando (BFS)\n"
            "11. Converter a árvore em uma lista e ordenar com Bubble Sort\n"
            "12. Converter a árvore em uma lista e ordenar com Selection Sort\n"
            "13. Converter a árvore em uma lista e ordenar com Insertion Sort\n"
            "14. Converter a árvore em uma lista e ordenar com Shell Sort" << endl;
    cout << "Digite: ";
}

struct Node* teste(struct Node* ptrRoot)
{
    struct Node *root = ptrRoot;

    for (int i = 0; i < 10; i++) {
        int j = 1 - 2 * (i % 2);
        root = insertNode(root, i * j);
    }

    traversePreOrder(root);
    cout << endl;


    cout << alturaArvore(root) << endl;

    cout << "Tamanho arvore: " << tamanhoArvore(root) << endl;

    return  root;
}

void menu(int iOpcao) {

    int iOpcaos = iOpcao;
    struct Node* root = nullptr;
    int iValor;

    while (iOpcaos != -1){

        system("cls");

        printMenu();
        cin >> iOpcaos;

        switch (iOpcaos) {
            case 1:
                cout << "01. Construir uma árvore binária de busca a partir de um arquivo texto\n" << endl;
                //root = arvoreTexto();
                break;

            case 2:
                cout << "02. Construir uma árvore binária de busca a partir de dados digitados pelo usuário\n" << endl;
                //root = arvoreUsuario();
                break;

            case 3:
                cout << "03. Verificar a altura da árvore\n" << endl;
                cout << "Altura arvore: " << alturaArvore(root) << endl;
                break;

            case 4:
                cout << "04. Verificar o tamanho da árvore\n" << endl;
                cout << "Tamanho arvore: " << tamanhoArvore(root) << endl;
                break;

            case 5:
                cout << "05. Inserir um elemento\n" << endl;
                cout << "Digite um elemento: ";
                cin >> iValor;

                insertNode(root, iValor);
                break;

            case 6:
                cout << "06. Remover um elemento\n" << endl;
                break;

            case 7:
                cout << "07. Buscar o endereço de memória de um elemento\n" << endl;
                break;

            case 8:
                cout << "08. Verificar se a árvore é completa\n" << endl;
                break;

            case 9:
                cout << "09. Verificar se a árvore é perfeita\n" << endl;
                break;

            case 10:
                cout << "10. Exibir a árvore utilizando (BFS)\n" << endl;
                break;

            case 11:
                cout << "11. Converter a árvore em uma lista e ordenar com Bubble Sort\n" << endl;
                break;

            case 12:
                cout << "12. Converter a árvore em uma lista e ordenar com Selection Sort\n" << endl;
                break;

            case 13:
                cout << "13. Converter a árvore em uma lista e ordenar com Insertion Sort\n" << endl;
                break;

            case 14:
                cout << "14. Converter a árvore em uma lista e ordenar com Shell Sort\n" << endl;

            case -1:
                cout << "Tchau!" << endl;
                break;

            default:
                root = teste(root);
                break;

        }
    }
}
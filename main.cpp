#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "arvore.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

void menu();

int main()
{
    setlocale(LC_ALL, "Portuguese");

    menu();

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
            "11. Exibir a árvore PreOrder\n"
            "12. Converter a árvore em uma lista e ordenar com Bubble Sort\n"
            "13. Converter a árvore em uma lista e ordenar com Selection Sort\n"
            "14. Converter a árvore em uma lista e ordenar com Insertion Sort\n"
            "15. Converter a árvore em uma lista e ordenar com Shell Sort\n"
            "-1. Sair" << endl;
    cout << "\nDigite sua opção: ";
}

struct Node* teste(struct Node* ptrRoot)
{
    struct Node *root = ptrRoot;

    for (int i = 0; i < 10; i++) 
    {
        int j = 1 - 2 * (i % 2);
        root = insertNode(root, i * j);
    }

    traversePreOrder(root);
    cout << endl;

    return  root;
}

void tempo(std::chrono::_V2::system_clock::time_point timeStart)
{
    auto timeStop = high_resolution_clock::now();
    auto timeDurationNano = duration_cast<nanoseconds>(timeStop - timeStart);
    auto timeDurationSegundo = duration_cast<seconds>(timeStop - timeStart);

    if (timeDurationSegundo.count() <= 0)
    { 
        cout << "\n\nTempo da operação: " << timeDurationNano.count() << " nanosegundos" << endl;
    }
    else 
    { 
        cout << "\n\nTempo da operação: " << timeDurationSegundo.count() << " segundos" << endl;
    }
}


void menu() {

    int iOption;
    int iValue;
    struct Node* root = nullptr;
    struct Node* ptrTemp = nullptr;
    string strPath;
    auto timeStart = high_resolution_clock::now();

    while (iOption != -1){

        system("cls");

        printMenu();
        cin >> iOption;

        system("cls");

        timeStart = high_resolution_clock::now();

        switch (iOption) 
        {
            case 1:
                cout << "01. Construir uma árvore binária de busca a partir de um arquivo texto\n" << endl;
                cout << "Digite o nome do arquivo: ";
                cin >> strPath;

                root = treeFromText(root, strPath);
                break;

            case 2:
                cout << "02. Construir uma árvore binária de busca a partir de dados digitados\n" << endl;
                cout << "Digite o numero de elementos: ";
                cin >> iValue;
                cout << "\n<< ";

                root = treeFromPrompt(root, iValue);
                break;

            case 3:
                cout << "03. Verificar a altura da árvore\n" << endl;
                cout << "Altura arvore: " << treeHeight(root) << endl;
                break;

            case 4:
                cout << "04. Verificar o tamanho da árvore\n" << endl;
                cout << "Tamanho arvore: " << treeSize(root) << endl;
                break;

            case 5:
                cout << "05. Inserir um elemento\n" << endl;
                cout << "Digite o elemento: ";
                cin >> iValue;

                root = insertNode(root, iValue);

                break;

            case 6:
                cout << "06. Remover um elemento\n" << endl;
                cout << "Digite o elemento para remoção: ";
                cin >> iValue;

                deleteNode(root, iValue);

                break;

            case 7:
                cout << "07. Buscar o endereço de memória de um elemento\n" << endl;
                cout << "Digite o elemento: ";
                cin >> iValue;

                ptrTemp =  searchNode(root, iValue);

                if (ptrTemp != nullptr)
                { 
                    cout << "Endereço de " << iValue  << ": " << ptrTemp;
                }
                else 
                {
                    cout << "Elemento não encontrado";
                }

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
                cout << "11. Exibir a árvore PreOrder\n" << endl;

                traversePreOrder(root);

                break;

            case 12:
                cout << "12. Converter a árvore em uma lista e ordenar com Bubble Sort\n" << endl;
                treeToLinkedList(root);
                bubbleSortList(&root);

                break;

            case 13:
                cout << "13. Converter a árvore em uma lista e ordenar com Selection Sort\n" << endl;
                break;

            case 14:
                cout << "14. Converter a árvore em uma lista e ordenar com Insertion Sort\n" << endl;
                break;

            case 15:
                cout << "15. Converter a árvore em uma lista e ordenar com Shell Sort\n" << endl;

            case -1:
                cout << "Tchau!" << endl;
                break;

            default:
                root = teste(root);
                break;
        }

        if(iOption != -1)
        {
            tempo(timeStart);
            system("pause");
        }
    }
}
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

/**
 * Exibe as opções do menu
 * 
 * Escreve na tela as possíveis das operações que 
 * podem ser realizadas para a escolha do usuário
*/
void printMenu()
{
    system("COLOR 2");
    cout << "_______0______________________________________________________________________________0________\n"
            "______000____________________________________________________________________________000_______\n"
            "_____00000__________________________________________________________________________00000______\n"
            "____0000000________________________________________________________________________0000000_____\n"
            "___000000000______________________________________________________________________000000000____\n"
            "______| |____________________________________________________________________________| |_______\n" << endl;
    cout << "01. Construir uma árvore binária de busca a partir de um arquivo texto\n"
            "02. Construir uma árvore binária de busca a partir de dados digitados\n"
            "03. Verificar a altura da árvore\n"
            "04. Verificar o tamanho da árvore\n"
            "05. Inserir um elemento\n"
            "06. Remover um elemento\n"
            "07. Buscar o endereço de memória de um elemento\n"
            "08. Verificar se a árvore é completa\n"
            "09. Verificar se a árvore é perfeita\n"
            "10. Exibir a árvore utilizando (BFS)\n"
            "11. Exibir a árvore em pré-ordem\n"
            "12. Converter a árvore em uma lista e ordenar com Bubble Sort\n"
            "13. Converter a árvore em uma lista e ordenar com Selection Sort\n"
            "14. Converter a árvore em uma lista e ordenar com Insertion Sort\n"
            "15. Converter a árvore em uma lista e ordenar com Shell Sort\n"
            "-1. Sair" << endl;
    cout << "\nDigite sua opção: ";
}


/**
 * Informa o tempo de duração de uma operação
 * 
 * Exibe na tela uma mensagem informando quando tempo durou uma
 * operação, considerando o tempo inicial formecido e que a operção 
 * foi finalizada logo antes da chamada dessa função
 * 
 * @param timeStart tempo em que a operação foi iniciada
*/
void tempo(std::chrono::_V2::system_clock::time_point timeStart)
{
    auto timeStop = high_resolution_clock::now();   // Tempo final da operação
    auto timeDurationNano = duration_cast<nanoseconds>(timeStop - timeStart);   // Duração da operação em nanosegundos
    auto timeDurationSegundo = duration_cast<seconds>(timeStop - timeStart);    // Duração da operação em segundos

    if (timeDurationSegundo.count() <= 0)
    { 
        cout << "\n\nTempo da operação: " << timeDurationNano.count() << " nanosegundos" << endl;
    }
    else 
    { 
        cout << "\n\nTempo da operação: " << timeDurationSegundo.count() << " segundos" << endl;
    }
}

/**
 * Cria o menu para operações com árvore binaria
*/
void menu() {
    int iOption;
    int iValue;
    struct Node* root = nullptr;
    struct Node* ptrTemp = nullptr;
    string strPath;
    auto timeStart = high_resolution_clock::now();

    while (iOption != -1){

        system("cls");  // Limpa a tela

        printMenu();    // Imprime as opções do menu
        cin >> iOption;

        system("cls");  // Limpa a tela

        timeStart = high_resolution_clock::now();

        switch (iOption) 
        {
            case 1:
                cout << "01. Construir uma árvore binária de busca a partir de um arquivo texto\n" << endl;
                cout << "Digite o nome do arquivo: ";
                cin >> strPath;

                deleteTree(&root);
                root = treeFromText(root, strPath);
                break;

            case 2:
                cout << "02. Construir uma árvore binária de busca a partir de dados digitados\n" << endl;
                cout << "Digite o numero de elementos: ";
                cin >> iValue;
                cout << "\n<< ";

                deleteTree(&root);

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

                deleteNode(&root, root, iValue);

                break;

            case 7:
                cout << "07. Buscar o endereço de memória de um elemento\n" << endl;
                cout << "Digite o elemento: ";
                cin >> iValue;

                ptrTemp =  searchNode(root, iValue);

                if (ptrTemp != nullptr)
                { 
                    cout << "\nEndereço de " << ptrTemp -> iPayload  << ": " << ptrTemp;
                }
                else 
                {
                    cout << "\nElemento não encontrado";
                }

                break;

            case 8:
                cout << "08. Verificar se a árvore é completa\n" << endl;
                if (isCompleteTree(root))
                    cout << "A arvore e completa." << endl;
                else
                    cout << "A arvore nao e completa." << endl;
                break;

            case 9:
                cout << "09. Verificar se a árvore é perfeita\n" << endl;
                if (isPerfectTree(root))
                    cout << "A arvore e perfeita." << endl;
                else
                    cout << "A arvore nao e perfeita." << endl;
                break;

            case 10:
                cout << "10. Exibir a árvore utilizando (BFS)\n" << endl;
                printLevelOrder(root);
                break;

            case 11:
                cout << "11. Exibir a árvore em pré-ordem\n" << endl;

                traversePreOrder(root);

                break;

            case 12:
                cout << "12. Converter a árvore em uma lista e ordenar com Bubble Sort\n" << endl;
                treeToLinkedList(root);
                bubbleSort(&root);
                root = linkedListToTree(root);

                break;

            case 13:
                cout << "13. Converter a árvore em uma lista e ordenar com Selection Sort\n" << endl;
                treeToLinkedList(root);
                selectSort(root);
                root = linkedListToTree(root);
                break;

            case 14:
                cout << "14. Converter a árvore em uma lista e ordenar com Insertion Sort\n" << endl;
                treeToLinkedList(root);
                insertSort(&root);
                root = linkedListToTree(root);
                break;

            case 15:
                cout << "15. Converter a árvore em uma lista e ordenar com Shell Sort\n" << endl;
                treeToLinkedList(root);
                shellSort(root);
                root = linkedListToTree(root);
                break;
            case -1:
                deleteTree(&root);
                cout << "Tchau!" << endl;
                break;

            default:
                break;
        }

        if(iOption != -1)
        {
            tempo(timeStart);
            system("pause");
        }
    }
}
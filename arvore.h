#ifndef TRABALHO_DE_ED_ARVORE_H
#define TRABALHO_DE_ED_ARVORE_H

#include <iostream>
#include <string>

using namespace std;

struct Node
{
    int iPayload;
    struct Node* ptrLeft;
    struct Node* ptrRight;
};

struct Node* newNode(int iData);

struct Node* arvoreTexto(struct Node* root, string sEndereco);
struct Node* arvoreDigitado(struct Node* root, int iTamanho);

void traversePreOrder(struct Node*);
void traverseInOrder(struct Node* );
void traversePosOrder(struct Node*);

int alturaArvore(struct Node* , int iAltura = 0);
int tamanhoArvore(struct Node* root,  int iTamanho = 0);

struct Node* insertNode(struct Node* node, int iData);
struct Node* deleteNode(struct Node* node, int iData);
struct Node* searchNode(struct Node* node, int iData);


struct Node* newNode(int iData){
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->iPayload = iData;
    newNode->ptrLeft = nullptr;
    newNode->ptrRight = nullptr;
    return newNode;
}


void traversePreOrder(struct Node* ptrStartingNode)
{
    if(ptrStartingNode != nullptr)
    {
        cout << " " << ptrStartingNode->iPayload;
        traversePreOrder(ptrStartingNode->ptrLeft);
        traversePreOrder(ptrStartingNode->ptrRight);
    }

}


void traverseInOrder(struct Node* ptrStartingNode)
{
    if(ptrStartingNode != nullptr)
    {
        traverseInOrder(ptrStartingNode->ptrLeft);
        cout << " " << ptrStartingNode->iPayload;
        traverseInOrder(ptrStartingNode->ptrRight);
    }
}


void traversePosOrder(struct Node* ptrStartingNode)
{
    if(ptrStartingNode != nullptr)
    {
        traversePosOrder(ptrStartingNode->ptrLeft);
        traversePosOrder(ptrStartingNode->ptrRight);
        cout << " " << ptrStartingNode->iPayload;
    }
}


struct Node* arvoreTexto(struct Node* root, string sEndereco)
{
    FILE *arq;
    
    arq = fopen(sEndereco.c_str(), "rt");

    if (arq == nullptr)
    {
        cout << "Erro ao encontrar o arquivo";
        return nullptr;
    }

    char Linha[100];
    char *result;
    int iValor;

    for(int i = 1; !feof(arq); i++)
    {
        // Lê uma linha (inclusive com o '\n')
        result = fgets(Linha, 100, arq);  // o 'fgets' lê até 99 caracteres ou até o '\n'
        if (result)  // Se foi possível ler
        {
            sscanf(Linha, "%d", &iValor);
            root = insertNode(root, iValor);
        }
    }

    fclose(arq);

    return root;
}


struct Node* arvoreDigitado(struct Node* root, int iTamanho)
{
    for(int i = 0; i < iTamanho; i++)
    {
        int iValor;
        cin >> iValor;
        root = insertNode(root, iValor);
    }
    return root;
}


struct Node* insertNode(struct Node* node, int iData)
{
    if(node == nullptr)
    {
        return newNode(iData);
    }

    if(iData < node->iPayload)
    {
        node->ptrLeft = insertNode(node->ptrLeft, iData);
    }
    else
    {
        node->ptrRight = insertNode(node->ptrRight, iData);
    }
    return node;
}

struct Node* menorFolha(struct Node* node)  //lesserLeaf
{
    struct Node* ptrCurrent = node;

    while(ptrCurrent && ptrCurrent->ptrLeft != nullptr) ptrCurrent = ptrCurrent->ptrLeft;

    return ptrCurrent;
}

struct Node* deleteNode(struct Node* node, int iData)
{
    if(node == nullptr) return node;

    if(iData < node->iPayload) node->ptrLeft = deleteNode(node->ptrLeft, iData);
    else if(iData > node->iPayload) node->ptrRight = deleteNode(node->ptrRight, iData);
    else
    {
        struct Node* ptrTemp = nullptr;
        if(node->ptrRight == nullptr)
        {
            ptrTemp = node->ptrLeft;
            free(node);

            return ptrTemp;
        }
        else if(node->ptrLeft == nullptr)
        {
            ptrTemp = node->ptrRight;
            free(node);

            return ptrTemp;
        }

        ptrTemp = menorFolha(node->ptrRight);

        node->iPayload = ptrTemp->iPayload;

        node->ptrRight = deleteNode(node->ptrRight, ptrTemp->iPayload);

    }
}


/**
 * Descobre a altura da árvore.
 *
 * Calcula a profundidade máxima de uma árvore binaria, passando por
 * toda ramificação da árvore, retornando a profundidade da folha
 * mais profunda.
 *
 * @param root Ponterio do Node raiz da árvore.
 * @param iAltura Inteiro, altura da raiz, inicializado em 0
 * @return inteiro representado a profundidade da folha mais profunda.
 */
int alturaArvore(struct Node* root, int iAltura)
{
    if (root != nullptr)
    {
        int AltLeft = alturaArvore(root->ptrLeft, iAltura + 1);
        int AltRight = alturaArvore(root->ptrRight, iAltura + 1);

        return max(AltLeft, AltRight);

    }
    else return iAltura;
}


/**
 * Descobre o tamanho da árvore,
 *
 * Calcula o tamanho de uma árvore binaria, contado o número de
 * nós em toda sua ramificação
 *
 * @param root Ponterio do Node raiz da árvore
 * @param iTamanho Inteiro, tamanho da raiz, inicializado em 0
 * @return inteiro representado o tamanho da árvore.
 */
int tamanhoArvore(struct Node* root, int iTamanho)
{
    if (root != nullptr)
    {
        int iTamLeft = tamanhoArvore(root->ptrLeft, iTamanho + 1);
        int iTamRight = tamanhoArvore(root->ptrRight, iTamanho + 1);

        return 1 + iTamLeft + iTamRight;
    }
    else return 0;
}

#endif //TRABALHO_DE_ED_ARVORE_H

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

struct Node* treeFromText(struct Node* root, string strPath);
struct Node* treeFromPrompt(struct Node* root, int iSize);

void traversePreOrder(struct Node*);
void traverseInOrder(struct Node* );
void traversePosOrder(struct Node*);

int treeHeight(struct Node* root, int iHeight = 0);
int treeSize(struct Node* root,  int iSize = 0);

struct Node* insertNode(struct Node* node, int iData);
struct Node* deleteNode(struct Node* node, int iData);
struct Node* searchNode(struct Node* node, int iData);


struct Node* newNode(int iData)
{
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));

    newNode -> iPayload = iData;
    newNode -> ptrLeft = nullptr;
    newNode -> ptrRight = nullptr;

    return newNode;
}

void traversePreOrder(struct Node* ptrStartingNode)
{
    if(ptrStartingNode != nullptr)
    {
        cout << " " << ptrStartingNode -> iPayload;

        traversePreOrder(ptrStartingNode -> ptrLeft);
        traversePreOrder(ptrStartingNode -> ptrRight);
    }
}


void traverseInOrder(struct Node* ptrStartingNode)
{
    if(ptrStartingNode != nullptr)
    {
        traverseInOrder(ptrStartingNode -> ptrLeft);

        cout << " " << ptrStartingNode -> iPayload;

        traverseInOrder(ptrStartingNode -> ptrRight);
    }
}


void traversePosOrder(struct Node* ptrStartingNode)
{
    if(ptrStartingNode != nullptr)
    {
        traversePosOrder(ptrStartingNode -> ptrLeft);
        traversePosOrder(ptrStartingNode -> ptrRight);

        cout << " " << ptrStartingNode -> iPayload;
    }
}

struct Node* treeFromText(struct Node* root, string strPath)
{
    FILE *archive;
    
    archive = fopen(strPath.c_str(), "rt");

    if (archive == nullptr)
    {
        cout << "Erro ao encontrar o arquivo";
        return nullptr;
    }

    char cRow[100];
    char *cResult;
    int iValue;

    for(int i = 1; !feof(archive); i++)
    {
        // Lê uma linha (inclusive com o '\n')
        cResult = fgets(cRow, 100, archive);  // o 'fgets' lê até 99 caracteres ou até o '\n'
        
        if (cResult)  // Se foi possível ler
        {
            sscanf(cRow, "%d", &iValue);
            root = insertNode(root, iValue);
        }
    }

    fclose(archive);

    return root;
}


struct Node* treeFromPrompt(struct Node* root, int iSize)
{
    for(int i = 0; i < iSize; i++)
    {
        int iValue;
        cin >> iValue;
        root = insertNode(root, iValue);
    }

    return root;
}


struct Node* insertNode(struct Node* sNode, int iData)
{
    if(sNode == nullptr)
    {
        return newNode(iData);
    }

    if(iData < sNode -> iPayload)
    {
        sNode -> ptrLeft = insertNode(sNode -> ptrLeft, iData);
    }
    else
    {
        sNode -> ptrRight = insertNode(sNode -> ptrRight, iData);
    }

    return sNode;
}

struct Node* lesserLeaf(struct Node* sNode)  //lesserLeaf
{
    struct Node* ptrCurrent = sNode;

    while (ptrCurrent && ptrCurrent->ptrLeft != nullptr)
    {   
        ptrCurrent = ptrCurrent->ptrLeft;
    }

    return ptrCurrent;
}

struct Node* deleteNode(struct Node* sNode, int iData)
{
    if (sNode == nullptr)
    { 
        return sNode;
    }

    if (iData < sNode -> iPayload) 
    {   
        sNode -> ptrLeft = deleteNode(sNode -> ptrLeft, iData);
    }
    else if (iData > sNode -> iPayload) 
    {
        sNode -> ptrRight = deleteNode(sNode -> ptrRight, iData);
    }
    else
    {
        struct Node* ptrTemp = nullptr;

        if (sNode -> ptrRight == nullptr)
        {
            ptrTemp = sNode -> ptrLeft;
    
            free(sNode);

            return ptrTemp;
        }
        else if(sNode -> ptrLeft == nullptr)
        {
            ptrTemp = sNode -> ptrRight;

            free(sNode);

            return ptrTemp;
        }

        ptrTemp = lesserLeaf(sNode -> ptrRight);

        sNode -> iPayload = ptrTemp -> iPayload;

        sNode -> ptrRight = deleteNode(sNode -> ptrRight, ptrTemp -> iPayload);
    }
}

struct Node* searchNode(struct Node* sNode, int iData)
{
    if (sNode == nullptr)
    {
        return nullptr;
    }

    if (iData == sNode -> iPayload)
    {
        return sNode;
    }
    else if (iData < sNode -> iPayload)
    {
        return searchNode(sNode -> ptrLeft, iData);
    }
    else
    {
        return searchNode(sNode -> ptrRight, iData);
    }

    return sNode;
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
int treeHeight(struct Node* root, int iHeight)
{
    if (root != nullptr)
    {
        int iHeightLeft = treeHeight(root -> ptrLeft, iHeight + 1);
        int iHeightRight = treeHeight(root -> ptrRight, iHeight + 1);

        return max(iHeightLeft, iHeightRight);
    }
    else
    {
        return iHeight;
    } 
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
int treeSize(struct Node* root, int iSize)
{
    if (root != nullptr)
    {
        int iSizeLeft = treeSize(root -> ptrLeft, iSize + 1);
        int iSizeRight = treeSize(root -> ptrRight, iSize + 1);

        return 1 + iSizeLeft + iSizeRight;
    }
    else
    {
        return 0;
    } 
}

#endif //TRABALHO_DE_ED_ARVORE_H

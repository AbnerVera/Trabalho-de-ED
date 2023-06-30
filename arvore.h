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
void traverseInOrder(struct Node*);
void traversePosOrder(struct Node*);
void treeToLinkedList(struct Node*);
void sortedInsert(struct Node**, struct Node*);
void deleteLinkedList(struct Node**);
void printLinkedList(struct Node*);
void bubbleSort(struct Node**);
void selectSort(struct Node*);
void insertSort(struct Node**);
void shellSort(struct Node*);

int treeHeight(struct Node* root, int iHeight = 0);
int treeSize(struct Node* root,  int iSize = 0);
int lengthLinkedList(Node* sNode); 

struct Node* insertNode(struct Node* sNode, int iData);
struct Node* deleteNode(struct Node* sNode, int iData);
struct Node* searchNode(struct Node* sNode, int iData);
struct Node* swapNodeValues(struct Node* sNode1, struct Node* sNode2);
struct Node* getNodeAtIndex(struct Node* sNode, int iIndex); 
struct Node* linkedListToTree(struct Node* sNode);

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

void treeToLinkedList(struct Node* root)
{
    while (root != nullptr) 
    {
        if (root -> ptrLeft != nullptr) 
        {
            struct Node* ptrCurrent = root -> ptrLeft;
            
            while (ptrCurrent -> ptrRight) 
            {
                ptrCurrent = ptrCurrent -> ptrRight;
            }

            ptrCurrent -> ptrRight = root -> ptrRight;

            root -> ptrRight = root -> ptrLeft;
            root -> ptrLeft = nullptr;
        }
        
        root = root -> ptrRight;
    }
}

struct Node* swapNodeValues(struct Node* sNode1, struct Node* sNode2) 
{
  struct Node* sNodeTemp = sNode2 -> ptrRight;

  sNode2 -> ptrRight = sNode1;
  sNode1 -> ptrRight = sNodeTemp;

  return sNode2;
}

void bubbleSort(struct Node** sNode)
{   
    struct Node** sNodeTemp = sNode;
    int iLength = 0;
    
    while (*sNodeTemp != nullptr)
    {
        iLength = iLength + 1;
        sNodeTemp = &(*sNodeTemp) -> ptrRight;
    }
    
    cout << "Inicio da ordenação pelo algoritmo Bubble Sort: " << endl; 

    for (int iOuterLoop = 0; iOuterLoop <= iLength; iOuterLoop++) 
    {
        sNodeTemp = sNode;
        bool bSwap = false;

        cout << "  Iteração " << iOuterLoop << ": " << endl;

        printLinkedList(*sNode);

        for (int iInnerLoop = 0; iInnerLoop < iLength - iOuterLoop - 1; iInnerLoop++)
        {   

            struct Node* sNode1 = *sNodeTemp;
            struct Node* sNode2 = sNode1 -> ptrRight;
  
            if (sNode1 -> iPayload > sNode2 -> iPayload) 
            {
                *sNodeTemp = swapNodeValues(sNode1, sNode2);
                bSwap = true;
            }
  
            sNodeTemp = &(*sNodeTemp) -> ptrRight;
        }
  
        if (bSwap == false)
        {
            break;
        }
    }
}

void selectSort(struct Node* sNode)
{
    struct Node* sTemp = sNode;
  
    while (sTemp != nullptr) 
    {
        struct Node* sMin = sTemp;
        struct Node* sNext = sTemp -> ptrRight;
  
        while (sNext != nullptr) 
        {
            if (sMin -> iPayload > sNext -> iPayload)
            {
                sMin = sNext;
            }
  
            sNext = sNext -> ptrRight;
        }
  
        int iValue = sTemp -> iPayload;

        sTemp -> iPayload = sMin -> iPayload;
        sMin -> iPayload = iValue;
        sTemp = sTemp -> ptrRight;
    }
}

void insertSort(struct Node** sNode)
{
    struct Node* sSorted = nullptr;
    struct Node* ptrCurrent = *sNode;

    while (ptrCurrent != nullptr)
    {
        struct Node* sNext = ptrCurrent -> ptrRight;

        sortedInsert(&sSorted, ptrCurrent);

        ptrCurrent = sNext;
    }

    *sNode = sSorted;
}

void sortedInsert(struct Node **sNode, struct Node *sNew)
{
    struct Node *ptrCurrent = nullptr;
    
    if (*sNode == nullptr or (*sNode) -> iPayload > sNew -> iPayload)
    {
        sNew -> ptrRight = *sNode;
        *sNode = sNew;
    }
    else
    {
        ptrCurrent = *sNode;
        while (ptrCurrent -> ptrRight != nullptr and ptrCurrent -> ptrRight -> iPayload <= sNew -> iPayload)
        {
            ptrCurrent = ptrCurrent -> ptrRight;
        }

        sNew -> ptrRight = ptrCurrent -> ptrRight;
        ptrCurrent -> ptrRight = sNew;
    }
}

int lengthLinkedList(struct Node* sNode) 
{
    int iLength = 0;
    
    while (sNode != nullptr) 
    {
        iLength++;
        sNode = sNode -> ptrRight;
    }
    
    return iLength;
}

struct Node* getNodeAtIndex(struct Node* sNode, int iIndex) 
{
    int iCount = 0;
    while (sNode != nullptr) 
    {
        if (iCount == iIndex)
        {
            return sNode;
        }

        iCount++;
        sNode = sNode -> ptrRight;
    }

    return nullptr;
}

void shellSort(struct Node* sNode) 
{
    int iLength = lengthLinkedList(sNode);
    
    for (int iGap = iLength / 2; iGap > 0; iGap /= 2) 
    {
        for (int iOuterLoop = iGap; iOuterLoop < iLength; iOuterLoop++) 
        {
            int iTemp = getNodeAtIndex(sNode, iOuterLoop) -> iPayload;
            int iInnerLoop;
            
            for (iInnerLoop = iOuterLoop; iInnerLoop >= iGap and getNodeAtIndex(sNode, iInnerLoop - iGap) -> iPayload > iTemp; iInnerLoop -= iGap) 
            {
                getNodeAtIndex(sNode, iInnerLoop) -> iPayload = getNodeAtIndex(sNode, iInnerLoop - iGap) -> iPayload;
            }

            getNodeAtIndex(sNode, iInnerLoop) -> iPayload = iTemp;
        }
    }

}

void deleteLinkedList(struct Node** sNode)
{
   struct Node* ptrCurrent = *sNode;
   struct Node* sNext;
 
   while (ptrCurrent != nullptr)
   {
       sNext = ptrCurrent -> ptrRight;
       free(ptrCurrent);
       ptrCurrent = sNext;
   }

   *sNode = nullptr;
}

struct Node* linkedListToTree(struct Node* sNode)
{
    struct Node* sTree = nullptr;

    while (sNode != nullptr)
    {   
        sTree = insertNode(sTree, sNode -> iPayload);
        sNode = sNode -> ptrRight;
    }

    deleteLinkedList(&sNode); 
    
    return sTree;
}

void printLinkedList(struct Node* sNode)
{
    while (sNode != nullptr)
    {
        cout << sNode -> iPayload << " -> ";
        sNode = sNode -> ptrRight;
    }

    cout << " nullptr " << endl;
}

#endif //TRABALHO_DE_ED_ARVORE_H
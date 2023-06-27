#ifndef TRABALHO_DE_ED_ARVORE_H
#define TRABALHO_DE_ED_ARVORE_H

#include <iostream>

using namespace std;

struct Node
{
    int iPayload;
    struct Node* ptrLeft;
    struct Node* ptrRight;
};

struct Node* newNode(int iData);

void traversePreOrder(struct Node*);
void traverseInOrder(struct Node* );
void traversePosOrder(struct Node*);

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


#endif //TRABALHO_DE_ED_ARVORE_H

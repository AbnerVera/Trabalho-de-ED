#ifndef TRABALHO_DE_ED_ARVORE_H
#define TRABALHO_DE_ED_ARVORE_H

#include <iostream>
#include <string>
#include <cmath>

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
void breadthFirstSearch(struct Node* root);
void treeToLinkedList(struct Node*);
void sortedInsert(struct Node**, struct Node*);
void deleteLinkedList(struct Node**);
void printLinkedList(struct Node*);
void bubbleSort(struct Node**);
void selectSort(struct Node*);
void insertSort(struct Node**);
void shellSort(struct Node*);
void enqueue(struct QueueNode** sQueueFront, struct QueueNode** sQueueRear, struct Node* sNode);

int treeHeight(struct Node* root, int iHeight = 0);
int treeSize(struct Node* root,  int iSize = 0);
int lengthLinkedList(Node* sNode); 

bool isCompleteTree(struct Node* root, int iIndex, int iNumberNodes);
bool isFullTree(struct Node* root);
bool isQueueEmpty(struct QueueNode* sQueueFront);

struct Node* insertNode(struct Node* sNode, int iData);
struct Node* deleteNode(struct Node** root, struct Node* sNode, int iData);
struct Node* searchNode(struct Node* sNode, int iData);
struct Node* swapNodeValues(struct Node* sNode1, struct Node* sNode2);
struct Node* getNodeAtIndex(struct Node* sNode, int iIndex); 
struct Node* linkedListToTree(struct Node* sNode);
struct Node* dequeue(struct QueueNode** sQueueFront, QueueNode** sQueueRear);

struct QueueNode* createQueueNode(struct Node* sNode);



/**
 * Cria um nó
 * 
 * Cria um nó para uma árvore binaria
 * 
 * @param iData inteiro, valor armazenado no nó.
*/
struct Node* newNode(int iData)
{
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));

    newNode -> iPayload = iData;
    newNode -> ptrLeft = nullptr;
    newNode -> ptrRight = nullptr;

    return newNode;
}

/**
 * Exibe a árvore em pré-ordem
 * 
 * Atravessa a árvore a exibindo por recusrsão. É exibido
 * para cada nó, primeiro o seu próprio valor, depois o valor 
 * do nó a esquerda e por último o valor nó a direita.
 * 
 * @param ptrStartingNode Ponteiro do nó raiz da árvore no
 * inicio da recursão.
*/
void traversePreOrder(struct Node* ptrStartingNode)
{
    if(ptrStartingNode != nullptr)
    {
        cout << " " << ptrStartingNode -> iPayload;     // O nó primeiro se imprime

        traversePreOrder(ptrStartingNode -> ptrLeft);   // Depois o nó a esquerda
        traversePreOrder(ptrStartingNode -> ptrRight);  // Depois o nó a direita
    }
}


/**
 * Cria uma árvore binária a partir da leitura de um arquivo .txt
 * 
 * Lê um arquivo .txt com 1 valor inteiro por linha e cria uma 
 * árvore binária a partir desses valores
 * 
 * @param root Ponterio do nó raiz da árvore.
 * @param strPath endereço do arquivo .txt a partir da pasta
 * onde está o programa. Deve conter ".txt" no final
*/
struct Node* treeFromText(struct Node* root, string strPath)
{
    FILE *archive;
    
    archive = fopen(strPath.c_str(), "rt");

    if (archive == nullptr) // Arquivo não foi encontrado
    {
        cout << "Erro ao encontrar o arquivo";
        return nullptr;
    }

    char cRow[100];
    char *cResult;
    int iValue;

    for(int iCount = 1; !feof(archive); iCount++)
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


/**
 * Cria uma árvore binária a partir do input do usuário
 * 
 * @param root Ponterio do nó raiz da árvore.
 * @param iSize número  de inputs a serem digitados pelo
 * usuário
*/
struct Node* treeFromPrompt(struct Node* root, int iSize)
{
    for(int iCount = 0; iCount < iSize; iCount++)

      // O usuário digita os valores e eles são inseridos
    {
        int iValue;
        cout << "Insira o Valor de nº: " << iCount << endl;
        cin >> iValue;
        root = insertNode(root, iValue);
    }

    return root;
}


/**
 * Insere um nó na árvore
 * 
 * Insere uma folha na árvore binária a partir da recursão.
 * O valor será inserido a esquerda do nó avaliado se for
 * menor que ele ou a direita caso contrário.
 * 
 * @param sNode Ponterio do nó raiz da árvore.
 * @param iData inteiro, valor a ser armazenado na árvore
*/
struct Node* insertNode(struct Node* sNode, int iData)
{
    if(sNode == nullptr)    // Encontrada a posição para o novo nó
    {
        return newNode(iData);
    }

    if(iData < sNode -> iPayload)   // A possição para o novo nó está a esquerda
    {
        sNode -> ptrLeft = insertNode(sNode -> ptrLeft, iData);
    }
    else    // A possição para o novo nó está a direita
    {
        sNode -> ptrRight = insertNode(sNode -> ptrRight, iData);
    }

    return sNode;
}

/**
 * Acha o nó de menor valor a partir da entrada
 * 
 * @param sNode Ponterio de um nó da árvore.
 * @return folha de menor valor, o nó mais a 
 * esquerda possível.
*/
struct Node* lesserLeaf(struct Node* sNode)
{
    struct Node* ptrCurrent = sNode;

    while (ptrCurrent && ptrCurrent->ptrLeft != nullptr)    // Indo mais a esquerda possível
    {   
        ptrCurrent = ptrCurrent->ptrLeft;
    }

    return ptrCurrent;
}

/**
 * Procura o endereço na memória do pai de um nó na árvore.
 *
 * Usa a forma recursiva da função para achar o nó pai do nó
 * buscado a partir da raiz. 
 *
 * @param root Ponterio do nó raiz da árvore.
 * @param sNode Endereço do filho do valor a ser buscado na árvore.
 * @return endereço do nó pai do nó buscado ou nullptr se o endereço
 * não existir na árovre ou caso seja a própria raiz.
*/
struct Node* searchParentNode(struct Node* root, struct Node* sNode)
{
    if (root == nullptr || root == sNode)   // O nó pai não foi encontrado
    {
        return nullptr;
    }

    if (sNode == root -> ptrLeft || sNode == root -> ptrRight)  // O nó pai foi encontrado
    {
        return root;
    }
    else if (sNode -> iPayload < root -> iPayload)  // O nó pode estar a esquerda
    {
        return searchParentNode(root -> ptrLeft, sNode);
    }
    else    // O nó pode estar a direita
    {
        return searchParentNode(root -> ptrRight, sNode);
    }
}

/**
 * Troca a posição de dois nós na árvore
 * 
 * Não deve ser usado fora do delete, pois existe o risco de
 * deordenar a árvore.
 * 
 * @param root Ponteiro do ponteiro do nó raiz da árvore
 * @param sNode1 Ponteiro de um dos nós a ser trocado
 * @param sNode2 Ponteiro de um dos nós a ser trocado
*/
void swapNode(struct Node** root, struct Node* sNode1, struct Node* sNode2)
{
    if(sNode1 == sNode2 || sNode1 == nullptr || sNode2 == nullptr)
    {
        return;
    }

    struct Node* parentNode1 = searchParentNode((*root), sNode1);
    struct Node* parentNode2 = searchParentNode((*root), sNode2);

    // Mudar os indicadores dos nós pais
    if(sNode1 == (*root))       // Caso o nó 1 seja a raiz
    {
        if(parentNode2 -> iPayload >= sNode2 -> iPayload) parentNode2 -> ptrLeft = sNode1;
        else parentNode2 -> ptrRight = sNode1;

        (*root) = sNode2;
    }
    else if (sNode2 == (*root))     // Caso o nó 2 seja a raiz
    {
        if(parentNode1 -> iPayload >= sNode1 -> iPayload) parentNode1 -> ptrLeft = sNode2;
        else parentNode1 -> ptrRight = sNode2;

        (*root) = sNode1;
    } 
    else
    {        
        if(parentNode1 -> iPayload >= sNode1 -> iPayload) parentNode1 -> ptrLeft = sNode2;
        else parentNode1 -> ptrRight = sNode2;

        if(parentNode2 -> iPayload >= sNode2 -> iPayload) parentNode2 -> ptrLeft = sNode1;
        else parentNode2 -> ptrRight = sNode1;
    }

    struct Node* ptrTempLeft = sNode1 -> ptrLeft;
    struct Node* ptrTempRight = sNode1 -> ptrRight;

    sNode1 -> ptrLeft = sNode2 -> ptrLeft;
    sNode1 -> ptrRight = sNode2 -> ptrRight;

    sNode2 -> ptrLeft = ptrTempLeft;
    sNode2 -> ptrRight = ptrTempRight;
    
}

/**
 * Deleta nó do valor dado na árvore e a ajusta da melhor forma.
 *
 * Usa a forma recursiva da função para achar um nó com o valor
 * buscado a partir da raiz. Se o valor buscado for menor que o
 * valor do nó, buscamos a esquerda da árvore; caso seja maior
 * buscamos a direita. A recursão acaba quando o valor é encontrado
 * ou quando chegamos ao fim da árvore.
 *
 * @param root Ponterio do nó raiz da árvore no inicio da recursão.
 * @param sNode Ponterio do nó raiz da árvore no inicio da recursão,
 * ponterio a ser avaliado para ser deletado durante a recursão.
 * @param iData Valor a ser deletado na árvore.
 * @return raiz da árvode uma vez que durante a recursão a árvore
 * é reconstruida.
*/
struct Node* deleteNode(struct Node** root, struct Node* sNode, int iData)
{
    if (sNode == nullptr)   // O nó não foi encontrado
    { 
        return sNode;
    }

    if (iData < sNode -> iPayload)  // O nó pode estar a esquerda
    {   
        sNode -> ptrLeft = deleteNode(root, sNode -> ptrLeft, iData);
    }
    else if (iData > sNode -> iPayload) // O nó pode estar a direita
    {
        sNode -> ptrRight = deleteNode(root, sNode -> ptrRight, iData);
    }
    else    // O nó foi encontrado
    {
        struct Node* ptrTemp = nullptr;

        if (sNode -> ptrRight == nullptr)
        {
            ptrTemp = sNode -> ptrLeft;

            if(sNode == (*root))    // Se o nó a ser removido for a raiz
            {
                (*root) = ptrTemp;
            }

            free(sNode);    // Libera o espço na memória

            return ptrTemp;
        }
        else if(sNode -> ptrLeft == nullptr)
        {
            ptrTemp = sNode -> ptrRight;

            if(sNode == (*root))    // Se o nó a ser removido for a raiz
            {
                (*root) = ptrTemp;
            }

            free(sNode);    // Libera o espço na memória

            return ptrTemp;
        }

        ptrTemp = lesserLeaf(sNode -> ptrRight);    // Acha a menor folha a direita do nó que será removido

        swapNode(root, sNode, ptrTemp); // Troca a menor folha a direita com o valor a ser deletado

        ptrTemp -> ptrRight = deleteNode(root, ptrTemp -> ptrRight, sNode -> iPayload); // Exclui o valor a ser deletado, agora na posição da menor folha
    }
}

/**
 * Deleta uma árvore binaria
 * 
 * Usa a função deleteNode para deletar todos os nós
 * 
 * @param root Ponteiro do ponteiro do nó raiz da árvore
*/
void deleteTree(struct Node** root)
{
    struct Node* ptrDel = (*root);
    while(ptrDel != nullptr)    // loop enquanto existir algum nó
    {
        ptrDel = deleteNode(root, ptrDel, ptrDel -> iPayload);
    }
}

/**
 * Procura o endereço na memória do valor dado na árvore.
 *
 * Usa a forma recursiva da função para achar um nó com o valor
 * buscado a partir da raiz. Se o valor buscado for menor que o
 * valor do nó, buscamos a esquerda da árvore; caso seja maior
 * buscamos a direita. A recursão acaba quando o valor é encontrado
 * ou quando chegamos ao fim da árvore.
 *
 * @param sNode Ponterio do nó raiz da árvore.
 * @param iData Valor a ser buscado na árvore.
 * @return endereço do primeiro valor de iData encontrado ou nullptr
 * se o dado não existir na árvore.
*/
struct Node* searchNode(struct Node* sNode, int iData)
{
    if (sNode == nullptr)   // O nó não foi encontrado
    {
        return nullptr;
    }

    if (iData == sNode -> iPayload) // O nó foi encontrado
    {
        return sNode;
    }
    else if (iData < sNode -> iPayload) // O nó pode estar a esquerda
    {
        return searchNode(sNode -> ptrLeft, iData);
    }
    else    // O nó pode estar a direita
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
 * @param root Ponterio do nó raiz da árvore no inicio da recursão.
 * @param iHeight Inteiro, altura da raiz, inicializado em 0.
 * @return inteiro representado a profundidade da folha mais profunda.
 */
int treeHeight(struct Node* root, int iHeight)
{
    if (root != nullptr)
    {
        int iHeightLeft = treeHeight(root -> ptrLeft, iHeight + 1);     // Confere a altura do galho a esquerda
        int iHeightRight = treeHeight(root -> ptrRight, iHeight + 1);   // Confere a altura do galho a direita

        return max(iHeightLeft, iHeightRight);  // A altura máxima é a altura da árvore
    }
    else
    {
        return iHeight;
    } 
}

/**
 * Descobre o tamanho da árvore.
 *
 * Calcula o tamanho de uma árvore binaria, contado o número de
 * nós em toda sua ramificação.
 *
 * @param root Ponterio do nó raiz da árvore no inicio da recursão.
 * @param iSize Inteiro, tamanho da raiz, inicializado em 0.
 * @return inteiro representado o tamanho da árvore.
 */
int treeSize(struct Node* root, int iSize)
{
    if (root != nullptr)
    {
        int iSizeLeft = treeSize(root -> ptrLeft, iSize + 1);   // Conta o número de nós a esquerda
        int iSizeRight = treeSize(root -> ptrRight, iSize + 1); // Conta o número de nós a direita

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
        // se o nó tem um filho à esquerda
        if (root -> ptrLeft != nullptr) 
        {
            // nó mais à direita do filho à esquerda
            struct Node* ptrCurrent = root -> ptrLeft;
            
            while (ptrCurrent -> ptrRight) 
            {
                ptrCurrent = ptrCurrent -> ptrRight;
            }

            // anexa o filho à direita do nó à direita do nó mais à direita do filho à esquerda
            ptrCurrent -> ptrRight = root -> ptrRight;

            // faz o nó apontar para o filho à esquerda como filho à direita
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

        // compara cada par de nós adjacentes
        for (int iInnerLoop = 0; iInnerLoop < iLength - iOuterLoop - 1; iInnerLoop++)
        {   

            struct Node* sNode1 = *sNodeTemp;
            struct Node* sNode2 = sNode1 -> ptrRight;
  
            // se o valor do nó atual é maior que o próximo, troca os valores
            if (sNode1 -> iPayload > sNode2 -> iPayload) 
            {
                *sNodeTemp = swapNodeValues(sNode1, sNode2);
                bSwap = true;
            }
  
            sNodeTemp = &(*sNodeTemp) -> ptrRight;
        }
  
        // se não houve trocas, a lista está ordenada
        if (bSwap == false)
        {
            break;
        }
    }
}

void selectSort(struct Node* sNode)
{
    struct Node* sTemp = sNode;
    int iCount = 1;

    cout << "Inicio da ordenação pelo algoritmo Select Sort: " << endl; 

    while (sTemp != nullptr) 
    {
        struct Node* sMin = sTemp;
        struct Node* sNext = sTemp -> ptrRight;
  
        // encontra o nó com o menor valor na lista restante
        while (sNext != nullptr) 
        {
            if (sMin -> iPayload > sNext -> iPayload)
            {
                sMin = sNext;
            }
  
            sNext = sNext -> ptrRight;
        }

        cout << "   Iteração " << iCount << endl;
        cout << "   Valor a ser comparado: " << sMin -> iPayload << endl;
        
        // troca os valores do nó atual e do nó com o menor valor
        int iValue = sTemp -> iPayload;

        sTemp -> iPayload = sMin -> iPayload;
        sMin -> iPayload = iValue;
        sTemp = sTemp -> ptrRight;
        
        printLinkedList(sNode);
        iCount++;
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
    
    // ordenação começa com um grande intervalo e vai diminuindo
    for (int iGap = iLength / 2; iGap > 0; iGap /= 2) 
    {
        for (int iOuterLoop = iGap; iOuterLoop < iLength; iOuterLoop++) 
        {
            // salva o valor do nó atual
            int iTemp = getNodeAtIndex(sNode, iOuterLoop) -> iPayload;
            int iInnerLoop;
            
            // move os elementos da lista que são maiores que o valor salvo para frente no intervalo dado
            for (iInnerLoop = iOuterLoop; iInnerLoop >= iGap and getNodeAtIndex(sNode, iInnerLoop - iGap) -> iPayload > iTemp; iInnerLoop -= iGap) 
            {
                getNodeAtIndex(sNode, iInnerLoop) -> iPayload = getNodeAtIndex(sNode, iInnerLoop - iGap) -> iPayload;
            }

            // valor salvo na posição correta dentro do intervalo
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
       // salva o próximo nó
       sNext = ptrCurrent -> ptrRight;
       // deleta o nó atual
       free(ptrCurrent);
       // vai para o próximo nó
       ptrCurrent = sNext;
   }

   *sNode = nullptr;
}

struct Node* linkedListToTree(struct Node* sNode)
{
    struct Node* sTree = nullptr;

    while (sNode != nullptr)
    {   
        // insere cada elemento da lista na árvore
        sTree = insertNode(sTree, sNode -> iPayload);
        // vai para o próximo elemento da lista
        sNode = sNode -> ptrRight;
    }

    // deleta a lista ligada
    deleteLinkedList(&sNode); 
    
    return sTree;
}

void printLinkedList(struct Node* sNode)
{
    while (sNode != nullptr)
    {
        // imprime o valor do nó
        cout << sNode -> iPayload << " -> ";
        // vai para o próximo nó
        sNode = sNode -> ptrRight;
    }

    // imprime nulo ao fim da lista
    cout << " nullptr " << endl;
}

int countNodes(struct Node* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    return (1 + countNodes(root -> ptrLeft) + countNodes(root -> ptrRight));
}

bool isCompleteTree(struct Node* root, int iIndex, int iNumberNodes) 
{
    // árvore vazia é considerada completa
    if (root == nullptr)
    {
        return true;
    }
 
    if (iIndex >= iNumberNodes)
    {
        return false;
    }
 
    return (isCompleteTree(root->ptrLeft, 2*iIndex + 1, iNumberNodes) and
            isCompleteTree(root->ptrRight, 2*iIndex + 2, iNumberNodes));
}

// função auxiliar para verificar se a árvore é perfeita (ou full)
bool isFullTree(struct Node* root) 
{
    if (root == nullptr)
    {
        return true;
    }
  
    if (root -> ptrLeft == nullptr and root -> ptrRight == nullptr)
    {
        return true;
    }
  
    if ((root -> ptrLeft) and (root -> ptrRight))
    {
        return (isFullTree(root -> ptrLeft) and isFullTree(root -> ptrRight));
    }
  
    return false;
}

struct QueueNode 
{
    struct Node* sNode;
    struct QueueNode* ptrNext;
    int iQueueSize;
};

struct QueueNode* createQueueNode(struct Node* sNode) 
{
    struct QueueNode* sQueueNewNode = (struct QueueNode*) malloc(sizeof(struct QueueNode));
    sQueueNewNode -> sNode = sNode;
    sQueueNewNode -> ptrNext = nullptr;
    sQueueNewNode -> iQueueSize = 0;

    return sQueueNewNode;
}

void enqueue(struct QueueNode** sQueueFront, struct QueueNode** sQueueRear, struct Node* sNode) 
{
    struct QueueNode* sQueueNewNode = createQueueNode(sNode);

    if (*sQueueFront == nullptr) 
    {
        *sQueueFront = *sQueueRear = sQueueNewNode;
    } 
    else 
    {
        (*sQueueRear) -> ptrNext = sQueueNewNode;
        *sQueueRear = sQueueNewNode;
    }

    (*sQueueFront) -> iQueueSize = (*sQueueFront) -> iQueueSize + 1;
    (*sQueueRear) -> iQueueSize = (*sQueueRear) -> iQueueSize + 1;
}

struct Node* dequeue(struct QueueNode** sQueueFront, QueueNode** sQueueRear) 
{
    if (*sQueueFront == nullptr) 
    {
        return nullptr;
    }

    struct QueueNode* sQueueTemp = *sQueueFront;
    struct Node* sNode = sQueueTemp -> sNode;

    *sQueueFront = (*sQueueFront) -> ptrNext;
    if (*sQueueFront == nullptr) 
    {
        *sQueueRear = nullptr;
    }

    free(sQueueTemp);
    return sNode;
}

bool isQueueEmpty(struct QueueNode* sQueueFront) 
{
    return sQueueFront == nullptr;
}

void breadthFirstSearch(struct Node* root) 
{
    if (root == nullptr) 
    {
        return;
    }

    struct QueueNode* sQueueFront = nullptr;
    struct QueueNode* sQueueRear = nullptr;

    enqueue(&sQueueFront, &sQueueRear, root);  

    while (!isQueueEmpty(sQueueFront)) 
    {   
        int iQueueSize = sQueueFront -> iQueueSize;

        for (int iCount = 1; iCount < iQueueSize; iCount++)
        {
            struct Node* sNode = dequeue(&sQueueFront, &sQueueRear);  
            cout << sNode -> iPayload << " ";  

            if (sNode -> ptrLeft != nullptr) 
            {
                enqueue(&sQueueFront, &sQueueRear, sNode -> ptrLeft);  
            }

            if (sNode -> ptrRight != nullptr) 
            {
                enqueue(&sQueueFront, &sQueueRear, sNode -> ptrRight); 
            }
        }
        cout << endl;
    }
}

void displayTree(struct Node* root, int iTab) 
{
    if (root == nullptr) 
    {
        return;
    }

    int iIdentation = 4;

    iTab += iIdentation;

    displayTree(root -> ptrRight, iTab);

    cout << endl;
    for (int iCount = iIdentation; iCount < iTab; iCount++) 
    {
        cout << " ";
    }
    
    cout << root -> iPayload << endl;

    displayTree(root -> ptrLeft, iTab);
}

#endif //TRABALHO_DE_ED_ARVORE_H

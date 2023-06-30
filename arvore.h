#ifndef TRABALHO_DE_ED_ARVORE_H
#define TRABALHO_DE_ED_ARVORE_H

#include <iostream>
#include <string>
#include <queue>
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
void printLevelOrder(struct Node* root);
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

bool isCompleteTree(struct Node* root);
bool checkPerfectTree(Node* sNode, int iNodeCount, int iExpectedNodeCount);
bool isPerfectTree(struct Node* root);

struct Node* insertNode(struct Node* sNode, int iData);
struct Node* deleteNode(struct Node** root, struct Node* sNode, int iData);
struct Node* searchNode(struct Node* sNode, int iData);
struct Node* swapNodeValues(struct Node* sNode1, struct Node* sNode2);
struct Node* getNodeAtIndex(struct Node* sNode, int iIndex); 
struct Node* linkedListToTree(struct Node* sNode);

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
        cout << " " << ptrStartingNode -> iPayload;

        traversePreOrder(ptrStartingNode -> ptrLeft);
        traversePreOrder(ptrStartingNode -> ptrRight);
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


/**
 * Cria uma árvore binária a partir do input do usuário
 * 
 * @param root Ponterio do nó raiz da árvore.
 * @param iSize número  de inputs a serem digitados pelo
 * usuário
*/
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

    while (ptrCurrent && ptrCurrent->ptrLeft != nullptr)
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
    if (root == nullptr || root == sNode)
    {
        return nullptr;
    }

    if (sNode == root -> ptrLeft || sNode == root -> ptrRight)
    {
        return root;
    }
    else if (sNode -> iPayload < root -> iPayload)
    {
        return searchParentNode(root -> ptrLeft, sNode);
    }
    else
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
    if (sNode == nullptr)
    { 
        return sNode;
    }

    if (iData < sNode -> iPayload) 
    {   
        sNode -> ptrLeft = deleteNode(root, sNode -> ptrLeft, iData);
    }
    else if (iData > sNode -> iPayload) 
    {
        sNode -> ptrRight = deleteNode(root, sNode -> ptrRight, iData);
    }
    else
    {
        struct Node* ptrTemp = nullptr;

        if (sNode -> ptrRight == nullptr)
        {
            ptrTemp = sNode -> ptrLeft;

            if(sNode == (*root)) 
            {
                (*root) = ptrTemp;
            }

            free(sNode);

            return ptrTemp;
        }
        else if(sNode -> ptrLeft == nullptr)
        {
            ptrTemp = sNode -> ptrRight;

            if(sNode == (*root)) 
            {
                (*root) = ptrTemp;
            }

            free(sNode);

            return ptrTemp;
        }

        ptrTemp = lesserLeaf(sNode -> ptrRight);

        swapNode(root, sNode, ptrTemp);

        ptrTemp -> ptrRight = deleteNode(root, ptrTemp -> ptrRight, sNode -> iPayload);
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
    while(ptrDel != nullptr)
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
 * @param root Ponterio do nó raiz da árvore no inicio da recursão.
 * @param iHeight Inteiro, altura da raiz, inicializado em 0.
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
    int iCount = 1;

    cout << "Inicio da ordenação pelo algoritmo Select Sort: " << endl; 

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

        cout << "   Iteração " << iCount << endl;
        cout << "   Valor a ser comparado: " << sMin -> iPayload << endl;
        
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

bool isCompleteTree(struct Node* root) 
{
    // árvore vazia é considerada completa
    if (root == nullptr)
    {
        return true;
    }

    queue<Node*> q;
    q.push(root);

    bool bFlag = false; // flag que infica se um nó não completo foi encontrado

    // percorrendo a árvore usando busca em largura
    while (!q.empty()) 
    {
        struct Node* sTemp = q.front();
        q.pop();

        // um nó não completo já foi encontrado,mas um nó filho não é nullptr, a árvore não é completa
        if (bFlag and (sTemp -> ptrLeft != nullptr or sTemp -> ptrRight != nullptr))
        {
            return false;
        }

        // o nó esquerdo não é nullptr
        if (sTemp -> ptrLeft != nullptr) 
        {
            q.push(sTemp -> ptrLeft);

            // um nó não completo foi encontrado anteriormente, mas o nó atual não tem filho direito, a árvore não é completa
            if (bFlag and sTemp -> ptrRight == nullptr)
            {
                return false;
            }
        }
        // o nó direito não é nullptr
        else if (sTemp -> ptrRight != nullptr) 
        {
            // A árvore não é completa
            return false;
        }
        // não entre em nenhum dos casos de não completa, então completa
        else
        {
            bFlag = true;
        }
    }
    
    return true;
}

// função auxiliar para verificar se a árvore é perfeita
bool checkPerfectTree(Node* sNode, int iNodeCount, int iExpectedNodeCount) 
{
    // nó é nullptr
    if (sNode == nullptr)
    {
        return true;
    }
    
    // o número de nós já excede o número máximo esperado, a árvore não é perfeita
    if (iNodeCount >= iExpectedNodeCount)
    {
        return false;
    }
    
    // recursivamente a subárvore esquerda e a subárvore direita
    return checkPerfectTree(sNode -> ptrLeft, 2 * iNodeCount + 1, iExpectedNodeCount) and 
           checkPerfectTree(sNode -> ptrRight, 2 * iNodeCount + 2, iExpectedNodeCount);
}


bool isPerfectTree(struct Node* root) 
{
    // árvore vazia é considerada perfeita
    if (root == nullptr)
    {
        return true;
    }
    
    int iHeight = treeHeight(root);
    
    // o número máximo de nós em uma árvore perfeita de altura 'height'
    int iExpectedNodeCount = pow(2, iHeight) - 1;
    
    return checkPerfectTree(root, 0, iExpectedNodeCount);
}

// realiza a travessia em largura (BFS)
void printLevelOrder(struct Node* root) 
{
    // a árvore está vazia
    if (root == nullptr)
    { 
        return;
    }

    // fila vazia para o BFS
    queue<Node*> q;

    q.push(root);

    while (true) 
    {
        // nós no nível atual
        int iNodeCount = q.size();
        // não há nós no nível, encerra
        if (iNodeCount == 0)
        { 
            break;
        }

        while (iNodeCount > 0) 
        {
            // remove o nó na frente da fila
            struct Node* sNode = q.front();
            q.pop();

            // imprime o valor do nó
            cout << sNode -> iPayload << " ";

            if (sNode -> ptrLeft != nullptr) q.push(sNode -> ptrLeft);
            if (sNode -> ptrRight != nullptr) q.push(sNode -> ptrRight);

            iNodeCount--;
        }

        // novo nível (BFS)
        cout << endl;
    }
}

#endif //TRABALHO_DE_ED_ARVORE_H

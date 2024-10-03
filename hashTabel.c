#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int info;
    struct Node* prox;
};


int getPosition(int value, int arraySize);
void show(struct Node** list, int sizeList);
int insertValue(struct Node** list, int sizeList, int value);
int searchValue(struct Node**, int sizeList, int value);
struct Node* createNode(int value);
int deleteValue(struct Node** list, int sizeList, int value);
void deleteList(struct Node** list, int sizeList);


int main() {
    
    struct Node* list[9];

    int sizeList = (int) sizeof(list) / sizeof(list[0]);
    for(int i = 0; i < sizeList; i++) 
    {
        list[i] = NULL;
    }

    int controller = 0;
    int value = 0;
  
    do
    {
       printf("Escolha uma das opções:\n[1] - Inserir um valor\n[2] - Exibir os valores\n[3] - Procurar um valor\n[4] - remover um valor\n[5] - Encerrar o programa\nDigite a sua escolha: ");

       if(scanf("%d", &controller) != 1)
       {
          printf("ERRO: o valor inserido não é valido");
          while(getchar() != '\n');
       }

       switch (controller)
       { 

       case 1:
        printf("digite o valor que deseja inserir: ");
        // printf("pegar valor");
        if(scanf("%d", &value) != 1)
        {
            printf("ERRO: O valor inserido não é um numero.\n");
            while(getchar() != '\n');
        }
        else
        {
        // printf("função inserir");
        insertValue(list, sizeList, value);
        break;

       case 2:
       show(list, sizeList);
       break;

       case 3:
         printf("digite o valor que deseja buscar: ");

         if(scanf("%d", &value) != 1)
         {
            printf("ERRO: O valor inserido não é um numero.\n");
            while(getchar() != '\n');
         }
         else{ 

         int searchedValue = (int) searchValue(list, sizeList, value);

          if(searchedValue == -1)
          {
            printf("ERRO: Valor não encontrado.\n");
          }else
          {
            printf("Valor encontrado: %d\n", searchedValue);
          }
         }
        } 
        break;

        case 4:
        printf("digite o valor a ser removido: ");
        scanf("%d", &value);

        if(deleteValue(list, sizeList, value) == -1)
        {
          printf("ERRO: Valor não foi encontrado na lista.\n");
        }

        break;

        case 5:
         printf("encerrando o programa...\n");
         break;
       
       default:
         printf("Opção invalida! Tente novamente.\n");
        break;
       }

        
    } while (controller != 5);

    deleteList(list, sizeList);


    show(list, sizeList);

    return 0;
}


struct Node* createNode(int value)
{
   struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));

   newNode->info = value;
   newNode->prox = NULL;

   return newNode;
}

void deleteList(struct Node** list, int sizeList){

  struct Node* moveList = NULL; 
    struct Node* temp = NULL;

    for(int i = 0; i < sizeList; i++)
    {
      moveList = list[i];

       while (moveList != NULL) {
        temp = moveList;         
        moveList = moveList->prox; 
        free(temp);              
    }
    list[i] = NULL;
  }
   
}

int deleteValue(struct Node** list, int sizeList, int value)
{
    int position = getPosition(value, sizeList);

    if(position >= sizeList){
        return -1;
    }

    struct Node* current = list[position];
    struct Node* previous = NULL;

    while(current != NULL){
      if(current->info == value){

        if(previous == NULL){
            list[position] = current->prox;
        }
        else{
            previous->prox = current->prox;
        }
          free(current);
          return 0;

      }
      previous = current;
      current = current->prox;
        
    }

    return -1;

}

int searchValue(struct Node** list, int sizeList, int value)
{
    int position = getPosition(value, sizeList);

    if(position >= sizeList){
            return -1;
        }

    struct Node* current = list[position];


        while(current != NULL)
        {
            if(current->info == value)
            { 
             return current->info;
            }
            current = current->prox;
        }  

    return -1;
}

int insertValue(struct Node** list, int sizeList, int value) 
{
   struct Node* Node = createNode(value);

   int position = getPosition(value, sizeList);

        if(position >= sizeList){
            return -1;
        }

        if(list[position] == NULL){
            list[position] = Node;
            return 0;
        }

        struct Node* moveList = list[position];

         while(moveList->prox != NULL)
         {
            moveList = moveList->prox;
         }

         moveList->prox = Node;
         return 0;
}

void show(struct Node** list, int sizeList)
{
    for(int i = 0; i < sizeList; i++) 
    {
       struct Node* current = list[i];

       printf("Lista %d: ", i);

      while(current != NULL)
      {
        printf("[%d] -> ", current -> info);
        current = current->prox;
      }
        printf("NULL\n");
    }
    
}

int getPosition(int value, int arraySize) 
{
   
   if(value < 0)
   {
     value *= -1;
   }

    return value % arraySize;
}


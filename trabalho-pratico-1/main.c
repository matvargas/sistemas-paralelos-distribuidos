#include "tree.h"
#include "pthread.h"
#include <stdio.h>

#define MAXTHREADS 100

// Struct para armzenar os dados da thread
typedef struct ThreadInfo {
    pthread_t thread;
    int threadID;
} ThreadInfo;

ThreadInfo threads[MAXTHREADS]; //Array de threads
pthread_mutex_t TreeLock; //Mutex para bloquear a sessão crítica
int threadCount = 0;

enum operationTypes {INSERT = 1, REMOVE, SEARCH} operationTypes;

/**
 * Função resposavel por triagem do tipo de operação que será feita na árvore.
 * Também utilizada para padronizar com a inicialização de threads
**/
void *threeOperation (void* operationType, void* value){
    switch (operationTypes){
    case INSERT:
        //TODO: Alterar a função para receber o valor de ID da thread
        // Insere(x, &Dicionario);
        break;
    case REMOVE:
        //TODO: Alterar a função para receber o valor de ID da thread
        // Retira(x, &Dicionario);
        break;
    case SEARCH:
        //TODO: Alterar a função para receber o valor de ID da thread
        // Pesquisa(x, &Dicionario);
        break;
    default:
        pritnf("Operação não reconhecida: %d \n", (int)value);
        exit(EXIT_FAILURE);
        break;
    }
}

int main(int argc, char *argv[])
{
  struct timeval t; TipoNo *Dicionario;
  TipoRegistro x; TipoChave vetor[MAX];
  int i, j, k, n;

  Inicializa(&Dicionario);
  /* Gera uma permutação aleatoria de chaves entre 1 e MAX */
  for (i = 0; i < MAX; i++) vetor[i] = i+1;
  gettimeofday(&t,NULL);
  srand((unsigned int)t.tv_usec);
  Permut(vetor,MAX-1);
  
  /* Insere cada chave na arvore e testa sua integridade apos cada insercao */
  for (i = 0; i < MAX; i++) 
    { x.Chave = vetor[i];
      Insere(x, &Dicionario);
      printf("Inseriu chave: %lu\n", x.Chave);
     Testa(Dicionario);
    }

  /* Retira uma chave aleatoriamente e realiza varias pesquisas */
  for (i = 0; i <= MAX; i++) 
    { k = (int) (10.0*rand()/(RAND_MAX+1.0));
      n = vetor[k];
      x.Chave = n;
      Retira(x, &Dicionario);
      Testa(Dicionario);
      printf("Retirou chave: %ld\n", x.Chave);
      for (j = 0; j < MAX; j++) 
        { x.Chave = vetor[(int) (10.0*rand()/(RAND_MAX+1.0))];
          if (x.Chave != n) 
          { printf("Pesquisando chave: %ld\n", x.Chave);
            Pesquisa(&x, &Dicionario);
          }
        }
      x.Chave = n;
      Insere(x, &Dicionario);
      printf("Inseriu chave: %ld\n", x.Chave);
      Testa(Dicionario);
    }

  /* Retira a raiz da arvore ate que ela fique vazia */
  for (i = 0; i < MAX; i++) 
    { x.Chave = Dicionario->Reg.Chave;
      Retira(x, &Dicionario);
      Testa(Dicionario);
      printf("Retirou chave: %ld\n", x.Chave);
    }
  return 0;
} 
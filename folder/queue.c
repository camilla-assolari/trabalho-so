//GRR20190573 - Camilla Luz Assolari

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

//------------------------------------------------------------------------------
// Conta o numero de elementos na fila
// Retorno: numero de elementos na fila

int queue_size (queue_t *queue){

		int cont = 1;
		queue_t *first = queue;
		if(queue == NULL)
			return 0;
		else{
			while(first->next != queue){
				first = first->next;
				cont++;
			}
		}
		return cont;
}
//------------------------------------------------------------------------------
// Percorre a fila e imprime na tela seu conteúdo. A impressão de cada
// elemento é feita por uma função externa, definida pelo programa que
// usa a biblioteca. Essa função deve ter o seguinte protótipo:
//
// void print_elem (void *ptr) ; // ptr aponta para o elemento a imprimir

void queue_print (char *name, queue_t *queue, void print_elem (void*)){

	printf("%s[", name);
	if (queue){
		queue_t *first = queue;
		do{
			if (first != queue){
				printf(" ");
			}
			print_elem(first);
			first = first->next;
		}while(first != queue);
	}
	printf("]\n");
}

//------------------------------------------------------------------------------
// Insere um elemento no final da fila.
// Condicoes a verificar, gerando msgs de erro:
// - a fila deve existir
// - o elemento deve existir
// - o elemento nao deve estar em outra fila
// Retorno: 0 se sucesso, <0 se ocorreu algum erro

int queue_append (queue_t **queue, queue_t *elem){
	
	if(queue == NULL){
		fprintf(stderr, "%s", "queue nao existe\n");
		return -1;
	}
	if(elem == NULL){
		fprintf(stderr, "%s", "elem nao existe\n");
		return -1;
	}
	if(elem-> next || elem->prev){
		fprintf(stderr, "%s", "elem esta em outra fila\n");
		return -1;
	}
	if(*queue == NULL){
		*queue = elem;
		(*queue)->next = (*queue);	
		(*queue)->prev = (*queue);
		return 0;
	}
	else{
		elem->next = *queue;
		elem->prev = (*queue)->prev;
		(*queue)->prev->next = elem;
		(*queue)->prev = elem;
		return 0;
	}
		
}

//------------------------------------------------------------------------------
// Remove o elemento indicado da fila, sem o destruir.
// Condicoes a verificar, gerando msgs de erro:
// - a fila deve existir
// - a fila nao deve estar vazia
// - o elemento deve existir
// - o elemento deve pertencer a fila indicada
// Retorno: 0 se sucesso, <0 se ocorreu algum erro

int queue_remove (queue_t **queue, queue_t *elem){
	
	if(queue == NULL){
		fprintf(stderr, "%s", "queue não existe\n");
		return -1;
	}
	if(*queue == NULL){
		fprintf(stderr, "%s", "queue vazia\n");
		return -1;
	}
	if(elem == NULL){
		fprintf(stderr, "%s", "elem nao existe\n");
		return -1;
	}
	queue_t *first = *queue;
	int cont = 0;
	do{
      if (first == elem){
        cont = 1;
        break;
      }
      first = first->next;
    }while (first != *queue);

	if(cont == 0){
		fprintf(stderr, "%s", "elem nao esta na fila\n");
		return -1;
	}
	else if (elem->next == elem && elem->prev == elem){
        elem->next = NULL;
        elem->prev = NULL;
        (*queue) = NULL;
        return 0;
    }
    else{
			if(elem == (*queue)){
				*queue = (*queue)->next;	
			} 
			elem->prev->next = elem -> next;
			elem->next->prev = elem -> prev;
			elem->next = NULL;
			elem->prev = NULL;
			return 0;
		}
}



#include <stdlib.h>
#include <stdio.h>

struct node {
    int valor;
    struct node *prox;
};
typedef struct node tipoLista;

void imprimir(tipoLista *lista) {
    if(lista != NULL) {
        printf("%d ", lista->valor);
        imprimir(lista->prox);
    }
}

tipoLista *inicializar(void) {
    return NULL;
}

tipoLista *buscar(int valor, tipoLista *lista) {
    tipoLista *p;
    p = lista;
    while((p != NULL) && (p->valor != valor))
        p = p->prox;
    
    return p;
}

tipoLista *inserir(int valor, tipoLista *lista) {
    tipoLista *novo, *aux;
    novo = (tipoLista *) malloc(sizeof(tipoLista));
    novo->valor = valor;
    novo->prox = NULL;

    if(lista == NULL) {
        lista = novo;
    }
    else {
        aux = lista;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
    return lista;
}

tipoLista *remover(int valor, tipoLista *lista) {
    tipoLista *ant = NULL;
    tipoLista *p;
    p = lista;

    while((p != NULL) && (p->valor != valor)) {
        ant = p;
        p = p->prox;
    }

    if(p == NULL) return lista; // nao achou o elemento

    if(ant == NULL) {
        lista = p->prox;
    }
    else {
        ant->prox = p->prox;
    }
    free(p);
    return lista;
}

int hash(int n, int t) {
    return (n % t);
}

int main() {

    int tamH, t, n, h, i, rem;
    scanf("%d", &tamH); // tamanho tabela hash
    scanf("%d", &t); // quantidade de entradas

    
    tipoLista *lista[tamH];
    for(i=0; i<tamH; i++) {
        lista[i] = inicializar();
    }


    for(i=0; i<t; i++) {
        scanf("%d", &n);
        h = hash(n, tamH);
        lista[h] = inserir(n, lista[h]);
    }

    scanf("%d", &rem);
    h = hash(rem, tamH);

    //insere ou remove
    if(buscar(rem, lista[h]) == NULL)
        lista[h] = inserir(rem, lista[h]);
    else
        lista[h] = remover(rem, lista[h]);
    
    // imprime saida
    for(i=0; i<tamH; i++) {
        printf("[%d] ", i);
        imprimir(lista[i]);
        printf("\n");
    }

}
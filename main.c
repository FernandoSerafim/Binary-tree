#include <stdio.h>
#include <stdlib.h>

//ÁRVORE BINÁRIA DE PESQUISA
// TIPO ESPECIAL DE LISTA ENCADEADA

typedef struct no{
    int dado;
    struct no* esquerda;
    struct no* direita;
} NO;

//criar nó; inserir novo nó; remover um nó; exibir árvore; opcional: Qtd elementos
//SOMENTE A FUNÇÃO DE EXIBIR A ÁRVORE SERÁ SEM RETORNO (VOID)


NO* aloca_no(){
    NO* novo_no =  malloc(sizeof(NO));
    novo_no->direita = NULL;
    novo_no->esquerda = NULL;
    return novo_no;
}

NO* insere_elemento(NO* raiz, NO* novo){
//OKAY
    if(raiz == NULL) return novo;

    if(novo->dado < raiz->dado){
        raiz->esquerda = insere_elemento(raiz->esquerda,novo);
    }else{
        raiz->direita = insere_elemento(raiz->direita,novo);
    }

    return raiz;
}

void exibe_arvore(NO* raiz){

    if(raiz != NULL){
        printf("%d  ", raiz->dado);
        exibe_arvore(raiz->esquerda);
        exibe_arvore(raiz->direita);
    }

}

NO* exclui_elemento(NO* raiz){
//
}

void exclui_arvore(NO* raiz){
/*
    if(raiz->direita == NULL && raiz->esquerda == NULL){
            printf("OI\n\n");
        free(raiz);
        raiz =  NULL;
    }else{
        exclui_arvore(raiz->esquerda);
        exclui_arvore(raiz->direita);
    }
*/

    if(raiz == NULL){
        return;
    }

    exclui_arvore(raiz->esquerda);
    exclui_arvore(raiz->direita);

    free(raiz);
    raiz = NULL;
    printf("EXCLUIDO\n\n\n");
}

int main()
{
    int contador = 0; int exclude;
    NO* raiz = NULL;

    while(contador < 7){

        NO* novo = aloca_no();

        printf("Digite o valor que deseja armazenar\n");
        scanf("%d", &novo->dado);
        raiz = insere_elemento(raiz, novo);
        contador++;
    }
    exibe_arvore(raiz);
    //printf("Digite o valor que deseja deletar\n\n");
    //scanf("%d", &exclude);
    exclui_arvore(raiz);
    return 0;
}

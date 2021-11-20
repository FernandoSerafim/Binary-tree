#include <stdio.h>
#include <stdlib.h>

//�RVORE BIN�RIA DE PESQUISA
// TIPO ESPECIAL DE LISTA ENCADEADA

typedef struct no{
    int dado;
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
} NO;

//criar n�; inserir novo n�; remover um n�; exibir �rvore; opcional: Qtd elementos
//SOMENTE A FUN��O DE EXIBIR A �RVORE SER� SEM RETORNO (VOID)


NO* aloca_no(){
    NO* novo_no =  malloc(sizeof(NO));
    novo_no->direita = NULL;
    novo_no->esquerda = NULL;
    novo_no->pai = NULL;
    return novo_no;
}

NO* insere_elemento(NO* raiz, NO* novo){
//OKAY

//PRECISO FAZER CADA ELEMENTO SABER QUEM � SEU PAI
//O PAI DA RA�Z PRINCIPAL � NULL

    if(raiz == NULL) return novo; //FA�O A RA�Z APONTAR O NOVO N�

    if(novo->dado < raiz->dado){
        novo->pai = raiz;
        raiz->esquerda = insere_elemento(raiz->esquerda,novo);
    }else{
        novo->pai = raiz;
        raiz->direita = insere_elemento(raiz->direita,novo);
    }

    return raiz;
}

void exibe_arvore(NO* raiz){

    if(raiz != NULL){
        printf("%d\n", raiz->dado);
        //if(raiz->pai == NULL) printf("PAI DE TODOS OS NOS\n");
        //else printf("%d\n", raiz->pai->dado);
        exibe_arvore(raiz->esquerda);
        exibe_arvore(raiz->direita);
    }

}

NO* encontra_filho(NO* raiz){

    NO* filho;

    if(raiz->esquerda != NULL) filho = raiz->esquerda;
    else filho = raiz->direita;

    return filho;
}


NO* exclui_elemento(NO* raiz, int elemento){
//0 filhos OK
//1 filho OK

    NO* filho, *pai;
    int DirEsq;

    if(raiz == NULL) return NULL;

    if(raiz->dado == elemento){

        //PARA DELETAR N�S QUE POSSUEM 2 FILHOS



        //PARA DELETAR N�S FOLHAS
        if(raiz->direita == NULL && raiz->esquerda == NULL){
            free(raiz);
            raiz =  NULL; //antes era o 2
            return raiz;
        }

        //PARA DELETAR N�S COM 1 FILHOS
        if(raiz->direita != NULL || raiz->esquerda != NULL){
            filho = encontra_filho(raiz); //QUEM � O FILHO DA RA�Z
            free(raiz);
            raiz = NULL;
            return filho;
            //POSSO FAZER ISSO PORQUE ESTOU RETORNANDO FILHO PARA A ESQUERDA
            //DA RA�Z PRINCIPAL (PAI DA RA�Z QUE EU DELETEI O N�)
        }

    }else{
        raiz->esquerda = exclui_elemento(raiz->esquerda, elemento);
        raiz->direita = exclui_elemento(raiz->direita, elemento);
    }

    return raiz;
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

    free(raiz); //S� CHEGA NESSE PONTO QUANDO OS DOIS LADOS J� FOREM NULL
    raiz = NULL;
}

int main()
{
    int contador = 0; int exclude;
    NO* raiz = NULL;

    printf("Digite os valores que deseja armazenar\n");

    while(contador < 6){
        NO* novo = aloca_no();
        scanf("%d", &novo->dado);
        raiz = insere_elemento(raiz, novo);
        contador++;
    }

    exibe_arvore(raiz);
    printf("\n");
    printf("Digite o valor que deseja deletar\n\n");
    scanf("%d", &exclude);

    raiz = exclui_elemento(raiz, exclude);
    exibe_arvore(raiz);

    exclui_arvore(raiz);
    raiz = NULL;
    return 0;
}

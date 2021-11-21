#include <stdio.h>
#include <stdlib.h>

//ÁRVORE BINÁRIA DE PESQUISA
// TIPO ESPECIAL DE LISTA ENCADEADA

typedef struct no{
    int dado;
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
} NO;

NO* aloca_no(){
    NO* novo_no =  malloc(sizeof(NO));
    novo_no->direita = NULL;
    novo_no->esquerda = NULL;
    novo_no->pai = NULL;
    return novo_no;
}

NO* insere_elemento(NO* raiz, NO* novo){
//OKAY

//PRECISO FAZER CADA ELEMENTO SABER QUEM É SEU PAI
//O PAI DA RAÍZ PRINCIPAL É NULL

    if(raiz == NULL) return novo; //FAÇO A RAÍZ APONTAR O NOVO NÓ

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
//2 filhos OK
//VAMOS ADOTAR O FILHO MAIS À DIREITA DA SUBÁRVORE ESQUERDA

    NO* filho, *troca, *pai;
    int DirEsq;

    if(raiz == NULL) return NULL;

    if(raiz->dado == elemento){
        //PARA DELETAR NÓS QUE POSSUEM 2 FILHOS
        if(raiz->esquerda != NULL && raiz->direita != NULL){
            troca = raiz->esquerda;
            if(troca != NULL) troca = troca->direita;//nó + à dir. da sub. esquerda
            troca->esquerda = raiz->esquerda;//SUBSTITUIÇÃO DO NÓ
            troca->direita = raiz->direita;
            pai = troca->pai;
            pai->direita = NULL;//SUBSTITUINDO A POSIÇÃO DO TROCA POR NULL
	        troca->pai = raiz->pai;
            free(raiz); //LEMBRANDO QUE TROCA ERA MEU ÚLTIMO NÓ À DIREITA
            raiz = NULL; //PORTANTO, SEU PAI PRECISA APONTAR PARA NULL
            return troca; //NA SUA POSIÇÃO
        }

        //PARA DELETAR NÓS FOLHAS
        if(raiz->direita == NULL && raiz->esquerda == NULL){
            free(raiz);
            raiz =  NULL; //antes era o 2
            return raiz;
        }

        //PARA DELETAR NÓS COM 1 FILHOS
        if(raiz->direita == NULL || raiz->esquerda == NULL){
            filho = encontra_filho(raiz); //QUEM É O FILHO DA RAÍZ
            free(raiz);
            raiz = NULL;
            return filho;
            //POSSO FAZER ISSO PORQUE ESTOU RETORNANDO FILHO PARA A ESQUERDA
            //DA RAÍZ PRINCIPAL (PAI DA RAÍZ QUE EU DELETEI O NÓ)
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

    free(raiz); //SÓ CHEGA NESSE PONTO QUANDO OS DOIS LADOS JÁ FOREM NULL
    raiz = NULL;
}

int main()
{
    int contador = 0; int exclude;
    NO* raiz = NULL;

    printf("Digite os valores que deseja armazenar\n");

    while(contador < 9){ //APENAS PARA FINS DE TESTE
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

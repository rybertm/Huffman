#include <stdio.h>
#include <stdlib.h>
#include "Lista_Arv.h"

List IniciaList(List head)
{
    head = (List) malloc(sizeof(struct list));
    head->prox = NULL;
    head->esq = NULL;
    head->dir = NULL;
    return head;
}

List InsereOrdenado(List head, int info, char letra)
{
    List novaList = (List) malloc(sizeof(struct list));
    novaList->info = info;
    novaList->letra = letra;

    List p = head;
    List q = head->prox;

    while(q != NULL)
    {
        if(info > q->info)
        {
            if(q->prox != NULL && info < q->prox->info)
            {
                novaList->prox = q->prox;
                q->prox = novaList;
                IniciaNoh(novaList);
                return novaList;
            }
            else
            {
                p = q;
                q = q->prox;
            }
        }
        else if(info == q->info)
        {
            if(novaList->letra > q->letra)
            {
                novaList->prox = q->prox;
                q->prox = novaList;
                IniciaNoh(novaList);
                return novaList;
            }
            else
                break;
        }
        else
            break;
    }
    novaList->prox = p->prox;
    p->prox = novaList;

    IniciaNoh(novaList);

    return novaList;
}

List RemoveList(List head, List rmv)
{
    List p, q;
    p = head;
    q = head->prox;
    while(q != NULL && q != rmv)
    {
        p = q;
        q = q->prox;
    }
    if(q != NULL)
        p->prox = q->prox;

    return head;
}

List BuscaProxList(List head)
{
    List q = head->prox;
    return q;
}

List IniciaNoh(List raiz)
{
    raiz->dir = NULL;
    raiz->esq = NULL;
    return raiz;
}

List criaNoh(int info,char letra)
{
    List raiz = (List) malloc(sizeof(struct list));
    raiz->info = info;
    raiz->letra = letra;
    raiz->dir = NULL;
    raiz->esq = NULL;
    return raiz;
}

List insereNoh(List raiz, int info,char letra)
{
    if(raiz == NULL)
        return criaNoh(info,letra);

    //Insere a esquerda caso a info seja menor q a info da raiz
    if(info < raiz->info)
    {
        if(raiz->esq == NULL)
            raiz->esq = insereNoh(raiz->esq,info,letra);
        else
            raiz->dir = insereNoh(raiz->dir,info,letra);
    }

    //Insere na direita caso contrario
    else if(info > raiz->info)
    {
        if(raiz->dir == NULL)
            raiz->dir = insereNoh(raiz->dir,info,letra);
        else
            raiz->esq = insereNoh(raiz->esq,info,letra);
    }

    //Retorna a arvore com o noh inserido
    return raiz;
}

List procura_Info(List raiz, int info)
{
    if(raiz == NULL || info == raiz->info)
        return raiz;
    if(info > raiz->info)
        return procura_Info(raiz->dir,info);

    return procura_Info(raiz->esq,info);
}

void imprime_em_Ordem(List raiz)
{
    if(raiz != NULL)
    {
        imprime_em_Ordem(raiz->esq);
        printf("\n%d\n",raiz->info);
        imprime_em_Ordem(raiz->dir);
    }
}

List deleta_Noh(List raiz, int info)
{
    if(raiz == NULL)
        return raiz;

    //Recursa(?) ate achar o noh com a info

    if(info < raiz->info)
        raiz->esq = deleta_Noh(raiz->esq,info);

    else if(info > raiz->info)
        raiz->dir = deleta_Noh(raiz->dir,info);

    else
    {
        //Caso o noh tenha apenas um subnoh ou nenhum subnoh
        if(raiz->esq == NULL)
        {
            List temp = raiz->dir;
            free(raiz);
            return temp;
        }
        else if(raiz->dir == NULL)
        {
            List temp = raiz->esq;
            free(raiz);
            return temp;
        }

        //Caso o noh tenha dois subnohs pega-se seu sucessor em ordem, copia-se o conteudo do sucessor para o noh atual
        // e exclui-se o sucessor
        List temp = sucessor_do_Noh_em_Ordem(raiz->dir);

        raiz->info = temp->info;

        raiz->dir = deleta_Noh(raiz->dir, temp->info);
    }
    return raiz;
}

List sucessor_do_Noh_em_Ordem(List nohDireita)
{
    //O sucessor do noh eh o menor noh (ultimo noh da esquerda) a partir do noh da direita do qual se quer o sucessor
    List atual = nohDireita;

    while(atual->esq != NULL)
        atual = atual->esq;

    return atual;
}

void preOrder(List raiz)
{
    if(raiz != NULL)
    {
        printf("%d ", raiz->info);
        preOrder(raiz->esq);
        preOrder(raiz->dir);
    }
}

void percorreArv(List raiz, char tab[], FILE* file, int n)
{
    if(raiz->esq != NULL)
    {
        tab[n] = 0;
        percorreArv(raiz->esq,tab,file, n + 1);
    }

    if(raiz->dir != NULL)
    {
        tab[n] = 1;
        percorreArv(raiz->dir,tab,file,n + 1);
    }

    if(raiz->esq == NULL && raiz->dir == NULL)
    {
        int i;
        fprintf(file,"%c = ", raiz->letra);
        for(i = 0; i < n; i++)
        {
            fprintf(file,"%d", tab[i]);
        }
        fprintf(file,"\n");

    }
}

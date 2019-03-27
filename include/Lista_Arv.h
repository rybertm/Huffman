#ifndef LISTA_ARV_H_INCLUDED
#define LISTA_ARV_H_INCLUDED

struct list
{
    int info;
    char letra;
    struct list *prox;
    struct list *esq;
    struct list *dir;
};
typedef struct list* List;

List IniciaList(List head);
List InsereOrdenado(List head, int info, char letra);
List RemoveList(List head, List rmv);
List BuscaProxList(List head);
List IniciaNoh(List raiz);
List criaNoh(int info,char letra);
List insereNoh(List raiz, int info,char letra);
List procura_Info(List raiz, int info);
void imprime_em_Ordem(List raiz);
List deleta_Noh(List raiz, int info);
List sucessor_do_Noh_em_Ordem(List nohDireita);
void preOrder(List raiz);
void percorreArv(List raiz,char tab[], FILE* file, int n);

#endif // LISTA-ARV_H_INCLUDED

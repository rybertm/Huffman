#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista_Arv.h"

int main()
{
    //Le e guarda frequencia dos caracteres
    FILE* arq = fopen("arq.txt","r");
    if(!arq)
	{
		printf("Nao foi possivel abrir o arquivo.\n");
		exit(0);
	}
    int ascii[256] = {0};
    int i, c, tam = 0;

    while((c = fgetc(arq)) != EOF)
    {
        for(i = 0; i < 256; i++)
        {
            if(i == c)
            {
                ascii[i]++;
            }
        }
    }
    fclose(arq);

    //Cria a lista de arvore
    List head = NULL;
    head = IniciaList(head);
    List current;
    for(i = 0; i < 256; i++)
    {
        if(ascii[i] != 0)
        {
            tam++;
            current = InsereOrdenado(head,ascii[i],(char) i);
        }
    }

    List p = head->prox;
    while(p->prox != NULL)
    {

        List temp1 = BuscaProxList(head);
        List temp2 = BuscaProxList(temp1);
        int sum = temp1->info + temp2->info;
        current = InsereOrdenado(head,sum,'\0');

        //Adiciona a current tem1 e temp2 como nohs

        current->esq = temp1;
        current->dir = temp2;

        //Remove temp1 e temp2 da Lista Encadeada
        head = RemoveList(head,temp1);
        head = RemoveList(head,temp2);

        p = head->prox;
    }

    preOrder(head->prox);

    //Tabela de Codifica��o
    FILE* file = fopen("arqComp.txt","w");

    int n = 0;
    char tab[tam];
    memset(tab,0,tam);

    percorreArv(head->prox,tab,file,n);
    fclose(file);

    return 0;
}

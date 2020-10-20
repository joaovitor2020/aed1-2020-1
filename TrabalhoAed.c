/*lista de gastos domesticos */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxv 1000
typedef struct{
	int id;
	char nome[50];
	float valor;
}item;
typedef struct{
	item v[maxv];
	int qtd;
}lista;
lista * criaLista(){
	lista * li;
	li = (lista *) malloc(sizeof(lista));
	if(li != NULL){
		li->qtd = 0;
		return li;
	}
}
void destroiLista(lista * li){
	free(li);
}
int insereItem(lista * li,char s[],float val){
	int c;
	if(li->qtd >= maxv)return -1;
	//printf("%d\n",li->qtd);
	strcpy(li->v[li->qtd].nome,s);
	li->v[li->qtd].valor = val;
	for(c=1;c<= li->qtd+1;c++){
		li->v[c-1].id = c;
	}
	//printf("%d %s %.2f\n",li->v[li->qtd].id,li->v[li->qtd].nome,li->v[li->qtd].valor);
	li->qtd++;
	return 1;
}
int buscaItem(lista * li, int iden){
	int i;
	if(li->qtd == 0)return -1;
	for(i=0;i<li->qtd;i++){
		if(li->v[i].id == iden)return i;
	}
	return -1;
}
int removeItem(lista * li, int iden){
	int i,c;
	if(li->qtd == 0)return -1;
	i = buscaItem(li,iden);
	if(i == -1)return -1;
	else if(i == li->qtd - 1){
		li->qtd -= 1;
	}
	else{
		for(c= 0;c < (li->qtd-i);c++){
			li->v[i] = li->v[i+1];
			li->v[i].id = li->v[i+1].id;
			i++;
		}
		li->qtd -= 1;
		return 1; 
	}
}
void mostraLista(lista * li){
	int c,t,i;
	char sv[20];
	printf("| ID | NOME                | VALOR       |\n");	
	for(c=0;c< li->qtd;c++){
		printf("| %d  | ",li->v[c].id);
		if(strlen(li->v[c].nome) <= 20){
			printf("%s",li->v[c].nome);
			t = 20 - strlen(li->v[c].nome);
			for(i=0;i<t;i++){
				printf(" ");
			}
		}
		sprintf(sv,"%.2f",li->v[c].valor);
		printf("| ");
		if(strlen(sv) <= 12){
			printf("%s",sv);
			t = 12 - strlen(sv);
			for(i=0;i<t;i++){
				printf(" ");
			}
			printf("|\n");
		}
	}
}
int gravaLista(FILE * arq,lista * li){
	int c;
	if(arq == NULL)return 0;
	arq = fopen("teste.txt","a");
	for(c=0;c< li->qtd;c++){
		fprintf(arq,"%d %s %.2f\n",li->v[c].id,li->v[c].nome,li->v[c].valor);
	}
	fclose(arq);
	return 1;
} 
int mostraArquivo(FILE * arq){
	lista * li;
	int c = 0,i,r;
	char name[50];
	float val;
	li = criaLista();
	if(arq == NULL)return 0;
	arq = fopen("teste.txt","r");
	while(1){
		r = fscanf(arq,"%d",&i);
		if(r == EOF)break;
		fscanf(arq,"%d",&i);
		fscanf(arq,"%s",name);
		fscanf(arq,"%f",&val);
		insereItem(li,name,val);
	}
	mostraLista(li);
	destroiLista(li);
	fclose(arq);
	return 1;
} 
int qtdItens(lista * li){
	if(li == NULL)return -1;
	return li->qtd;
}
float valorTotalLista(lista * li){
	int c;
	float tot=0;
	if(li == NULL)return -1;
	for(c=0;c< li->qtd;c++){
		tot += li->v[c].valor;
	}
return tot;
} 
int main(){
FILE * arq;
lista * li = NULL;
char n[20];
item i;
li = criaLista();
destroiLista(li);
return 0;
}

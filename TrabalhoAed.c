/*lista de gastos domesticos */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxv 1000
typedef struct{
	int id;		//identificador
	char nome[50];	//nome do item
	float valor;	//valor do item
}item;
//lista estática
typedef struct{
	item v[maxv]; //vetor de itens com capacidade para 1000 itens
	int qtd;	//quantidades de elementos no vetor
}lista;

/**
 * aloca dinamicamente uma estrutura lista 
 * @return li lista alocada
 */
lista * criaLista(){
	lista * li;
	li = (lista *) malloc(sizeof(lista));
	if(li != NULL){
		li->qtd = 0;
		return li;
	}
}
/**
 * libera a memoria que foi alocada dinamicamente
 * @param li lista a ser liberada
 */
void destroiLista(lista * li){
	free(li);
}
/**
 * Insere um item em uma lista
 * Insere sempre no final
 * @param li lista que será inserido os valores
 * @param s  string com o nome do item
 * @param val valor do item
 * @return -1 erro se a lista estiver cheia
 * @return 1  se ocorreu sucesso na inserçao	
 */ 
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
/**
 * Busca um item com um id definido
 * @param li lista que será buscado o item
 * @param iden id a ser buscado
 * @return -1 erro se o item com id não for encontrado
 * @return 1  se for encontrado o item 
 */ 
int buscaItem(lista * li, int iden){
	int i;
	if(li->qtd == 0)return -1;
	for(i=0;i<li->qtd;i++){
		if(li->v[i].id == iden)return i;
	}
	return -1;
}
/**
 * Remove o item com um id definido
 * @param li lista que será removido o item
 * @param iden id do item a ser removido  
 * @return -1 erro se o item com id não for encontrado
 * @return 1  se o item for removido com sucesso
 */ 
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
/**
 * Apresenta a lista na tela em um formato de tabela
 * @param li lista a ser apresentada
 */ 
void mostraLista(lista * li){
	int c,t,i,j;
	char sv[20];
	printf("_________________________________________\n");
	printf("| ID | NOME                | VALOR       |\n");
	printf("|____|_____________________|_____________|\n");	
	for(c=0;c< li->qtd;c++){
		printf("| %d  | ",li->v[c].id);
		if(strlen(li->v[c].nome) <= 20){
			printf("%s",li->v[c].nome);
			t = 20 - strlen(li->v[c].nome);
			for(i=0;i<t;i++){
				printf(" ");
			}
		}else{
			for(j=0;j<20;j++){
				printf("%c",li->v[c].nome[j]);	//Se a string for maior que 20 caracteres ela será truncada
			} 
		}
		sprintf(sv,"%.2f",li->v[c].valor);		//transforma um float em uma string
		printf("| ");
		if(strlen(sv) <= 12){
			printf("%s",sv);
			t = 12 - strlen(sv);
			for(i=0;i<t;i++){
				printf(" ");
			}
			printf("|\n");
		}else{
			for(j=0;j<12;j++){
				printf("%c",sv[j]);
			} 		
		}	
	printf("|____|_____________________|_____________|\n");	
	}
}
/**
 * Grava uma lista em um arquivo txt
 * @param arq Ponteiro para um arquivo
 * @param li Lista a ser gravada
 * @param m Nome do arquivo
 * @return 0 Se ocorrer algum erro
 * @return 1 Em caso de sucesso 
 */ 
int gravaLista(FILE * arq,lista * li,char m[]){
	int c;
	if(arq == NULL)return 0;
	if(li == NULL)return 0;
	arq = fopen(m,"w");
	for(c=0;c< li->qtd;c++){
		fprintf(arq,"%d %s\n %.2f\n",li->v[c].id,li->v[c].nome,li->v[c].valor);
	}
	fclose(arq);
	return 1;
} 
/**
 * Carrega um arquivo existente em uma lista
 * @param arq Ponteiro para um arquivo
 * @param m Nome do arquivo
 * @return 0 Se ocorrer algum erro
 * @return li Retorna uma lista carregada com os itens do arquivo
 */ 
lista * carregaArquivo(FILE * arq,char m[]){
	lista * li;
	int c = 0,i,r;
	char name[50];
	float val;
	
	li = criaLista();
	if(li == NULL)return 0;
	if(arq == NULL)return 0;
	arq = fopen(m,"r");
	while(1){
		r = fscanf(arq,"%d",&i);
		if(r == EOF)break;
		fscanf(arq,"%d",&i);
		fscanf(arq,"%[^\n]s",name);
		fscanf(arq,"%f",&val);
		insereItem(li,name,val);
	}
	//mostraLista(li);
	//destroiLista(li);
	fclose(arq);
	//return 1;
	return li;
} 
/**
 * Verifica a quantidade de itens em uma lista
 * @param li lista a ser contada
 * @return -1 Se ocorrer algum erro
 * @return li->qtd Retorna a quantidades de itens da lista
 */ 
int qtdItens(lista * li){
	if(li == NULL)return -1;
	return li->qtd;
}
/**
 * Verifica o valor total de todos os itens da lista
 * @param li lista a ser verificada
 * @return -1 Se ocorrer algum erro
 * @return tot valor de todos os itens somados
 */ 
float valorTotalLista(lista * li){
	int c;
	float tot=0;
	if(li == NULL)return -1;
	for(c=0;c< li->qtd;c++){
		tot += li->v[c].valor;
	}
return tot;
} 
/**
 * Verifica se o arquivo existe ou não
 * @param arq  Ponteriro de um arquivo
 * @param m  Nome do arquivo
 * @return -1 Se o arquivo não existir
 * @return 1 Se o arquivo existir
 */ 
int verificaArquivo(FILE * arq,char m[]){
	int c = 1;  
	arq = fopen(m,"r");
	if(arq == NULL){
		c= -1;
	}else{
		fclose(arq);
	}
return c;	
}

int main(){
FILE * arq;
lista * li = NULL;
char n[20];
char m[20];
char a[10];
int ano,mes,estado,i;
float v;


printf("digite o mes de referencia :\n");
scanf("%d",&mes);
printf("digite o ano de referencia :\n");
scanf("%d",&ano);
sprintf(m,"%d",mes);
sprintf(a,"%d",ano);
strcat(m,"-");
strcat(m,a);
strcat(m,".txt");
//printf("%s",m);
//printf("%d",verificaArquivo(arq,m));
if(verificaArquivo(arq,m) == 1){
	li = carregaArquivo(arq,m);
}
else{
	li = criaLista();
	
}
printf("1 - Inserir item\n");
printf("2 - Remover item com o id\n");
printf("3 - Mostrar lista\n");
printf("4 - Mostrar valor total dos itens\n");
printf("5 - Mostrar a quantidade(s) de itens\n");
printf("6 - Salvar\n");
printf("7 - Sair\n");
while(1){
	printf("Digite uma opcao :\n");
	scanf("%d",&estado);
	if(estado == 7)break;
	switch(estado){
		case 1 :
			printf("Nome do item :\n");
			getchar();
			scanf("%[^\n]s",n);
			getchar();
			printf("Valor do item :\n");	
			scanf("%f",&v);
			insereItem(li,n,v);
		break;
		case 2 :
			printf("Digite o id a ser removido:\n");
			scanf("%d",&i);
			if(removeItem(li,i) == -1){
				printf("Id nao encontrado\n");
			}else{
				printf("Item com o id %d foi removido\n",i);
			}
		break;
		case 3 :
			mostraLista(li);
		break;
		case 4 :
			printf("Valor total do(s) iten(s) : %.2f\n",valorTotalLista(li));
		break;
		case 5:
			printf("Quantidade(s) de iten(s): %d\n",qtdItens(li));
		break;
		case 6:
			gravaLista(arq,li,m);
			printf("Salvo com sucesso\n");
		break;
		default :
			printf("Comando inexistente\n");
	}
}

destroiLista(li);
return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct
{
	char  nome[20];
	int tamanho;
} tApp;

tApp storeApp[20];
tApp Installed[20];
tApp runing[20];

int storeAppTam = 0, InstalledTam = 0, runingTam = 0; // tamanho dos vetores

int read(){
	/*
	Fun��o responsavel por ler os aplicativos da loja que se encontram no arquivo .txt
	Parametros: n�o recebe
	Retorno: numero de linhas do arquivo(1 aplicativo por linha)
	Estrutura Usada na implementa��o:
	*/
	int  indice = 0, i = 0, j = 0;
	tApp temp;
	FILE *arq;
	arq = fopen("apps.txt", "r");
	if(arq == NULL)
		printf("Erro, nao foi possivel abrir o arquivo\n");
	else
		while( (fscanf(arq, "%s %d \n", temp.nome , &temp.tamanho)) != EOF )
		{
			if(indice == 0){
				storeApp[0] = temp;
			}else{
				for(i = 0; i < indice; i++){
					if(storeApp[i].tamanho > temp.tamanho ) break;
				}
				for(j = indice; j > i; j--)
				{
					storeApp[j] = storeApp[j - 1];
				}
				storeApp[i] = temp;
			}
			indice++;
		}
	fclose(arq);
	return(indice);
}

int StoreED( )
{
	/*
	Fun��o que Mostra a Storeed
	parametros: N�o tem
	retorno: Aplicativo a ser instalado
	*/

	int length = 0, cod = 0 , i = 0;
	system("clear || cls");

	printf("\t\t\t StoreED \n\n\n\n" );
	length = read();
	for(i = 0; i < length; i++)
	{
		printf("\t\t%d %s  %d \n", i + 1, storeApp[i].nome , storeApp[i].tamanho);
	}
	printf("\n\nSelecione um aplicativo para instalar: ");
	scanf("%d", &cod);
	system("clear || cls");
	return cod - 1;
}

void print(tApp  *vetor, int tamanho)
{
	/*
	fun��o responsavel por mostrar os aplicativos de um vertor
	parametros: Vertor e o tamanho do mesmo
	retorno: N�o tem
	*/
	int i = 0;
	system("clear || cls");
	if(tamanho == 0)
	{
		printf("\t\tNenhum aplicativo instaldo\n\n\n");

	}
	for(i = 0; i < tamanho; i++)
	{
		printf("\t\t%d %s - %dmb \n", i + 1, vetor[i].nome, vetor[i].tamanho);
	}
}
int inserir(tApp *vetorA, int tamanho, tApp *vetorB, int indice)
{
	/* fun��o responsavel por inserir de forma ordenada um elemento em um vetor;
	*prarametros: vetorA(vetor que sera inserido a variavel),int tamanho(tamanho do vetorA),
	*tApp *vetorB(vetor que contem a viavel a ser inserida no vetorA), int indice(indice da estrutura dentro do vetorB)
	* retorno: tamanho atualizado do vetorA
	*/
	int i = 0, j = 0;
	if(vetorB[indice].tamanho > 0)
	{
		for(i = 0; i < tamanho; i ++)
		{
			if(strcmp(vetorA[i].nome, vetorB[indice].nome) == 0)
			{
				printf("\tAplicativo j� se encontra foi instalado em seu MobileED leED\n\n\n");
				return tamanho; //se estiver instalado
			}
		}

		if(tamanho == 0)
		{
			vetorA[0] = vetorB[indice];
		}
		else
		{
			for(i = 0; i < tamanho; i++)
			{
				if(vetorA[i].tamanho > vetorB[indice].tamanho ) break;
			}
			for(j = tamanho; j > i; j--)
			{
				vetorA[j] = vetorA[j - 1];
			}
			vetorA[i] = vetorB[indice];
		}
		tamanho++;
	}
	else
	{
		printf("Aplicativo nao encontrado\n" );
	}
	return tamanho;
}
int remover(tApp *vetor, int tamanho, int indice){
	/* fun��o responsavel por remorver de forma ordenada um elemento em um vetor;
	*prarametros: vetor(vetor que sera removido a variavel),int tamanho(tamanho do vetor),e o indice onde se encontra o elemento a ser removido
	* retorno: tamanho atualizado do vetor
	*/

	int i =0 ;
	if(indice  < tamanho){
	if(vetor[indice].tamanho > 0)
	{
		for(i = indice; i < tamanho-1; i++)
		{
			vetor[i] = vetor[i + 1];
		}
		tamanho --;
	}

	}
	return tamanho;
}
void gerenciadorDeTarefas()
{
	/*
	fun��o responsavel desinstalar e encerrar aplicativos
	parametros: N�o recebe
	retorno:N�o tem
	*/
	system("clear || cls");
	int resp, i = 0;
	printf("\t\t\tGerenciador De Tarefas\n\n\n\n");
	printf("\t\t1-Aplicativos em execu��o\n\t\t2-desinstalar Aplicativo \n");
	printf("\n\n\tSelecione uma Op��o: " );
	scanf("%d", &resp);
	switch(resp)
	{
	case 1:
		print(runing, runingTam);
		if(runingTam != 0)
		{
			printf("\t\tqual o Aplicativo a ser fechado?");
			scanf("%d", &resp);
			printf("\t\t%s ser� fechado\n", runing[resp - 1].nome);
			runingTam = remover(runing, runingTam, resp - 1);
		}
		break;
	case 2:
		print(Installed, InstalledTam);
		if(InstalledTam != 0)
		{
			printf("qual o Aplicativo a ser desinstalado?");
			scanf("%d", &resp);

			for(i = 0; i < runingTam; i++)
			{
				if (strcmp(Installed[resp - 1].nome, runing[i].nome) == 0)
				{
					runingTam = remover(runing, runingTam, i);
					break;
				}
			}
			InstalledTam = remover(Installed, InstalledTam, resp - 1);
		}
		break;
	}
}

	/* fun��o responsavel por inserir de forma ordenada um elemento em um vetor;
	*prarametros: vetorA(vetor que sera inserido a variavel),int tamanho(tamanho do vetorA),
	*tApp *vetorB(vetor que contem a viavel a ser inserida no vetorA), int indice(indice da estrutura dentro do vetorB)
	* retorno: tamanho atualizado do vetorA
	*/
void desktop(tApp  *vetor, int tamanho){
	int i = 0;
	system("clear || cls");
	if(tamanho == 0)
	{
		printf("\t\tNenhum aplicativo na �rea de trabalho.\n\t\tInstale aplicativos na StoreED\n\n\n");

	}
	for(i = 0; i < tamanho; i++)
	{
		if((i%3)==0){
			printf("\n");
		}
		printf("\t%d %s - %dmb ", i + 1, vetor[i].nome, vetor[i].tamanho);
	}
}
int main( )
{
	setlocale(LC_ALL, "Portuguese");
	int option, a = 1, resp = 0, cod = 0;

	while (a)
	{
		printf("\t\t\t MobileED lED Home\n\n" );
		desktop(Installed, InstalledTam);
		printf("\n\n\t\t 1-Aplicativos instalados\n\t\t 2-StoreED\n\t\t 3-Gerenciador de tarefas \n\t\t 0-Desligar\n\n" );
		printf("\n\tSelecione uma Op��o: " );
		scanf("%d", &option);
		switch (option)
		{
		case 1:
			print(Installed, InstalledTam);
			if(InstalledTam != 0)
			{
				printf("\n\nQual o Aplicativo a ser Executado:\n");
				scanf("%d", &resp);
				runingTam = inserir(runing, runingTam, Installed, resp - 1);
				printf("\n\n");
			}
			break;
		case 2:
			cod = StoreED();
			InstalledTam = inserir(Installed, InstalledTam, storeApp, cod);
			break;
		case 3:
			gerenciadorDeTarefas();
			break;
		case 0:
			a = 0;
			break;
		}
	}
	return 0;
}

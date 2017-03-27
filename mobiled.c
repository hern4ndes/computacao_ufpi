#include <stdio.h>
#include <locale.h>

typedef struct{
  char  nome[20];
  int tamanho;
}tApp;
tApp storeApp[20];
tApp Installed[20];
tApp runing[20];

int storeAppTam = 0,InstalledTam = 0,runingTam = 0; // tamanho dos vetores


int read(){//OK
  /*
  função responsavel por ler os aplicativos da loja que se encontram no arquivo .txt
  parametros: não recebe
  retorno: numero de linhas do arquivo(1 aplicativo por linha)
  */
  
  int count;
  FILE *arq;
  arq = fopen("apps.txt", "r");
  if(arq == NULL)
  printf("Erro, nao foi possivel abrir o arquivo\n");
  else
  while( (fscanf(arq,"%s %d \n",storeApp[count].nome , &storeApp[count].tamanho))!=EOF ){
    count ++;
  }
  fclose(arq);
  return(count);
  
}

int StoreED( ){
  
  int length;
  int cod,i;
  system("clear || cls");
  
  printf("\t\t\t StoreED \n" );
  length = read();
  for(i = 0; i < length;i++){
    printf("%d %s  %d \n",i+1,storeApp[i].nome , storeApp[i].tamanho);
  }
  printf("Selecione um aplicativo para instalar: ");
  scanf("%d",&cod);
  system("clear || cls");
  return cod-1;
}



void print(tApp  *vetor, int tamanho){
  
  int i = 0;
  char resp;
  system("clear || cls");
  if(tamanho == 0){
    printf("Não foram encontadas aplicações\n\n\n");
    
  }
  
  for(i = 0;i < tamanho;i++){
    printf("%d %s \n",i+1,vetor[i].nome, vetor[i].tamanho);
  }
}
int remover(tApp *vetor, int tamanho, int indice){
  int i;
  for(i = indice; i < tamanho;i++){
    vetor[i-1] = vetor[i]; 
  }
  tamanho --;  
  return tamanho;
}
void gerenciadorDeTarefas(){
  system("clear || cls");
  int resp;
  printf("1 Aplicativos em execução\n2 Desistalar Aplicativo \n3 Gerenciador de memória ");
  printf("\nSelecione uma opicao: " );
  scanf("%d",&resp);
  switch(resp){
    case 1: print(runing,runingTam);
    if(runingTam!=0){
      printf("qual o Aplicativo a ser fechado?");
      scanf("%d",&resp);
      printf("%s será fechado\n",runing[resp-1].nome);
      runingTam = remover(runing, runingTam,resp-1);
    }
    break;
    case 2:print(Installed,InstalledTam);
    if(InstalledTam!=0){
      printf("qual o Aplicativo a ser desinstalado?");
      scanf("%d",&resp);
      printf("%s será desinstalado\n",Installed[resp-1].nome);
      InstalledTam = remover(Installed, InstalledTam,resp-1);
    }
    break;
    case 3: printf("%d Aplicativos instalados",InstalledTam);
  }
  
  
  
}

int inserir(tApp *vetorA,int tamanho, tApp *vetorB, int indice){
  /* função responsavel por inserir de forma ordenada um elemento em um vetor;
  *prarametros: vetorA(vetor que sera inserido a variavel),int tamanho(tamanho do vetorA),
  *tApp *vetorB(vetor que contem a viavel a ser inserida), int indice(indice da estrutura dentro do vetorB)
  * retorno: tamanho atualizado do vetorA
  */
  int i,j;	
  
  for(i=0; i < tamanho; i ++){
    if(strcmp(vetorA[i].nome, vetorB[indice].nome)==0){
      printf("Aplicativo já se encontra foi intalado em seu MobileED\n");
      return tamanho; //se estiver instalado
    }
  }
  
  
  if(tamanho == 0){
    vetorA[0] = vetorB[indice];
    
  }else{
    for(i = 0; i < tamanho;i++){
      if(vetorA[i].tamanho > vetorB[indice].tamanho ) break;
    }
    for(j = tamanho;j>i;j--){
      vetorA[j] = vetorA[j-1];
      
    }
    vetorA[i] = vetorB[indice];
  }
  tamanho++;
  return tamanho;
}

int main( ){
  setlocale(LC_ALL, "Portuguese");
  int option,a = 1,resp;
  int i;
  int cod;
  int tamanho = 0;
  
  while (a) {
    
    printf("\t\t\t MobilED Home\n\n" );
    printf("\n\n  1-Area de trabalho.\n  2-StoreED\n  3-Gerenciador de tatefas\n  0-Dsligar\n\n" );
    printf("\nSelecione uma opicao: " );
    
    scanf("%d",&option);
    
    
    switch (option) {
      
      case 1:
      print(Installed, InstalledTam);
      if(InstalledTam != 0){
        printf("Qual o Aplicativo a ser Executado:\n");
        scanf("%d",&resp);
        runingTam = inserir(runing,runingTam,Installed,resp-1);
        printf("\n\n")
      }
      break;
      case 2: cod = StoreED();
      InstalledTam = inserir(Installed,InstalledTam,storeApp,cod);
      printf("%s Instalado com sucesso \n\n\n",storeApp[cod].nome);
      
      break;
      case 3: gerenciadorDeTarefas();
      break;
      case 0: a = 0;
      break;
      
    }
    
    
    
    /* code */
    
    //  StoreED(numApps);
    
  }
  return 0;
}

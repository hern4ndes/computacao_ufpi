/* TRABALHO FINAL DE PROGRAMACAO ESTRUTURADA
*  Desenvolvido por: Diego Winter
*					 Hernandes Erick
*  Nosso projeto e repositorio no Github: https://github.com/hern4ndes/Trabalho_Final_PE
*/
// includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//estruturas
typedef struct{
	int dia;
	int mes;
	int ano;
}tdata;
typedef struct{
	char cpf[12];
	char nome[100];
	tdata dt_adm;
	tdata dt_nasc;
	int cargo;
	int dept;
}tFuncionario;
typedef struct{
	char nome[100];
	int cod;
	int quant;
}tDepartamento;


//variaveis globais
tFuncionario func[150];
int prox[150];
int controle[1][11];
tDepartamento dep[11];

void ler_arquivos(){
int i = 0;
FILE *funcionario;
 funcionario = fopen("funcionario.txt","ab");
if(funcionario ==  NULL){
	printf("impossivel abrir o arquivo\n" );
}
else{
	for(i = 0; i < 150;i++){
		fread(&func[i],sizeof(tFuncionario),1,funcionario);
	}
}
fclose(funcionario);
}

void gravar_arquivos(){
int i = 0;
FILE *funcionario;
funcionario = fopen("funcionario.txt","ab");
if(funcionario ==  NULL){
	printf("impossivel abrir o arquivo\n" );
}
else{
	while (!feof(funcionario)){
		fwrite(&func[i],sizeof(tFuncionario),1, funcionario);
		i++;
	}
}
fclose(funcionario);
}



	//FUNCOES UTEIS PARA OUTRAS FUNCOES (valida-datas, mostra dados, etc)
	//Objetivo: Mostra os dados de um funcionario em diferentes funcoes
	//Parametros: i, que recebe o indice do funcionario
	//Retorno: sem retorno

	void mostrarDados(int i) {
		int j, k, nomeDep; //ESSAS VARIAVEIS SERVEM PARA MOSTRAR O NOME DO DEPARTAMENTO TAMBEM
		printf("  CPF: %s\n", func[i].cpf);
		printf("  Nome: %s\n",func[i].nome);
		printf("  Data de Admissao: %d/%d/%d\n",func[i].dt_adm.dia,func[i].dt_adm.mes,func[i].dt_adm.ano);
		printf("  Data de Nascimento: %d/%d/%d\n",func[i].dt_nasc.dia ,func[i].dt_nasc.mes, func[i].dt_nasc.ano);
		printf("  Codigo do Cargo: %d\n",func[i].cargo);

		j=func[i].dept;            //=============================
		for(k=0;k<11;k++){         // PARA MOSTRAR
			if(j==dep[k].cod){     // O NOME DO DEPARTAMENTO
				nomeDep=k;         // NA HORA DE MOSTRAR OS DADOS.
				break;             //=============================
			}
		}
		printf("  Departamento: %d (%s)\n",func[i].dept, dep[nomeDep].nome);
		printf("-> Funcionario indice: %d \n\n", i); //extra para informar o indice dele em func
	}
	//Objetivo: Valida datas inseridas em diferentes funcoes
	//Parametros: dia, mes e ano que se deseja validar
	//Retorno: 1 se valida ou 0 se nao valida
	int valida_data(int dia, int mes, int ano){
		if ((dia>=1 && dia<=31)&&(mes>=1 && mes<=12)&&(ano>=1900 && ano<=2100))
		{
			if ((dia==29 && mes==2) && ((ano%4)==0)){
				return 1;
			}
			if (dia<=28 && mes==2){
				return 1;
			}
			if ((dia<=30) && (mes==4 || mes==6 || mes==9 || mes==11)){
				return 1;
			}
			if ((dia<=31) && (mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12)){
				return 1;
			} else{
				return 0;
			}
		} else{
			return 0;
		}
	}
	//Objetivo: Funcao de testes, exibe a matriz controle
	//Parametros: nenhum
	//Retorno: nenhum
	void testecontrole(){
		int i = 0, j = 0;
		for (i = 0; i <= 1; i++){
			for (j = 0; j <= 10; j++) {
				printf("%3d ", controle[i][j]);
			}
			printf("\n");
		}
	}
	void testeprox() {
		int i;
		printf("\n");
		for (i = 0;i<11; i++) {
			printf("%d ",prox[i] );
		}
		printf("\n");

	}
	void printdep(/* arguments */) {
		int i;
		for (i = 0; i < 11; i ++) {
			printf("%d ",func[i].dept );
		}
		printf("\n");
		/* code */
	}

	//Objetivo: ---//---
	//Parametros: ---//---
	//Retorno: ---//---
	void matrizControle(int dep, int func) {
		controle[1][func] = func;
	}




	//0. MENU PRINCIPAL
	//Objetivo: mostra o menu principal
	//Parametros: nenhum
	//Retorno: retorna a resposta
	int menuPrincipal(){
		int resp;
		printf("\t\tMenu Principal\n\n");
		printf("1. Funcionario\n");
		printf("2. Departamento\n");
		printf("0. Sair\n");
		printf("Digite uma opcao do menu: ");
		scanf ("%d", &resp);
		return resp;
	}








	//1. MENU FUNCIONARIO e suas funcoes
	//Objetivo: mostra o menu funcionario
	//Parametros: nenhum
	//Retorno: retorna a resposta
	int menuFuncionario(){
		int resp;
		system("clear || cls");
		printf("\n\t\tMenu Funcionario\n\n");
		printf("1. rar funcionario\n");
		printf("2. Alterar dados do funcionario\n");
		printf("3. Transferir funcionario de departamento\n");
		printf("4. Demitir Funcionario\n");
		printf("5. Pesquisar Funcionario\n");
		printf("6. Listar todos os funcionarios\n");
		printf("7. Listar todos de um departamento\n");
		printf("0. Sair\n\n");
		printf("Digite uma opcao do menu: ");
		scanf ("%d", &resp);
		system("cls || clear" );
		return resp;
	}
	//1.1 rar funcionario
	//Objetivo: cadastra um funcionario
	//Parametros: o vetor func e pos que indica a posicao
	//Retorno: 1 se tudo ocorrer bem
	int cadastarFuncionario(tFuncionario func[150], int pos){
		int depOK=0;//1: Departamento OK, 0:Departamento nao existe
		int i, j, k;
		printf ("1. Cadastrar novo funcionario\n");
		printf("Preencha os dados que se pedem a seguir\n\n");
		printf ("CPF: ");
		scanf ("%s", &func[pos].cpf);
		printf ("Nome Completo: ");
		scanf (" %100[^\n]s", &func[pos].nome);
		/*
		do{
		printf ("Data de Admiss%co: ", 198);
		scanf ("%d%d%d", &func[pos].dt_adm.dia, &func[pos].dt_adm.mes, &func[pos].dt_adm.ano);
		if (valida_data(func[pos].dt_adm.dia, func[pos].dt_adm.mes, func[pos].dt_adm.ano) == 0){
		printf ("Data inv%clida! Digite novamente\n", 160);
	}
} while (valida_data(func[pos].dt_adm.dia, func[pos].dt_adm.mes, func[pos].dt_adm.ano) == 0);
do{
printf ("Data de Nascimento: ");
scanf ("%d%d%d", &func[pos].dt_nasc.dia, &func[pos].dt_nasc.mes, &func[pos].dt_nasc.ano);
if (valida_data(func[pos].dt_nasc.dia, func[pos].dt_nasc.mes, func[pos].dt_nasc.ano)==0){
printf ("Data inv%clida! Digite novamente\n", 160);
}
} while (valida_data(func[pos].dt_nasc.dia, func[pos].dt_nasc.mes, func[pos].dt_nasc.ano)==0);
*/
printf ("Codigo do cargo a ser designado: ");
scanf ("%d", &func[pos].cargo);
do{
	printf ("Departamento a ser designado: ");
	scanf ("%d", &func[pos].dept);
	for(i=1;i<=11;i++){
		if(func[pos].dept== controle[0][i]){ //// func[pos].dept==dep[i].cod troquei func[pos].dept==dep[i].cod por func[pos].dept==controle[0][i+1] por que precisei de colocar o funcionario que começa o Departamento
			depOK=1;
			prox[pos] = controle[1][i];
			controle[1][i] = pos; // mostra o funcionario que inicia o dapartamento na matriz controle



			break;

		}
	}
}while(depOK==0);
j=func[pos].dept;
for(k=0;k<11;k++){
	if(j==dep[k].cod){
		dep[k].quant++;;
		break;
	}
}
system("clear || cls");
printf("Funcionario cadastrado com sucesso! Verifique seus dados:\n");
mostrarDados(pos);
controle[1][0]++;
return 1;
}

//1.2 alterar dados do funcionario
//Objetivo: mostra o menu alterar funcionario se for digitado um cep valido
//Parametros: cpf
//Retorno: a resposta
int menu_AlterarFuncionario(char cpf[12]){
	int resp;
	printf("1. CPF\n");
	printf("2. Nome\n");
	printf("3. Data de Nascimento\n");
	printf("4. Data de Admissao na Empresa\n");
	printf("5. Cargo\n");
	printf("0. Sair\n");
	printf("Digite uma opcao: ");
	scanf("%d", &resp);
	return resp;
}
//Objetivo: verifica existencia de cpf
//Parametros:  cpf
//Retorno: i se encontrar
int alterarFuncionario_CPF(char cpf[12]){
	int i;
	for(i=0;i<150;i++){
		if(strcmp(func[i].cpf, cpf)==0){
			return i;
		}
	}
	return -1;
}
//Objetivo: altera dados do funcionario
//Parametros: cpf
//Retorno: 10 se existir
int verificarExistenciaCPF(char cpf[12]){
	int i;
	for(i=0;i<150;i++){
		if(strcmp(func[i].cpf, cpf)==0){
			printf("%s", cpf);
			return 10; //Se existir
		}
	}
	return 5; //Se nao existir
}
//Objetivo: altera dados do funcionario
//Parametros: nenhum
//Retorno: 0 se ocorrer tudo de acordo
int funcao_AlterarFuncionario(){
	char cpf[12];
	int i, j;
	int resp, rsp; //rsp PARA O MENU e resp PARA AS CONDICOES DE REPETICAO
	printf("Qual o CPF do funcionario? ");
	scanf("%s", &cpf);
	if(alterarFuncionario_CPF(cpf) != -1){
		j=alterarFuncionario_CPF(cpf);
		printf("Menu Alterar Funcionario - CPF %s\n", cpf);
		rsp=menu_AlterarFuncionario(cpf);
	}
	if(alterarFuncionario_CPF(cpf) == -1){
		printf("Esse CPF nao esta cadastrado!\n1. Digitar outro\n0. Sair\nResposta: ");
		scanf("%d", &resp);
		if (resp==1){
			funcao_AlterarFuncionario();
		}
	}
	if(rsp==1){
		char cpf[12];
		do{
			printf("Digite o novo CPF: ");
			scanf("%s", cpf);
			resp=verificarExistenciaCPF(cpf);//Verifica a existencia do CPF. Retorna 10 se ja existir ou 5 se nao existir
			if(resp==5){
				strcpy(func[j].cpf, cpf);
				printf("CPF alterado com sucesso!\n");
			}else if (resp==10){
				printf("Esse cpf ja existe.\n1.digitar outro\n2.Sair\nResposta: ");
				scanf("%d", &resp);
			}
		}while(resp==1);
	}
	if(rsp==2){
		printf("Qual o novo nome? ");
		scanf("%s", &func[j].nome);
		printf("Nome alterado com sucesso!");
	}
	if(rsp==3){
		do{
			printf ("Qual a nova data de nascimento? ");
			scanf ("%d%d%d", &func[j].dt_nasc.dia, &func[j].dt_nasc.mes, &func[j].dt_nasc.ano);
			if (valida_data(func[j].dt_nasc.dia, func[j].dt_nasc.mes, func[j].dt_nasc.ano)==0){
				printf ("Data invalida! Digite novamente: ");
			}else{
				printf("Data de nascimento alterada com sucesso!");
			}
		}while (valida_data(func[j].dt_nasc.dia, func[j].dt_nasc.mes, func[j].dt_nasc.ano)==0);
	}
	if(rsp==4){
		do{
			printf ("Qual a nova data de admissao? ");
			scanf ("%d%d%d", &func[j].dt_adm.dia, &func[j].dt_adm.mes, &func[j].dt_adm.ano);
			if (valida_data(func[j].dt_adm.dia, func[j].dt_adm.mes, func[j].dt_adm.ano) == 0){
				printf ("Data invalida! Digite novamente:");
			}else{
				printf("Data de admissao alterada com sucesso!");
			}
		}while (valida_data(func[j].dt_adm.dia, func[j].dt_adm.mes, func[j].dt_adm.ano) == 0);
	}
	if(rsp==5){
		printf("Qual o novo cargo? ");
		scanf("%d", &func[j].cargo);
		printf("Cargo alterado com sucesso!");
	}
	if(rsp==0){
		return 0;
	}
	return 0;
}

//1.3 transferir funcionario
//Objetivo: transfere funcionario de departamento
//Parametros: -
//Retorno: nenhum
void alterarFuncDept(){
	int i;
	char cpf[12];
	printf("Qual o cpf do funcionario? ");
	scanf("%s", cpf);
	//busca funcionario com um for{
	//busca seu departamento na matriz dep{
	//processo de exclusao{
	//code
	//}
	//}
	//}
	//Se nao encontrar, retorna
}

//1.4 demitir funcionario
//Objetivo: -
//Parametros: -
//Retorno: -
/* CODE */

//1.5 pesquisar funcionario
//Objetivo: pesquisa um funcionario e exibe os dados
//Parametros: nenhum
//Retorno: nenhum
void pesquisarFuncionario(){
	char cpf[12];
	int i, resp=0;
	do{
		printf("Qual o CPF do funcionario? ");
		scanf("%s", cpf);
		for(i=0;i<150;i++){
			if(strcmp(func[i].cpf, cpf)==0){
				mostrarDados(i);
				resp=5;// 5 se o funcionario foi encontrado e tudo ocorreu bem
				break;
			}
		}
		if(resp!=5){
			printf("CPF %s nao cadastrado!\nDigite 0 para retornar ao menu funcionario ou 1 para digitar um novo cpf: ", cpf);
			scanf("%d", &resp);
		}
	}while(resp==1);
}

//1.6 listar todos os funcionarios
//Objetivo: lista todos os funcionarios, separando por departamento
//Parametros: cont
//Retorno: nenhum
void listarTodos(int cont){
	int i, j;
	printf ("Lista de funcionarios:\n");
	for(i=0;i<11;i++){
		if(dep[i].cod>0){
			printf("----------------------------------------\n");
			printf("Departamento %d - %s\n", dep[i].cod, dep[i].nome);
			printf("----------------------------------------\n");
			for(j=0;j<cont;j++){
				if(dep[i].cod==func[j].dept){
					mostrarDados(j);
				}
			}
		}
	}
}
//1.7 listar um departamento
//Objetivo: lista apenas um departamento
//Parametros: cont
//Retorno: nenhum
void listarPorDept(int cont){
	int i, j, resp=0, cod;
	printf("Qual o codigo do departamento? ");
	scanf("%d", &cod);
	for(i=0; i<11;i++){
		if(dep[i].cod==cod){
			printf("Departamento %d - %s\n", dep[i].cod, dep[i].nome);
			resp=5;// 5 para se achar o departamento e tudo ocorrer bem
			for(j=0;j<150;j++){
				if(dep[i].cod==func[j].dept){
					mostrarDados(j);
				}
			}
		}
	}
	if(resp==0){
		printf("Departamento %d nao existe!\n", cod);
	}
}
int listarpordptinprox(int contDep) {
	int cod, i ;

	printf("Qual o codigo do departamento? ");
	scanf("%d", &cod);
	for (i = 1;i <= contDep; i++) {
		if (cod == controle[0][i]) {
			break;
		}
	}
	//1'

	mostrarDados(controle[1][i]); // funcio que inicia o dep
	if (prox[controle[1][i]] == -1){
		return 0;
	}
	i =  controle[1][i];
	//mostrarDados(prox[controle[1][i]]);

	/* code */

	while (i != -1){
		if (i != 0) {
			mostrarDados(prox[i]);
			i = prox[i];
		}else if (i =!-1||i == 0) {
			break;
		}


	}
	/* code */



}

//2. MENU DEPARTAMENTO e suas funcoes
//Objetivo: Mostrar o menu Departamento
//Parametros: Nenhum
//Retorno: A resposta do usuario, ou seja, a opcao desejada do menu
int menuDepartamento(){
	system("clear || cls");
	int resp;
	printf ("\n\tMenu Departamento\n\n");//#1
	printf("1. Criar departamento\n");//#2
	printf("2. Alterar nome do departamento\n");//#3
	printf("3. Consultar departamento\n");//#4
	printf("4. Listar departamentos\n");//#5
	printf("5. Excluir departamento\n");//#6
	printf("0. Sair\n");//Saida
	printf("Digite sua resposta: ");
	scanf("%d", &resp);
	system ("cls || clear" );
	return resp;
}

//2.1 criar departamento
//Objetivo: Criar um departamento
//Parametros: contDep que controla os departamentos cadastrados
//Retorno: retorna o contDep pra fazer incremento

int criarDepartamento(int contDep){
	system("clear || cls");
	printf("\tCriar Departamento\n\n");
	int i;
	do{
		printf("Qual o codigo do departamento? ");
		scanf("%d", &dep[contDep].cod);
	}while (dep[contDep].cod > 10);
	for(i = 1; i <= 11; i++){
		while (controle[0][i] == dep[contDep].cod){
			printf("O departamento %d ja existe!\nDigite 0 para retornar ao menu departamento ou 1 para digitar um novo codigo\n",dep[contDep].cod );
			int resp;
			scanf("%d",&resp);
			if (resp == 1){
				printf("Qual o codigo do departamento? ");
				scanf("%d", &dep[contDep].cod);
			}else if( resp == 0 ){
				menuDepartamento();
			}	else {
				printf("digite uma opcao valida\n" );
			}
		}
	}
	printf("Qual o nome do departamento? ");
	scanf("%s", &dep[contDep].nome);
	dep[contDep].quant=0;
	controle[0][contDep + 1] = dep[contDep].cod;
	controle[1][contDep+1]=-1;
	printf("\nDepartamento criado com sucesso. Pronto para cadastrar funcionarios.\n");
	contDep++;
	return contDep; //Quando for chamado novamente, esse valor retornado eh incrementado no main
	//e volta como parametro.
}


//2.2 alterar nome de departamento
//Objetivo: altera o nome de um departamento
//Parametros: nenhum
//Retorno: nenhum
void alterarNomeDept(){
	system("clear || cls");
	printf("\tAlterar nome de Departamento\n\n");
	int cod;
	int i;
	int y=0, n=0, pos;
	int resp;
	do{
		printf("Qual o codigo do departamento? ");
		scanf("%d", &cod);
		for(i=0;i<11;i++){
			if(cod==dep[i].cod){
				y=1;
				pos=i;
			}               //y=sim, n=nao. 0 e o valor pra nao e 1 pra sim. COISAS QUE SO O DIEGO ENTENDE :D
			else{
				n=0;
			}
		}
		if(y==1){
			printf("Qual o novo nome do departamento? ");
			scanf("%s", dep[pos].nome);
			resp=0;
		}
		if((y==0)&&(n==0)){
			printf("O Departamento %d nao existe!\nDigite 0 para retornar ao menu departamento ou 1 para digitar um novo codigo: ", cod);
			scanf("%d", &resp);
		}
	}while(resp==1);
}

//2.3 consultar departamento
//Objetivo: consulta a existencia de um departamento e exibe seus dados
//Parametros: nenhum
//Retorno: nenhum
void consultarDepartamento(){
	system("clear || cls");
	printf("\tConsultar Departamento\n\n");
	int i;
	int cod;
	int nope=0;
	printf("Qual o codigo do departamento? ");
	scanf("%d", &cod);

	for(i=0;i<11;i++){
		if(cod==dep[i].cod){
			printf("Nome: %s\nQuantidade de funcionarios: %d", dep[i].nome, dep[i].quant);
		}else{
			nope=1;
		}
	}
	if(nope==1){
		printf("Departamento %d nao existe!", cod);
	}
}

//2.4 listar departamentos
//Objetivo: lista todos os departamentos cadastrados
//Parametros: nenhum
//Retorno: nenhum
void listarDepartamento(){
	system("clear || cls");
	printf("\tListar Departamento\n\n");
	int i;
	int cont=0;
	for(i=0;i<11;i++){
		if (dep[i].cod>0){		//considerando que os codigos nao sejam negativos
			cont++;             //Esse for serve pra apenas selecionar os departamentos cadastrados na listagem
		}                       //  ja que os departamentos estao no vetor dep de forma contigua :)
	}
	printf("Lista de Departamentos cadastrados: ");
	for(i=0;i<cont;i++){
		printf("\nCodigo: %d\nNome: %s\nQuantidade de funcionarios cadastrados: %d\n", dep[i].cod, dep[i].nome, dep[i].quant);
	}
}

//2.5 excluir departamento
//Objetivo: exclui um departamento
//Parametros: contDep pra receber a quantidade de deps cadastrados
//Retorno: nenhum
int excluirDepartamento(int contDep){
	int i, j, cont;
	int resp=0, resp3=0, stop;
	char resp2[1];
	int cod, pos;
	do{
		printf("Qual o codigo do departamento? ");
		scanf("%d", &cod);
		for(i=0;i<11;i++){
			if(cod == controle[0][i+1]){
				printf("%d\n",i );
				printf("%d\n",contDep );
				printf("Departamento %d - %s\n", dep[i].cod, dep[i].nome);
				pos=i;
				printf("Deseja realmente excluir o departamento? <s/n>: ");
				scanf("%s", resp2);
				if(resp2[0]=='s'){
					if(dep[i].quant>0){
						printf("Ha fucionario(s) lotado(s) no departamento %d. Nao e possivel excluir o departamento!\nDigite 0 para retornar ao menu departamento ou 1 para digitar um novo codigo: ", cod);
						scanf("%d", &resp3);
					}
					else if(controle[1][i+1] ==-1){

						for (i+1  ;i <= contDep ; i++){
							controle[0][i+1] = controle[0][i+2];
							controle[1][i+1] = controle[1][i+2];
							dep[i] = dep[i+1] ;

						}
						contDep--;

					}
				}
				else if(resp2[0]=='n'){
					resp=1;
				}
				resp=5;
			}
		}
		if(resp==0){
			printf("Departamento %d nao existe!\nDigite 0 para retornar ao menu departamento ou 1 para digitar um novo codigo: ", cod);
			scanf("%d", &resp);
		}
	}while((resp==1)||(resp3==1));
	return contDep;
}

int main (){

	int i, cont, contDep=0;    //===========
	controle[0][0]=-1;         //===========
	ler_arquivos();
	while (1) {
		printdep();

		testeprox();
		printf("\n" );

		testecontrole();

		switch (menuPrincipal()){
			case 1:	switch (menuFuncionario()){
				case 1: cadastarFuncionario(func, controle[1][0]);
				break;
				case 2: funcao_AlterarFuncionario();
				break;
				case 3: menuFuncionario();
				break;
				case 4: menuFuncionario();
				break;
				case 5: pesquisarFuncionario();
				break;
				case 6: listarTodos(controle[1][0]);
				break;
				case 7: listarpordptinprox(contDep);
				break;
				//case 8:
				//break;
				case 0: break;
				default: printf ("Erro. Por favor, digite novamente. Dessa vez, use uma opcao valida:\n\n");
			}
			break;
			case 2: switch (menuDepartamento()){
				case 1:contDep = criarDepartamento(contDep);
				break;
				case 2: alterarNomeDept();
				break;
				case 3: consultarDepartamento();
				break;
				case 4: listarDepartamento();
				break;
				case 5: contDep = excluirDepartamento(contDep);
				break;
				case 0: break;
			}
			break;
			case 0: gravar_arquivos();
							 exit(0);
			break;
			default: system ("clear || cls");
			printf ("Erro. Por favor, digite novamente. Dessa vez, use uma opcao valida:\n\n");

		}
	}
	return 0;
}

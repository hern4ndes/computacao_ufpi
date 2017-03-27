/* TRABALHO FINAL DE PROGRAMACAO ESTRUTURADA
*  Desenvolvido por: Diego Winter
*					 Hernandes Erick
* OBS.: Trabalho feito em versao simples, sem arquivos e sem a matriz prox.
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
int controle[1][11]; //so esta sendo usado [1][0] pro proximo e [0][1]~[10] pros departamentos. 
tDepartamento dep[11];

//prototipos de funcoes para evitar conflitos
void listarDepartamento();
int verificarExistenciaCPF(char cpf[12]);


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
	printf("  Departamento: %d (%s)\n\n",func[i].dept, dep[nomeDep].nome);
	//printf("-> Funcionario indice: %d \n\n", i); //extra para informar o indice dele em func
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
			printf("%d ", controle[i][j]);
		}
		printf("\n");
	}
	printf("\nPressione uma tecla para para continuar...");
	getch();
}

//0. MENU PRINCIPAL
//Objetivo: mostra o menu principal
//Parametros: nenhum
//Retorno: resp - retorna a resposta
int menuPrincipal(){
	int resp;
	printf("\n\n\t\tMenu Principal\n\n");
	printf("1. Funcionario\n");
	printf("2. Departamento\n");
	printf("0. Sair\n\n");
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
	printf("\n\n\t\t1. Menu Funcionario\n\n");
	printf("1. Cadastrar funcionario\n");
	printf("2. Alterar dados do funcionario\n");
	printf("3. Transferir funcionario de departamento\n");
	printf("4. Demitir Funcionario\n");
	printf("5. Pesquisar Funcionario\n");
	printf("6. Listar todos os funcionarios\n");
	printf("7. Listar todos de um departamento\n");
	printf("0. Voltar\n\n");
	printf("Digite uma opcao do menu: ");
	scanf ("%d", &resp);
	system("cls || clear" );
	return resp;
}
//1.1 cadastrar funcionario
//Objetivo: cadastra um funcionario
//Parametros: o vetor func e pos que indica a posicao em controle[1][0]
//Retorno: 1 se tudo ocorrer bem, -1 em casos de desistencia
int cadastarFuncionario(tFuncionario func[150], int pos){
	int depOK=3;
	int i, j, k, resp;
	char cpf[12];
	printf ("1.1 Cadastrar novo funcionario\n\n");
	printf("Preencha os dados que se pedem a seguir\n\n");
	
	do{
		printf("CPF: ");
		scanf("%s", cpf);
		resp=verificarExistenciaCPF(cpf);//Verifica a existencia do CPF. Retorna 10 se ja existir ou 5 se nao existir
		if(resp==5){
			strcpy(func[pos].cpf, cpf);
		}else if (resp==10){
			printf("CPF %s ja cadastrado!\nDigite 0 para retornar ao menu funcionario ou 1 para digitar um novo cpf: ", cpf);
			scanf("%d", &resp);
		}
		if(resp==0){
			return -1;
		}
	}while(resp==1);
	
	printf ("Nome Completo: ");
	scanf (" %100[^\n]s", &func[pos].nome);

	do{
	printf ("Data de Admissao na empresa: ");
	scanf ("%d%d%d", &func[pos].dt_adm.dia, &func[pos].dt_adm.mes, &func[pos].dt_adm.ano);
	if (valida_data(func[pos].dt_adm.dia, func[pos].dt_adm.mes, func[pos].dt_adm.ano) == 0){
	printf ("Data invalida! Digite novamente\n");
	}
	} while (valida_data(func[pos].dt_adm.dia, func[pos].dt_adm.mes, func[pos].dt_adm.ano) == 0);
	do{
	printf ("Data de Nascimento: ");
	scanf ("%d%d%d", &func[pos].dt_nasc.dia, &func[pos].dt_nasc.mes, &func[pos].dt_nasc.ano);
	if (valida_data(func[pos].dt_nasc.dia, func[pos].dt_nasc.mes, func[pos].dt_nasc.ano)==0){
	printf ("Data invalida! Digite novamente\n");
	}
	} while (valida_data(func[pos].dt_nasc.dia, func[pos].dt_nasc.mes, func[pos].dt_nasc.ano)==0);

	printf ("Codigo do cargo: ");
	scanf ("%d", &func[pos].cargo);
	do{
		printf ("Departamento: ");
		scanf ("%d", &func[pos].dept);
		for(i=0;i<=11;i++){
			if(func[pos].dept==dep[i].cod){ 
				depOK=2;
				break;
			}
		}
		if(depOK==3){
			printf("Departamento %d nao existe!\n", func[pos].dept);
			listarDepartamento();
			printf("\nDigite 0 para retornar ao menu funcionario ou 1 para digitar um novo codigo de departamento: ");
			scanf("%d", &depOK);
			if(depOK==0){
				return -1;
			}
		}
	}while(depOK==1);
	
	j=func[pos].dept;
	for(k=0;k<11;k++){
		if(j==dep[k].cod){
			dep[k].quant++;;
			break;
		}
	}
	system("clear || cls");
	printf("Funcionario cadastrado com sucesso! Verifique seus dados:\n\n");
	mostrarDados(pos);
	controle[1][0]++;
	printf("\nPressione uma tecla para para continuar...");
	getch();
	return 1;
}

//1.2 alterar dados do funcionario
//Objetivo: mostra o menu alterar funcionario se for digitado um cep valido
//Parametros: cpf
//Retorno: resp - a resposta
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
//Retorno: a posicao do funcionario
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
			//printf("%s", cpf);
			return 10; //Se existir
		}
	}
	return 5; //Se nao existir
}
//Objetivo: funcao principal de alterar dados do funcionario
//Parametros: nenhum
//Retorno: 0 se ocorrer tudo de acordo
int funcao_AlterarFuncionario(){
	char cpf[12];
	int i, j;
	int resp, rsp; //rsp PARA O MENU e resp PARA AS CONDICOES DE REPETICAO
	printf("1.2 Alterar dados de um funcionario\n\n");
	printf("Qual o CPF do funcionario? ");
	scanf("%s", &cpf);
	if(alterarFuncionario_CPF(cpf) != -1){
		j=alterarFuncionario_CPF(cpf);
		printf("Menu Alterar Funcionario - CPF %s\n", cpf);
		rsp=menu_AlterarFuncionario(cpf);
	}
	if(alterarFuncionario_CPF(cpf) == -1){
		printf("CPF %s nao cadastrado!\nDigite 0 para retornar ao menu funcionario ou 1 para digitar um novo cpf: ", cpf);
		scanf("%d", &resp);
		if(resp==0){
			return -1;
		}
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
				printf("Esse cpf ja existe.\n1. Digitar outro\n2. Sair\nResposta: ");
				scanf("%d", &resp);
			}
		}while(resp==1);
		printf("\nPressione uma tecla para para continuar...");
		getch();
	}
	if(rsp==2){
		printf("Qual o novo nome? ");
		scanf(" %100[^\n]s", &func[j].nome);
		printf("Nome alterado com sucesso!");
		printf("\nPressione uma tecla para para continuar...");
		getch();
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
		printf("\nPressione uma tecla para para continuar...");
		getch();
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
		printf("\nPressione uma tecla para para continuar...");
		getch();
	}
	if(rsp==5){
		printf("Qual o novo cargo? ");
		scanf("%d", &func[j].cargo);
		printf("Cargo alterado com sucesso!");
		printf("\nPressione uma tecla para para continuar...");
		getch();
	}
	if(rsp==0){
		return 0;
	}
	return 0;
}

//1.3 transferir funcionario

//Objetivo: Procura pelo departamento de origem 
//Parametros: nenhum
//Retorno: retorna a posicao do departamento no vetor dep ou -1 se o usuario desistir
int TransOrigem(){
	int i, cod, resp;
	do{
		printf("Qual o codigo departamento de origem? ");
		scanf("%d", &cod);
		for(i=0;i<11;i++){
			if(dep[i].cod==cod){
				return i;//indice do departamento
			}	
		}
		printf("O departamento %d nao existe!\n", cod);
		listarDepartamento();
		printf("\nDigite 0 para retornar ao menu funcionario ou 1 para digitar um novo codigo de departamento: ");
		scanf("%d", &resp);
		if(resp==0){
			return -1;
		}
	}while(resp==1);
}
//Objetivo: procura um funcionario com o cpf digitado no departamento de origem
//Parametros: nenhum
//Retorno: posicao do funcionario no vetor func ou -1 se o usuario desistir
int TransCPF(){
	int i, cod, resp;
	char cpf[12];
	printf("Digite novamente o departamento de origem para confirmar\n");
	cod=TransOrigem();
	do{
		printf("Qual o cpf do funcionario? ");
		scanf("%s", &cpf);
		for(i=0;i<150;i++){
			if((strcmp(func[i].cpf, cpf)==0)&&(func[i].dept==dep[cod].cod)){
				return i;
			}
		}
		printf("“Departamento %d nao possui funcionario com o cpf %s!\nDigite 0 para retornar ao menu funcionario ou 1 para digitar outro cpf: ", dep[cod].cod, cpf);
		scanf("%d", &resp);
		if(resp==0){
			return -1;
		}
	}while(resp==1);
}
//Objetivo: procura a existencia do departamento de destino
//Parametros: nenhum
//Retorno: retorna a posicao do departamento no vetor dep ou -1 se o usuario desistir
int TransDestino(){
	int i, cod, resp;
	do{
		printf("Qual o codigo departamento de destino? ");
		scanf("%d", &cod);
		for(i=0;i<11;i++){
			if(dep[i].cod==cod){
				return i;//indice do departamento
			}	
		}
		printf("O departamento %d nao existe!\n", cod);
		listarDepartamento();
		printf("\nDigite 0 para retornar ao menu funcionario ou 1 para digitar um novo codigo de departamento: ");
		scanf("%d", &resp);
		if(resp==0){
			return -1;
		}
	}while(resp==1);	
}
//Objetivo: Funcao principal. Altera o departamento de um funcionario
//Parametros: nenhum
//Retorno: -1 pras desistencias dos menus anteriores
int alterarFuncDept(){
	int depOrigem, posFunc, depDestino, i, resp, ok;
	printf("2.3 Alterar funcionario de departamento\n\n");
	depOrigem=TransOrigem();
	if(depOrigem==-1){
		return -1;
	}
	posFunc=TransCPF();
	if(posFunc==-1){
		return -1;
	}
	depDestino=TransDestino();
	if(depDestino==-1){
		return -1;
	}
	func[posFunc].dept=dep[depDestino].cod;//Alterando o Departamento
	printf("Funcionario transferido com sucesso!\n");//Anunciando o sucesso da operacao
	dep[depOrigem].quant=dep[depOrigem].quant-1;//Decrementando o quant do departamento antigo
	dep[depDestino].quant=dep[depDestino].quant+1;//Incrementando o quant do novo departamento
	printf("\nPressione uma tecla para para continuar...");
	getch();
}


//1.4 demitir funcionario
//Objetivo: procura um departamento para a demissao
//Parametros: nenhum
//Retorno: -1 se o usuario desistir
int depDelFunc(){
	int i, cod, resp;
	do{
		printf("Qual o codigo do departamento? ");
		scanf("%d", &cod);
		for(i=0;i<11;i++){
			if(dep[i].cod==cod){
				return i;//indice do departamento
			}	
		}
		printf("O departamento %d nao existe!\n", cod);
		listarDepartamento();
		printf("\nDigite 0 para retornar ao menu funcionario ou 1 para digitar um novo codigo de departamento: ");
		scanf("%d", &resp);
		if(resp==0){
			return -1;
		}
	}while(resp==1);
}
//Objetivo: procura um cpf compativel com o departamento informado
//Parametros: nenhum
//Retorno: -1 para o caso de desistencia
int cpfDelFunc(){
	int i, cod, resp;
	char cpf[12];
	printf("Digite novamente o departamento para confirmar\n");
	cod=depDelFunc();
	do{
		printf("Qual o cpf do funcionario? ");
		scanf("%s", &cpf);
		for(i=0;i<150;i++){
			if((strcmp(func[i].cpf, cpf)==0)&&(func[i].dept==dep[cod].cod)){
				return i;
			}
		}
		printf("“Departamento %d nao possui funcionario com o cpf %s!\nDigite 0 para retornar ao menu funcionario ou 1 para digitar outro cpf: ", dep[cod].cod, cpf);
		scanf("%d", &resp);
		if(resp==0){
			return -1;
		}
	}while(resp==1);
}
//Objetivo: Funcao principal. Demite um funcionario e apaga seus dados
//Parametros:  nenhum
//Retorno: -1 se o usuario desistir
int delFuncionario(){
	printf("1.4 Demitir funcionario\n\n");
	char resp[1];
	int depPos, funcPos, i, pos;
	depPos=depDelFunc();
	if(depPos==-1){
		return -1;
	}
	funcPos=cpfDelFunc();
	if(funcPos==-1){
		return -1;
	}
	printf("Deseja realmente demitir o funcionario? <s/n> ");
	scanf("%s", resp);
	
	if(resp[0]=='n'){
		printf("Funcionario nao demitido!");
		return -1;
	}
	if(resp[0]=='s'){
		pos=controle[1][0];
		for(i=funcPos;i<=pos;i++){
			func[i] = func[i+1];
		}
		controle[1][0]=controle[1][0]-1;
		printf("Funcionario demitido com sucesso!\n");
		dep[depPos].quant=dep[depPos].quant-1;//decrementando o departamento pois um funcionario foi demitido dele
	}
	printf("\nPressione uma tecla para para continuar...");
	getch();
}

//1.5 pesquisar funcionario
//Objetivo: pesquisa um funcionario e exibe os dados
//Parametros: nenhum
//Retorno: nenhum
void pesquisarFuncionario(){
	char cpf[12];
	int i, resp=0;
	printf("1.5 Pesquisar Funcionario\n\n");
	do{
		printf("Qual o CPF do funcionario? ");
		scanf("%s", cpf);
		for(i=0;i<150;i++){
			if(strcmp(func[i].cpf, cpf)==0){
				printf("Funcionario encontrado: \n\n");
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
	printf("\nPressione uma tecla para para continuar...");
	getch();
}

//1.6 listar todos os funcionarios
//Objetivo: lista todos os funcionarios, separando por departamento
//Parametros: cont
//Retorno: nenhum
void listarTodos(int cont){
	int i, j;
	printf ("1.6 Listar todos os funcionarios\n\n");
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
	printf("\nPressione uma tecla para para continuar...");
	getch();
}
//1.7 listar um departamento
//Objetivo: lista apenas um departamento
//Parametros: cont
//Retorno: nenhum
void listarPorDept(int cont){
	int i, j, resp=0, cod;
	printf("1.7 Listar todos de um departamento\n\n");
	printf("Qual o codigo do departamento? ");
	scanf("%d", &cod);
	for(i=0; i<11;i++){
		if(dep[i].cod==cod){
			printf("----------------------------------------\n");
			printf("Departamento %d - %s\n", dep[i].cod, dep[i].nome);
			printf("----------------------------------------\n");
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
	printf("\nPressione uma tecla para para continuar...");
	getch();
}

//2. MENU DEPARTAMENTO e suas funcoes
//Objetivo: Mostrar o menu Departamento
//Parametros: Nenhum
//Retorno: resp - A resposta do usuario, ou seja, a opcao desejada do menu
int menuDepartamento(){
	system("clear || cls");
	int resp;
	printf ("\n\n\t\t2. Menu Departamento\n\n");//#1
	printf("1. Criar departamento\n");//#2
	printf("2. Alterar nome do departamento\n");//#3
	printf("3. Consultar departamento\n");//#4
	printf("4. Listar departamentos\n");//#5
	printf("5. Excluir departamento\n");//#6
	printf("0. Voltar\n\n");//Saida
	printf("Digite sua resposta: ");
	scanf("%d", &resp);
	system ("cls || clear" );
	return resp;
}

//2.1 criar departamento
//Objetivo: Verifica o codigo do departamento
//Parametros: nenhum
//Retorno: o codigo se estiver de acordo ou -1 se o usuario desistir
int criarDepCod(){
	int i, resp, cod;
	do{
		resp=5;
		do{
			printf("Qual o codigo do departamento? ");
			scanf("%d", &cod);
		} while(cod<1);
		for(i=0;i<10;i++){
			if(dep[i].cod == cod){
				printf("O departamento %d ja existe!\nDigite 0 para retornar ao menu departamento ou 1 para digitar um novo codigo\n", cod);
				scanf("%d", &resp);
			}
		}
		if(resp==5){
			return  cod;
		}
		if(resp==0){
			return -1;
		}
	} while(resp==1);
}
//Objetivo: Funcao principal de Criar um departamento
//Parametros: contDep que controla os departamentos cadastrados
//Retorno: retorna o contDep pra fazer incremento ou -1 pra desistencia
int criarDepartamento(int contDep){
	system("clear || cls");
	printf("2.1 Criar Departamento\n\n");
	int i, cod, resp;
	if(contDep==10){//Limita a criacao de departamentos
		printf("Ja existem 10 departamentos. Nao e possivel criar mais");
		printf("\nPressione uma tecla para para continuar...");
		getch();
		return -1;
	}
	cod=criarDepCod();
	if(cod==-1){
		return -1;
	}
	dep[contDep].cod=cod;
	printf("Qual o nome do departamento? ");
	scanf("%s", &dep[contDep].nome);	
	dep[contDep].quant=0;//inicia o departamento com a quantidade de funcs =0
	controle[0][contDep + 1] = dep[contDep].cod;
	controle[1][contDep+1]=-1;
	printf("\nDepartamento criado com sucesso. Pronto para cadastrar funcionarios.\n");
	contDep++;
	printf("\nPressione uma tecla para para continuar...");
	getch();
	return contDep; //Quando for chamado novamente, esse valor retornado eh incrementado no main
	//e volta como parametro.
}


//2.2 alterar nome de departamento
//Objetivo: altera o nome de um departamento
//Parametros: nenhum
//Retorno: nenhum
void alterarNomeDept(){
	system("clear || cls");
	printf("2.2 Alterar nome de Departamento\n\n");
	int cod;
	int i;
	int y=0, n=0, pos;
	int resp;
	do{
		printf("Qual o codigo do departamento? ");
		scanf("%d", &cod);
		for(i=0;i<11;i++){
			if(cod==dep[i].cod){
				y=1;//achou o departamento
				pos=i;
			}               //y=sim, n=nao. 0 e o valor pra nao e 1 pra sim.
			else{
				n=0;//nao achou
			}
		}
		if(y==1){
			printf("Qual o novo nome do departamento? ");
			scanf("%s", dep[pos].nome);
			resp=0;
			printf("Nome alterado com sucesso!\n");
		}
		if((y==0)&&(n==0)){
			printf("O Departamento %d nao existe!\nDigite 0 para retornar ao menu departamento ou 1 para digitar um novo codigo: ", cod);
			scanf("%d", &resp);
		}
	}while(resp==1);
	printf("\nPressione uma tecla para para continuar...");
	getch();
}

//2.3 consultar departamento
//Objetivo: consulta a existencia de um departamento e exibe seus dados
//Parametros: nenhum
//Retorno: -1 pra acabar a funcao quando atingir seu objetivo
int consultarDepartamento(){
	system("clear || cls");
	printf("2.3 Consultar Departamento\n\n");
	int i, cod;
	printf("Qual o codigo do departamento? ");
	scanf("%d", &cod);
	for(i=0;i<11;i++){
		if(dep[i].cod==cod){
			printf("Nome: %s\nQuantidade de funcionarios: %d", dep[i].nome, dep[i].quant);
			return -1;
		}
	}
	printf("Departamento %d nao existe!", cod);
	printf("\nPressione uma tecla para para continuar...");
	getch();
}

//2.4 listar departamentos
//Objetivo: lista todos os departamentos cadastrados
//Parametros: nenhum
//Retorno: nenhum
void listarDepartamento(){
	int i;
	int cont=0;
	for(i=0;i<11;i++){
		if (dep[i].cod>0){		//considerando que os codigos nao sejam negativos
			cont++;             //Esse 'for' serve pra apenas selecionar os departamentos cadastrados na listagem
		}                       //ja que os departamentos estao no vetor dep de forma contigua :)
	}
	printf("Lista de Departamentos cadastrados: ");
	for(i=0;i<cont;i++){
		printf("\nCodigo: %d\nNome: %s\nQuantidade de funcionarios cadastrados: %d\n", dep[i].cod, dep[i].nome, dep[i].quant);
	}
	printf("\nPressione uma tecla para para continuar...");
	getch();
	
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
	printf("2.5 Excluir departamento\n\n");
	do{
		printf("Qual o codigo do departamento? ");
		scanf("%d", &cod);
		for(i=0;i<11;i++){
			if(cod == controle[0][i+1]){
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
							dep[i] = dep[i+1];
						}
						contDep--;
						printf("Departamento excluido com sucesso");
					}
				}
				else if(resp2[0]=='n'){
					resp=1;
					printf("Departamento nao excluido!");
				}
				resp=5;
			}
		}
		if(resp==0){
			printf("Departamento %d nao existe!\nDigite 0 para retornar ao menu departamento ou 1 para digitar um novo codigo: ", cod);
			scanf("%d", &resp);
		}
	}while((resp==1)||(resp3==1));
	printf("\nPressione uma tecla para para continuar...");
	getch();
	return contDep;
}

int main (){

	int contDep=0;
	int aa=0, bb=0, cc=0;
	controle[0][0]=-1;
	while(1) {
		aa=menuPrincipal();
		switch (aa){
			do{
				case 1:	do{
							bb=menuFuncionario();
							switch (bb){
								case 1: if(contDep==0){
											printf("Voce deve cadastrar um departamento primeiro.\n");
											printf("Qualquer tecla para continuar...");
											getch();
										}
										if(contDep>0){
											cadastarFuncionario(func, controle[1][0]);
										}
										break;
								case 2: funcao_AlterarFuncionario();
										break;
								case 3: alterarFuncDept();
										break;
								case 4: delFuncionario();
										break;
								case 5: pesquisarFuncionario();
										break;
								case 6: listarTodos(controle[1][0]);
										break;
								case 7: listarPorDept(controle[1][0]);
										break;
								case 123: testecontrole();
										break;
								case 0: break;
								default: printf ("Erro. Por favor, digite novamente. Dessa vez, use uma opcao valida:\n\n");
							}
						}while(bb!=0); break;
				case 2: do{
						cc=menuDepartamento();
							switch (cc){
								case 1: contDep = criarDepartamento(contDep);
										break;
								case 2: alterarNomeDept();
										break;
								case 3: consultarDepartamento();
										break;
								case 4: system("clear||cls");
										printf("2.4 Listar Departamentos\n\n");
										listarDepartamento();
										break;
								case 5: contDep = excluirDepartamento(contDep);
										break;
								case 0:	break;
								default: printf ("Erro. Por favor, digite novamente. Dessa vez, use uma opcao valida:\n\n");
							}
						}while(cc!=0); break;
				case 0: exit(0);
						break;
				default: system ("clear || cls");
						printf ("Erro. Por favor, digite novamente. Dessa vez, use uma opcao valida:\n\n");
			}while(aa!=0);
		}
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

	struct cadastroDisciplina{
		int codigo;
		char nome[20];
		struct cadastroDisciplina *proximo;
	};
	
	struct cadastroDisciplina *headDisciplina = NULL;
	struct cadastroDisciplina *atualDisciplina = NULL;
	
	struct cadastroEstudante{
		int  codigoAluno;
		char nome[40];
		int  codigoDisc[5];
		struct cadastroEstudante *proximo;
	};
	
	struct cadastroEstudante *headEstudante = NULL;
	struct cadastroEstudante *atualEstudante = NULL;
	

	int indiceNota=0;
	float notas[100][6];
	

/*          ESPECIFICAÇÕES      */

void exibirDisciplinas();
struct cadastroDisciplina* buscarDisciplina(int cod);
void inserirDisciplina(int cod, char* nm);
void disciplina();

void exibirEstudantes();
void inserirEstudante(int codEstu, int codDisc, char* nm);
struct cadastroEstudante* removerEstudante(int cod);
int contarDiscE(int cod);
struct cadastroEstudante* buscarEstudante(int cod);
void estudante();

void inserirNotas(float codAlu,float codDisc,float a1,float a2,float a3,int i);
void alterarNotas();
void nota();
void calculaConceito(float media);


int main (){
	setlocale(LC_ALL, "Portuguese");
	
	int opcao;
	
	do{
	system("cls");
	printf ("\n\n ********** Sistema de Gerenciamento de Aluno ************** \n\n");
	printf ("\n [1]Cadastrar Disciplina \n");
	printf (" [2]Cadastrar Estudante \n");
	printf (" [3]Lançar Nota \n");
	printf (" [4]Alterar Nota \n");
	printf (" [5]Mostrar Relatório dos Estudantes \n");
	printf (" [6]Mostrar Relatório das Disciplinas \n");	
	printf (" [0]Sair \n\n ");
	printf ("Insira a opção desejada: ");
	scanf (" %d", &opcao);
	switch (opcao){
		case 1:
			disciplina();
		break;
		case 2:
			estudante();
		break;
		case 3:
			nota();
		break;
		case 4:
			alterarNotas();
				printf (" . \n");
		break;
		case 5:
				exibirEstudantes();
		break;
		case 6:
			system("cls");
			printf("\n ******* DISCIPLINAS CADASTRADAS *************\n\n");
			exibirDisciplinas();
			break;
		case 0:
			break;
		default: 
			printf (" ERRO: Insira um número válido...");
		break;
	}
	printf("\n\n Pressione qualquer tecla para continuar: ");
	system("pause>null");
	}while (opcao!=0);
	
}

/////////////////////////////////////////// Disciplinas ////////////////////////////////////////

void disciplina(){
 	char continuar;
 	int auxCod;
 	char auxNome[20];
	
		do{
			system("cls");
			printf ("\n Digite um código para a Disciplina(entre 1 e 100): ");
			scanf ("%d", &auxCod);
			while(auxCod<1 || auxCod>100)
			{
				printf ("\n ERRO!!!\n\n Digite um código para a Disciplina(entre 1 e 100): ");
				scanf ("%d", &auxCod);
			}
			printf ("\n Digite um nome para a Disciplina: ");
			setbuf(stdin,NULL);
			gets (auxNome);
			inserirDisciplina(auxCod, &auxNome[0]);	
			printf("\n\n Continuar cadastrando? (s/n): ");
			setbuf(stdin,NULL);
			scanf("%c",&continuar);
			continuar = tolower(continuar);
		}
		while(continuar == 's');
	
		printf ("\n\n Cadastro Concluído.");
}

void inserirDisciplina(int cod, char* nm){
	struct cadastroDisciplina *nodo;
	struct cadastroDisciplina *aux;		
	nodo = (struct cadastroDisciplina*) malloc (sizeof(struct cadastroDisciplina));
	
	if(nodo == NULL)
	{
		printf(" Erro na Alocação de Memória! ");
	}
	else{	
			/*incializando os dados no nó*/
			nodo->codigo= cod;
			strcpy(nodo->nome,nm);
			
			/*apontando para o nó antigo*/
			nodo->proximo= headDisciplina;
		
			/*apontando para o novo nó*/
			headDisciplina= nodo;		
	}
}


struct cadastroDisciplina* buscarDisciplina(int cod){
	
	/*começa a buscar o primeiro nó*/
	struct cadastroDisciplina* atualDisciplina= headDisciplina;
	
	/*verifica se está vazia*/
	if(headDisciplina==NULL){
		return NULL;
	}	
	
	/*navavegando pela lista*/
	while(atualDisciplina->codigo != cod){  /*id= 1*/
	
	/*se for o ultimo nó*/
	if(atualDisciplina->proximo == NULL){
		return NULL;
	}
	else 
		atualDisciplina = atualDisciplina->proximo;
	}
	
	return atualDisciplina;
} 


void exibirDisciplinas()
{
	struct cadastroDisciplina *ptr= headDisciplina;
			
	while (ptr != NULL){
			printf ("\n\t Código da Disciplina: %d   \n\t Nome: %s \n",ptr->codigo,ptr->nome);
			ptr= ptr->proximo;
		}	
}
	
///////////////////////////////////////estudantes////////////////////////////////////////////////////
void estudante(){
	int auxCodAlu, auxCodDisc;
	char auxNome[40];
	cadastroDisciplina* auxValidacao;
	char continuar;
	do
	{
	
 		system("cls");
 		printf("\n ****** CADASTRO DO ESTUDANTE ******\n\n");
		printf ("\n Digite o código do Aluno: ");
		scanf ("%d", &auxCodAlu);
		if(buscarEstudante(auxCodAlu)==NULL)
		{
			printf (" Digite o nome do Aluno: ");
			setbuf(stdin,NULL);
			gets(auxNome);
		}

		printf("\n\n Disciplinas Disponíveis:\n");
		exibirDisciplinas();
		printf ("\n\n Digite o Código da Disciplina para efetuar a matrícula: ");
		scanf ("%d", &auxCodDisc);
		auxValidacao = buscarDisciplina(auxCodDisc);
		while(auxValidacao == NULL)
		{
			printf("\n\n\n DISCIPLINA NÃO ENCONTRADA!!!");
			printf("\n\n Disciplinas disponíveis:\n");
			exibirDisciplinas();
			printf ("\n Digite o Código da Disciplina desejada para efetuar a matrícula: ");
			scanf ("%d", &auxCodDisc);
			auxValidacao = buscarDisciplina(auxCodDisc);
		}
		inserirEstudante(auxCodAlu,auxCodDisc,&auxNome[0]);
		
		printf("\n Deseja continuar cadastrando? (s/n): ");
		setbuf(stdin,NULL);
		scanf("%c",&continuar);
		continuar = tolower(continuar);
	}while(continuar == 's');
	printf ("\n\n Cadastro Concluído. \n\n");
}

struct cadastroEstudante* buscarEstudante(int cod){
	/*começa a buscar o primeiro nó*/
	struct cadastroEstudante* atualEstudante= headEstudante;
	
	/*verifica se está vazia*/
	if(headEstudante==NULL){
		return NULL;
	}	
	
	/*navavegando pela lista*/
	while(atualEstudante->codigoAluno != cod){  /*id= 1*/
	
	/*se for o ultimo nó*/
	if(atualEstudante->proximo == NULL){
		return NULL;
	}
	else 
		atualEstudante = atualEstudante->proximo;
	}
	
	return atualEstudante;
} 


int contarDiscE(int cod){
	int qtd = 0;
	/*começa a buscar o primeiro nó*/
	struct cadastroEstudante* atualEstudante= headEstudante;
	
	/*verifica se está vazia*/
	if(headEstudante==NULL){
		return NULL;
	}	
	
	/*navavegando pela lista*/
	while(atualEstudante->codigoAluno != cod){  /*id= 1*/
	
	/*se for o ultimo nó*/
	if(atualEstudante->proximo == NULL){
		return NULL;
	}
	else 
		atualEstudante = atualEstudante->proximo;
	}
	
	int i = 0;
	while(atualEstudante->codigoDisc[i]!=NULL)
	{
		qtd++;
		i++;
	}
	
	
	return qtd;
} 
	
//remover um nodo de acordo com o id
struct cadastroEstudante* removerEstudante(int cod) 
{
	 //inicia no primeiro nodo
 	struct cadastroEstudante* atualEstudante = headEstudante;
 	struct cadastroEstudante* anteriorEstudante = NULL;
 	//se a lista estiver vazia
 	if(headEstudante == NULL) {
 		return NULL;
 	}
 	//navega pela lista
 	while(atualEstudante->codigoAluno != cod) {///////////////////////////////////
 		//se for o último nó
 		if(atualEstudante->proximo == NULL) {
 			return NULL;
 		} 
		else 
		{
 			//armazena referência para o nodo atual
 			anteriorEstudante = atualEstudante;
 			//move para o próximo nodo
 			atualEstudante = atualEstudante->proximo;
 		}
 	}
 	//found a match, update the nodo
 	if(atualEstudante == headEstudante) 
	{
 		//encontrou uma correspondência, atualize o nodo
 		headEstudante = headEstudante->proximo;
 	} 
	else 
	{
 		//ignorar o nodo atual
 		anteriorEstudante->proximo = atualEstudante->proximo;
 	}
 	return atualEstudante;
}


void inserirEstudante(int codEstu, int codDisc, char* nm)
{
	int cont;
	cadastroEstudante* auxDel;
	cadastroEstudante* validacaoE;
	validacaoE = buscarEstudante(codEstu);
	struct cadastroEstudante *nodo;
	struct cadastroEstudante *aux;		
	nodo = (struct cadastroEstudante*) malloc (sizeof(struct cadastroEstudante));
		
	
	if(validacaoE == NULL)
	{
		for(int i = 0;i<5;i++)
			nodo->codigoDisc[i]=NULL;
			
			
		if(nodo == NULL)
		{
			printf("Erro na Alocação de Memória!");
		}
		else{	
			/*incializando os dados no nó*/
			nodo->codigoAluno = codEstu;
			strcpy(nodo->nome,nm);
			cont = contarDiscE(codEstu);
			nodo->codigoDisc[cont] = codDisc;
			/*apontando para o nó antigo*/
			nodo->proximo= headEstudante;
			/*apontando para o novo nó*/
			headEstudante= nodo;	
		}
	}	
	else
	{///////////////////////////////////////////////////////////////obter, apagar e reescrever
		if(nodo == NULL)
		{
			printf("Erro na Alocação de Memória!");
		}
		else{	
			/*incializando os dados no nó*/
			auxDel = removerEstudante(codEstu);
			nodo = auxDel;
			nodo->codigoDisc[cont+1] = codDisc;
			/*apontando para o nó antigo*/
			nodo->proximo= headEstudante;
			/*apontando para o novo nó*/
			headEstudante= nodo;
		}
	}
	
}

void exibirEstudantes()
{
	int qtd =0;
	char conceito;
	int achou=0;
	float fcodE,fcodD;
	int icodE,icodD;
	struct cadastroDisciplina *resultadoBusca;
	struct cadastroEstudante *ptr = headEstudante;
			
	while (ptr != NULL){
			printf("\n\n------------------------------------------------------------------------\n\n");
			printf("\n Código do Aluno: %d",ptr->codigoAluno);
			printf("\n Nome do Aluno: %s",ptr->nome);
			qtd = contarDiscE(ptr->codigoAluno);
			for(int i = 0;i<qtd;i++)
			{
				resultadoBusca = buscarDisciplina(ptr->codigoDisc[i]);
				printf("\n Disciplina Matrículada: %s",resultadoBusca->nome);
				for(int x = 0;x<200;x++)
				{
					////////////////////////////////////
					icodE = ptr->codigoAluno;
					icodD = ptr->codigoDisc[i];
					fcodE = (float) icodE;
					fcodD = (float) icodD;
					if((notas[x][0]==fcodE)&&(notas[x][1]==fcodD))
					{
						achou = 1;
						printf("\n\n A1: %.2f \n A2: %.2f \n A3: %.2f",notas[x][2],notas[x][3],notas[x][4]);
						printf("\n\n Média: %.2f  -  ",notas[x][5]);
						calculaConceito(notas[x][5]);
					}
				}
				if(achou == 0)
					printf("\n\n\t\t Disciplina ainda não avaliada!");
				achou = 0;
			}
			//printf("\nd1: %d\nd2: %d",ptr->codigoDisc[0],ptr->codigoDisc[1]);
			ptr= ptr->proximo;
			
		}	
}

////////////////////////////notas///////////////////////////////////////////

void nota(){
	int discCursando[5];
	int auxCod;
	int auxDisc;
	float a1,a2,a3;
	cadastroEstudante* auxValidacaoE;
	cadastroDisciplina* auxValidacaoD;
	
	printf("\n Insira o Código do Aluno: ");
	scanf("%d",&auxCod);
	auxValidacaoE = buscarEstudante(auxCod);
	while(auxValidacaoE == NULL)
	{
		printf("\n\nERRO!!!\n Insira o Código do Aluno: ");
		scanf("%d",&auxCod);
		auxValidacaoE = buscarEstudante(auxCod);	
	}
	for(int i = 0;i<5;i++)
	{
		discCursando[i] = auxValidacaoE->codigoDisc[i];
	}
	printf("\n Insira o Código da Disciplina: ");
	scanf("%d",&auxDisc);
	while(auxDisc<1 || auxDisc>100)
	{
		printf ("\nERRO!!!\n\n Digite um Código para a Disciplina (entre 1 e 100): ");
		scanf ("%d", &auxDisc);
	}
	
	while((auxDisc != discCursando[0])&&(auxDisc != discCursando[1])&&(auxDisc != discCursando[2])&&(auxDisc != discCursando[3])&&(auxDisc != discCursando[4])&&(auxDisc != discCursando[5]))
	{
		printf("\n ERRO!!! O Aluno não cursa essa Disciplina.\n\n Insira o código da disciplina: ");
		scanf("%d",&auxDisc);
		auxValidacaoD = buscarDisciplina(auxDisc);
	}
	
	//auxValidacaoD = buscarDisciplina(auxDisc);
/*	while(auxValidacaoD == NULL)
	{
		printf("\nERRO!!!Insira o código da disciplina: ");
		scanf("%d",&auxDisc);
		auxValidacaoD = buscarDisciplina(auxDisc);
	}*/
	
	printf("\n Insira a nota da primeira avaliação: ");
	scanf("%f",&a1);
	while((a1<0)||(a1>10))
	{
		printf("\n ERRO!!! Insira a nota da primeira avaliação: ");
		scanf("%f",&a1);
	}
	
	printf("\n Insira a nota da segunda avaliação: ");
	scanf("%f",&a2);
	while((a2<0)||(a2>10))
	{
		printf("\n ERRO!!! Insira a nota da segunda avaliação: ");
		scanf("%f",&a2);
	}
	
		printf("\n Insira a nota da terceira avaliação: ");
	scanf("%f",&a3);
	while((a3<0)||(a3>10))
	{
		printf("\n ERRO!!! Insira a nota da terceira avaliação: ");
		scanf("%f",&a3);
	}
	inserirNotas(auxCod,auxDisc,a1,a2,a3,indiceNota);
	
	//for(int i = 0;i<5;i++)
//	{
	//	printf("\n%f",notas[indiceNota][i]);
//	}

	indiceNota++;		
}

void alterarNotas()
{
	int discCursando[5];
	int achou = 0;
	cadastroEstudante* auxValidacaoE;
	cadastroDisciplina* auxValidacaoD;
	float auxNota,media;
	float codAlu;
	int op;
	float codDisc;
	system("cls");
	printf("\n Insira o Código do Aluno: ");
	scanf("%f",&codAlu);
	auxValidacaoE = buscarEstudante(codAlu);
	while(auxValidacaoE == NULL)
	{
		printf("\n\n ERRO!!!\n Insira o Código do Aluno: ");
		scanf("%f",&codAlu);
		auxValidacaoE = buscarEstudante(codAlu);	
	}
	for(int i = 0;i<5;i++)
	{
		discCursando[i] = auxValidacaoE->codigoDisc[i];
	}
	printf("\n Insira o Código da Disciplina: ");
	scanf("%f",&codDisc);
	while((codDisc != discCursando[0])&&(codDisc != discCursando[1])&&(codDisc != discCursando[2])&&(codDisc != discCursando[3])&&(codDisc != discCursando[4])&&(codDisc != discCursando[5]))
	{
		printf("\n ERRO!!!O Aluno não cursa essa Disciplina.\n\n Insira o Código da Disciplina: ");
		scanf("%f",&codDisc);
		while(codDisc<1 || codDisc>100)
		{
			printf ("\n ERRO!!!\n\n Digite um Código para a Disciplina (entre 1 e 100): ");
			scanf ("%f", &codDisc);
		}
	}
	for(int i = 0;i<200;i++)
	{
		if((notas[i][0]==codAlu)&&(notas[i][1]==codDisc))
		{
			achou = 1;
			printf("\n\tA1: %.2f,  A2: %.2f, A3: %.2f",notas[i][2],notas[i][3],notas[i][4]);
			printf ("\n\n [1] - A1 \n");
			printf (" [2] - A2 \n");
			printf (" [3] - A3 \n");
			printf("\n\n Digite o Número correspondente a Nota em que deseja mudar: ");
			scanf("%d",&op);
			while((op!=0)&&(op!=1)&&(op!=2)&&(op!=3))
			{
				printf("\n\n ERRO!!!\n\n Digite a opcão desejada: ");
				scanf("%d",&op);
			}
			switch(op)
			{
				case 1:
					printf("\n Insira a nova nota para a A1: ");
					scanf("%f",&auxNota);
					while((auxNota<0)||(auxNota>10))
					{
						printf("\n ERRO!!!\n\n Insira a nova ota para a A1: ");
						scanf("%f",&auxNota);
					}
					notas[i][2] = auxNota;
					break;
				case 2:
					printf("\n Insira a nova nota para a A2: ");
					scanf("%f",&auxNota);
					while((auxNota<0)||(auxNota>10))
					{
						printf("\n ERRO!!!\n\n Insira a nova nota para a A2: ");
						scanf("%f",&auxNota);
					}
					notas[i][3] = auxNota;
					break;
				case 3:
					printf("\n Insira a nova nota para a A3: ");
					scanf("%f",&auxNota);
					while((auxNota<0)||(auxNota>10))
					{
						printf("\n ERRO!!!\n\n Insira a nova nota para a A3: ");
						scanf("%f",&auxNota);
					}
					notas[i][4] = auxNota;
					break;
				default:
					printf("\n Opção Inválida!");
					break;
			}
			media = (notas[i][2]+notas[i][3]+notas[i][4])/3;
			notas[i][5] = media;
		}
	}
	if(achou == 0)
	{
		printf("\n\n Não existem Notas para alterar! ");
	}
//	auxValidacaoD = buscarDisciplina(codDisc);
	
}

void inserirNotas(float codAlu,float codDisc,float a1,float a2,float a3,int i)
{
	float media;
	notas[i][0] = codAlu;
	notas[i][1] = codDisc;
	notas[i][2] = a1;
	notas[i][3] = a2;
	notas[i][4] = a3;
	media = (a1+a2+a3)/3;
	notas[i][5] = media;
}
void calculaConceito(float media)
{
	char conceito;
	if(media>=8.5)
		conceito = 'A';
	else
		if(media>=7)
		conceito = 'B';
		else
			if(media>=6)
			conceito = 'C';
			else 
				if(media >=4)
				conceito = 'D';
				else
				conceito = 'F';
	printf("Conceito: %c",conceito);
	if((conceito == 'D')||(conceito == 'F'))
		printf(" - Reprovado\n");
	else
		printf(" - Aprovado\n");
}

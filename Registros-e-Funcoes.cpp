#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string.h>
#include "Registros-e-Funcoes.h"
using namespace std;


/*===================================================================================================================================================================================================*/
/*=========================================================================FUNÇÕES DO GERADOR DE CARTAS==============================================================================================*/
/*===================================================================================================================================================================================================*/

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------FUNÇÃO QUE ZERA O VETOR------------------------------------------------------------------------------*/
void ZeraVetor(Cartas* posicao)
{
	for (int n = 0; n < 32; n++)			//usando o laço para para colocar 0 em todas as posições do vetor.
	{
		strcpy(posicao[n].nome, "0");
		posicao[n].ataque = 0;
		posicao[n].defesa = 0;
		posicao[n].numestrelas = 0;

	}
}


/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------FUNÇÃO QUE EXIBE A DIVISÃO DE TELA------------------------------------------------------------------*/
void Exibedivisao(int n)		
{
	for (int v = 0; v <= n; v++)		//criando um ção para exibir o mesmo carctere 16 vezes
	{
		cout << "-";
	}
	cout << endl;					//colocando uma quebra de linha no final
}


/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------FUNÇÃO QUE FAZ O GERADOR DE CARTAS------------------------------------------------------------------*/
void GeradordeCartas(char* alternativa)		
{
	cout << "Gerador de cartar\n";			//menagem inicial.
	Exibedivisao(16);						//chamando a função que exibe a divisão de tela.

	cout << "(C)adastrar\n(I)mportar\n(A)lterar\n(E)xcluir\n(L)istar\n(S)air\n\n";		//perguntando o que o usuário quer fazer.
	
	cout << "Escolha uma opção [ ]\b\b";		//lendo a opção digitada.
	cin >> alternativa;
	cout << "\n\n";

}


/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------FUNÇÃO QUE ADASTRA UMA CARTA------------------------------------------------------------------------*/
unsigned short Cadastro(Cartas* carta, int posicao)
{
	unsigned short umacarta = 1;			//uma variavel que vai representar a carta somada no baralho.

	cout << "Cadastrar Carta\n";			//mensaguem inicial.
	Exibedivisao(16);

	cout << "Nome       : ";				//perguntando o nome da carta.
	cin >> carta[posicao].nome;
	cout << "Ataque     : ";				//perguntando o valor de ataque da carta.
	cin >> carta[posicao].ataque;
	cout << "Defesa     : ";				//perguntando o valor de defesa da carta.
	cin >> carta[posicao].defesa;
	cout << "Estrelas   : ";				//perguntando o número de estrelas da carta
	cin >> carta[posicao].numestrelas;
	cout << endl;							//terminando com um endl.

	return umacarta;
}


/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------FUNÇÃO QUE iMPORTA CARTAS---------------------------------------------------------------------------*/
unsigned short Importar(Cartas* carta, int posicao)
{
	ifstream fin;								//variavel que vai fazer a leitura do arquivo .txt.
	char arquivo[30], cabecalho[8];				//vetores que vão guardar o nome do arquivo e ver se o cabeçalho do arquivo está correto.
	string compara;								//variavel da biblioteva da string para comparar se o cabeçalho do arquito tem a palabra BARALHO.
	unsigned short quantidade;					//guarda a qutidade de cartas que se tem no arquivo.

	cout << "Importar Cartas\n";				//mensaguem inicial.
	Exibedivisao(16);							//chamando a função que faza divisão de tela.

	cout << "Arquivo: ";						//perguntando ao usuário o nome do arquivo que ele quer abrir para obter a novas cartas.
	cin >> arquivo;
	
	fin.open(arquivo);							//abrindo o arquivo que o usuário deseja.


	if (!fin.is_open())			//verificando se o arquivo abriu com não.
	{
		cout << "A abertura do arquivo " << arquivo << " falhou!" << endl;			//mensaguem caso o aarquivo não abra.
		cout << "Programa encerrando.\n";
		exit(EXIT_FAILURE);															//encerrando o programa com erro.
	}
	else
	{
		fin >> cabecalho;		//lendo o cabeçalho do arquivo.
		fin >> quantidade;		//lendo a qunatidade de cartas que tem no arquivo.

		compara = cabecalho;	//colocando o cabeçalho lido em uma variavel do tipo string para comparar a stringo toda de uma vez.
		
			if (compara.compare("BARALHO") == 0)					//comparando o cabeçalho lido com a string BARALHO e se for igual a condição é aceita.
			{
				cout << "\n\nImportando: \n";						

					for (int n = 0; n < quantidade; n++, posicao++)		//criando laço para ler os dados do arquivo e colocá-los no vetor
					{
						fin >> carta[posicao].nome;						//lendo os dados do arquivo e colocando no vetor de a cordo com a posição recebida da função main.
						fin >> carta[posicao].ataque;
						fin >> carta[posicao].defesa;
						fin >> carta[posicao].numestrelas;

						cout << carta[posicao].nome << " ";				//exibindo os dados do vetor;
						cout << carta[posicao].ataque << " ";
						cout << carta[posicao].defesa << " ";
						cout << carta[posicao].numestrelas << endl;
					}
		
			}
			else													//fechando caso o arquivo tenha o cabeçalho errado.
			{
				cout<< "A abertura do arquivo " << arquivo << " falhou!" << endl;
				cout << "O cabeçalho está incorreto. Corrija-o para 'BARALHO' e tente novamente." << endl;
				cout << "Programa encerrando.\n";
				exit(EXIT_FAILURE);

			}
	}

	fin.close();								//fechando o arquivo.
	cout << "\n\n";
	return quantidade;							//retornando a quantidade de cartas adicionadas ao vetor.
}


/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------FUNÇÃO QUE ALTERA UMA CARTA-------------------------------------------------------------------------*/
void Alterar(Cartas* carta)
{
	int cartaalterada;					//variavel que vai guardar a posição a ser alterada do vetor.

	cout << "Atualizar Cartas\n";		//mensagem inicial.
	Exibedivisao(16);
	
	for(int n=0; carta[n].nome[0] != '0'; n++)					//exibindo os nmes das cartas que estão no vetor.Usando uma posição que contem 0 no vetor para parar o laço.
	{
		cout << n + 1 << ") " << carta[n].nome << endl;		//exibindo o nome das cartas.
	} 

	cout << "Digite o número da carta: [  ]\b\b\b";		//perguntando o número da carta paraser alterada.
	cin >> cartaalterada;

	cartaalterada--;									//tirando 1 do valor digitado pelo usuário pois o vetor começa sempre com posição 0.

	cout << "\nAlterando Carta " << carta[cartaalterada].nome << endl;		//exibindo o nome da carta a ser alterada. 
	cout << "Nome     : ";													//perguntando o novo nome.
	cin >> carta[cartaalterada].nome;
	cout << "Ataque   : ";													//perguntando o novo nivel de ataque.
	cin >> carta[cartaalterada].ataque;
	cout << "Defesa   : ";													//perguntando o novo nivel de defesa.
	cin >> carta[cartaalterada].defesa;
	cout << "Estrelas : ";													//perguntando o novo número de estrelas.
	cin >> carta[cartaalterada].numestrelas;

	cout << "\n\n";
}


/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------FUNÇÃO QUE EXCLUI UMA CARTA-------------------------------------------------------------------------*/
void Excluir(Cartas* carta)
{
	int posicaodeexculsao;				//variavel que vai guardar a posição da carta a ser excluida.
	char nomedacartaexcluida[20];		//criando vetor para guarda o nome da carta e exibi-lo depsi da exclusão.

	cout << "Excluir Carta\n";
	Exibedivisao(16);

	for (int n = 0; carta[n].ataque != 0; n++)				//exibindo os nmes das cartas que estão no vetor.Usando uma posição que contem 0 no vetor para parar o laço.
	{
		cout << n + 1 << ") " << carta[n].nome << endl;		//exibindo o nome das cartas.
	}

	cout << "Digite o número da carta: [  ]\b\b\b";				//perguntando qual carta deve se excluida.
	cin >> posicaodeexculsao;

	posicaodeexculsao--;									//tirando 1 do valor digitado pelo usuário pois o vetor começa sempre com posição 0.					

	strcpy(nomedacartaexcluida, carta[posicaodeexculsao].nome);		//copiando o nome da carta que se deseja excluir.

	for (int n = posicaodeexculsao; n < 32; n++)		//criando um laço para que as cartas anteriores a carta que se vai excluir subam uma posição.
	{
		strcpy(carta[n].nome, carta[n + 1].nome);
		carta[n].ataque = carta[n + 1].ataque;
		carta[n].defesa = carta[n + 1].defesa;
		carta[n].numestrelas = carta[n + 1].numestrelas;
	}

	cout << "Carta " << nomedacartaexcluida << " foi excluída do baralho.\n\n\n";			//exibindo o nome da carta excluida.
}


/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------FUNÇÃO QUE LISTA TODAS AS CARTAS--------------------------------------------------------------------*/
void Listar(Cartas* baralho, int quantidade)
{
	cout << "Cartas no Baralho\n";					//mensagem inicial.
	Exibedivisao(16);

	for (int n = 0; n < quantidade; n++)			//criando laço para exibir tudo no vetor
	{
		cout << "#" << n + 1 << " "
			<< baralho[n].nome << " "		//exibindo nome.
			<< baralho[n].ataque << " "						//exibindo ataque.
			<< baralho[n].defesa << " "						//exibindo defesa
			<< baralho[n].numestrelas << endl;				//exibindo número de estrelas.
	}

	cout << "\n\n";
}



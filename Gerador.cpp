#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "Registros-e-Funcoes.h"
using namespace std;


int main()
{
	SetConsoleCP(1252);					//usando da biblioeca Windows.h para poder ler e exibis palavras com a entua��o correta.
	SetConsoleOutputCP(1252);

	ifstream fin;										//criando variavel do tipo ifstream para poder ler do arquivo.
	ofstream fout;										//criando variavel do tipo ofstream para poder escrever no arquivo.
	Cartas baralho[32];									//vetor de tamanho 32 para guardar todas as cartas.
	char nome[8] = "BARALHO", alternativa = 'A';
	unsigned short NumCartas = 0;						//n�mero de cartas do arquivo.
	int posicao = 0;									//variavel que vai dizer em qual posi��o do vetor se coloca a nova carta ou onde se deve alterar.
	unsigned short cartasadicionadas;					//variavel que guarda a quantidade de cartas adicionadas pelas fun��es.

	ZeraVetor(baralho);									//colocando 0 em tudo no vetor baralho.

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------VERIFICANDO SE O ARQUIVI J� EXISTE---------------------------------------------------------------------------------------*/


	fin.open("../Baralho.dat", ios_base::in | ios_base::binary);		//abrindo o arquivo para a leitura das cartas

	
	if (fin.is_open())			//testando se a abertura do arquivo foi bem sucedida.
	{
		cout << "Abrindo arquivo das cartas....\n";					//mensaguem de espera.
		
		fin.read((char*)&nome, sizeof(char) * 7);					//lendo o cabe�alho do arquivo bin�rio.
		fin.read((char*)&NumCartas, sizeof(unsigned short));
		fin.read((char*)&baralho, sizeof(Cartas) * NumCartas);

		fin.close();												//como j� foi lido tudo do arquivo e salvo no vetor e nas variaveis de cabe�alho, o arquivo de leitura pode ser fechado.

		string compara = nome;

			if (compara.compare("BARALHO") == 0)
			{
				posicao = NumCartas;							//variavel que vai dizer em qual posi��o do vetor se coloca a nova carta ou onde se deve alterar.


				cout << "                                                 Bem vindo!! :)\n";															//mensaguem inicial.
				cout << "       Aqui voc� pode adiconar novas cartas para o seu jogo, ou atualizar o baralho que voc� j� possui\n";
				cout << "OBS: Para importar cartas � preciso de um arquivo .txt com o cabe�alho BARALHO e o n�mero de cartas que ele tem\n"
					<< "   Voc� pode usar o arquivo que j� temos disponivel, ele se chama - maiscartas.txt -, use ele pra come�ar.\n\n" << endl;

					do
					{
						cout << "Gerador de cartar\n";				//menagem inicial.
						Exibedivisao(16);							//chamando a fun��o que exibe a divis�o de tela.

						cout << "(C)adastrar\n(I)mportar\n(A)lterar\n(E)xcluir\n(L)istar\n(S)air\n\n";		//perguntando o que o usu�rio quer fazer.

						cout << "Escolha uma op��o [ ]\b\b";		//lendo a op��o digitada.
						cin >> alternativa;
						cout << "\n\n";


							if (alternativa == 'C')		//se o que for retornado da fun��o for C � cadastrada uma nova carta.
							{
								cartasadicionadas = Cadastro(baralho, posicao);			//chamando a fun��o que cadastra uma nova carta.
								NumCartas = NumCartas + cartasadicionadas;
								posicao = NumCartas + posicao;							//posicao via ser somada com o n�mero de cartas para que as proximas cartas sejam guardadas na proximas posi��es do vetor.
							}

							if (alternativa == 'I')		//se o que for retronado da fun��o for I � importado cartas de um arquivo que o usu�rio digita o nome.
							{
								cartasadicionadas = Importar(baralho, posicao);			//chamando a fun��o que importa cartas de um arquivo.
								NumCartas = NumCartas + cartasadicionadas;				//adicionando a quantidade de cartas importadas ao n�mero total de cartas.
								posicao = NumCartas + posicao;							//posicao via ser somada com o n�mero de cartas para que as proximas cartas sejam guardadas na proximas posi��es do vetor.
							}

							if (alternativa == 'A')		//se o que for retornado for A, uma carta ser� alterada no baralho.
							{
								Alterar(baralho);										//chamando a fun��o que altera uma carta do baralho
							}

							if (alternativa == 'E')		//se o que for retornado for E, uma carta � excluida do baralho.
							{
								Excluir(baralho);										//chamando a fun��o que exclui a carta.
								NumCartas--;											//excluido 1 da quantidade de cartas.
								posicao--;												//exclindo 1 do n�mero de posi��es no vetor.
							}

							if (alternativa == 'L')		//se o que for retornado for L, � listado todas as cartas do baralho.
							{
								Listar(baralho, NumCartas);								//chamandoa fun��o que exibe todas as cartas do baralho.
							}


					} while (alternativa != 'S');		//la�o se repete at� que se digite S
			}
			else
			{
				cout << "A abertura do arquivo Baralho.dat falhou!" << endl;										//exibindo mendaguem de erro.
				cout << "O cabe�alho est� incorreto. Corrija-o para 'BARALHO' e tente novamente." << endl;
				cout << "Programa encerrando.\n";
				exit(EXIT_FAILURE);
			}

		fout.open("../Baralho.dat", ios_base::trunc | ios_base::out | ios_base::binary);	//abrindo o arquivo para a escrita. Limpando o que se tem nele e gravando os novos dados.
		fout.write((char*)&nome, sizeof(char[7]));										//gravando no arquivo no cabe�alho BARALHO.
		fout.write((char*)&NumCartas, sizeof(unsigned short));							//gravando no arquino o n�mero de cartas que tem no arquivo.
		fout.write((char*)&baralho, sizeof(Cartas) * NumCartas);						//gravando no arquivo as cartas que est�o contidas no vetor baralho.
		fout.close();																	//fechando o arquivo bin�rio de escrita.


		cout << "Obrigado por me usar!!\nTudo foi feito e salvo no arquivo.\nSe divirta no jogo. :)\n\n";		//mensagem final do programa.

		system("pause");
		return 0;

	}
	else         //-------------------------------------------------------SE N�O EXISTIR O ARQUIVO � CRIADO------------------------------------------------------------------------------------
	{
		posicao = 0;									//variavel que vai dizer em qual posi��o do vetor se coloca a nova carta ou onde se deve alterar.


		cout << "                                                 Bem vindo!! :)\n";																//mensaguem inicial.
		cout << "       Aqui voc� pode adiconar novas cartas para o seu jogo, ou atualizar o baralho que voc� j� possui\n";
		cout << "       Como voc� ainda n�o tem um arquivo com cartas vamos come�ar criando um e cadastrando as cartas.\n";
		cout << "OBS: Para importar cartas � preciso de um arquivo .txt com o cabe�alho BARALHO e o n�mero de cartas que ele tem\n"
			<< "   Voc� pode usar o arquivo que j� temos disponivel, ele se chama - maiscartas.txt -, use ele praa come�ar.\n\n" << endl;

			do
			{
				cout << "Gerador de cartar\n";				//menagem inicial.
				Exibedivisao(16);							//chamando a fun��o que exibe a divis�o de tela.

				cout << "(C)adastrar\n(I)mportar\n(A)lterar\n(E)xcluir\n(L)istar\n(S)air\n\n";		//perguntando o que o usu�rio quer fazer.

				cout << "Escolha uma op��o [ ]\b\b";		//lendo a op��o digitada.
				cin >> alternativa;
				cout << "\n\n";


					if (alternativa == 'C')										//se o que for retornado da fun��o for C � cadastrada uma nova carta.
					{
						cartasadicionadas = Cadastro(baralho, NumCartas);		//chamando a fun��o que cadastra uma nova carta.
						NumCartas = NumCartas + cartasadicionadas;
						posicao = NumCartas + posicao;							//posicao via ser somada com o n�mero de cartas para que as proximas cartas sejam guardadas na proximas posi��es do vetor.
					}

					if (alternativa == 'I')		//se o que for retronado da fun��o for I � importado cartas de um arquivo que o usu�rio digita o nome.
					{
						cartasadicionadas = Importar(baralho, posicao);			//chamando a fun��o que importa cartas de um arquivo.
						NumCartas = NumCartas + cartasadicionadas;				//adicionando a quantidade de cartas importadas ao n�mero total de cartas.
						posicao = NumCartas + posicao;							//posicao via ser somada com o n�mero de cartas para que as proximas cartas sejam guardadas na proximas posi��es do vetor.
					}

					if (alternativa == 'A')		//se o que for retornado for A, uma carta ser� alterada no baralho.
					{
						Alterar(baralho);										//chamando a fun��o que altera uma carta do baralho
					}

					if (alternativa == 'E')		//se o que for retornado for E, uma carta � excluida do baralho.
					{
						Excluir(baralho);										//chamando a fun��o que exclui a carta.
						NumCartas--;											//excluido 1 da quantidade de cartas.
						posicao--;												//exclindo 1 do n�mero de posi��es no vetor.
					}

					if (alternativa == 'L')		//se o que for retornado for L, � listado todas as cartas do baralho.
					{
						Listar(baralho, NumCartas);								//chamandoa fun��o que exibe todas as cartas do baralho.
					}

					

			} while (alternativa != 'S');		//la�o se repete at� que se digite S



			fout.open("Baralho.dat", ios_base::out | ios_base::app | ios_base::binary);		//abrindo arquivo bin�rio.

			fout.write((char*)&nome, sizeof(char[7]));										//gravando no arquivo no cabe�alho BARALHO.
			fout.write((char*)&NumCartas, sizeof(unsigned short));							//gravando no arquino o n�mero de cartas que tem no arquivo.
			fout.write((char*)&baralho, sizeof(Cartas) * NumCartas);						//gravando no arquivo as cartas que est�o contidas no vetor baralho.
			
			fout.close();																	//fechando o arquivo bin�rio.


			cout << "Obrigado por me usar!!\nTudo foi feito e salvo no arquivo.\nSe divirta no jogo. :)\n\n";		//mensagem final do programa.
			
			system("pause");
			return 0;
	}
	
	return 0;
}
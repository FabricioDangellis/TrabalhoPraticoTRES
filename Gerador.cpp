#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "Registros-e-Funcoes.h"
using namespace std;


int main()
{
	SetConsoleCP(1252);					//usando da biblioeca Windows.h para poder ler e exibis palavras com a entuação correta.
	SetConsoleOutputCP(1252);

	ifstream fin;										//criando variavel do tipo ifstream para poder ler do arquivo.
	ofstream fout;										//criando variavel do tipo ofstream para poder escrever no arquivo.
	Cartas baralho[32];									//vetor de tamanho 32 para guardar todas as cartas.
	char nome[8] = "BARALHO", alternativa = 'A';
	unsigned short NumCartas = 0;						//número de cartas do arquivo.
	int posicao = 0;									//variavel que vai dizer em qual posição do vetor se coloca a nova carta ou onde se deve alterar.
	unsigned short cartasadicionadas;					//variavel que guarda a quantidade de cartas adicionadas pelas funções.

	ZeraVetor(baralho);									//colocando 0 em tudo no vetor baralho.

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------VERIFICANDO SE O ARQUIVI JÁ EXISTE---------------------------------------------------------------------------------------*/


	fin.open("../Baralho.dat", ios_base::in | ios_base::binary);		//abrindo o arquivo para a leitura das cartas

	
	if (fin.is_open())			//testando se a abertura do arquivo foi bem sucedida.
	{
		cout << "Abrindo arquivo das cartas....\n";					//mensaguem de espera.
		
		fin.read((char*)&nome, sizeof(char) * 7);					//lendo o cabeçalho do arquivo binário.
		fin.read((char*)&NumCartas, sizeof(unsigned short));
		fin.read((char*)&baralho, sizeof(Cartas) * NumCartas);

		fin.close();												//como já foi lido tudo do arquivo e salvo no vetor e nas variaveis de cabeçalho, o arquivo de leitura pode ser fechado.

		string compara = nome;

			if (compara.compare("BARALHO") == 0)
			{
				posicao = NumCartas;							//variavel que vai dizer em qual posição do vetor se coloca a nova carta ou onde se deve alterar.


				cout << "                                                 Bem vindo!! :)\n";															//mensaguem inicial.
				cout << "       Aqui você pode adiconar novas cartas para o seu jogo, ou atualizar o baralho que você já possui\n";
				cout << "OBS: Para importar cartas é preciso de um arquivo .txt com o cabeçalho BARALHO e o número de cartas que ele tem\n"
					<< "   Você pode usar o arquivo que já temos disponivel, ele se chama - maiscartas.txt -, use ele pra começar.\n\n" << endl;

					do
					{
						cout << "Gerador de cartar\n";				//menagem inicial.
						Exibedivisao(16);							//chamando a função que exibe a divisão de tela.

						cout << "(C)adastrar\n(I)mportar\n(A)lterar\n(E)xcluir\n(L)istar\n(S)air\n\n";		//perguntando o que o usuário quer fazer.

						cout << "Escolha uma opção [ ]\b\b";		//lendo a opção digitada.
						cin >> alternativa;
						cout << "\n\n";


							if (alternativa == 'C')		//se o que for retornado da função for C é cadastrada uma nova carta.
							{
								cartasadicionadas = Cadastro(baralho, posicao);			//chamando a função que cadastra uma nova carta.
								NumCartas = NumCartas + cartasadicionadas;
								posicao = NumCartas + posicao;							//posicao via ser somada com o número de cartas para que as proximas cartas sejam guardadas na proximas posições do vetor.
							}

							if (alternativa == 'I')		//se o que for retronado da função for I é importado cartas de um arquivo que o usuário digita o nome.
							{
								cartasadicionadas = Importar(baralho, posicao);			//chamando a função que importa cartas de um arquivo.
								NumCartas = NumCartas + cartasadicionadas;				//adicionando a quantidade de cartas importadas ao número total de cartas.
								posicao = NumCartas + posicao;							//posicao via ser somada com o número de cartas para que as proximas cartas sejam guardadas na proximas posições do vetor.
							}

							if (alternativa == 'A')		//se o que for retornado for A, uma carta será alterada no baralho.
							{
								Alterar(baralho);										//chamando a função que altera uma carta do baralho
							}

							if (alternativa == 'E')		//se o que for retornado for E, uma carta é excluida do baralho.
							{
								Excluir(baralho);										//chamando a função que exclui a carta.
								NumCartas--;											//excluido 1 da quantidade de cartas.
								posicao--;												//exclindo 1 do número de posições no vetor.
							}

							if (alternativa == 'L')		//se o que for retornado for L, é listado todas as cartas do baralho.
							{
								Listar(baralho, NumCartas);								//chamandoa função que exibe todas as cartas do baralho.
							}


					} while (alternativa != 'S');		//laço se repete até que se digite S
			}
			else
			{
				cout << "A abertura do arquivo Baralho.dat falhou!" << endl;										//exibindo mendaguem de erro.
				cout << "O cabeçalho está incorreto. Corrija-o para 'BARALHO' e tente novamente." << endl;
				cout << "Programa encerrando.\n";
				exit(EXIT_FAILURE);
			}

		fout.open("../Baralho.dat", ios_base::trunc | ios_base::out | ios_base::binary);	//abrindo o arquivo para a escrita. Limpando o que se tem nele e gravando os novos dados.
		fout.write((char*)&nome, sizeof(char[7]));										//gravando no arquivo no cabeçalho BARALHO.
		fout.write((char*)&NumCartas, sizeof(unsigned short));							//gravando no arquino o número de cartas que tem no arquivo.
		fout.write((char*)&baralho, sizeof(Cartas) * NumCartas);						//gravando no arquivo as cartas que estão contidas no vetor baralho.
		fout.close();																	//fechando o arquivo binário de escrita.


		cout << "Obrigado por me usar!!\nTudo foi feito e salvo no arquivo.\nSe divirta no jogo. :)\n\n";		//mensagem final do programa.

		system("pause");
		return 0;

	}
	else         //-------------------------------------------------------SE NÃO EXISTIR O ARQUIVO É CRIADO------------------------------------------------------------------------------------
	{
		posicao = 0;									//variavel que vai dizer em qual posição do vetor se coloca a nova carta ou onde se deve alterar.


		cout << "                                                 Bem vindo!! :)\n";																//mensaguem inicial.
		cout << "       Aqui você pode adiconar novas cartas para o seu jogo, ou atualizar o baralho que você já possui\n";
		cout << "       Como você ainda não tem um arquivo com cartas vamos começar criando um e cadastrando as cartas.\n";
		cout << "OBS: Para importar cartas é preciso de um arquivo .txt com o cabeçalho BARALHO e o número de cartas que ele tem\n"
			<< "   Você pode usar o arquivo que já temos disponivel, ele se chama - maiscartas.txt -, use ele praa começar.\n\n" << endl;

			do
			{
				cout << "Gerador de cartar\n";				//menagem inicial.
				Exibedivisao(16);							//chamando a função que exibe a divisão de tela.

				cout << "(C)adastrar\n(I)mportar\n(A)lterar\n(E)xcluir\n(L)istar\n(S)air\n\n";		//perguntando o que o usuário quer fazer.

				cout << "Escolha uma opção [ ]\b\b";		//lendo a opção digitada.
				cin >> alternativa;
				cout << "\n\n";


					if (alternativa == 'C')										//se o que for retornado da função for C é cadastrada uma nova carta.
					{
						cartasadicionadas = Cadastro(baralho, NumCartas);		//chamando a função que cadastra uma nova carta.
						NumCartas = NumCartas + cartasadicionadas;
						posicao = NumCartas + posicao;							//posicao via ser somada com o número de cartas para que as proximas cartas sejam guardadas na proximas posições do vetor.
					}

					if (alternativa == 'I')		//se o que for retronado da função for I é importado cartas de um arquivo que o usuário digita o nome.
					{
						cartasadicionadas = Importar(baralho, posicao);			//chamando a função que importa cartas de um arquivo.
						NumCartas = NumCartas + cartasadicionadas;				//adicionando a quantidade de cartas importadas ao número total de cartas.
						posicao = NumCartas + posicao;							//posicao via ser somada com o número de cartas para que as proximas cartas sejam guardadas na proximas posições do vetor.
					}

					if (alternativa == 'A')		//se o que for retornado for A, uma carta será alterada no baralho.
					{
						Alterar(baralho);										//chamando a função que altera uma carta do baralho
					}

					if (alternativa == 'E')		//se o que for retornado for E, uma carta é excluida do baralho.
					{
						Excluir(baralho);										//chamando a função que exclui a carta.
						NumCartas--;											//excluido 1 da quantidade de cartas.
						posicao--;												//exclindo 1 do número de posições no vetor.
					}

					if (alternativa == 'L')		//se o que for retornado for L, é listado todas as cartas do baralho.
					{
						Listar(baralho, NumCartas);								//chamandoa função que exibe todas as cartas do baralho.
					}

					

			} while (alternativa != 'S');		//laço se repete até que se digite S



			fout.open("Baralho.dat", ios_base::out | ios_base::app | ios_base::binary);		//abrindo arquivo binário.

			fout.write((char*)&nome, sizeof(char[7]));										//gravando no arquivo no cabeçalho BARALHO.
			fout.write((char*)&NumCartas, sizeof(unsigned short));							//gravando no arquino o número de cartas que tem no arquivo.
			fout.write((char*)&baralho, sizeof(Cartas) * NumCartas);						//gravando no arquivo as cartas que estão contidas no vetor baralho.
			
			fout.close();																	//fechando o arquivo binário.


			cout << "Obrigado por me usar!!\nTudo foi feito e salvo no arquivo.\nSe divirta no jogo. :)\n\n";		//mensagem final do programa.
			
			system("pause");
			return 0;
	}
	
	return 0;
}
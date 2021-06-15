#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "Registros-e-Funcoes.h"
using namespace std;

int main()
{
	SetConsoleCP(1252);								//usando da biblioeca Windows.h para poder ler e exibis palavras com a entuação correta.
	SetConsoleOutputCP(1252);


	ifstream fin;																	//criando variavel ifstream para a leitura do arquivo.
	char nome[8] = "BARALHO", alternativa, jogador1[20], jogador2[20];				//variaveis de controle do cabeçalho, alternativa escolhida e nme dos jogadores.
	unsigned short NumCartas = 0;													//variavel que guada o número de cartas que tem no arquivo.

	fin.open("../Baralho.dat", ios_base::in | ios_base::binary);					//abrindo o arquivo para a leitura das cartas
	

	if (fin.is_open())			//testando a abertura do arquivo.
	{

		fin.read((char*)&nome, sizeof(char) * 7);						//lendo o cabeçalho do arquivo binário.
		fin.read((char*)&NumCartas, sizeof(unsigned short));

		Cartas* baralho = new Cartas[NumCartas];						//criando um vetor dinâmico com o número de cartas existentes no rquivo binário.
		fin.read((char*)baralho, sizeof(Cartas) * NumCartas);			//colocando o conteudo do arquivo no vetor.

		string compara = nome;											//colocando o nome(cabeçalho lido do arquivo) na variavel do tipo string para comparar toda a cedeia de caracteres de uma vez.


			if (compara.compare("BARALHO") == 0)		 //verificando se o nome recebido do arquivo(cabeçalho) corresponde a palavra BARALHO.
			{
				
					do									 //fazendo um laço que vai perguntar se o usuário quer iniciar uma nova partida ou sair do programa.
					{
						cout << "Super Trunfo Yu-Gi-Oh" << endl;		//mensaguem inicial.
						alternativa = SuperTrunfo();					//chamando a função que vai retornar o que o usuário quer fazer(iniciar nova partida ou sair).


							if (alternativa == 'S')			//se o que for retornado for S, uma nova partida começa.
							{
								cout << "Jogador 1: ";		//lendo os nomes do jogadores.
								cin >> jogador1;
								cout << "Jogador 2: ";
								cin >> jogador2;

								Jogo(baralho, jogador1, jogador2, NumCartas);		//chamando a função que faz o jogo.
							}

					} while (alternativa == 'S');		//laço vai repetir até que alternativa for diferente de S.

				
				delete[] baralho;			//deletando o vetor dinâmico.

				cout << "\n  Bela partida!!\n O programa será encerrado.\a" << endl;		//mensaguem final.
				system("pause");
				return 0;
			}
			else
			{
				cout << "A abertura do arquivo Baralho.dat falhou!" << endl;				//exibindo mendaguem de erro.
				cout << "O cabeçalho está incorreto. Corrija-o para 'BARALHO' no programa do gerador de cartas e tente novamente." << endl;
				cout << "Programa encerrando.\n";
				exit(EXIT_FAILURE);
			}

	}
	else
	{
		cout << "A abertura do arquivo Baralho.dat falhou!" << endl;						//exibindo mendaguem de erro.
		cout << "Programa encerrando.\n";
		exit(EXIT_FAILURE);
	}
	
}
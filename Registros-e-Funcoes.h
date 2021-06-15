struct Cartas							//registro e cartas.
{
	char nome[20];
	int ataque, defesa, numestrelas;
};



/*===================================================================================================================================================================================================*/
/*=========================================================================FUNÇÕES DO GERADOR DE CARTAS==============================================================================================*/
/*===================================================================================================================================================================================================*/

void ZeraVetor(Cartas*);					//protótipo da função que coloca 0 em todas as posições do vetor.
void Exibedivisao(int);						//protótipo da função que faz a divisão das partes da tela.
void GeradordeCartas(char*);				//protótipo da função que pergunta o que o usuário quer fazer.
unsigned short Cadastro(Cartas*, int);		//protótipo da função que faz o cadastro de uma nova carta.
unsigned short Importar(Cartas*, int);		//protótipo da função que importa cartas de um arquivo.
void Alterar(Cartas*);						//protótipo da função que altera uma carta.
void Excluir(Cartas*);						//protótipo da função que exclui uma carta
void Listar(Cartas*, int);					//protótipo da função que lista as cartas.
struct Cartas							//registro e cartas.
{
	char nome[20];
	int ataque, defesa, numestrelas;
};



/*===================================================================================================================================================================================================*/
/*=========================================================================FUN��ES DO GERADOR DE CARTAS==============================================================================================*/
/*===================================================================================================================================================================================================*/

void ZeraVetor(Cartas*);					//prot�tipo da fun��o que coloca 0 em todas as posi��es do vetor.
void Exibedivisao(int);						//prot�tipo da fun��o que faz a divis�o das partes da tela.
void GeradordeCartas(char*);				//prot�tipo da fun��o que pergunta o que o usu�rio quer fazer.
unsigned short Cadastro(Cartas*, int);		//prot�tipo da fun��o que faz o cadastro de uma nova carta.
unsigned short Importar(Cartas*, int);		//prot�tipo da fun��o que importa cartas de um arquivo.
void Alterar(Cartas*);						//prot�tipo da fun��o que altera uma carta.
void Excluir(Cartas*);						//prot�tipo da fun��o que exclui uma carta
void Listar(Cartas*, int);					//prot�tipo da fun��o que lista as cartas.
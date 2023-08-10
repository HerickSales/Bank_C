/**
	Atividade Avaliativa 2 - A2
	Disciplina de Estruturas de Dados
	
	Aluno1: Herick Sales
	Aluno2: Elias Gabriel
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 100
#define MAX_NOME 30

/**
 * Você deverá completar a definição dos TADS (Movimentacao, Conta, Cliente e Banco)
*/

typedef struct _mov *ptrMovimentacao;
typedef struct _mov {
    short int tipo;
    int idClientDest;
    int idClientOrig;
    float valor;
    ptrMovimentacao proxMov;
} Movimentacao;

typedef struct _conta {
    int numero;
    float saldoIni;
    float saldo;
    ptrMovimentacao movs;
} Conta;

typedef struct _cliente *ptrCliente;
typedef struct _cliente {
	int id;
    Conta conta;
    ptrCliente proxCliente;
} Cliente;

typedef struct _banco {
    char nome[MAX_NOME];
    ptrCliente clientes;
} Banco;


/** 
	Função para criacao de uma nova movimentacao
	Você deverá implementar as funcionalidades desta função
*/
Movimentacao* criarNovaMovimentacao(short int tipo, float valor, int idClienteOrig, int idClienteDest) {
    Movimentacao* novaMov= (Movimentacao*)(malloc(sizeof(Movimentacao)));
    if(novaMov != NULL){
        novaMov->proxMov=NULL;
        novaMov->tipo=tipo;
        novaMov->valor=valor;
        novaMov->idClientOrig=idClienteOrig;
        if(tipo!=2)
            novaMov->idClientDest=0;
        else
            novaMov->idClientDest=idClienteDest;   
    }
    return novaMov;
}

/**
	Função que realiza a busca de um determinado cliente. 
	Esta função deverá retornar NULL caso cliente não esteja na lista.
	Você deverá implementar as funcionalidades desta função
*/
Cliente* buscarCliente(Banco *b, int idCliente) {   
    ptrCliente auxPtr= b->clientes;
    while(auxPtr!= NULL){
   
        if(auxPtr->id==idCliente){
            return auxPtr;
        }else{
            auxPtr=auxPtr->proxCliente;
        }
    }
    return auxPtr;
}

void realizarSaque(Cliente *c, Movimentacao* saque) {
    ptrMovimentacao ptrMov;
    saque->valor*=-1;
        c->conta.saldo+=saque->valor;
        if(c->conta.movs==NULL){
            c->conta.movs=saque;
        }else{
            ptrMov=c->conta.movs;
            while(ptrMov->proxMov!=NULL){
                ptrMov=ptrMov->proxMov;
            }
             ptrMov->proxMov=saque;
             saque->proxMov=NULL;
        }
}

/** 
	Função que tem por objetivo realizar uma movimentação de depósito: Adição de uma movimentação no cliente c
	Você deverá implementar as funcionalidades desta função
*/
void realizarDeposito(Cliente *c, Movimentacao* dep) {
    ptrMovimentacao ptrMov;

        c->conta.saldo+=dep->valor;
        if(c->conta.movs==NULL){
            c->conta.movs=dep;
            dep->proxMov=NULL;
        }else{
            ptrMov=c->conta.movs;
            while(ptrMov->proxMov!=NULL){
                ptrMov=ptrMov->proxMov;
            }
             ptrMov->proxMov=dep;
             dep->proxMov=NULL;

        }
}


/** 
	Função que tem por objetivo a realização de transferencia: orig -> dest
	Você deverá implementar as funcionalidades desta função
*/
void realizarTransferencia(Cliente *orig, Cliente *dest, float valor) {
    ptrMovimentacao transforig,transfdest, ptrMovOrig=orig->conta.movs;

    ptrMovimentacao ptrMovDest=dest->conta.movs;
    orig->conta.saldo-=valor;
    dest->conta.saldo+=valor;
    valor*=-1;
    transforig=criarNovaMovimentacao(2,valor,orig->id,dest->id);
    valor*=-1;
    transfdest=criarNovaMovimentacao(2,valor,orig->id,dest->id);

    if(transforig==NULL|| transfdest==NULL){
        printf("ERRO- erro ao alocar memoria.");
    }else{
            transforig->proxMov=NULL;

            if(orig->conta.movs==NULL){
                orig->conta.movs=transforig;
            }else{
                        //adicionando a orig
                    while(ptrMovOrig->proxMov!= NULL){
                        ptrMovOrig=ptrMovOrig->proxMov;
                    }
                    ptrMovOrig->proxMov=transforig;

            }
            if(dest->conta.movs==NULL){
                dest->conta.movs=transfdest;
                
            }else{
            //adicionando ao dest
                ptrMovDest=dest->conta.movs;  
                while(ptrMovDest->proxMov!= NULL){
                    ptrMovDest=ptrMovDest->proxMov;
                }
                ptrMovDest->proxMov=transfdest;
        }
    }
    
}

/** 
	Função que tem por objetivo a adição de um cliente no banco de forma ordenada
	Você deverá implementar as funcionalidades desta função
*/
void adicionarCliente(Banco *b, Cliente *c) {  
    if (b->clientes == NULL) {
        b->clientes = c;
    } else {
        
        ptrCliente auxPtr = b->clientes;
        while (auxPtr->proxCliente != NULL) {
            auxPtr = auxPtr->proxCliente;
        }
        auxPtr->proxCliente = c;
    }
    c->proxCliente = NULL;
}



/** 
	Função que tem por objetivo a adição de um novo cliente com seus dados iniciais.
	Lembre-se que um cliente deverá possuir uma conta e esta conta possui uma lista de movimentações.
	Você deverá completar as funcionalidades desta função
*/
ptrCliente criarNovoCliente(int idCliente, int numConta, float saldo) {
	ptrCliente novoCliente = (ptrCliente) malloc(sizeof(Cliente));
    if(novoCliente !=NULL){
        novoCliente->id = idCliente;
        novoCliente->conta.numero=numConta;
        novoCliente->conta.saldo=saldo;
        novoCliente->conta.saldoIni=saldo;
        novoCliente->conta.movs=NULL;
    }
    return novoCliente;
}

/** 
	Função que tem por objetivo a criação de um novo banco.
	Lembre-se, o banco possui uma lista de clientes.
	Você deverá implementar as funcionalidades desta função
*/
Banco* criarBanco(char *nome) {
    Banco* novoBanco= (Banco*) malloc(sizeof(Banco));
    if(novoBanco != NULL){
        strcpy(novoBanco->nome,nome);
        novoBanco->clientes=NULL;
    }
    return novoBanco;

    
}

/** 
	Função que tem por objetivo liberar toda e qualquer memória alocada dinamicamente para o banco, na seguinte ordem:
	1 - Lista de movimentações de cada cliente
	2 - Lista de clientes
	3 - banco
	
	Você deverá implementar as funcionalidades desta função
*/
void liberarBanco(Banco *b) {
    ptrCliente auxClientPtr = b->clientes;
    ptrCliente proxClient;
    ptrMovimentacao proxMov;

    while (auxClientPtr != NULL) {
        ptrMovimentacao auxMovPtr = auxClientPtr->conta.movs; 
        while (auxMovPtr != NULL) { 
            proxMov = auxMovPtr->proxMov;
            free(auxMovPtr); 
            auxMovPtr = proxMov;
        }

        proxClient = auxClientPtr->proxCliente;
        free(auxClientPtr); 
        auxClientPtr = proxClient;
    }
    free(b); 
}



// Função que realiza a abertura do arquivo. NÃO altere esta função
FILE* openFile(char *path, char *mode) {
    return fopen(path, mode);
}

/**
 * Função que realiza a leitura dos dados no arquivo.
 * Para uma melhor compreensão desta função, leia o arquivo LEIA-ME.txt
 
	-----------------------------------
	| ATENCAO: NÃO altere esta função |
	-----------------------------------
 
 * Colunas presentes no arquivo: 
 * cn = Coluna n, onde n = (1..4)
 * c1 = mov
 * c2 = (idCliente ou TipoMov)
 * c3 = (numConta, idCliente ou idClienteOrig-idClienteDest)
 * c4 = valor
 * */
void readFile(FILE *ptr, Banco *banco)
{
    char c1[4], c3[8];
    int c2;
    int idCliente, idClienteOrig, idClienteDest, numConta;
    float c4, valor;
    // clientes usados para busca

    ptrCliente clienteOrig = NULL, clienteDest = NULL;

    // Iterando nas linhas do arquivo
    while (fscanf(ptr, "%s\t%d\t%s\t%f\n", c1, &c2, c3, &c4) != EOF) {
        valor = c4;

        if (strcmp("add", c1) == 0) { // adicionar cliente
            idCliente = c2;
            numConta = atoi(c3);

            ptrCliente novoCliente = criarNovoCliente(idCliente, numConta, valor);
            if (novoCliente) {
                 adicionarCliente(banco, novoCliente);

            } else {
                printf("ERRO - Ocorreu um erro ao tentar adicionar o cliente %d\n", idCliente);
                liberarBanco(banco);
                fclose(ptr);
                exit(1);
            }
        } else if (strcmp("mov", c1) == 0) { // realizar movimentacoes
            ptrMovimentacao novaMovimentacao = NULL;
            
            switch(c2) {
                case 0: // deposito
                    idCliente = atoi(c3);
                    clienteOrig = buscarCliente(banco, idCliente);


                    if (clienteOrig) {
                        novaMovimentacao = criarNovaMovimentacao(0, valor, clienteOrig->id, 0);

                        if (novaMovimentacao) {
                            realizarDeposito(clienteOrig, novaMovimentacao);

                            clienteOrig = NULL;

                        } else {
                            printf("ERRO - Ocorreu um erro ao tentar depositar %.2f para o cliente %d.\n", valor, idCliente);
                            liberarBanco(banco);
                            fclose(ptr);                                                     
                            exit(1);
                        }

                    } else {
                        printf("ERRO - Cliente %d nao encontrado para realizacao de deposito no valor de %.2f.\n", idCliente, valor);
                        liberarBanco(banco);
                        fclose(ptr);
                        exit(1);
                    }
                break;

                case 1: // saque
                    idCliente = atoi(c3);
                    clienteOrig = buscarCliente(banco, idCliente);

                    if (clienteOrig) {
                        novaMovimentacao = criarNovaMovimentacao(1, valor, clienteOrig->id, 0);

                        if (novaMovimentacao) {
                            realizarSaque(clienteOrig, novaMovimentacao);
                            clienteOrig = NULL;
                        } else {
                            printf("ERRO - Ocorreu um erro ao tentar realizar o saque de %.2f para o cliente %d.\n", valor, idCliente);
                            liberarBanco(banco);
                            fclose(ptr);                            
                            exit(1);
                        }

                    } else {
                        printf("ERRO - Ocorreu um erro ao tentar buscar o cliente %d para realizar o saque de %.2f.\n", idCliente, valor);
                        liberarBanco(banco);
                        fclose(ptr);                                                        
                        exit(1);
                    }
                break;

                case 2: // transferencia
                    idClienteOrig = atoi(strtok(c3, "-"));
                    idClienteDest = atoi(strtok(NULL, "-"));

                    clienteOrig = buscarCliente(banco, idClienteOrig);
                    clienteDest = buscarCliente(banco, idClienteDest);

                    if (clienteOrig && clienteDest) {
                        realizarTransferencia(clienteOrig, clienteDest, valor);
                        clienteOrig = NULL;
                        clienteDest = NULL;
                    } else {
                        printf("ERRO - Ocorreu um erro ao tentar buscar clientes orig %d e dest %d para transferencia do valor %.2f\n", idClienteOrig, idClienteDest, valor);
                        liberarBanco(banco);
                        fclose(ptr);
                        exit(1);
                    }
                break;

                default:
                    printf("ERRO - movimentacao desconhecida.\n");
                    liberarBanco(banco);
                    fclose(ptr);
                    exit(1);
                break;
            }
        }
    }
}
Banco* sort(Banco* b) {
    Banco* auxiliar = criarBanco("aux");
    
    if (auxiliar == NULL) {
        return NULL;
    }

    while (b->clientes != NULL) {
        ptrCliente auxPtr = b->clientes;
        ptrCliente antPtr = NULL;
        ptrCliente ptrOrdem = b->clientes;
        ptrCliente antPtrOrdem = NULL;
        int menor = b->clientes->id;

        while (auxPtr != NULL) {
            if (auxPtr->id < menor) {
                menor = auxPtr->id;
                ptrOrdem = auxPtr;
                antPtrOrdem = antPtr;
            }
            antPtr = auxPtr;
            auxPtr = auxPtr->proxCliente;
        }

        if (ptrOrdem == b->clientes) {
            b->clientes = b->clientes->proxCliente;
        } else {
            antPtrOrdem->proxCliente = ptrOrdem->proxCliente;
        }

        ptrOrdem->proxCliente = auxiliar->clientes;
        auxiliar->clientes = ptrOrdem;
    }

    Banco* resultado = criarBanco("resultado");
    ptrCliente auxPtr = auxiliar->clientes;
    while (auxPtr != NULL) {
        ptrCliente prox = auxPtr->proxCliente;
        auxPtr->proxCliente = resultado->clientes;
        resultado->clientes = auxPtr;
        auxPtr = prox;
    }
    free(auxiliar);
    return resultado;
}

/** 
	Função que tem por objetivo imprimir todos os dados do banco no padrão requerido da especificação
	Você deverá implementar as funcionalidades desta função
*/
void imprimirDados(Banco *b) {
    // A linha abaixo é apenas ilustrativa, remova-a posteriormente.
    b=sort(b);
    ptrCliente auxClient= b->clientes;
    ptrMovimentacao auxMov;

    while(auxClient!=NULL){
        auxMov=auxClient->conta.movs;
        
        printf("=====================================================\n"); 
        printf("Id. Cliente  :    %d\n",auxClient->id);
        printf("Numero Conta :    %d\n", auxClient->conta.numero);
        printf("Saldo inicial:    %.2f\n",auxClient->conta.saldoIni);
        printf("------------------- Movimentacoes -------------------\n");
        if(auxMov==NULL){
            printf("Sem movimentacoes\n");
        }
        while (auxMov!=NULL){
            
            printf("Tipo: ");
            if(auxMov->tipo==0)
                printf("Deposito | Valor: ");
            else if(auxMov->tipo==1)
                printf("Saque    | Valor: ");

            else 
                printf("Transf.  | Valor: ");

            if(auxMov->tipo<2){
                printf("%.2f\n", auxMov->valor);
            }else{
                if(auxMov->idClientOrig==auxClient->id){
                    printf("%.2f ===> ",auxMov->valor);
                    printf("Destinatario: %d\n",auxMov->idClientDest);
                }else{
                    printf("%.2f ===> ",auxMov->valor);
                    printf("Origem: %d\n",auxMov->idClientOrig);

                }
            }
            auxMov=auxMov->proxMov;
        }
        printf("\nSaldo Final: %.2f\n",auxClient->conta.saldo);
        auxClient=auxClient->proxCliente;   
    }
        
    printf("=====================================================\n");

}


int main(int argc, char *argv[])
{
    char path[MAX_PATH];
    FILE *filePtr = NULL;
    Banco *bomBanco = NULL;

    scanf("%s", path);
    filePtr = openFile(path, "r");
    if (filePtr) {
        bomBanco = criarBanco("BomBanco");
        if (bomBanco) {
           readFile(filePtr, bomBanco);
           imprimirDados(bomBanco);
	        liberarBanco(bomBanco);

        }
        fclose(filePtr);
    } else {
        printf("Falha ao tentar abrir o arquivo\n");
        exit(1);
    }
    return 0;
}
#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores:   avs   Arndt Von Staa
*             cai   Caique Molina
*             gui   Guilherme Dantas
*             nag   Nagib Suaid
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     6       gui   03/dez/2018 revis�o da instrumenta��o
*     5       gui   29/nov/2018 in�cio instrumenta��o
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa listas gen�ricas duplamente encadeadas.
*     Podem existir n listas em opera��o simultaneamente.
*     As listas possuem uma cabe�a encapsulando o seu estado.
*
*     Cada lista � homog�nea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que cont�m.
*
*     Os ponteiros para os dados s�o copiados para elementos da lista.
*        N�o � copiado o valor apontado por estes ponteiros.
*
*     O controle da destrui��o do valor de um elemento a ser exclu�do
*        � realizado por uma fun��o fornecida pelo usu�rio.
*
*     Cada lista referencia uma fun��o que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A fun��o de libera��o dos valores contidos nos elementos deve
*        assegurar a libera��o de todos os espa�os refer�nciados pelo
*        valor contido em um elemento.
*        Esta fun��o � chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso n�o seja necess�rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*        Caso o elemento da lista seja a �nica �ncora do valor referenciado,
*        esta fun��o deve promover a destrui��o (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista n�o cont�m elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* N�o encontrou o valor procurado */

         LIS_CondRetFaltouMemoria ,
               /* Faltou mem�ria ao tentar criar um elemento de lista */

#ifdef _DEBUG
         LIS_CondRetErroEstrutura ,
               /* Algum erro na estrutura ocorreu */

         LIS_CondRetErroParametro
               /* Fun��o recebeu um par�metro inv�lido */
#endif

   } LIS_tpCondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Modos de deturpar
*
*
***********************************************************************/

#ifdef _DEBUG

   typedef enum {

         LIS_ModoDeturpacaoEliminaCorr = 1 ,
            /* Elimina o elemento corrente da lista */

         LIS_ModoDeturpacaoProxNULL = 2 ,
            /* Atribui NULL ao ponteiro para o pr�ximo n� */

         LIS_ModoDeturpacaoAntNULL = 3 ,
            /* Atribui NULL ao ponteiro para o n� anterior */

         LIS_ModoDeturpacaoProxLixo = 4 ,
            /* Atribui lixo ao ponteiro para o pr�ximo n� */

         LIS_ModoDeturpacaoAntLixo = 5 ,
            /* Atribui lixo ao ponteiro para o n� anterior */

         LIS_ModoDeturpacaoConteudoNULL = 6 ,
            /* Atribui NULL ao ponteiro para o conte�do do n� */

         LIS_ModoDeturpacaoAlteraTipoNo = 7 ,
            /* Altera o tipo de estrutura apontado no n� */

         LIS_ModoDeturpacaoDesencadeiaNo = 8 ,
            /* Desencadeia n� sem liber�-lo com free */

         LIS_ModoDeturpacaoPontCorrNULL = 9 ,
            /* Atribui NULL ao ponteiro corrente */

         LIS_ModoDeturpacaoPontOrigNULL = 10 ,
            /* Atribui NULL ao ponteiro de origem */

         LIS_ModoDeturpacaoPontFimNULL = 11 ,
            /* Atribui NULL ao ponteiro de final */

         LIS_ModoDeturpacaoEliminaLista = 12 ,
            /* Elimina lista */

         LIS_ModoDeturpacaoCorrLixo = 13 ,
            /* Atribui lixo ao ponteiro para n� corrente */

         LIS_ModoDeturpacaoOrigLixo = 14 ,
            /* Atribui lixo ao ponteiro para n� origem */

         LIS_ModoDeturpacaoFinalLixo = 15 ,
            /* Atribui lixo ao ponteiro para n� final */

         LIS_ModoDeturpacaoNumElemNegativo = 16 ,
            /* Atribui valor negativo ao contador de elementos */

         LIS_ModoDeturpacaoCorrElemNovo = 17 ,
            /* Fazer ponteiro corrente apontar para novo elemento */

         LIS_ModoDeturpacaoCorrTipoErrado = 18 ,
            /* Fazer ponteiro corrente apontar para lista */

         LIS_ModoDeturpacaoOrigTipoErrado = 19 ,
            /* Fazer ponteiro origem apontar para lista */

         LIS_ModoDeturpacaoFinalTipoErrado = 20 ,
            /* Fazer ponteiro final apontar para lista */

         LIS_ModoDeturpacaoOrigElemNovo = 21 ,
            /* Fazer ponteiro origem apontar para novo elemento */

         LIS_ModoDeturpacaoElemCorrCabNULL = 22 ,
            /* Fazer pCab do elemento corrente NULL */

         LIS_ModoDeturpacaoDuplicarElem = 23 ,
            /* Duplica elemento de modo que se possa continuar
               a percorrer em ambos os sentidos por caminhos diferentes */

         LIS_ModoDeturpacaoTamNegativo = 24 ,
            /* Faz tam = -1 */

         LIS_ModoDeturpacaoTamUm = 25 ,
            /* Faz tam = 1 */

         LIS_ModoDeturpacaoConteudoLixo = 26 ,
            /* Faz pValor apontar para lixo */

         LIS_ModoDeturpacaoConteudoApontaElem = 27 ,
            /* Faz pValor apontar para elemento */

         LIS_ModoDeturpacaoAntApontaCab = 28 ,
            /* Faz pAnt do elemento corrente apontar para cabe�a */

         LIS_ModoDeturpacaoProxApontaCab = 29 
            /* Faz pProx do elemento corrente apontar para cabe�a */

   } LIS_tpModosDeturpacao ;

#endif

/***********************************************************************
*
*  $FC Fun��o: LIS  &Criar lista
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado � lista.
*
*  $EP Par�metros
*     ExcluirValor  - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro ser� utilizado pelas fun��es que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

   LIS_tppLista LIS_CriarLista( void   ( * ExcluirValor ) ( void * pDado )
#ifdef _DEBUG
                              , char TipoValor
#endif
      ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Destruir lista
*
*  $ED Descri��o da fun��o
*     Destr�i a lista fornecida.
*     O par�metro ponteiro para a lista n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, a lista resultar�
*     estruturalmente incorreta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   void LIS_DestruirLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Esvaziar lista
*
*  $ED Descri��o da fun��o
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a ser esvaziada
*
***********************************************************************/

   void LIS_EsvaziarLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir elemento antes
*
*  $ED Descri��o da fun��o
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
*
*     Para _DEBUG ativo:
*     LIS_CondRetErroParametro
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor
#ifdef _DEBUG
                                          , char TipoValor
                                          , int tam
#endif
      ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir elemento ap�s
*
*  $ED Descri��o da fun��o
*     Insere novo elemento ap�s o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     Par�metros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*           
*
*  $FV Valor retornado
*     Valor retornado
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor
#ifdef _DEBUG
                                          , char TipoValor
                                          , int tam
#endif
      ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Excluir elemento
*
*  $ED Descri��o da fun��o
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente ser� o novo corrente.
*     Se n�o existir e existir o elemento � direita, este se tornar� corrente.
*     Se este tamb�m n�o existir a lista tornou-se vazia.
*
*  $EP Par�metros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o valor contido no elemento corrente da lista
*
*  $EP Par�metros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     n�o NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
***********************************************************************/

   void * LIS_ObterValor( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir para o elemento inicial
*
*  $ED Descri��o da fun��o
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista est� vazia.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

   void IrInicioLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir para o elemento final
*
*  $ED Descri��o da fun��o
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista est� vazia.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

   void IrFinalLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Avan�ar elemento
*
*  $ED Descri��o da fun��o
*     Avan�a o elemento corrente numElem elementos na lista
*     Se numElem for positivo avan�a em dire��o ao final
*     Se numElem for negativo avan�a em dire��o ao in�cio
*     numElem pode ser maior do que o n�mro de elementos existentes na
*               dire��o desejada
*     Se numElem for zero somente verifica se a lista est� vazia
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o n�mero de elementos a andar
*
*  $FV Valor retornado
*     LIS_CondRetOK         - se numElem elementos tiverem sido andados
*     LIS_CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     LIS_CondRetListaVazia - se a lista est� vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Procurar elemento contendo valor
*
*  $ED Descri��o da fun��o
*     Procura o elemento que referencia o valor dado.
*     A fun��o compara ponteiro e n�o conte�do apontado.
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente � o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que cont�m o ponteiro procurado
*
*     LIS_CondRetNaoAchou - se o ponteiro n�o foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        ) ;

/***********************************************************************
*
*  $FC Fun��o: LIS  &Verificar uma lista
*
*  $ED Descri��o da fun��o
*     Fun��o da interface de teste.
*     Verifica completamente uma determinada lista.
*     Tamb�m marca todos os espa�os por ela ocupados.
*
*  $EP Par�metros
*     pListaParam  - ponteiro para cabe�a da lista a ser deturpada
*
*  $FV Valor retornado
*     Quantidade de falhas encontradas.
*
***********************************************************************/

#ifdef _DEBUG

   int LIS_VerificarLista( void * pListaParam ) ;

#endif

/***********************************************************************
*
*  $FC Fun��o: LIS  &Deturpar lista
*
*  $ED Descri��o da fun��o
*     Fun��o da interface de teste.
*     Corrompe elementos espec�ficos da estrutura da lista.
*     Essa fun��o destina-se a preparar os cen�rios de teste dos
*     casos de teste utilizados ao testar os verificadores estruturais
*     da lista.
*     Esta fun��o n�o tem prote��o contra erros de uso, consequentemente
*     poder� levar o programa a ser cancelado pelo sistema operacional.
*
*  $EP Par�metros
*     pListaParam  - ponteiro para cabe�a da lista a ser deturpada
*     ModoDeturpar - identifica como deve ser feita a deturpa��o
*                    LIS_tpModosDeturpacao identifica os modos de
*                    deturpa��o conhecidos
*
***********************************************************************/

#ifdef _DEBUG

   void LIS_Deturpar( void ** pListaParam ,
                      LIS_tpModosDeturpacao ModoDeturpar ) ;

#endif

/***********************************************************************
*
*  $FC Fun��o: LIS  &Liberar espa�os inativos relativos ao m�dulo Lista
*
*  $ED Descri��o da fun��o
*     Fun��o da interface de teste.
*     Libera da mem�ria todo espa�o de mem�ria inativo na LEA
*     que tenha como tipo de espa�o de dados um dos seguintes:
*
*     - LIS_TipoEspacoElemento
*     - LIS_TipoEspacoCabeca
*     - LIS_TipoEspacoEstrutura
*
*  $AE Assertivas de Entrada:
*     Implicitamente � usada a LEA, componente do m�dulo
*     CESPDIN.H, importado apenas para _DEBUG.
*
*  $AS Assertivas de Sa�da:
*     Se houver outros espa�os apontados por esta estrutura,
*     e n�o forem dos tipos citados, n�o ser�o tratadas.
*
***********************************************************************/

#ifdef _DEBUG

   int LIS_LiberarEspacosInativos ( void ) ;

#endif

#undef LISTA_EXT

/********** Fim do m�dulo de defini��o: LIS  Lista duplamente encadeada **********/

#else
#endif

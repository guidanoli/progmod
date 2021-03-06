/***************************************************************************
*  $MCI M�dulo de implementa��o: TLIS Teste lista duplamente encadeada
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores:   avs   Arndt Von Staa
*             cai   Caique Molina Soares
*             gui   Guilherme Dantas de Oliveira
*             nag   Nagib Moura Suaid
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     5     gui,nag 03/dez/2018 Intrumenta��o do m�dulo LISTA
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"
#include    "Lista.h"

#ifdef _DEBUG
#include "CONTA.H"
#include "CESPDIN.H"
#include "INTRPCNT.H"
#include "Tabelas\\IdTiposEspaco.def"
#endif

// comandos de script

static const char RESET_LISTA_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_LISTA_CMD         [ ] = "=criarlista"     ;
static const char DESTRUIR_LISTA_CMD      [ ] = "=destruirlista"  ;
static const char ESVAZIAR_LISTA_CMD      [ ] = "=esvaziarlista"  ;
static const char INS_ELEM_ANTES_CMD      [ ] = "=inselemantes"   ;
static const char INS_ELEM_APOS_CMD       [ ] = "=inselemapos"    ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorelem" ;
static const char EXC_ELEM_CMD            [ ] = "=excluirelem"    ;
static const char IR_INICIO_CMD           [ ] = "=irinicio"       ;
static const char IR_FIM_CMD              [ ] = "=irfinal"        ;
static const char AVANCAR_ELEM_CMD        [ ] = "=avancarelem"    ;
static const char PROCURAR_VALOR_CMD      [ ] = "=procurarvalor"  ;

// apenas para _DEBUG

static const char INICIALIZAR_CONTADORES_CMD [ ] = "=inicializarcontadores"   ;
static const char TERMINAR_CONTADORES_CMD    [ ] = "=terminarcontadores"      ;
static const char REGISTRAR_ACUMULADOR_CMD   [ ] = "=registraracumulador"     ;
static const char LER_CONTADORES_CMD         [ ] = "=lercontadores"           ;
static const char GRAVAR_CONTADORES_CMD      [ ] = "=gravarcontadores"        ;
static const char ZERAR_CONTADORES_CMD       [ ] = "=zerartodoscontadores"    ;
static const char ZERAR_CONTADOR_DADO_CMD    [ ] = "=zerarcontador"           ;
static const char INICIAR_CONTAGEM_CMD       [ ] = "=iniciarcontagem"         ;
static const char PARAR_CONTAGEM_CMD         [ ] = "=pararcontagem"           ;
static const char OBTER_CONTAGEM_CMD         [ ] = "=contagemcontador"        ;
static const char EXIBIR_CONTAGEM_CMD        [ ] = "=exibircontagem"          ;
static const char OBTER_NUM_CONTADORES_CMD   [ ] = "=numcontadores"           ;
static const char OBTER_TOTAL_CONTAGEM_CMD   [ ] = "=contagemtotal"           ;
static const char VERIFICAR_CONTAGENS_CMD    [ ] = "=verificarcontagens" ;

static const char VRF_CMD                 [ ] = "=verificar"         ;
static const char DETURPAR_CMD            [ ] = "=deturpar"          ;
static const char LIBERA_ESP_LISTA_CMD    [ ] = "=liberaresplista"   ;
static const char TORNAR_INATIVOS_CMD     [ ] = "=tornarinativos"    ;
static const char EXIBIR_ESPACOS_CMD      [ ] = "=exibirespacos"     ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1
#define NAO_CHECA 2

#define DIM_VT_LISTA   10
#define DIM_VALOR     100

#define ID_ESPACO_LIXO 999

/************** Vari�veis globais *****************/

   #ifdef _DEBUG

   static char *EspacoLixo;
      /* Espa�o de dados lixo usado ao testar */

   #endif

   LIS_tppLista vtListas[ DIM_VT_LISTA ] ;
      /* Vetor de listas */

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxLista( int inxLista , int Modo ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TLIS &Testar lista
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 10 listas, identificadas pelos �ndices de 0 a 9
*
*     Comandos dispon�veis:
*
*     =resetteste - anula o vetor de listas. Provoca vazamento de mem�ria
*
*     =criarlista                   inxLista
*     =destruirlista                inxLista
*     =esvaziarlista                inxLista
*     =inselemantes                 inxLista  string  CondRetEsp
*     =inselemapos                  inxLista  string  CondRetEsp
*     =obtervalorelem               inxLista  string  CondretPonteiro
*     =excluirelem                  inxLista  CondRetEsp
*     =irinicio                     inxLista
*     =irfinal                      inxLista
*     =procurarvalor                inxLista  string  CondRetEsp
*     =avancarelem                  inxLista  numElem CondRetEsp
*
*     Comandos para _DEBUG:
*
*     =inicializarcontadores   <nome arquivo contadores acumulado>
*          o nome do arquivo pode ser nulo.
*          Se o nome do arquivo for ".", ser� tamb�m tratado como nulo.
*
*     =terminarcontadores    <n�mero contadores iguais a zero esperado>
*          Grava o arquivo de contadores acumulados, caso esteja
*          definido (nome n�o vazio).
*
*     =registraracumulador   <nome arquivo contadores acumulado>
*          substitui o nome registrado.
*          o nome do arquivo pode ser nulo.
*          Se o nome do arquivo for ".", ser� tamb�m tratado como nulo.
*
*     =lercontadores         <nome arquivo contadores>
*          le� o arquivo e atribui os valores iniciais somente se
*          o contador tiver sido lido de um arquivo acumulado.
*
*     =gravarcontadores      <nome arquivo contadores acumulado>
*          grava o arquivo de contadores acumulado registrado.
*          A grava��o ocorre tamb�m ao terminar contadores
*
*     =zerartodoscontadores
*
*     =zerarcontador   <string nome do contador>
*
*     =iniciarcontagem
*          Ativa a contagem. Este comando precisa ser dado.
*          =inicializarcontadores n�o ativa a contagem, somente ativa
*          o m�dulo
*
*     =pararcontagem
*          Desativa a contagem
*
*     =contagemcontador   <n�mero esperado>
*
*     =exibircontagem
*
*     =numcontadores      <n�mero esperado>
*
*     =contagemtotal      <somat�rio das contagens esperado>
*
*     =verificarcontagens <n�mero contadores zero iguais a zero esperado>
*
*     =deturpar                     inxLista  modoDeturpacao
*        Deturpa lista de �ndice inxLista com o modo de deturpa��o
*        indicado pelo identificador modoDeturpacao.
*        [ ! ] Deve-se ter cuidado para, ao usar outras fun��es
*              do m�dulo lista depois de deturpada a lista, n�o
*              usar espa�os com lixo ou nulos indevidamente, pois
*              h� alto risco do programa voar.
*
*     =verificar                    inxLista  qtFalhasEsp
*        Verifica a lista de �ndice inxLista de acordo com as assertivas
*        estruturais do modelo de lista auto-verific�vel, e compara a
*        qt. de falhas acusadas pela fun��o com qtFalhasEsp.
*
*     =liberarinativos              qtFalhasEsp
*        Percorre a LEA e libera todos os seus espa�os inativos que est�o
*        marcados com tipos de espa�os de dados pertencentes ao m�dulo
*        Lista ( vide TiposEspacosLista.def ).
*
*     =tornarinativos
*        Torna todos os espa�os presentes na LEA inativos.
*
*     =exibirespacos
*        Exibe todos os espa�os na LEA.
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxLista  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      LIS_tpCondRet CondRet ;

      char   StringDado[  DIM_VALOR ] ;
      char * pDado ;

      int i;

      int ValEsp = -1 ;

      int numElem = -1 ;

      StringDado[ 0 ] = 0 ;

      /* Efetuar reset de teste de lista */

         if ( strcmp( ComandoTeste , RESET_LISTA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_LISTA ; i++ )
            {
               vtListas[ i ] = NULL ;     // TRATAR DISSO -> N�O PASSA PELA LEA
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar CriarLista */

         else if ( strcmp( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                       &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtListas[ inxLista ] =
                 LIS_CriarLista( DestruirValor 
#ifdef _DEBUG
                                 , 's'      
#endif
                 ) ;

            return TST_CompararPonteiroNulo( 1 , vtListas[ inxLista ] ,
               "Erro em ponteiro de nova lista."  ) ;

         } /* fim ativa: Testar CriarLista */

      /* Testar Esvaziar lista lista */

         else if ( strcmp( ComandoTeste , ESVAZIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_EsvaziarLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Esvaziar lista lista */

      /* Testar Destruir lista */

         else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_DestruirLista( vtListas[ inxLista ] ) ;
            vtListas[ inxLista ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir lista */

      /* Testar inserir elemento antes */

         else if ( strcmp( ComandoTeste , INS_ELEM_ANTES_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxLista , StringDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , StringDado ) ;

            CondRet = LIS_InserirElementoAntes( vtListas[ inxLista ] , pDado 
#ifdef _DEBUG
               , 's' , strlen( StringDado ) + 1
#endif
               ) ;

            if ( CondRet != LIS_CondRetOK )
            {
               free( pDado ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir antes."                   ) ;

         } /* fim ativa: Testar inserir elemento antes */

      /* Testar inserir elemento apos */

         else if ( strcmp( ComandoTeste , INS_ELEM_APOS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxLista , StringDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */


            strcpy( pDado , StringDado ) ;

            CondRet = LIS_InserirElementoApos( vtListas[ inxLista ] , pDado 
#ifdef _DEBUG
               , 's' , strlen( StringDado ) + 1
#endif
               ) ;

            if ( CondRet != LIS_CondRetOK )
            {
               free( pDado ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir apos."                   ) ;

         } /* fim ativa: Testar inserir elemento apos */

      /* Testar excluir simbolo */

         else if ( strcmp( ComandoTeste , EXC_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                  &inxLista , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_ExcluirElemento( vtListas[ inxLista ] ) ,
                     "Condi��o de retorno errada ao excluir."   ) ;

         } /* fim ativa: Testar excluir simbolo */

      /* Testar obter valor do elemento corrente */

         else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxLista , StringDado , &ValEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) LIS_ObterValor( vtListas[ inxLista ] ) ;

            if ( ValEsp == 0 )
            {
               return TST_CompararPonteiroNulo( 0 , pDado ,
                         "Valor n�o deveria existir." ) ;
            } /* if */

            if ( pDado == NULL )
            {
               return TST_CompararPonteiroNulo( 1 , pDado ,
                         "Dado tipo um deveria existir." ) ;
            } /* if */

            return TST_CompararString( StringDado , pDado ,
                         "Valor do elemento errado." ) ;

         } /* fim ativa: Testar obter valor do elemento corrente */

      /* Testar ir para o elemento inicial */

         else if ( strcmp( ComandoTeste , IR_INICIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            IrInicioLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar ir para o elemento inicial */

      /* LIS  &Ir para o elemento final */

         else if ( strcmp( ComandoTeste , IR_FIM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            IrFinalLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: LIS  &Ir para o elemento final */

      /* LIS  &Avan�ar elemento */

         else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" , &inxLista , &numElem ,
                                &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_AvancarElementoCorrente( vtListas[ inxLista ] , numElem ) ,
                      "Condicao de retorno errada ao avancar" ) ;

         } /* fim ativa: LIS  &Avan�ar elemento */

      /* LIS &Procurar valor */

         else if ( strcmp( ComandoTeste, PROCURAR_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" , &inxLista , StringDado ,
                                &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            if( strcmp( StringDado, "ElemCorr" ) == 0 )
            {
               pDado = (char *) LIS_ObterValor( vtListas[ inxLista ] );
               CondRet = LIS_ProcurarValor( vtListas[ inxLista ] , pDado );
            } /* if */
            else
            {
               CondRet = LIS_ProcurarValor( vtListas[ inxLista ] , StringDado );
            } /* else */

            return TST_CompararInt( CondRetEsp , CondRet ,
                                    "Condicao de retorno errada ao procurar valor" );

         } /* fim ativa: LIS  &Procurar valor */

#ifdef _DEBUG

      /* LIS &Verificar lista */

         else if ( strcmp( ComandoTeste, VRF_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxLista , &CondRetEsp ) ;

            if( numLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            if( inxLista == ID_ESPACO_LIXO )
            {
               TST_tpCondRet retorno;
               EspacoLixo = (char *) malloc(256);
               strcpy(EspacoLixo,"lixo");
               retorno = TST_CompararInt( CondRetEsp ,
                         LIS_VerificarLista( EspacoLixo ) ,
                         "Condicao de retorno errada ao verificar lista" ) ;
               free(EspacoLixo);
               return retorno;
            } /* if */
            else if( ValidarInxLista( inxLista , NAO_CHECA ) )
            {
               return TST_CompararInt( CondRetEsp ,
                      LIS_VerificarLista( vtListas[ inxLista ] ) ,
                      "Condicao de retorno errada ao verificar lista" ) ;
            } /* if */

            return TST_CondRetParm ;

         } /* fim ativa: LIS  &Verificar lista */

      /* LIS &Deturpar */

         else if ( strcmp( ComandoTeste, DETURPAR_CMD ) == 0 )
         {

            LIS_tpModosDeturpacao modoDeturpacao;

            numLidos = LER_LerParametros( "ii" , &inxLista, &modoDeturpacao ) ;

            if( ( numLidos != 2 )
             || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_Deturpar( (void **) &( vtListas[ inxLista ] ) , modoDeturpacao );

            return TST_CondRetOK ;

         } /* fim ativa: LIS  &Iniciar contador */

      /* LIS &Liberar espa�os inativos */

         else if ( strcmp( ComandoTeste , LIBERA_ESP_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &CondRetEsp );

            if( numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp , LIS_LiberarEspacosInativos() ,
                                    "Quantidade de falhas diferente da esparada" );

         } /* fim ativa: LIS &Liberar espa�os inativos */

      /* CED &Tornar todos os espa�os na LEA inativos */

         else if ( strcmp( ComandoTeste , TORNAR_INATIVOS_CMD ) == 0 )
         {

            CED_MarcarTodosEspacosInativos();

            return TST_CondRetOK;

         } /* fim ativa: CED &Tornar todos os espa�os na LEA inativos */

      /* CED &Exibir espa�os alocados dinamicamente */

         else if ( strcmp( ComandoTeste , EXIBIR_ESPACOS_CMD ) == 0 )
         {

            CED_ExibirTodosEspacos( CED_ExibirTodos );

            return TST_CondRetOK;

         } /* fim ativa: CED &Exibir espa�os alocados dinamicamente */

      /* ICNT &Comandos do m�dulo de interpretador de contadores */

         else if (   strcmp( ComandoTeste , INICIALIZAR_CONTADORES_CMD ) == 0 ||
                     strcmp( ComandoTeste , TERMINAR_CONTADORES_CMD ) == 0 ||
                     strcmp( ComandoTeste , REGISTRAR_ACUMULADOR_CMD ) == 0 ||
                     strcmp( ComandoTeste , LER_CONTADORES_CMD ) == 0 ||
                     strcmp( ComandoTeste , GRAVAR_CONTADORES_CMD ) == 0 ||
                     strcmp( ComandoTeste , ZERAR_CONTADORES_CMD ) == 0 ||
                     strcmp( ComandoTeste , INICIAR_CONTAGEM_CMD ) == 0 ||
                     strcmp( ComandoTeste , PARAR_CONTAGEM_CMD ) == 0 ||
                     strcmp( ComandoTeste , OBTER_CONTAGEM_CMD ) == 0 ||
                     strcmp( ComandoTeste , EXIBIR_CONTAGEM_CMD ) == 0 ||
                     strcmp( ComandoTeste , OBTER_NUM_CONTADORES_CMD ) == 0 ||
                     strcmp( ComandoTeste , OBTER_TOTAL_CONTAGEM_CMD ) == 0 ||
                     strcmp( ComandoTeste , VERIFICAR_CONTAGENS_CMD ) == 0 )
         {
            return ICNT_EfetuarComadoContagem( ComandoTeste );
         } /* fim ativa: ICNT &Comandos do m�dulo de interpretador de contadores */

#endif

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TLIS &Testar lista */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim fun��o: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Fun��o: TLIS -Validar indice de lista
*
***********************************************************************/

   int ValidarInxLista( int inxLista , int Modo )
   {

      if ( ( inxLista <  0 )
        || ( inxLista >= DIM_VT_LISTA ))
      {
         return FALSE ;
      } /* if */
      
      if( Modo == NAO_CHECA )
      {
         return TRUE ;
      } /* else */
      else if ( Modo == VAZIO )
      {
         if ( vtListas[ inxLista ] != 0 )
         {
            return FALSE ;
         } /* if */
      } /* else-if */
      else
      {
         if ( vtListas[ inxLista ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* else */
         
      return TRUE ;

   } /* Fim fun��o: TLIS -Validar indice de lista */

/********** Fim do m�dulo de implementa��o: TLIS Teste lista duplamente encadeada **********/


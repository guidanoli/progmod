﻿# Grupo de Programação Modular (INF1031)
**Alunos: Caique, Guilherme e Nagib**

## Source

Esta pasta possui os módulos e a biblioteca estática do teste automatizado.
Para trabalhar no Visual Studio 2010 com estes arquivos, basta arrastá-los para o seu projeto no VS. Não se esqueça de configurar o seu projeto para que não haja problemas na compilação! Siga os passos a seguir caso seu ambiente de desenvolvimento não esteja configurado ainda:

`Alt+F7 > Configuration Properties > C/C++ > Code Generation > Runtime Library > Multi-threaded Debug (/MTd)`

`Alt+F7 > Configuration Properties > C/C++ > Precompiled Headers > Precompiled Header > Not Using Precompiled Headers`

## Scripts

Na pasta **_SCRIPTS_** se encontram todos os scripts de teste. Você pode editar um arquivo de script seu ou criar um novo. Para testar o script, rode o batch  **__LimpaDistribuicao.bat__** e, em seguida, **__Distruibui.bat__**. Dentro da pasta **DISTRIBUICAO**, rode o batch **__Testa.bat__**, e escreva o nome do seu arquivo de script (Dica: use TAB para auto-completar) e a saída estará salva como **__saida.log__** na mesma pasta. Para scripts de debug, é capaz de mais de um arquivo ser gerado. Geralmente este arquivo extra compreende os contadores inseridos no código.

## Executável

Como este repositório deve se encontrar na pasta Debug, é fácil acessar o executável gerado pelo Visual Basic. Lembre-se sempre que não basta salvar os módulos alterados, você há de compilar o projeto toda vez para atualizar o executável. Em seguida, limpe a pasta distribuição e repopule-a com os arquivos mais recentes.
Vale lembrar que cada executável corresponde a um teste automatizado para um módulo de teste diferente. Portanto, quando for testar módulos diferentes, certifique-se que compilará um projeto do VS2010 apenas com o módulo de teste que deseja. Se ambos estiverem no seu projeto, o programa não compilará!

## Relatórios

Sempre que fizer alguma alteração relevante no programa, sinalize no arquivo "RELATORIO-SeuNome.txt" a tarefa que você realizou no seguinte formato, e dê commit em seguida:

`Data - Horas Trabalhadas - Tipo de Tarefa - Descrição da Tarefa Realizada`

Os tipos de tarefa são:
* estudar
* especificar os módulos
* especificar as funções
* revisar especificações
* projetar
* revisar projetos
* codificar módulo
* revisar código do módulo
* redigir script de teste
* revisar script de teste
* realizar os testes
* diagnosticar e corrigir os problemas encontrados

## Diretório de distribuição

Primeiramente, certifique-se que esta pasta esteja na pasta do seu projeto do Visual Basic. Assim:

`[...]\Visual Studio 2010\Projects\<NomeProjeto>\Debug\progmod`

A localização do repositório na sua máquina é fundamental para que o arquivo batch consiga copiar o executável automaticamente. Para gerar o diretório de distribuição, rode o batch _**Distribui.bat**_ para copiar apenas os arquivos importantes para a pasta **_DISTRIBUICAO_**.

## Debugger do Visual Studio

Caso acho necessário debugar algum erro com o Visual Studio, é simples:

* crie um novo projeto no Visual Studio para debugar
* copie os arquivos-fonte para a pasta do seu projeto
* crie um arquivo .c para sua função main
* importe o(s) módulo(s) que deseja debugar
* pronto! agora você poderá livremente colocar assertivas nos módulos e achar o bug!

## .gitignore

Este repositório ignora a pasta **__DISTRIBUICAO__**. Portanto, caso você queira submeter uma determinada distribuição, certifique-se que a colocará em uma pasta com outro nome! Assim quando você usar o comando "git add", esta pasta será considerada para o seu próximo commit!

_Att,
Guilherme_

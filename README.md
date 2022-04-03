# Busca-em-Memoria-Principal

O objetivo é implementar um método de busca em textos, chamado de keyword-in-context (KWIC) search (busca de palavras chave em contexto). Um método como esse é muito utilizado em variadas aplicações, tais como linguística, banco de dados, busca na web, processamento de texto, etc.

## Especificação
Dado um texto com N caracteres, encontrar todas as ocorrências de uma string Q a ser consultada (query string)  juntamente com o contexto C. O contexto é o número de caracteres adicionais de cada lado que devem ser exibidos quando o termo da busca for encontrado. Deve-se fazer um pré processamento para permitir uma busca rápida de substrings usando array de sufixos.

## Execuções implementadas
seguindo o modelo de entrada ./a.out [-aorcs] caminho_arquivo [contexto] [query]

para [-aorcs] temos as seguintes parâmetros:
	(a) Processa o texto e imprime o array de sufixos
	(o) Processa o texto e imprime o array de sufixos ordenado
  (r) Processa o texto, produz o array de sufixo, ordena usando dois (ou mais) métodos e imprime o tempo de ordenação para cada método.
	(c) Dado um contexto e uma query, imprime as ocorrências encontradas
  (s) Dado um contexto, lê queries do teclado e imprime as ocorrências encontradas, até que uma string vazia seja informada.

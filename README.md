# hexview

Utilitário de linha de comando para visualização hexadecimal (Hex Dump) de alta performance desenvolvido em C11.

## Descrição do Projeto

O hexview é uma aplicação especializada na leitura e exibição de arquivos em formato hexadecimal acompanhado da representação ASCII. O projeto foi arquitetado com foco em programação de baixo nível, priorizando a eficiência no uso de recursos do sistema, previsibilidade de execução e alto desempenho em arquivos de grande porte.

## Motivação Técnica e Otimizações

Para garantir alta performance e baixo overhead, foram adotadas as seguintes estratégias:

* **I/O Bufferizado**: Uso de buffers de 64KB para melhor aproveitamento de cache e páginas de memória.
* **Lookup Table**: Conversão hexadecimal via tabelas estáticas, evitando funções genéricas custosas.
* **Bufferização Manual**: Montagem das linhas em buffer de stack com uma única escrita por linha.
* **Buffering de Saída**: Configuração de buffering total no `stdout` para reduzir syscalls.
* **Sem Alocação Dinâmica**: Uso apenas de memória estática e stack, evitando overhead do heap.

## Tecnologias Utilizadas

- **Linguagem**: C (Padrão ISO C11).
- **Compilador**: GCC.
- **Sistema de Build**: GNU Make com suporte a geração automática de dependências (.d).
- **Ambiente**: Compatível com sistemas Unix (POSIX).

## Como Compilar

Para compilar o projeto, utilize o Makefile fornecido:

```bash
make
```

## Como Executar

O programa aceita um caminho de arquivo como argumento:

```bash
./hexview <caminho_do_arquivo>
```

## Estrutura de Diretórios

```bash
├── include/     # Arquivos de cabeçalho (.h)
├── src/         # Implementação (.c)
├── build/       # Artefatos de compilação (gerado automaticamente)
├── Makefile     # Script de automação de build
└── README.md    # Documentação técnica
```

## Validação e Testes

Para garantir a integridade do visualizador, utilize os seguintes comandos para gerar arquivos de teste:

**1. Teste de ASCII e Alinhamento:**

```bash
echo "Teste de visualizacao para o projeto hexview." > teste_texto.txt
./hexview teste_texto.txt
```

**2. Teste de Dados Binários (1MB):**

```bash
head -c 1048576 /dev/urandom > teste_aleatorio.bin
time ./hexview teste_aleatorio.bin > /dev/null
```

**3. Teste de Padding (Fim de arquivo):**

``` bash
echo -n "1234567890" > teste_curto.bin
./hexview teste_curto.bin
```

## Possíveis Melhorias Futuras

* Implementação de flags para definir o tamanho da linha (atualmente fixo em 16 bytes).
* Suporte para colorização de bytes via sequências de escape ANSI.
* Implementação de busca por padrões hexadecimais (Grep-like).
* Opção de limitar a visualização a um range específico de bytes (seek/limit).

## Licença

Este projeto é distribuído sob os termos da Licença MIT. Consulte o arquivo [LICENSE](LICENSE) para mais detalhes.
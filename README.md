# ITP – Segunda Avaliação: Boletim de uma pequena turma

## Identificação

- **Nome:** [SEU NOME COMPLETO]
- **Projeto escolhido:** Opção 1 – Boletim de uma pequena turma

## Descrição

O programa resolve o problema de registrar três notas de cada estudante e obter um resumo dos resultados da turma. Foi escrito em C, em um único arquivo (`main.c`).

### Funcionalidades implementadas

- Solicita a quantidade de estudantes (de 1 a 10, número inteiro) e o nome de cada um. Nomes vazios ou só com espaços são rejeitados.
- Lê três notas por estudante, com valores entre 0 e 10. Notas fora do intervalo ou texto no lugar de número são rejeitados e a nota é solicitada novamente. A vírgula decimal também é aceita (ex.: `7,5`).
- Armazena as notas em uma matriz `notas[10][3]` (linhas = estudantes, colunas = avaliações).
- Calcula a média aritmética de cada estudante e guarda em um vetor alocado dinamicamente (`calloc`), com uma posição por estudante.
- Exibe uma tabela com nome, notas, média e situação: **"atingiu a meta"** quando a média é maior ou igual a 6, e **"abaixo da meta"** nos demais casos (regra do projeto, não a aprovação na disciplina).
- Exibe a média geral da turma e o nome de quem obteve a maior média; em caso de empate, exibe todos os nomes empatados.

### Organização do código

| Elemento | Uso |
|---|---|
| `float notas[10][3]` | matriz com as notas |
| `char nomes[10][50]` | nomes dos estudantes (lidos com `fgets`, respeitando o tamanho) |
| `double *medias` | vetor dinâmico de médias (`calloc`, verificação de `NULL` e `free`) |
| `calcular_medias(...)` | recebe a matriz e um ponteiro e escreve cada média em `medias[i]` |
| `ler_linha`, `ler_numero`, `ler_nome` | leitura e validação das entradas |
| `imprimir_nome`, `exibir_tabela`, `exibir_resumo` | saída formatada |

As notas são `float`; médias e somas são `double`, evitando perda de informação por divisão inteira.

## Compilação e execução

Requer o compilador GCC.

```
gcc -std=c11 -Wall -Wextra main.c -o programa
./programa
```

No Windows (por exemplo, com MinGW/MSYS2), use:

```
gcc -std=c11 -Wall -Wextra main.c -o programa.exe
.\programa.exe
```

Se os acentos aparecerem errados no terminal do Windows, execute `chcp 65001` antes de rodar o programa.

## Testes

### Teste 1 – funcionamento normal

**Entradas:**

```
Quantidade de estudantes: 2
Nome 1: Ana     Notas: 5, 6, 7
Nome 2: Bruno   Notas: 8, 9, 10
```

**Resultado esperado:**

```
Nome                  Nota1  Nota2  Nota3    Media  Situacao
Ana                     5.0    6.0    7.0     6.00  atingiu a meta
Bruno                   8.0    9.0   10.0     9.00  atingiu a meta

Media geral da turma: 7.50
Maior media (9.00): Bruno
```

A média de Ana (5, 6 e 7) é 6, portanto a situação é "atingiu a meta".

### Teste 2 – entradas inválidas e limites

**Entradas (em sequência):**

| Campo pedido | Valor digitado | Resultado esperado |
|---|---|---|
| Quantidade de estudantes | `0` | rejeitada: "Valor fora do intervalo [1, 10]" |
| Quantidade de estudantes | `11` | rejeitada: "Valor fora do intervalo [1, 10]" |
| Quantidade de estudantes | `1` | aceita |
| Nome do estudante 1 | *(vazio)* | rejeitado: "O nome nao pode ser vazio." |
| Nome do estudante 1 | `Carla` | aceito |
| Nota 1 | `11` | rejeitada: "Valor fora do intervalo [0, 10]" |
| Nota 1 | `abc` | rejeitada: "Entrada invalida. Digite um numero." |
| Nota 1, 2 e 3 | `4`, `6`, `8` | aceitas |

**Resultado final esperado:** média 6,00, situação "atingiu a meta", média geral 6,00 e maior média de Carla.

### Teste 3 (extra) – empate na maior média

Dois estudantes, Ana e Bia, ambas com notas 6, 6 e 6: o programa exibe `Maior media (6.00): Ana, Bia`.

## Vídeo

Apresentação no YouTube: [COLE AQUI O LINK DO VÍDEO]

## Referências

- Página da disciplina de ITP e Aulas 6 a 11 (matrizes, tipos de dados, strings, estrutura de memória, memória estática e heap, ponteiros e alocação dinâmica).
- Enunciado da Segunda Avaliação – Projeto em C.

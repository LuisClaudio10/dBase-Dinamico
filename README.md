# 💾 Simulador dBASE III PLUS com Listas Encadeadas Dinâmicas

Este projeto simula o funcionamento do ambiente dBASE III PLUS utilizando **linguagem C** com **listas encadeadas dinâmicas**, baseado em comandos clássicos como `CREATE`, `USE`, `APPEND`, `LIST`, `DISPLAY`, `DELETE`, `RECALL`, `PACK`, `ZAP`, `SORT` e outros.

## 📚 Objetivo

O objetivo do trabalho é aplicar os conceitos de estruturas de dados dinâmicas — como listas encadeadas — para representar e manipular arquivos `.DBF` inteiramente em memória, simulando o comportamento do antigo banco de dados **dBASE III PLUS**.

Projeto desenvolvido para a disciplina **Estruturas de Dados II** da **Faculdade de Informática de Presidente Prudente (FIPP)** – 1º Bimestre de 2025.

## 👨‍🏫 Professores
- Francisco Assis da Silva

## 🧱 Estrutura de Dados

As principais estruturas implementadas incluem:

- **Diretório** com duas unidades (`C:` e `D:`)
- **Arquivos DBF** contendo:
  - Nome do arquivo
  - Data e hora de criação
  - Lista de campos (nome, tipo, largura e decimais)
  - Lista de registros (`Status`) com valores

Campos disponíveis:
- `N` - Numérico
- `D` - Data (char[10])
- `L` - Lógico (char)
- `C` - Caracter (char[50])
- `M` - Memo (char[50])

## 📜 Comandos Implementados

| Comando            | Descrição                                                                 |
|--------------------|---------------------------------------------------------------------------|
| `SET DEFAULT TO D:`| Define a unidade ativa para D:                                            |
| `SET DEFAULT TO C:`| Define a unidade ativa para C:                                            |
| `CREATE`           | Cria um novo arquivo `.DBF` na unidade atual                              |
| `DIR`              | Lista todos os arquivos da unidade atual                                  |
| `USE`              | Abre um arquivo `.DBF` para uso                                           |
| `LIST STRUCTURE`   | Exibe a estrutura (campos) do arquivo aberto                              |
| `APPEND`           | Adiciona novos registros                                                  |
| `LIST`             | Lista todos os registros                                                  |
| `LIST FOR <campo> = <valor>` | Lista registros com filtro por campo                           |
| `DISPLAY`          | Exibe o registro atual                                                    |
| `EDIT`             | Permite editar o registro atual                                           |
| `DELETE`           | Marca o registro atual para exclusão lógica                               |
| `DELETE ALL`       | Marca todos os registros para exclusão                                    |
| `RECALL`           | Reativa o registro atual                                                  |
| `RECALL ALL`       | Reativa todos os registros excluídos (após SET DELETED OFF)              |
| `SET DELETED ON/OFF`| Exibe ou oculta registros marcados para exclusão                         |
| `PACK`             | Remove permanentemente os registros excluídos                             |
| `ZAP`              | Remove todos os registros do arquivo                                      |
| `GOTO <n>`         | Vai para o registro número `<n>`                                          |
| `LOCATE FOR <campo> = <valor>` | Localiza o primeiro registro que corresponde                   |
| `MODIFY STRUCTURE` | Permite editar ou adicionar campos (se não houver registros)             |
| `SORT <campo>`     | Ordena os registros por um campo específico                               |
| `CLEAR`            | Limpa a tela                                                              |
| `QUIT`             | Encerra o programa                                                        |

## 🖥️ Interface

O programa simula um terminal semelhante ao **dBASE original das décadas de 80 e 90**, usando `conio2.h` para desenhar molduras, campos e comandos com destaque em tela.

## 📦 Compilação e Execução

Este projeto foi desenvolvido para ambiente **Windows** e usa bibliotecas específicas como `conio2.h`.

### Pré-requisitos:
- Compilador C (ex: Dev-C++, Code::Blocks com MinGW, Turbo C)
- Sistema Windows (uso de `windows.h` e `conio2.h`)

### Compilação:
```bash
gcc main.c -o dbase.exe -lconio

# lista-1-INF006

## Questões

### Questão 1
Cada linha, um `start` marca o início de uma lista de números naturais que acaba na ocorrência do próximo `start` ou na quebra de linha. No arquivo de saída devem aparecer todas as listas em ordem crescente. As listas deverão também ser ordenadas entre si conforme a soma de seus elementos.

**Arquivo de entrada:** `L1Q1.in`  
**Arquivo de saída:** `L1Q1.out`  
**Código fonte:** [`RL1Q1.c`](lista%201/RL1Q1.c)

### Questão 2
Implemente uma pilha de texto onde todos os elementos estão sempre ordenados alfabeticamente sem ferir a política LIFO (last-in, first-out).

**Arquivo de entrada:** `L1Q2.in`  
**Arquivo de saída:** `L1Q2.out`  
**Código fonte:** [`RL1Q2.c`](lista%201/RL1Q2.c)

### Questão 3
Considere uma lista duplamente ligada não-circular onde cada elemento possui uma chave inteira. Cada elemento dessa lista pode ter associado a ele uma outra lista simplesmente ligada circular também de valores reais que diferem deste por no máximo 0,99. Todas as listas devem estar ordenadas.

**Arquivo de entrada:** `L1Q3.in`  
**Arquivo de saída:** `L1Q3.out`  
**Código fonte:** [`RL1Q3.c`](lista%201/RL1Q3.c)

## Configuração do ambiente

Para compilar e depurar os códigos, utilize o Visual Studio Code com as seguintes configurações:

- **Compilador:** gcc
- **Depurador:** gdb

### Arquivo `tasks.json`

Configuração para compilar os arquivos `.c`:

```json
{
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: gcc arquivo de build ativo",
            "command": "/usr/bin/gcc",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}/${fileBasenameNoExtension}"
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "Tarefa gerada pelo Depurador."
        }
    ],
    "version": "2.0.0"
}
```
### Como executar

1. Abra o **Visual Studio Code**.
2. Abra a pasta do projeto `cd lista 1`  .
3. Compile o código utilizando a tarefa de build (`Ctrl+Shift+B`).
4. Inicie a depuração (`F5`).

### Licença
Este projeto está licenciado sob a licença MIT. Veja o arquivo LICENSE para mais detalhes. 
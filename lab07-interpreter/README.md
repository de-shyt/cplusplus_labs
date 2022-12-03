# Lab №7 (interpreter)

An interpreter for an assembler-like programming language. There are ten registers from $\$0$ to $\$9$. Each register saves a matrix of a random size with integers. 

Possible commands:

- load a matrix from a file into a register
- show a matrix saved in a spesific register
- addition and multiplication of matrixes

On default, each register saves a matrix of size $0 \times 0$.



### Format of commands

A string splits into tokens. The first token is the name of the command.

If the command is unknown, a message `Unknown command: <command>` is shown. For other errors a message `Invalid command format` is shown. 

If one of parameters for a command is a register, it is writen as `$<digit>`, where `digit` is a number of a register. If a register is required, but something else is got, a message `<smth unknown> is not a register`. 



#### `load`

Gets two parameters: a ragister and a file name. Loads a matrix to a register from a file. Elements of a matrix are numbers $n \ : \ |n| \leqslant 100$.  

If it is impossible to open a file, a message `Unable to open file <filename>` is shown.

File format is:

```txt
<#rows, positive number <= 10^6> <#cols, positive number <= 10^6>
<element 0-0> ... <element 0-#cols>
...
<element #rows-0> ... <element #rows-#cols>
```

If a file has another format, a message `Invalid file format` is shown. 



#### `print`

Gets one parameter: a register and writes a matrix to `stdout`. 



#### `elem`

Gets three parameters: a register, numbers of a row $\texttt{r}$ and a colomn $\texttt{c}$.   $0 \leqslant \texttt{r, c}$.

Writes an element on a position $\texttt{[r][c]}$. 

If an element does not exist, a message `Requested element is out of bounds` is shown. 



#### `exit`
The interpreter successfuly terminates. 



#### `add`

Gets two parameters: registers $A$ and $B$. Writes a result of $A + B$ to $A$.

If sizes of matrixes are different, a message `Dimension mismatch: lhs=<A>, rhs=<B>` is shown, where `lhs` and `rhs` are ismismatched characteristics of matrixes. 



#### `mul`
Gets two parameters: registers $A$ and $B$. Writes a result of $A \cdot B$ to $A$. 

If sizes of matrixes are different, a message `Dimension mismatch: lhs=<A>, rhs=<B>` is shown, where `lhs` and `rhs` are ismismatched characteristics of matrixes. 

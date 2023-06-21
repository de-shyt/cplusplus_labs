# Lab №5 (Tic Tac Toe)

A console game tic-tac-toe on a field $10 \times 10$. The view of the field can be changed during the game session. 



### Rules 

The field has a size of $10 \times 10$. A user with `O` starts the game.  The aim of the game is to have 5 symbols of the same type in a row. 

When the application is launched, an argument `view-compact` or `view-pretty` can be added:

```
./tic-tac-toe view-compact
```

The default view is `view-compact`. 



### Possible commands

| Command              | Behaviour                                         |
| :------------------- | :------------------------------------------------ |
| `<number>, <number>` | Make a move on a cell with respective coordinates |
| `view-pretty`        | Change a view mode to a pretty mode               |
| `view-compact`       | Change a view mode to a compact mode              |
| `<empty line>`       | The application successfully terminates           |

The result of one session can be one of the messages: `X wins!`, `O wins!` или `Draw.`




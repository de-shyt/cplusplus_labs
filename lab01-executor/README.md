# Lab №1 (executor)

This task consists of 2 parts:

1. ### Quote book

   Commands `sherlock-holmes` and `cat-jeoffry` show fragments from Sherlock Holmes and Jubilate Agno respectively.
   Command `quit` exits the interpreter.
   Commands can have pseudonyms. 

   Invalid commands should lead to a message `Invalid command: <command>`.

   | pseudonyms                    | Behaviour                            |
   | ----------------------------- | ------------------------------------ |
   | `quit`, `exit`                | Successful exit from the interpreter |
   | `sherlock`, `sherlock-holmes` | Show a quote from Sherlock Holmes    |
   | `cat`, `cat-jeoffry`          | Show a qoute from Jubilate Agno      |

   

   Quote from Sherlock Holmes:

   ```txt
   I had had so many reasons to believe in my friend's subtle powers of
   reasoning and extraordinary energy in action that I felt that he must
   have some solid grounds for the assured and easy demeanour with which
   he treated the singular mystery which he had been called upon to
   fathom. Once only had I known him to fail, in the case of the King of
   Bohemia and of the Irene Adler photograph; but when I looked back to
   the weird business of the Sign of Four, and the extraordinary
   circumstances connected with the Study in Scarlet, I felt that it would
   be a strange tangle indeed which he could not unravel.
   ```

   

   Quote from Jubilate Agno:

   ```txt
   For he is of the tribe of Tiger.
   For the Cherub Cat is a term of the Angel Tiger.
   For he has the subtlety and hissing of a serpent, which in goodness he suppresses.
   For he will not do destruction, if he is well-fed, neither will he spit without provocation.
   For he purrs in thankfulness, when God tells him he's a good Cat.
   For he is an instrument for the children to learn benevolence upon.
   For every house is incomplete without him and a blessing is lacking in the spirit.
   For the Lord commanded Moses concerning the cats at the departure of the Children of Israel from Egypt.
   For every family had one cat at least in the bag.
   For the English Cats are the best in Europe.
   ```

   

2. ### Wanderer

   A wanderer walks no the infinite plane. Initially, the wanderer is in `(0, 0)` and looks to the cell above them. 

   Commands allow to move forward and backward; turn around on 90 degrees to the left and to the right; show the map.

   Also, reconding of a sequnce of commands is supported. The recorded sequence can be executed later. 

   

   | Pseudonyms            | Behaviour                                      |
   | --------------------- | ---------------------------------------------- |
   | `forward`, `fwd`      | pass one cell forward                          |
   | `backward`, `bwd`     | pass one cell backward                         |
   | `turn-right`, `right` | turn around on 90 degrees clockwise            |
   | `turn-left`, `left`   | turn around on 90 degrees counterclockwise     |
   | `show-map`            | show the current map                           |
   | `start-macro`         | Start a recond of a sequnce of commands        |
   | `run-macro`           | Execute the last recorded sequence of commands |

   #### 

   #### Format of showing a map:

   Find a minimum rectangle which contains all cells visited by the wanderer. The cells are shown as symbols:

   * `.` — клетка ещё не была посещена игроком;
   * `o` — клетка была посещена игроком;
   * `^`/`>`/`v`/`<` — игрок сейчас находится в этой клетке и смотрит наверх/направо/вниз/налево.

   Reconding a sequnce of commands

   

   #### Macros

   The interpreter remembers only one macro -- the last recorded sequnce of commands. 

   We the recording is on, commands are read from `stdin`, saved to the macro and then a message `Recorded` is shown in `stdout`. 

   Commands that can be recorded are `forward`, `backward`, `turn-right`, `turn-left`, `show-map` and their pseudonyms. Other commands lead to a message `Invalid command` and ignored. 

   The recording finishes with a command `end-macro`, and a message `New macro of <amount> command(s)`  is shown in `stdout`.

   The macro can be executed via a command `run-macro`.

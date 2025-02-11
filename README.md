# ReversiConsole
Implementation of the strategy game [Reversi](https://en.wikipedia.org/wiki/Reversi) as a console application with 
move validation a simple TUI and a computer opponent. The game is implemented in C++ in a modular way, with the game 
logic separated from the user interface. The game can be played by two human players or by a human player against a
computer opponent. The computer opponent uses a minmax variant with alpha-beta pruning to determine its moves.

## How to play
1. Clone the repository
2. In the project root, run:
    ```shell
    mkdir build
    cd build
    cmake ..
    make
    ./ReversiConsole
    ```
3. Follow the instructions on the screen to play the game.

## Screenshots
![Reversi](resources/Reversi.png "Reversi")
#include "game.h"
#include "view.h"

#include <iostream>

tictactoe::Game::commands tictactoe::Game::parse_line(std::string &s, std::unique_ptr<Game> &game_ptr) {
    std::stringstream input;
    input << s;
    std::string tmp1;
    std::string tmp2;
    input >> tmp1 >> tmp2;
    if (tmp2.empty()) {
        if (tmp1 == "exit" || tmp1 == "quit" || tmp1 == "q") {
            return tictactoe::Game::commands::exit;
        }
        if (tmp1 == "view-compact") {
            return tictactoe::Game::commands::change_view_compact;
        }
        if (tmp1 == "view-pretty") {
            return tictactoe::Game::commands::chang_view_pretty;
        }
        return tictactoe::Game::commands::bad_move;
    }
    try {
        int x = stoi(tmp1);
        int y = stoi(tmp2);
        if (game_ptr->move(x, y)) {
            return tictactoe::Game::commands::make_move;
        }
    } catch (...) {
        return tictactoe::Game::commands::bad_move;
    }
    return tictactoe::Game::commands::bad_move;
}

void tictactoe::Game::change_player() {
    if (player == OptionalPlayer::O) {
        player = OptionalPlayer::X;
    } else {
        player = OptionalPlayer::O;
    }
}

bool tictactoe::Game::move(int x, int y) {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE ||
        field[x][y] != OptionalPlayer::free) {
        return false;
    }
    field[x][y] = player;
    return true;
}

tictactoe::OptionalPlayer tictactoe::Game::check_winner() {
    int O_amount, X_amount;
    for (int i = 0; i < SIZE; ++i) {
        O_amount = 0, X_amount = 0;
        for (int j = 0; j < SIZE; ++j) {
            if (field[i][j] == OptionalPlayer::X)
                X_amount++;
            else if (field[i][j] == OptionalPlayer::O)
                O_amount++;
        }
        if (O_amount == SIZE)
            return OptionalPlayer::O;
        if (X_amount == SIZE)
            return OptionalPlayer::X;
    }
    for (int j = 0; j < SIZE; ++j) {
        O_amount = 0, X_amount = 0;
        for (int i = 0; i < SIZE; ++i) {
            if (field[i][j] == OptionalPlayer::X)
                X_amount++;
            else if (field[i][j] == OptionalPlayer::O)
                O_amount++;
        }
        if (O_amount == SIZE)
            return OptionalPlayer::O;
        if (X_amount == SIZE)
            return OptionalPlayer::X;
    }
    O_amount = 0, X_amount = 0;
    for (int i = 0; i < SIZE; ++i) {
        if (field[i][i] == OptionalPlayer::O)
            O_amount++;
        else if (field[i][i] == OptionalPlayer::X)
            X_amount++;
    }
    if (O_amount == SIZE)
        return OptionalPlayer::O;
    if (X_amount == SIZE)
        return OptionalPlayer::X;
    O_amount = 0, X_amount = 0;
    for (int i = 0; i < SIZE; ++i) {
        if (field[i][SIZE - i - 1] == OptionalPlayer::O)
            O_amount++;
        else if (field[i][SIZE - i - 1] == OptionalPlayer::X)
            X_amount++;
    }
    if (O_amount == SIZE)
        return OptionalPlayer::O;
    if (X_amount == SIZE)
        return OptionalPlayer::X;
    return OptionalPlayer::free;
}

void tictactoe::Game::terminating_process(OptionalPlayer winner) {
    if (winner == OptionalPlayer::X)
        std::cout << "X wins!\n";
    else if (winner == OptionalPlayer::O)
        std::cout << "O wins!\n";
    else std::cout << "Draw.\n";
}

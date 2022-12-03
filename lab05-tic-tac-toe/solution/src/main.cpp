#include <iostream>
#include <memory>
#include <string>
#include <cstring>
#include <map>
#include <cmath>
#include "game.h"
#include "view.h"

namespace tictactoe {
    void line_who_moves(const std::unique_ptr<Game> &game_ptr) {
        if (game_ptr->player == OptionalPlayer::X) {
            std::cout << "X move: ";
        } else {
            std::cout << "O move: ";
        }
    }

    std::map<view_types, View *> views
    {
            {view_types::compact, new view_compact()},
            {view_types::pretty,  new view_pretty()}
    };
}  // namespace tictactoe

int main(int argc, char **argv) {
    std::unique_ptr<tictactoe::Game> game(new tictactoe::Game());

    tictactoe::View* cur_view = tictactoe::views[tictactoe::view_types::compact];
    if (argc > 1) {
        if (strcmp(argv[1], "view-pretty") == 0) {
            cur_view = tictactoe::views[tictactoe::view_types::pretty];
        }
    }

    cur_view->print_field(game);
    line_who_moves(game);

    int correct_moves_amount = 0;
    std::string arguments;
    std::getline(std::cin, arguments);
    while (!arguments.empty()) {
        auto answer = game->parse_line(arguments, game);
        if (answer == tictactoe::Game::commands::exit) {
            return 0;
        }
        if (answer == tictactoe::Game::commands::change_view_compact) {
            cur_view = tictactoe::views[tictactoe::view_types::compact];
        }
        else if (answer == tictactoe::Game::commands::chang_view_pretty) {
            cur_view = tictactoe::views[tictactoe::view_types::pretty];
        }
        else if (answer == tictactoe::Game::commands::bad_move) {
            std::cout << "Bad move!\n";
        }
        else {
            cur_view->print_field(game);
            correct_moves_amount++;
            if (correct_moves_amount == static_cast<int>(pow(tictactoe::SIZE, 2))) {
                game->terminating_process(tictactoe::OptionalPlayer::free);
                return 0;
            }
            auto maybe_winner = game->check_winner();
            if (maybe_winner == tictactoe::OptionalPlayer::free) {
                game->change_player();
            } else {
                game->terminating_process(maybe_winner);
                return 0;
            }
        }
        line_who_moves(game);
        arguments.clear();
        std::getline(std::cin, arguments);
    }
}

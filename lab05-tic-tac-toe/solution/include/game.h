#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <vector>
#include <memory>
#include <map>

namespace tictactoe {
    const int SIZE = 10;

    enum class OptionalPlayer {
        O, X, free
    };

    struct Game {
        OptionalPlayer player = OptionalPlayer::O;
        std::vector<std::vector<OptionalPlayer>> field;

        Game() : field(std::vector<std::vector<OptionalPlayer>>(
                SIZE,
                std::vector<OptionalPlayer>(SIZE, OptionalPlayer::free))) {
        }

        enum class commands {
            exit, change_view_compact, chang_view_pretty, bad_move, make_move
        };

        commands parse_line(std::string &s, std::unique_ptr<Game> &game_ptr);

        void change_player();

        bool move(int x, int y);

        OptionalPlayer check_winner();

        void terminating_process(OptionalPlayer winner);
    };
}  // namespace tictactoe
#endif  // GAME_H_
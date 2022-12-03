#include "view.h"

void tictactoe::view_compact::print_field(std::unique_ptr<Game> &game_ptr) {
    std::cout << '\n';
    for (auto &line: game_ptr->field) {
        std::string answer;
        for (auto j: line) {
            if (j == OptionalPlayer::O) {
                answer += "O";
            } else if (j == OptionalPlayer::X) {
                answer += "X";
            } else {
                answer += ".";
            }
        }
        std::cout << answer << '\n';
    }
}
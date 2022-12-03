#include "view.h"

char tictactoe::view_pretty::get_symbol(OptionalPlayer symb, int di, int dj) {
    if (dj == 1 || dj == 4)
        return ' ';
    if (symb == OptionalPlayer::O)
        return '@';
    if (symb == OptionalPlayer::free)
        return ' ';
    else {
        if (di + dj == 4)
            return '/';
        else return '\\';
    }
}

void tictactoe::view_pretty::print_field(std::unique_ptr<Game> &game_ptr) {
    std::cout << '\n';
    for (int i = 0, i_field = 0; i <  3 * SIZE + 1; ++i, i_field += (i % 3 == 0 ? 1 : 0)) {
        std::string answer;
        for (int j = 0, j_field = 0; j < 5 * SIZE + 1; ++j, j_field += (j % 5 == 0 ? 1 : 0)) {
            if (i % 3 == 0) {
                if (j % 5 == 0)
                    answer += '+';
                else answer += '-';
                continue;
            }
            if (j % 5 == 0) {
                answer += '|';
                continue;
            }
            answer += get_symbol(game_ptr->field[i_field][j_field], i % 3, j % 5);
//            std::cout << answer << '\n';
        }
        std::cout << answer << '\n';
    }
}
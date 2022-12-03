#ifndef VIEW_H_
#define VIEW_H_

#include <memory>
#include <sstream>
#include <string>
#include <map>
#include "game.h"

namespace tictactoe {
    struct View {
        View(const View &) = delete;

        View(View &&) = delete;

        View &operator=(const View &) = delete;

        View &operator=(View &&) = delete;

        View() = default;

        virtual ~View() = default;

        virtual void print_field(std::unique_ptr<Game> &game_ptr) = 0;
    };

    struct view_compact : View {
        view_compact() = default;

        void print_field(std::unique_ptr<Game> &game_ptr) override;
    };

    struct view_pretty : View {
        view_pretty() = default;

        void print_field(std::unique_ptr<Game> &game_ptr) override;

        char get_symbol(OptionalPlayer symb, int di, int dj);
    };

    enum class view_types {
        compact, pretty
    };
}  // namespace tictactoe
#endif  // VIEW_H_
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

void show_map(const std::map<long, std::set<long>> &visited_dots,
              const long &x,
              const long &y,
              char direction) {
    long x_min = 0;
    long x_max = 0;

    for (const auto &it : visited_dots) {
        auto it_x_forward = it.second.begin();
        x_min = std::min(x_min, *it_x_forward);
        auto it_x_reverse = it.second.rbegin();
        x_max = std::max(x_max, *it_x_reverse);
    }

    std::string spaces_line;
    for (int i = 0; i < x_max - x_min + 1; i++) {
        spaces_line += "  ";
    }
    spaces_line += " \n";

    std::cout << spaces_line;

    auto it_y = visited_dots.rbegin();
    while (it_y != visited_dots.rend()) {
        auto it_x = it_y->second.begin();
        std::string one_line = " ";
        for (long i = x_min; i <= x_max; i++) {
            if (it_x != it_y->second.end() && i == *it_x) {
                if (it_y->first == y && i == x) {
                    one_line.push_back(direction);
                    one_line += " ";
                } else {
                    one_line += "o ";
                }
                it_x++;
            } else {
                one_line += ". ";
            }
        }
        std::cout << one_line << '\n' << spaces_line;
        it_y++;
    }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity,-warnings-as-errors)
int main() {
    const char *holmes =
        R"(I had had so many reasons to believe in my friend's subtle powers of
reasoning and extraordinary energy in action that I felt that he must
have some solid grounds for the assured and easy demeanour with which
he treated the singular mystery which he had been called upon to
fathom. Once only had I known him to fail, in the case of the King of
Bohemia and of the Irene Adler photograph; but when I looked back to
the weird business of the Sign of Four, and the extraordinary
circumstances connected with the Study in Scarlet, I felt that it would
be a strange tangle indeed which he could not unravel.)";

    const char *jeof = R"(For he is of the tribe of Tiger.
For the Cherub Cat is a term of the Angel Tiger.
For he has the subtlety and hissing of a serpent, which in goodness he suppresses.
For he will not do destruction, if he is well-fed, neither will he spit without provocation.
For he purrs in thankfulness, when God tells him he's a good Cat.
For he is an instrument for the children to learn benevolence upon.
For every house is incomplete without him and a blessing is lacking in the spirit.
For the Lord commanded Moses concerning the cats at the departure of the Children of Israel from Egypt.
For every family had one cat at least in the bag.
For the English Cats are the best in Europe.)";

    std::stringstream stream;
    std::string s;
    std::string g;
    std::string g2;

    std::vector<int> dx = {0, 1, 0, -1};
    std::vector<int> dy = {1, 0, -1, 0};
    std::vector<char> direction = {'^', '>', 'v', '<'};
    int where = 0;

    enum class AllCommands {
        fwd,
        bwd,
        right,
        left,
        map,
        jeof,
        holmes,
        exit,
        startmac,
        endmac,
        runmac
    };

    std::map<std::string, AllCommands> entered_commands = {
        {"fwd", AllCommands::fwd},
        {"forward", AllCommands::fwd},
        {"bwd", AllCommands::bwd},
        {"backward", AllCommands::bwd},
        {"right", AllCommands::right},
        {"turn-right", AllCommands::right},
        {"left", AllCommands::left},
        {"turn-left", AllCommands::left},
        {"show-map", AllCommands::map},
        {"start-macro", AllCommands::startmac},
        {"end_macro", AllCommands::endmac},
        {"run-macro", AllCommands::runmac},
        {"cat", AllCommands::jeof},
        {"cat-jeoffry", AllCommands::jeof},
        {"sherlock", AllCommands::holmes},
        {"sherlock-holmes", AllCommands::holmes},
        {"exit", AllCommands::exit},
        {"quit", AllCommands::exit}};

    std::map<long, std::set<long>> visited_dots;
    long x = 0;
    long y = 0;
    visited_dots[y].insert(x);

    bool running_macro = false;
    std::vector<std::string> macro_commands;
    int i_macro = 0;

    while ((!running_macro && std::getline(std::cin, s)) || running_macro) {
        stream.clear();
        g.clear();
        g2.clear();

        if (!running_macro) {
            stream.str(s);
        } else {
            stream.str(macro_commands[i_macro++]);
            if (i_macro == static_cast<int>(macro_commands.size())) {
                running_macro = false;
            }
        }

        stream >> g >> g2;

        if (g.empty() || !g2.empty()) {
            std::cout << "Invalid command: '" << s << "'\n";
            continue;
        }
        auto it_user_command = entered_commands.find(g);
        if (it_user_command == entered_commands.end()) {
            std::cout << "Invalid command: '" << s << "'\n";
            continue;
        }
        if (it_user_command->second == AllCommands::jeof) {
            std::cout << jeof << '\n';
        } else if (it_user_command->second == AllCommands::holmes) {
            std::cout << holmes << '\n';
        } else if (it_user_command->second == AllCommands::exit) {
            return 0;
        } else if (it_user_command->second == AllCommands::right) {
            where = (where + 1) % 4;
        } else if (it_user_command->second == AllCommands::left) {
            where = (where + 3) % 4;
        } else if (it_user_command->second == AllCommands::fwd ||
                   it_user_command->second == AllCommands::bwd) {
            if (it_user_command->second == AllCommands::bwd) {
                where = (where + 2) % 4;
            }

            /*
             * direction    ^       >        v        <
             *     where    0       1        2        3
             *   (dx,dy)  (0,1)   (1,0)   (0,-1)   (-1,0)
             */

            y += dy[where];
            x += dx[where];
            visited_dots[y].insert(x);

            if (it_user_command->second == AllCommands::bwd) {
                where = (where + 2) % 4;
            }
        } else if (it_user_command->second == AllCommands::map) {
            show_map(visited_dots, x, y, direction[where]);
        } else if (it_user_command->second == AllCommands::startmac) {
            std::map<std::string, AllCommands> valid_commands = {
                {"fwd", AllCommands::fwd},
                {"forward", AllCommands::fwd},
                {"bwd", AllCommands::bwd},
                {"backward", AllCommands::bwd},
                {"right", AllCommands::right},
                {"turn-right", AllCommands::right},
                {"left", AllCommands::left},
                {"turn-left", AllCommands::left},
                {"show-map", AllCommands::map},
                {"end-macro", AllCommands::endmac}};

            macro_commands.clear();
            while (true) {
                stream.clear();
                g.clear();
                g2.clear();
                std::getline(std::cin, s);
                stream.str(s);
                stream >> g >> g2;
                if (g.empty() || !g2.empty()) {
                    std::cout << "Invalid command: '" << s << "'\n";
                    continue;
                }
                auto it = valid_commands.find(g);
                if (it == valid_commands.end()) {
                    std::cout << "Invalid command: '" << s << "'\n";
                    continue;
                }
                if (it->second == AllCommands::endmac) {
                    break;
                } else {
                    macro_commands.push_back(g);
                    std::cout << "Recorded\n";
                }
            }
            std::cout << "New macro of " << macro_commands.size()
                      << " command(s)\n";
        } else if (it_user_command->second == AllCommands::runmac) {
            if (!macro_commands.empty()) {
                running_macro = true;
                i_macro = 0;
            }
        }
    }
}

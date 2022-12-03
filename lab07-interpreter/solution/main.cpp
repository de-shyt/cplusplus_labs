#include "matrix.h"
#include <map>
#include <sstream>

int main() {
    std::map<std::string, std::size_t> param_amount{{"exit", 0}, {"print", 1},
                                                    {"add", 2},  {"load", 2},
                                                    {"mul", 2},  {"elem", 3}};

    std::vector<matrix_interpreter::matrix> matrices(10);

    std::stringstream stream;
    std::string tmp;
    while (std::getline(std::cin, tmp)) {
        stream.clear();
        stream.str(tmp);

        std::string word;
        stream >> word;

        try {
            if (param_amount.count(word) == 0) {
                throw custom_exceptions::unknown_command(word);
            }

            std::vector<std::string> params;

            while (stream >> tmp) {
                params.push_back(tmp);
            }

            if (param_amount[word] != params.size()) {
                throw custom_exceptions::invalid_command_format();
            }

            if (word == "exit") {
                return 0;
            }

            if (word == "add") {
                int regA = params::check_param(params[0]);
                int regB = params::check_param(params[1]);
                matrix_interpreter::add(regA, regB, matrices);
                continue;
            }

            if (word == "mul") {
                int regA = params::check_param(params[0]);
                int regB = params::check_param(params[1]);
                matrix_interpreter::mul(regA, regB, matrices);
                continue;
            }

            int reg = params::check_param(params[0]);

            if (word == "print") {
                matrix_interpreter::print(reg, matrices);
            }

            else if (word == "load") {
                matrix_interpreter::load(reg, params[1], matrices);
            }

            else if (word == "elem") {
                try {
                    matrix_interpreter::elem(reg, std::stoi(params[1]),
                                             std::stoi(params[2]), matrices);
                } catch (const std::invalid_argument &) {
                    throw custom_exceptions::invalid_command_format();
                }
            }
        } catch (const std::bad_alloc &) {
            std::cout << "Unable to allocate memory\n";
        } catch (const std::exception &e) {
            std::cout << e.what();
        }

        tmp.clear();
    }
}

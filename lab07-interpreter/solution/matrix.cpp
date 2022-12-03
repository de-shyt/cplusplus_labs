#include "matrix.h"
#include <climits>
#include <cmath>
#include <utility>

custom_exceptions::unknown_command::unknown_command(std::string &word)
    : std::runtime_error("Unknown command: '" + word + "'\n") {
}

custom_exceptions::invalid_command_format::invalid_command_format()
    : std::runtime_error("Invalid command format\n") {
}

custom_exceptions::not_a_register::not_a_register(std::string &reg)
    : std::runtime_error("'" + reg + "' is not a register\n") {
}

custom_exceptions::unable_to_open_a_file::unable_to_open_a_file(
    const std::string &name)
    : std::runtime_error("Unable to open file '" + name + "'\n") {
}

custom_exceptions::invalid_file_format::invalid_file_format()
    : std::runtime_error("Invalid file format\n") {
}

custom_exceptions::elem_out_of_bounds::elem_out_of_bounds()
    : std::runtime_error("Requested element is out of bounds\n") {
}

custom_exceptions::dimension_mismatch::dimension_mismatch(std::size_t value1,
                                                          std::size_t value2)
    : std::runtime_error("Dimension mismatch: lhs=" + std::to_string(value1) +
                         ", rhs=" + std::to_string(value2) + "\n") {
}

custom_exceptions::int_overflow::int_overflow(int lhs, int rhs, char op)
    : std::runtime_error("int overflow: " + std::to_string(lhs) + ' ' + op +
                         ' ' + std::to_string(rhs) + " is not int.\n") {
}

int check_overflow::sum(int lhs, int rhs) {
    if (lhs >= 0) {
        if (INT_MAX - lhs < rhs) {
            throw custom_exceptions::int_overflow(lhs, rhs, '+');
        }
    } else {
        if (rhs < INT_MIN - lhs) {
            throw custom_exceptions::int_overflow(lhs, rhs, '+');
        }
    }
    return lhs + rhs;
}

int check_overflow::mul(int lhs, int rhs) {
    if (abs(lhs) > INT_MAX / abs(rhs)) {
        throw custom_exceptions::int_overflow(lhs, rhs, '*');
    }
    return lhs * rhs;
}

matrix_interpreter::matrix::matrix() = default;

matrix_interpreter::matrix::matrix(std::size_t rows, std::size_t cols) {
    if (cols != 0 && rows != 0) {
        data = std::vector<std::vector<int>>(rows, std::vector<int>(cols, 0));
    }
}

[[nodiscard]] std::size_t matrix_interpreter::matrix::get_rows() const {
    return data.size();
}

[[nodiscard]] std::size_t matrix_interpreter::matrix::get_cols() const {
    return data[0].size();
}

[[nodiscard]] int matrix_interpreter::matrix::get_matrix_elem(
    std::size_t i,
    std::size_t j) const {
    return data[i][j];
}

void matrix_interpreter::matrix::set_matrix_elem(std::size_t i,
                                                 std::size_t j,
                                                 int value) {
    data[i][j] = value;
}

void matrix_interpreter::matrix::update(const matrix_interpreter::matrix &src) {
    std::size_t rows = src.get_rows();
    std::size_t cols = src.get_cols();
    data.resize(rows);
    for (std::size_t i = 0; i < rows; i++) {
        data[i].resize(cols);
        for (std::size_t j = 0; j < cols; j++) {
            set_matrix_elem(i, j, src.get_matrix_elem(i, j));
        }
    }
}

void matrix_interpreter::load(
    int reg,
    const std::string &filename,
    std::vector<matrix_interpreter::matrix> &matrices) {
    std::ifstream f(filename);
    if (!f.is_open()) {
        throw custom_exceptions::unable_to_open_a_file(filename);
    }
    f.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    try {
        std::size_t rows = 0;
        f >> rows;
        std::size_t cols = 0;
        f >> cols;
        if (rows > 1000000 || cols > 1000000) {
            throw custom_exceptions::invalid_command_format();
        }
        matrix m_(rows, cols);
        if (rows != 0 && cols != 0) {
            for (std::size_t i = 0; i < rows; i++) {
                for (std::size_t j = 0; j < cols; j++) {
                    int value = 0;
                    f >> value;
                    if (value > 100) {
                        throw custom_exceptions::invalid_command_format();
                    }
                    m_.set_matrix_elem(i, j, value);
                }
            }
        }
        matrices[reg] = m_;
    } catch (const std::ios_base::failure &) {
        throw custom_exceptions::invalid_file_format();
    }
}

void matrix_interpreter::print(
    int reg,
    std::vector<matrix_interpreter::matrix> &matrices) {
    for (std::size_t i = 0; i < matrices[reg].get_rows(); i++) {
        for (std::size_t j = 0; j < matrices[reg].get_cols(); j++) {
            if (j != 0) {
                std::cout << ' ';
            }
            std::cout << matrices[reg].get_matrix_elem(i, j);
        }
        std::cout << '\n';
    }
}

void matrix_interpreter::elem(
    int reg,
    int i,
    int j,
    std::vector<matrix_interpreter::matrix> &matrices) {
    if (i < 0 || i > 10000000 || j < 0 || j > 1000000) {
        throw custom_exceptions::invalid_command_format();
    }
    auto i_cpy = static_cast<std::size_t>(i);
    auto j_cpy = static_cast<std::size_t>(j);
    if (matrices[reg].get_rows() > i_cpy && matrices[reg].get_cols() > j_cpy) {
        std::cout << matrices[reg].get_matrix_elem(i_cpy, j_cpy) << '\n';
    } else {
        throw custom_exceptions::elem_out_of_bounds();
    }
}

void matrix_interpreter::add(
    int A,
    int B,
    std::vector<matrix_interpreter::matrix> &matrices) {
    std::size_t rows = matrices[A].get_rows();
    if (rows != matrices[B].get_rows()) {
        throw custom_exceptions::dimension_mismatch(rows,
                                                    matrices[B].get_rows());
    }

    std::size_t cols = matrices[A].get_cols();
    if (cols != matrices[B].get_cols()) {
        throw custom_exceptions::dimension_mismatch(cols,
                                                    matrices[B].get_cols());
    }

    matrix answer(rows, cols);

    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            answer.set_matrix_elem(
                i, j,
                check_overflow::sum(matrices[A].get_matrix_elem(i, j),
                                    matrices[B].get_matrix_elem(i, j)));
        }
    }

    matrices[A].update(answer);
}

void matrix_interpreter::mul(
    int A,
    int B,
    std::vector<matrix_interpreter::matrix> &matrices) {
    std::size_t K = matrices[A].get_cols();
    if (K != matrices[B].get_rows()) {
        throw custom_exceptions::dimension_mismatch(K, matrices[B].get_rows());
    }

    std::size_t rows = matrices[A].get_rows();
    std::size_t cols = matrices[B].get_cols();

    matrix answer(rows, cols);

    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            int result = 0;
            for (std::size_t k = 0; k < K; k++) {
                result = check_overflow::sum(
                    result,
                    check_overflow::mul(matrices[A].get_matrix_elem(i, k),
                                        matrices[B].get_matrix_elem(k, j)));
            }
            answer.set_matrix_elem(i, j, result);
        }
    }

    matrices[A].update(answer);
}

int params::check_param(std::string &param) {
    if (param[0] == '$' && param.size() == 2) {
        return std::stoi(param.substr(1, 1));
    }
    throw custom_exceptions::not_a_register(param);
}

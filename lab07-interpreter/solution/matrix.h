#ifndef MATRIX_INTERPRETER_H_
#define MATRIX_INTERPRETER_H_
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace custom_exceptions {
struct unknown_command : std::runtime_error {
    explicit unknown_command(std::string &word);
};

struct invalid_command_format : std::runtime_error {
    invalid_command_format();
};

struct not_a_register : std::runtime_error {
    explicit not_a_register(std::string &reg);
};

struct unable_to_open_a_file : std::runtime_error {
    explicit unable_to_open_a_file(const std::string &name);
};

struct invalid_file_format : std::runtime_error {
    invalid_file_format();
};

struct elem_out_of_bounds : std::runtime_error {
    elem_out_of_bounds();
};

struct dimension_mismatch : std::runtime_error {
    explicit dimension_mismatch(std::size_t value1, std::size_t value2);
};

struct int_overflow : std::runtime_error {
    explicit int_overflow(int lhs, int rhs, char op);
};
}  // namespace custom_exceptions

namespace check_overflow {
int sum(int lhs, int rhs);
int mul(int lhs, int rhs);
}  // namespace check_overflow

namespace matrix_interpreter {
struct matrix {
private:
    std::vector<std::vector<int>> data;

public:
    matrix();
    matrix(std::size_t r, std::size_t c);

    [[nodiscard]] std::size_t get_rows() const;
    [[nodiscard]] std::size_t get_cols() const;
    [[nodiscard]] int get_matrix_elem(std::size_t i, std::size_t j) const;
    void set_matrix_elem(std::size_t i, std::size_t j, int value);
    void update(const matrix &src);
};  // matrix

void load(int reg,
          const std::string &filename,
          std::vector<matrix_interpreter::matrix> &matrices);
void print(int reg, std::vector<matrix_interpreter::matrix> &matrices);
void elem(int reg,
          int i,
          int j,
          std::vector<matrix_interpreter::matrix> &matrices);
void add(int A, int B, std::vector<matrix_interpreter::matrix> &matrices);
void mul(int A, int B, std::vector<matrix_interpreter::matrix> &matrices);
}  // namespace matrix_interpreter

namespace params {
int check_param(std::string &param);
};  // namespace params

#endif  // MATRIX_INTERPRETER_H_

#ifndef S21_MATRIX_OOP_
#define S21_MATRIX_OOP_

#include <math.h>

#include <algorithm>
#include <iostream>

using std::cout;
using std::endl;

// Constant EPSILON for Equal
constexpr double kEpsilon = 1e-7;

class S21Matrix {
 private:
  int cols_, rows_;
  double** matrix_;

 public:
  // A basic constructor that initialises a matrix of some predefined dimension
  S21Matrix();
  // Parametrized constructor with number of rows and columns
  S21Matrix(int rows, int cols);
  // Parametrized constructor with number of rows = columns
  explicit S21Matrix(int rows);
  // Copy constructor
  S21Matrix(const S21Matrix& other);
  // Move constructor
  S21Matrix(S21Matrix&& other);
  // Destructor
  ~S21Matrix();

  // Accessors - дает доступ к приватным полям
  int get_rows() const;
  int get_cols() const;
  double get_matrix(int row, int col) const;
  // Mutators
  void set_rows(int rows);
  void set_cols(int cols);
  void set_matrix(int row, int col, double num);

  //  Checks matrices for equality with each other
  bool EqMatrix(const S21Matrix& other);
  // Adds the second matrix to the current one
  void SumMatrix(const S21Matrix& other);
  // Subtracts another matrix from the current one
  void SubMatrix(const S21Matrix& other);
  // Multiplies the current matrix by a number
  void MulNumber(const double num);
  // Multiplies the current matrix by the second matrix
  void MulMatrix(const S21Matrix& other);
  //  Creates a new transposed matrix from the current one and returns it
  S21Matrix Transpose();
  // Calculates the algebraic addition matrix of the current one and returns it
  S21Matrix CalcComplements();
  // Calculates and returns the determinant of the current matrix
  double Determinant();
  // Calculates and returns the inverse matrix
  S21Matrix InverseMatrix();

  // Addition of two matrices
  // S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix operator+(const S21Matrix& other);
  // Subtraction of one matrix from another
  S21Matrix operator-(const S21Matrix& other) const;
  // Matrix multiplication and matrix multiplication by a number
  S21Matrix operator*(const double num) const;
  S21Matrix operator*(const S21Matrix& other) const;
  // ЧТО ЭТО???    friend S21Matrix operator*(const double left, const
  // S21Matrix& right); Checks for matrices equality (eq_matrix)
  bool operator==(const S21Matrix& other);
  // Assignment of values from one matrix to another one
  // S21Matrix& operator=(const S21Matrix& other);
  // S21Matrix& operator=(S21Matrix &&other) noexcept;
  S21Matrix& operator=(const S21Matrix& other);
  // Addition assignment (sum_matrix)
  S21Matrix& operator+=(const S21Matrix& other);
  // Difference assignment (sub_matrix)
  S21Matrix& operator-=(const S21Matrix& other);
  // Difference assignment (mul_matrix)
  S21Matrix& operator*=(const S21Matrix& other);
  // Indexation by matrix elements (row, column)
  const double& operator()(int row, int col) const;
  double& operator()(int row, int col);

  // Print matrix
  // void PrintMatrix() {
  //   for (int i = 0; i < rows_; i++) {
  //     for (int j = 0; j < cols_; j++) {
  //       std::cout << matrix_[i][j] << " ";
  //     }
  //     std::cout << std::endl;
  //   }
  // }

  // Other private functions
 private:
  void get_minor(int row, int column);
  void create_matrix();
  void remove_matrix();
  void resize_matrix(int rows, int cols);
  void copy_matrix(const S21Matrix& other);
  bool check_matrix() const;
};

#endif  // S21_MATRIX_OOP_
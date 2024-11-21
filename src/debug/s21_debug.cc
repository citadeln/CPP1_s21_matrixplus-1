#define IFDEBUG 0
#if IFDEBUG == 1

#include <algorithm>
#include <iostream>
#include "../s21_matrix_oop.h"

#include "../tests/test.h"

void S21Matrix::MulMatrix(const S21Matrix &other) {
std::cout << "This:" << std::endl;
  this->PrintMatrix();

 // other.PrintMatrix();

  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Incorrect matrix sizes for the multiplication (MulMatrix)");
  }

  int cols_2 = other.cols_;

  S21Matrix result(rows_, cols_2);
  std::cout << "Result:" << std::endl;
  result.PrintMatrix();

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_2; ++j) {
      for (int k = 0; k < cols_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  // std::cout << "Result:" << std::endl;
  // result.PrintMatrix();


  *this = std::move(result);

  // std::cout << "Result:" << std::endl;
  // result.PrintMatrix();
}


void SetMatrix3x3(S21Matrix &matrix, double expected[3][3]) {
  for (int i = 0; i < matrix.get_rows(); ++i) {
    for (int j = 0; j < matrix.get_cols(); ++j) {
      matrix(i, j) = expected[i][j];
    }
  }
}

void SetMatrix3x4(S21Matrix &matrix, double expected[3][4]) {
  for (int i = 0; i < matrix.get_rows(); ++i) {
    for (int j = 0; j < matrix.get_cols(); ++j) {
      matrix(i, j) = expected[i][j];
    }
  }
}

// static double mulMatrixFirstValue[3][3] = {{3, 4, 55}, {6, 7, 8}, {9, 3, 4}};
// static double mulMatrixSecondValue[3][4] = {
//     {1, 2, 3, 4}, {4, 5, 6, 5}, {6, 7, 8, 9}};
// static double mulMatrixResult[3][4] = {
//     {349, 411, 473, 527}, {82, 103, 124, 131}, {45, 61, 77, 87}};

int main() {
  std::cout << "Well done!" << std::endl;

  S21Matrix example(3, 3);
  S21Matrix term(3, 4);
  S21Matrix result(3, 4);
  SetMatrix3x3(example, mulMatrixFirstValue);
  SetMatrix3x4(term, mulMatrixSecondValue);
  SetMatrix3x4(result, mulMatrixResult);


  std::cout << "Printing example matrix:" << std::endl;
  example.PrintMatrix();

    std::cout << "Printing example matrix:" << std::endl;
  term.PrintMatrix();

    std::cout << "Printing example matrix:" << std::endl;
  result.PrintMatrix();


  example.MulMatrix(term);

  std::cout << "Printing example matrix:" << std::endl;
  example.PrintMatrix();
  
  std::cout << "Printing result matrix:" << std::endl;
  result.PrintMatrix();

  EXPECT_EQ(result.EqMatrix(example), true);
  std::cout << "2 Well done!" << std::endl;
}

#endif
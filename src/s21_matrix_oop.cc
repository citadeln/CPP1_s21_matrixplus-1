#include "s21_matrix_oop.h"

#include <algorithm>
#include <iostream>
// #include <gtest/gtest.h>

S21Matrix::S21Matrix() : S21Matrix(1, 1) {}

S21Matrix::S21Matrix(int rows) : S21Matrix(rows, rows) {}

S21Matrix::S21Matrix(int rows, int cols) {
  this->rows_ = rows;
  this->cols_ = cols;
  if (this->rows_ > 0 && this->cols_ > 0) {
    this->create_matrix();
  } else {
    throw std::out_of_range("Rows/Cols should be great 0");
  }
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  this->rows_ = other.rows_;
  cols_ = other.cols_;

  create_matrix();

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = other.cols_ = 0;
}

S21Matrix::~S21Matrix() { this->remove_matrix(); }

void S21Matrix::create_matrix() {
  if (rows_ <= 0 || cols_ <= 0)
    throw std::invalid_argument("Invalid matrix size (create_matrix)");

  matrix_ = new double *[rows_] {};
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]{};
  }
}

void S21Matrix::remove_matrix() {
  if (this->check_matrix()) {
    for (int i = 0; i < this->rows_; i++) {
      delete[] this->matrix_[i];
      this->matrix_[i] = nullptr;
    }
    delete[] this->matrix_;
    this->matrix_ = nullptr;
  }
  this->rows_ = 0;
  this->cols_ = 0;
}

void S21Matrix::resize_matrix(int rows, int cols) {
  if (this->rows_ != rows || this->cols_ != cols) {
    S21Matrix tmp(*this);
    this->remove_matrix();
    this->rows_ = rows;
    this->cols_ = cols;
    this->create_matrix();
    for (int i = 0; i < std::min(this->rows_, tmp.rows_); i++) {
      for (int j = 0; j < std::min(this->cols_, tmp.cols_); j++) {
        this->matrix_[i][j] = tmp.matrix_[i][j];
      }
    }
    tmp.remove_matrix();
  }
}

void S21Matrix::copy_matrix(const S21Matrix &other) {
  if (cols_ != other.cols_ || rows_ != other.rows_)
    throw std::invalid_argument("different range (copy_matrix)");
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  create_matrix();
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

bool S21Matrix::check_matrix() const {
  bool result = false;
  if (this->rows_ > 0 && this->cols_ > 0 && this->matrix_ != nullptr)
    result = true;
  return result;
}

// Accessors and mutators

int S21Matrix::get_rows() const {
  int result = this->rows_;
  return result;
}
int S21Matrix::get_cols() const {
  int result = this->cols_;
  return result;
}

double S21Matrix::get_matrix(int row, int col) const {
  double result;
  if (row < this->rows_ && col < this->cols_ && row >= 0 && col >= 0) {
    result = this->matrix_[row][col];
  } else {
    throw std::out_of_range(
        "Rows/Cols should be LT than matrix size or GE than 0");
  }
  return result;
}

void S21Matrix::set_rows(int rows) {
  if (rows > 0) {
    this->resize_matrix(rows, this->cols_);
  } else {
    throw std::out_of_range("Rows should be GT than 0");
  }
}

void S21Matrix::set_cols(int cols) {
  if (cols > 0) {
    this->resize_matrix(this->rows_, cols);
  } else {
    throw std::out_of_range("Cols should be GT than 0");
  }
}

void S21Matrix::set_matrix(int row, int col, double num) {
  if (row >= 0 && col >= 0 && row < this->rows_ && col < this->cols_) {
    this->matrix_[row][col] = num;
  } else {
    throw std::out_of_range(
        "Rows/Colss should be GE than 0 and LT than size matrix");
  }
}

// Operators

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix tmp{*this};
  tmp.SubMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix tmp{*this};
  tmp.MulNumber(num);
  return tmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix tmp{*this};
  tmp.MulMatrix(other);
  return tmp;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    remove_matrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    create_matrix();
    // std::copy(other.matrix_, other.matrix_ + rows_ * cols_, matrix_);
    for (size_t i = 0; i < rows_; i++)
      for (size_t j = 0; j < cols_; j++) matrix_[i][j] = other.matrix_[i][j];
  }
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

double &S21Matrix::operator()(int row, int col) {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_)
    throw std::invalid_argument("Incorrect matrix index");
  return matrix_[row][col];
}

const double &S21Matrix::operator()(int row, int col) const {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_)
    throw std::invalid_argument("Incorrect matrix index");
  return matrix_[row][col];
}

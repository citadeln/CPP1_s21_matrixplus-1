#include "s21_matrix_oop.h"

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.get_rows() || cols_ != other.get_cols())
    throw std::invalid_argument("Incorrect matrix sizes(SumMatrix)");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] + other(i, j);
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument("Incorrect matrix size(EqMatrix)");
  bool result = false;
  bool flag = false;

  for (int i = 0; i < this->rows_; i++) {
    if (flag) break;
    for (int j = 0; j < this->cols_; j++) {
      if (fabs(this->matrix_[i][j] - other.matrix_[i][j]) < kEpsilon) {
        result = true;
      } else {
        result = false;
        flag = true;
        break;
      }
    }
  }

  return result;
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.get_rows() || cols_ != other.get_cols())
    throw std::invalid_argument("Incorrect matrix size(SubMatrix)");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] - other(i, j);
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.get_rows()) {
    throw std::invalid_argument(
        "Incorrect matrix sizes for the multiplication (MulMatrix)");
  }

  int cols_2 = other.get_cols();

  S21Matrix result(rows_, cols_2);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_2; ++j) {
      for (int k = 0; k < cols_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  *this = std::move(result);
}

S21Matrix S21Matrix::Transpose() {
  if (this->check_matrix()) {
    S21Matrix tmp(*this);
    this->remove_matrix();
    this->rows_ = tmp.cols_;
    this->cols_ = tmp.rows_;
    this->create_matrix();
    for (int i = 0; i < tmp.rows_; i++) {
      for (int j = 0; j < tmp.cols_; j++) {
        this->matrix_[j][i] = tmp.matrix_[i][j];
      }
    }
    tmp.remove_matrix();
  } else {
    throw std::invalid_argument("Matrix should be really");
  }
  return *this;
}

void S21Matrix::get_minor(int row, int column) {
  S21Matrix tmp(*this);
  this->remove_matrix();
  this->rows_ = tmp.rows_ - 1;
  this->cols_ = tmp.cols_ - 1;
  this->create_matrix();
  int z = 0;
  for (int i = 0; i < tmp.rows_; i++) {
    if (i != row) {
      int k = 0;
      for (int j = 0; j < tmp.cols_; j++) {
        if (j != column) {
          this->matrix_[z][k] = tmp.matrix_[i][j];
          k++;
        }
      }
      z++;
    }
  }
  tmp.remove_matrix();
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_)
    throw std::invalid_argument("The matrix is not square (CalcComplements)");
  S21Matrix tmp(*this);
  if (this->rows_ == 1) {
    tmp.matrix_[0][0] = 1;
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        S21Matrix minor(*this);
        minor.get_minor(i, j);
        double number = minor.Determinant();
        tmp.matrix_[i][j] = ((i + j) % 2 == 1 ? -1 : 1) * number;
        // minor.remove_matrix();
      }
    }
  }
  return tmp;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_)
    throw std::invalid_argument("The matrix is not square (Determinant)");

  double determ = 0.0;
  if (this->rows_ == 1) {
    determ = this->matrix_[0][0];
  } else if (this->rows_ == 2) {
    determ += (this->matrix_[0][0] * this->matrix_[1][1] -
               this->matrix_[1][0] * this->matrix_[0][1]);
  } else {
    int minus = -1;
    for (int i = 0; i < this->rows_; i++) {
      S21Matrix minor(*this);
      minor.get_minor(i, 0);
      minus *= -1;
      determ += (minus * this->matrix_[i][0] * minor.Determinant());
      // minor.remove_matrix();
    }
  }
  return determ;
}

S21Matrix S21Matrix::InverseMatrix() {
  S21Matrix tmp(this->CalcComplements());
  double Determinant = this->Determinant();
  if (Determinant != 0.0) {
    tmp.Transpose();
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        tmp.matrix_[i][j] = (double)tmp.matrix_[i][j] / (double)Determinant;
      }
    }
  } else {
    throw std::invalid_argument(
        "Matrix should be square or Determinant should be not equal 0");
  }

  return tmp;
}

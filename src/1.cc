#include <algorithm>
#include <iostream>
#include <gtest>

class S21Matrix{
    private:
        int cols_, rows_;
        double ** matrix_;
    public:
    S21Matrix();
    S21Matrix(const S21Matrix& other);
    S21Matrix(int rows, int cols){
        this->rows_= rows;
        this->cols_= cols;
        this->matrix_= new double*[rows_];
        for(int i=0; i < rows; i++) {
            this->matrix_[i] = new double[cols]();
        }
    }

    S21Matrix operator+(S21Matrix& other);
    S21Matrix friend operator*(double a, S21Matrix& other);
    ~S21Matrix();
    S21Matrix(S21Matrix&& other);
    void SumMatrix(const S21Matrix& other);
};


S21Matrix::S21Matrix(){
    S21Matrix(1, 1);

    /* rvalue - ничего не меняет
    lvalue - что-то меняет
    int x = 3
    x + 5
    int& y = x; // y ссылается на x
    y +=1; // x тоже поменяется
    */
}

S21Matrix::S21Matrix(S21Matrix&& other){
    other.matrix_=nullptr;
}

// деструктор
S21Matrix::~S21Matrix(){
    for(int i=0; i<rows_; i++) {
        delete[] this->matrix_[i];
    }
    delete[] this->matrix_;
}

void S21Matrix::SumMatrix(const S21Matrix& other){
    if(cols_!=other.cols_ || rows_!=other.rows_) {
        throw std::invalid_argument("different dimensions");
    }
}

// S21Matrix S21Matrix::operator+(S21Matrix& other){
//     S21Matrix result(*this);
//     return result.SumMatrix(other);
// }

int main(){
    /*
    S21Matrix b(3, 3);
    // S21Matrix a = b; // b - это lvalue ссылка
    S21Matrix a(std::move(b)); // конвертирование из lvalue в rvalue, перенос матрицы. В отличии от копирования - не создается новый объект, здесь же просто перенос, а объект b зануляется
    */
    S21Matrix b(3, 3);
    S21Matrix a(3, 3);
    EXPECT_THROW(a+b, std::invalid_argument);

}
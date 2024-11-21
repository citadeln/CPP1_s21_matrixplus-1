#include "test.h"

TEST(CreateTest, DefaultConstructor) {
  S21Matrix example;
  EXPECT_EQ(example.get_rows(), 1);
  EXPECT_EQ(example.get_cols(), 1);
}

TEST(CreateTest, ParametrizedConstructorSuccess) {
  S21Matrix example(1, 1);
  EXPECT_EQ(example.get_rows(), 1);
  EXPECT_EQ(example.get_cols(), 1);
  EXPECT_EQ(example(0, 0), 0);
}

// удалить 
// TEST(CreateTest, CopyConstructor) {
//   S21Matrix example(3, 3);
//   S21Matrix res(example);
//   EXPECT_EQ(res.get_cols(), example.get_cols());
// }

TEST(CreateTest, CopyConstructor) {
    S21Matrix example(3, 3);
    S21Matrix res(example);

    EXPECT_EQ(res.get_rows(), example.get_rows());
    EXPECT_EQ(res.get_cols(), example.get_cols());

    for (int i = 0; i < example.get_rows(); i++) {
        for (int j = 0; j < example.get_cols(); j++) {
            EXPECT_EQ(res(i, j), example(i, j));
        }
    }
}

TEST(CreateTest, MovedConstructor) {
  S21Matrix example(3, 3);
  S21Matrix res = std::move(example);
  EXPECT_EQ(res.get_cols(), 3);
  EXPECT_EQ(example.get_cols(), 0);
}

TEST(CreateTest, ParametrizedConstructorFailure) {
  EXPECT_THROW(S21Matrix example(-1, 1), std::out_of_range);
}

TEST(OverrideOperators, Brackets) {
  S21Matrix example(1, 1);
  EXPECT_EQ(example(0, 0), 0);
}

TEST(OverrideOperators, BracketsOverride) {
  S21Matrix example(1, 1);
  example(0, 0) = 5;
  EXPECT_EQ(example(0, 0), 5);
}

TEST(OverrideOperators, BracketsOutOfRange) {
  S21Matrix example(1, 1);
  EXPECT_THROW(example(-5, 4), std::invalid_argument);
}

TEST(OverrideOperators, BracketsOverrideOutOfRange) {
  S21Matrix example(1, 1);
  EXPECT_THROW(example(5, 0) = 4, std::invalid_argument);
}

TEST(TestPrivateAccess, Accessors) {
  S21Matrix example(1, 2);
  EXPECT_EQ(example.get_rows(), 1);
  EXPECT_EQ(example.get_cols(), 2);
}

TEST(TestPrivateAccess, Mutators) {
  int rows = 3, cols = 3;
  S21Matrix matrix(rows, cols);
  SetMatrix3x3(matrix, val1[0]);
  matrix.set_rows(10);
  matrix.set_cols(2);
  EXPECT_NE(matrix.get_rows(), rows);
  EXPECT_NE(matrix.get_cols(), cols);
  EXPECT_EQ(matrix(1, 1), 4);
  EXPECT_EQ(matrix(5, 1), 0);
}

TEST(TestPrivateAccess, MutatorsInvailid) {
  int rows = 3, cols = 3;
  S21Matrix matrix(rows, cols);
  EXPECT_THROW(matrix.set_cols(-4), std::out_of_range);
  EXPECT_THROW(matrix.set_rows(-4), std::out_of_range);
}

TEST(BaseFunctions, EqualOutOfRange) {
  S21Matrix example(3, 3);
  S21Matrix out_of_range_example(3, 4);
  EXPECT_THROW(example.EqMatrix(out_of_range_example), std::invalid_argument);
}

TEST(BaseFunctions, EqualTrue) {
  S21Matrix example(3, 3);
  S21Matrix equal_example(3, 3);
  EXPECT_EQ(example.EqMatrix(equal_example), 1);
}

TEST(BaseFunctions, EqualFalse) {
  S21Matrix example(3, 3);
  S21Matrix non_equal_example(3, 3);
  non_equal_example(1, 1) = 3;
  EXPECT_EQ(example.EqMatrix(non_equal_example), 0);
}

TEST(BaseFunctions, SumOutOfRange) {
  S21Matrix example(3, 3);
  S21Matrix non_equal_example(3, 4);
  EXPECT_THROW(example.SumMatrix(non_equal_example), std::invalid_argument);
}

TEST(BaseFunctions, SumDefaultTest) {
  for (int i = 0; i < 5; ++i) {
    S21Matrix example(3, 3);
    S21Matrix summand(3, 3);
    S21Matrix result(3, 3);
    SetMatrix3x3(example, summandFirst[i]);
    SetMatrix3x3(summand, summandSecond[i]);
    SetMatrix3x3(result, sumResult[i]);
    example.SumMatrix(summand);
    EXPECT_EQ(result.EqMatrix(example), compareSumResult[i]);
  }
}

TEST(BaseFunctions, SubOutOfRange) {
  S21Matrix example(3, 3);
  S21Matrix non_equal_example(3, 4);
  EXPECT_THROW(example.SubMatrix(non_equal_example), std::invalid_argument);
}

TEST(BaseFunctions, SubDefaultTest) {
  for (int i = 0; i < 2; ++i) {
    S21Matrix example(3, 3);
    S21Matrix term(3, 3);
    S21Matrix result(3, 3);
    SetMatrix3x3(example, minuend[i]);
    SetMatrix3x3(term, subtrahend[i]);
    SetMatrix3x3(result, subResult[i]);
    example.SubMatrix(term);
    EXPECT_EQ(result.EqMatrix(example), compareSubResult[i]);
  }
}

TEST(BaseFunctions, MulNumberTest) {
  S21Matrix example(1, 1);
  example(0, 0) = 5;
  example.MulNumber(4);
  EXPECT_EQ(example(0, 0), 20);
}

TEST(BaseFunctions, MulMatrixTest) {  
  S21Matrix example(3, 3);
  S21Matrix term(3, 4);
  S21Matrix result(3, 4);
  SetMatrix3x3(example, mulMatrixFirstValue);
  SetMatrix3x4(term, mulMatrixSecondValue);
  SetMatrix3x4(result, mulMatrixResult);
  example.MulMatrix(term);
  EXPECT_EQ(result.EqMatrix(example), true);
}

TEST(BaseFunctions, TransposeTest) {
  S21Matrix example(3, 3);
  S21Matrix result(3, 3);
  S21Matrix current;
  SetMatrix3x3(example, summandFirst[0]);
  SetMatrix3x3(result, transposeResult);
  current = example.Transpose();
  EXPECT_EQ(result.EqMatrix(current), true);
}

// конец сеги

TEST(BaseFunctions, MulMatrixOutOfRangeTest) {
  S21Matrix example(3, 3);
  S21Matrix term(5, 4);
  EXPECT_THROW(example.MulMatrix(term), std::invalid_argument);
}

TEST(BaseFunctions, Determinant) {
  for (int i = 0; i < 5; i++) {
    S21Matrix matrix(3, 3);
    SetMatrix3x3(matrix, val1[i]);
    EXPECT_NEAR(matrix.Determinant(), determinantResult[i], 1E-11);
  }
}

TEST(BaseFunctions, Determinant_10x10) {
  S21Matrix matrix(10, 10);
  SetMatrix10x10(matrix, valDeterminant);
  EXPECT_NEAR(matrix.Determinant(), 0, 1E-5);
}

TEST(BaseFunctions, DeterminantOutOfRange) {
  S21Matrix matrix(3, 4);
  EXPECT_THROW(matrix.Determinant(), std::invalid_argument);
}

TEST(BaseFunctions, CalcCompl) {
  for (int i{0}; i < 5; ++i) {
    S21Matrix matrix(3, 3), result(3, 3), checkResult(3, 3);
    SetMatrix3x3(matrix, val1[i]);
    SetMatrix3x3(checkResult, calcComplementsResults[i]);
    result = matrix.CalcComplements();
    EXPECT_EQ(checkResult.EqMatrix(result), 1);
  }
}

TEST(BaseFunctions, CalcComplOutOfRange) {
  S21Matrix matrix(3, 4);
  EXPECT_THROW(matrix.CalcComplements(), std::invalid_argument);
}

TEST(BaseFunctions, Inverse) {
  for (int i = 0; i < 5; ++i) {
    S21Matrix matrix(3, 3);
    SetMatrix3x3(matrix, val1[i]);
    if (i == 1) {
      EXPECT_THROW(matrix.InverseMatrix(), std::invalid_argument);
    } else {
      matrix = matrix.InverseMatrix();
      CompareForInverse(matrix, inverseResults[i]);
    }
  }
}

TEST(BaseFunctions, InverseOutOfRange) {
  S21Matrix matrix(3, 4);
  EXPECT_THROW(matrix.InverseMatrix(), std::invalid_argument);
}

TEST(OverrideMethods, PlusUno) {
  S21Matrix example(3, 3);
  S21Matrix summand(3, 3);
  S21Matrix result(3, 3);
  SetMatrix3x3(example, summandFirst[0]);
  SetMatrix3x3(summand, summandSecond[0]);
  SetMatrix3x3(result, sumResult[0]);
  example += summand;
  EXPECT_EQ(example.EqMatrix(result), compareSumResult[0]);
}

TEST(OverrideMethods, MinusUno) {
  S21Matrix example(3, 3);
  S21Matrix summand(3, 3);
  S21Matrix result(3, 3);
  SetMatrix3x3(example, minuend[0]);
  SetMatrix3x3(summand, subtrahend[0]);
  SetMatrix3x3(result, subResult[0]);
  example -= summand;
  EXPECT_EQ(example.EqMatrix(result), compareSubResult[0]);
}

TEST(OverrideMethods, EqualUnoTrue) {
  S21Matrix example(3, 3);
  S21Matrix equal_example(3, 3);
  EXPECT_EQ(example == equal_example, 1);
}

TEST(OverrideMethods, EqualUnoFalse) {
  S21Matrix example(3, 3);
  S21Matrix non_equal_example(3, 3);
  non_equal_example(1, 1) = 3;
  EXPECT_EQ(example == non_equal_example, 0);
}

TEST(OverrideMethods, PlusBiAndEqualToMovedConstructor) {
  S21Matrix example(3, 3);
  S21Matrix summand(3, 3);
  S21Matrix result(3, 3);
  S21Matrix res;
  SetMatrix3x3(example, summandFirst[0]);
  SetMatrix3x3(summand, summandSecond[0]);
  SetMatrix3x3(result, sumResult[0]);
  res = summand + example;
  EXPECT_EQ(res == result, compareSumResult[0]);
}

TEST(OverrideMethods, MinusBiAndEqualToMovedConstructor) {
  S21Matrix example(3, 3);
  S21Matrix summand(3, 3);
  S21Matrix result(3, 3);
  S21Matrix res;
  SetMatrix3x3(example, minuend[0]);
  SetMatrix3x3(summand, subtrahend[0]);
  SetMatrix3x3(result, subResult[0]);
  res = example - summand;
  EXPECT_EQ(res == result, compareSubResult[0]);
}

TEST(OverrideMethods, EqualToCopyConstructor) {
  S21Matrix example(3, 3);
  S21Matrix res;
  SetMatrix3x3(example, minuend[0]);
  res = example;
  EXPECT_EQ(res == example, 1);
}

TEST(OverrideMethods, MulMatrixUno) {
  S21Matrix example(3, 3);
  S21Matrix term(3, 4);
  S21Matrix result(3, 4);
  S21Matrix answer;
  SetMatrix3x3(example, mulMatrixFirstValue);
  SetMatrix3x4(term, mulMatrixSecondValue);
  SetMatrix3x4(result, mulMatrixResult);
  answer = example * term;
  EXPECT_EQ(answer.EqMatrix(result), true);
}

TEST(OverrideMethods, MulMatrixMono) {
  S21Matrix example(3, 3);
  S21Matrix term(3, 4);
  S21Matrix result(3, 4);
  SetMatrix3x3(example, mulMatrixFirstValue);
  SetMatrix3x4(term, mulMatrixSecondValue);
  SetMatrix3x4(result, mulMatrixResult);
  example *= term;
  EXPECT_EQ(example.EqMatrix(result), true);
}

TEST(OverrideMethods, MulNumberUnoLeft) {
  S21Matrix example(1, 1);
  example(0, 0) = 4;
  example = example * 5;
  EXPECT_EQ(example(0, 0), 20);
}

// TEST(OverrideMethods, MulNumberUnoRight) {
//   S21Matrix example(1, 1);
//   example(0, 0) = 4;
//   example = 5 * example;
//   EXPECT_EQ(example(0, 0), 20);
// }

/* TEST(OverrideMethods, MulNumberMono) {
  S21Matrix example(1, 1);
  example(0, 0) = 4;
  example *= 5;
  EXPECT_EQ(example(0, 0), 20);
} */

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

//    std::cout << "Result:" << matrix(i, j) << std::endl;
    }
  }
}

void SetMatrix10x10(S21Matrix &matrix, double expected[10][10]) {
  for (int i = 0; i < matrix.get_rows(); ++i) {
    for (int j = 0; j < matrix.get_cols(); ++j) {
      matrix(i, j) = expected[i][j];
    }
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void CompareForInverse(S21Matrix matrix, double result[3][3]) {
  for (int i{0}; i < matrix.get_rows(); ++i) {
    for (int j{0}; j < matrix.get_cols(); ++j) {
      EXPECT_NEAR(matrix(i, j), result[i][j], 1E-5);
    }
  }
}

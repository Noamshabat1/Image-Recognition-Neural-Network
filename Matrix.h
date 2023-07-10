#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <fstream>

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims {
    int rows, cols;
} matrix_dims;

class Matrix {
 public:
  /**
   * @brief Constructs a matrix with the specified number of rows and columns.
   * @param rows The number of rows in the matrix.
   * @param cols The number of columns in the matrix.
   */
  Matrix (int rows, int cols);

  /**
   * @brief Default constructor. Constructs an empty matrix.
   */
  Matrix ();

  /**
   * @brief Copy constructor. Constructs a copy of a given matrix.
   * @param matrix The matrix to be copied by the constructor.
   */
  Matrix (const Matrix &matrix);

  /**
   * @brief Destructor. Deallocated memory for the matrix.
   */
  ~Matrix ();

  // Methods & Functions:
  /**
   * @brief Returns the number of rows in the matrix.
   * @return The number of rows.
   */
  int get_rows () const;

  /**
   * @brief Returns the number of columns in the matrix.
   * @return The number of columns.
   */
  int get_cols () const;

  /**
   * @brief Transposes the matrix by swapping its rows and columns.
   * @return A transposed matrix.
   */
  Matrix &transpose ();

  /**
   * @brief Converts the matrix into a column vector by concatenating
   * all its columns.
   * @return A reference to the vectorized matrix.
   */
  Matrix &vectorize ();

  /**
   * @brief  Normally Printing the matrix.
   */
  void plain_print () const;

  /**
   * @brief Computes the dot product of the matrix with another matrix.
   * @param matrix The matrix to compute the dot product with.
   * @return The resulting matrix of the dot product operation.
   */
  Matrix dot (const Matrix &matrix) const;

  /**
   * @brief Computes the norm of the matrix.
   * @return The norm of the matrix.
   */
  double norm () const;

  Matrix rref () const;

  /**
   * @brief Finds the index of the maximum element in the matrix.
   * @return The index of the maximum element.
   */
  int argmax () const;

  /**
   * @brief Computes the sum of all elements in the matrix.
   * @return Sum of the matrix elements.
   */
  float sum () const;

// Operators section:
  /**
   * @brief Adding two matrices.
   * @param rhs_matrix The matrix to be added.
   * @return The resulting matrix of the element-wise adding.
   */
  Matrix operator+ (const Matrix &rhs_matrix) const;

  /**
   * @brief Assigns the values of another matrix to this matrix.
   * @param rhs_matrix The matrix to be assigned.
   * @return A reference to the assigned matrix.
   */
  Matrix &operator= (const Matrix &rhs_matrix);

  /**
   * @brief Computes the matrix multiplication of two matrices.
   * @param rhs_matrix The matrix to be multiplied.
   * @return The resulting matrix of the matrix multiplication.
   */
  Matrix operator* (const Matrix &rhs_matrix) const;

  /**0549341825
   * @brief Multiplies the matrix by a scalar value.
   * @param c The scalar value.
   * @return Matrix of the scalar multiplication.
   */
  Matrix operator* (float c) const;

  /**
   * @brief Multiplies a scalar value by a matrix.
   * @param c The scalar value.
   * @param rhs_matrix The matrix.
   * @return matrix of the scalar multiplication.
   */
  friend Matrix operator* (float c, const Matrix &rhs_matrix);

  // Read:
  /**
   * @brief Accesses the value of an element in the matrix (read-only).
   * @param row The row index.
   * @param col The column index.
   * @return A constant reference to the element value.
   */
  const float &operator() (int row, int col) const;

  /**
   * @brief Accesses the value of an element in the matrix (read-only)
   * using the linear index.
   * @param i The linear index.
   * @return A constant reference to the element value.
   */
  const float &operator[] (int i) const;

// Write:
  /**
   * @brief Accesses the value of an element in the matrix.
   * @param row The row index.
   * @param col The column index.
   * @return A reference to the element value.
   */
  float &operator() (int row, int col);

  /**
   * @brief Accesses the value of an element in the matrix using the
   * linear index.
   * @param i The linear index.
   * @return A reference to the element value.
   */
  float &operator[] (int i);

  /**
   * @brief Adds another matrix to this matrix.
   * @param rhs_matrix The matrix to be added.
   * @return A reference to the modified matrix.
   */
  Matrix &operator+= (const Matrix &rhs_matrix);

  /**
   * @brief Prints the matrix to the output stream in a human-readable format.
   * @param os The output stream.
   * @param matrix The matrix to be printed.
   * @return The output stream.
   */
  friend std::ostream &operator<< (std::ostream &os, const Matrix &matrix);

  /**
   * @brief Reads the matrix from the input stream.
   * @param is The input stream.
   * @param matrix The matrix to be read.
   * @return The input stream.
   */
  friend std::istream &operator>> (std::istream &is, Matrix &matrix);

 private:
  /**
   * @brief The dimensions of the matrix (number of rows and columns).
   */
  matrix_dims _dims;

  /**
   * @brief The data of the matrix stored as a 2D array.
   */
  float **_data;
};

#endif // MATRIX_H
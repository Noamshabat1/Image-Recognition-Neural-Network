#include "Activation.h"
#include <cmath>

Matrix activation::relu (const Matrix &matrix)
{
  Matrix new_matrix = Matrix (matrix);
  int rep = new_matrix.get_rows () * new_matrix.get_cols ();

  for (int i = 0; i < rep; i++)
    {
      if (new_matrix[i] < 0)
        {
          new_matrix[i] = 0;
        }
    }
  return new_matrix;
}

Matrix activation::softmax (const Matrix &matrix)
{
  Matrix new_matrix = Matrix (matrix);
  int rep = new_matrix.get_rows () * new_matrix.get_cols ();
  float sigma = 0;

  for (int i = 0; i < rep; i++)
    {
      sigma += std::exp (matrix[i]);
    }

  float expiration = 1 / sigma;

  for (int i = 0; i < rep; i++)
    {
      new_matrix[i] = expiration * std::exp (new_matrix[i]);
    }
  return new_matrix;
}


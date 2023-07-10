#include "Matrix.h"

#define LENGTH_ERROR "There has been a problem with the diameters! pleas try" \
" again. "
#define NO_ACCESS_ERROR "There is no available access option to the given. " \
"coord! pleas try again. "
#define INPUT_ERROR "The given input is not valid! pleas try again. "

#define CUR 0.1

// Constructors :

Matrix::Matrix (int rows, int cols) : _dims ({rows, cols})
{
  if (rows <= 0 || cols <= 0)
    {
      throw std::length_error (LENGTH_ERROR);
    }
  else
    {
      _data = new (std::nothrow) float *[rows];
      if (_data == nullptr)
        {
          throw std::bad_alloc ();
        }

      for (int i = 0; i < rows; ++i)
        {
          _data[i] = new (std::nothrow) float[cols];
          if (_data[i] == nullptr)
            {
              for (int k = 0; k < i; k++)
                {
                  delete[] _data[k];
                }
              delete[] _data;
              throw std::bad_alloc ();
            }

          for (int j = 0; j < cols; ++j)
            {
              _data[i][j] = 0;
            }
        }
    }
}

Matrix::Matrix () : Matrix (1, 1)
{}

Matrix::Matrix (const Matrix &matrix)
    : Matrix (matrix._dims.rows, matrix._dims.cols)
{
  for (int i = 0; i < _dims.rows; ++i)
    {
      for (int j = 0; j < _dims.cols; ++j)
        {
          _data[i][j] = matrix._data[i][j];
        }
    }
}

Matrix::~Matrix ()
{
  if (_dims.rows == 1 && _dims.cols == 1)
    {
      delete[] _data[0];
    }
  else
    {
      for (int i = 0; i < _dims.rows; ++i)
        {
          delete[] _data[i];
        }
    }

  delete[] _data;
  _data = nullptr;
}

// Methods & Functions :

int Matrix::get_rows () const
{
  int rows = _dims.rows;
  return rows;
}

int Matrix::get_cols () const
{
  int cols = _dims.cols;
  return cols;
}

Matrix &Matrix::transpose ()
{
  int rows = _dims.cols;
  int cols = _dims.rows;

  Matrix transpose_matrix (rows, cols);
  for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
        {
          transpose_matrix (i, j) = (*this) (j, i);
        }
    }

  (*this) = transpose_matrix;
  return *this;
}

Matrix &Matrix::vectorize ()
{
  int new_rows = _dims.rows * _dims.cols;
  int new_cols = 1;

  Matrix new_matrix (new_rows, new_cols);

  for (int i = 0; i < new_rows; i++)
    {
      new_matrix[i] = (*this)[i];
    }

  (*this) = new_matrix;
  return *this;
}

void Matrix::plain_print () const
{
  int rows = _dims.rows;
  int cols = _dims.cols;

  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          std::cout << (*this) (i, j) << " ";
        }
      std::cout << std::endl;
    }
}

Matrix Matrix::dot (const Matrix &matrix) const
{
  int og_rows = _dims.rows;
  int og_cols = _dims.cols;

  if (og_cols != matrix._dims.cols || og_rows != matrix._dims.rows)
    {
      throw std::length_error (LENGTH_ERROR);
    }
  Matrix new_matrix (og_rows, og_cols);

  for (int i = 0; i < get_rows (); i++)
    {
      for (int j = 0; j < get_cols (); j++)
        {
          new_matrix (i, j) = (*this) (i, j) * matrix (i, j);
        }
    }
  return new_matrix;
}

double Matrix::norm () const
{
  double sigma = 0;
  int power = 2;
  int rows = _dims.rows;
  int cols = _dims.cols;

  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          sigma += std::pow ((*this) (i, j), power);
        }
    }
  double ans = std::sqrt (sigma);
  return ans;
}

Matrix Matrix::rref () const // TODO: to implement
{
  return *this;
}

int Matrix::argmax () const
{
  float max_num = (*this) (0, 0);
  int index = 0;
  int rows = _dims.rows;
  int cols = _dims.cols;

  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          if ((*this) (i, j) > max_num)
            {
              max_num = (*this) (i, j);
              index = i * cols + j;
            }
        }
    }
  return index;
}

float Matrix::sum () const
{
  float sum = 0;
  int rows = _dims.rows;
  int cols = _dims.cols;

  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          sum += (*this) (i, j);
        }
    }
  return sum;
}

// Operators section:

Matrix Matrix::operator+ (const Matrix &rhs_matrix) const
{
  int og_rows = _dims.rows;
  int og_cols = _dims.cols;

  if (og_rows != rhs_matrix._dims.rows || og_cols != rhs_matrix._dims.cols)
    {
      throw std::length_error (LENGTH_ERROR);
    }

  Matrix new_matrix = Matrix (*this);
  for (int i = 0; i < og_rows; ++i)
    {
      for (int j = 0; j < og_cols; ++j)
        {
          new_matrix (i, j) += rhs_matrix (i, j);
        }
    }
  return new_matrix;
}

Matrix &Matrix::operator= (const Matrix &rhs_matrix)
{
  if (this == &rhs_matrix)
    { return *this; }


  // deleting data.
  for (int i = 0; i < _dims.rows; ++i)
    {
      delete[] _data[i];
    }
  delete[] _data;

  // allocate new memory for rhs_matrix.
  _dims.rows = rhs_matrix._dims.rows;
  _dims.cols = rhs_matrix._dims.cols;
  _data = new (std::nothrow) float *[_dims.rows];
  if (_data == nullptr)
    {
      throw std::bad_alloc ();
    }

  // copy data from rhs_matrix.
  for (int i = 0; i < _dims.rows; ++i)
    {
      _data[i] = new (std::nothrow) float[_dims.cols];
      if (_data[i] == nullptr)
        {
          for (int k = 0; k < i; k++)
            {
              delete[] _data[k];
            }

          delete[] _data;
          throw std::bad_alloc ();
        }

      for (int j = 0; j < _dims.cols; ++j)
        {
          _data[i][j] = rhs_matrix._data[i][j];
        }
    }
  return *this;
}

Matrix Matrix::operator* (const Matrix &rhs_matrix) const
{
  int og_rows = _dims.rows;
  int og_cols = _dims.cols;

  if (og_cols != rhs_matrix._dims.rows)
    {
      throw std::length_error (LENGTH_ERROR);
    }

  Matrix new_matrix (og_rows, rhs_matrix._dims.cols);
  for (int i = 0; i < og_rows; i++)
    {
      for (int j = 0; j < rhs_matrix._dims.cols; j++)
        {
          for (int k = 0; k < og_cols; k++)
            {
              new_matrix (i, j) += (*this) (i, k) * rhs_matrix (k, j);
            }
        }
    }
  return new_matrix;
}

Matrix Matrix::operator* (float c) const
{
  int rows = _dims.rows;
  int cols = _dims.cols;
  Matrix new_matrix (rows, cols);

  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          new_matrix (i, j) = (*this) (i, j) * c;
        }
    }
  return new_matrix;
}

Matrix operator* (float c, const Matrix &rhs_matrix)
{
  return rhs_matrix * c; // using the * operator above.
}

const float &Matrix::operator() (int row, int col) const // const
{
  int og_rows = _dims.rows;
  int og_cols = _dims.cols;

  if (row < 0 || row >= og_rows || col < 0 || col >= og_cols)
    {
      throw std::out_of_range (NO_ACCESS_ERROR);
    }
  return _data[row][col];
}

const float &Matrix::operator[] (int i) const // const
{
  int rows = _dims.rows;
  int cols = _dims.cols;

  int mat_size = rows * cols;
  if (i < 0 || i >= mat_size)
    {
      throw std::out_of_range (NO_ACCESS_ERROR);
    }

  int new_row = i / cols; // new rows
  int new_col = i % cols; // new cols
  return _data[new_row][new_col];
}

float &Matrix::operator() (int row, int col) // not const () operator.
{
  int og_rows = _dims.rows;
  int og_cols = _dims.cols;

  if (row < 0 || row >= og_rows || col < 0 || col >= og_cols)
    {
      throw std::out_of_range (NO_ACCESS_ERROR);
    }
  return _data[row][col];
}

float &Matrix::operator[] (int i) // not const [] operator.
{
  int rows = _dims.rows;
  int cols = _dims.cols;

  int mat_size = rows * cols;
  if (i < 0 || i >= mat_size)
    {
      throw std::out_of_range (NO_ACCESS_ERROR);
    }

  int new_row = i / cols; // new rows
  int new_col = i % cols; // new cols
  return _data[new_row][new_col];
}

Matrix &Matrix::operator+= (const Matrix &rhs_matrix)
{
  int og_rows = _dims.rows;
  int og_cols = _dims.cols;

  if (og_cols != rhs_matrix._dims.cols || og_rows != rhs_matrix._dims.rows)
    {
      throw std::length_error (LENGTH_ERROR);
    }
  for (int i = 0; i < og_rows; ++i)
    {
      for (int j = 0; j < og_cols; ++j)
        {
          (*this) (i, j) += rhs_matrix (i, j);
        }
    }
  return *this;
}

// using the pseudocode from the pdf.
std::ostream &operator<< (std::ostream &os, const Matrix &matrix)
{
  int rows = matrix._dims.rows;
  int cols = matrix._dims.cols;

  if (!os)
    {
      return os;
    }
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          if (matrix (i, j) > CUR)
            {
              os << "**";
            }
          else
            {
              os << "  ";
            }
        }
      os << std::endl;
    }
  return os;
}

/**
 * using the pseudocode from web:
 * https://cplusplus.com/reference/istream/istream/read
*/
std::istream &operator>> (std::istream &is, Matrix &matrix) // check!
{
  int rows = matrix._dims.rows;
  int cols = matrix._dims.cols;

  if (!is)
    {
      throw std::runtime_error (INPUT_ERROR);
    }

  is.seekg (0, std::istream::end);
  long int input_length = is.tellg ();
  is.seekg (0, std::istream::beg);

  unsigned int mat_size = rows * cols;
  unsigned int input_size = input_length / sizeof (float);
  if (input_size < mat_size)
    {
      throw std::runtime_error (INPUT_ERROR);
    }

  char *buffer = new char[input_length];
  is.read (buffer, input_length);

  if (!is)
    {
      delete[] buffer;
      throw std::runtime_error (INPUT_ERROR);
    }

  float *items = (float *) buffer;

  for (unsigned int i = 0; i < mat_size; i++)
    {
      matrix[i] = items[i];
    }

  delete[] buffer;
  return is;
}


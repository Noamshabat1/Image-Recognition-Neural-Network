#include "MlpNetwork.h"

MlpNetwork::MlpNetwork (Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE]) :
    _level_1 (weights[0], biases[0], activation::relu),
    _level_2 (weights[1], biases[1], activation::relu),
    _level_3 (weights[2], biases[2], activation::relu),
    _level_4 (weights[3], biases[3], activation::softmax)
{

}

digit MlpNetwork::operator() (const Matrix &matrix) const
{
  Matrix start_matrix;
  // copy
  start_matrix = matrix;
  start_matrix.vectorize ();

  Matrix layer_1 = _level_1 (start_matrix);
  Matrix layer_2 = _level_2 (layer_1);
  Matrix layer_3 = _level_3 (layer_2);
  Matrix layer_4 = _level_4 (layer_3);

  int max_digit_index = layer_4.argmax ();

  return {(unsigned int) max_digit_index, layer_4[max_digit_index]};
}

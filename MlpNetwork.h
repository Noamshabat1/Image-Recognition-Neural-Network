#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"

#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit {
    unsigned int value;
    float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
                                    {64,  128},
                                    {20,  64},
                                    {10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
                                 {64,  1},
                                 {20,  1},
                                 {10,  1}};

class MlpNetwork {
 public:
  /**
  * Main class constructor. that initialize two array's as follows.
  * @param weights
  * @param biases
  */
  MlpNetwork (Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE]);

  /**
  * This operator is Applies the layer on the input and returns an out
   * put matrix.
  * @param matrix matrix input
  * @return the digit with highest probability (index) after applying all of
   * the layers like in the example.
  */
  digit operator() (const Matrix &matrix) const;

  /**
   * Initialize the privet parameter's.
   */
 private:
  Dense _level_1;
  Dense _level_2;
  Dense _level_3;
  Dense _level_4;
};

#endif // MLPNETWORK_H


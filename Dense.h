#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

class Dense {
 public:
  /**
  * @brief: the declaration of class constructor. returns - noting.
  */
  Dense (const Matrix &weights, const Matrix &bias,
         ActivationFunction activation_function);

  /**
   * @brief:a getter func that returns the weights of the layer.
   */
  const Matrix &get_weights () const
  {
    return _weights;
  }
  /**
   * @brief:a getter func that returns the bias of the layer.
   */
  const Matrix &get_bias () const
  {
    return _bias;
  }
  /**
   * @brief:a getter func that returns the activation function of the layer.
   */
  ActivationFunction get_activation () const
  {
    return _activation_function;
  }

  /**
   * @brief: The Operator Parenthesis - executes the layer on a copy of the
   * given matrix and returns a correct copied matrix with new weight and bias.
   */
  Matrix operator() (const Matrix &matrix) const;

  /**
 * @brief: The privet data of the class Dense.
 */
 private:
  Matrix _weights;
  Matrix _bias;
  ActivationFunction _activation_function;
};

#endif //DENSE_H

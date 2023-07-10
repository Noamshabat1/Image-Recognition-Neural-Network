#include "Dense.h"

Dense::Dense (const Matrix &weight, const Matrix &bias,
              ActivationFunction activation_function) :
    _weights (weight),
    _bias (bias),
    _activation_function (activation_function)
{

}

Matrix Dense::operator() (const Matrix &matrix) const
{
  return _activation_function ((_weights * matrix) + _bias);
}


#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

// from the tip in the pdf.
typedef Matrix (*ActivationFunction) (const Matrix &);

namespace activation
{
    /**
    * Applies the relu activation function on a given matrix.
    *
    * @param matrix The matrix to apply the activation function on.
    * @return The resulting matrix after applying relu.
    */
    Matrix relu (const Matrix &matrix);

/**
 * Applies the softmax activation function on a given matrix.
 *
 * @param matrix The matrix to apply the activation function on.
 * @return The resulting matrix after applying softmax.
 */
    Matrix softmax (const Matrix &matrix);
}

#endif //ACTIVATION_H




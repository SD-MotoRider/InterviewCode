#ifndef MATRIX_H
#define MATRIX_H

// MIT License
//
// Copyright (c) 2018 Michael Simpson
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <algorithm>
#include <iomanip>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>
#include <thread>

template<typename T> class Matrix
{
public:
	/*!
		\fn Matrix()
		\relates Matrix

		Constructs and empty Matrix, isEmpty will return true;

		\sa isEmpty()
	*/
	Matrix() :
		_rows(0),
		_cols(0),
		_array(nullptr)
	{
	}

	/*!
		\fn Matrix(const Matrix& copyMe)
		\relates Matrix

		Copy constructor
		The resulting matrix, if copyMe is sucessful is a Matrix that returns false on isEmpty

		\sa isEmpty()
	*/
	Matrix(const Matrix& copyMe)
	{
		_rows = 0;
		_cols = 0;

		unsigned long arrayCells(_rows * _cols);
		_array =  new T[arrayCells];
		if (_array != nullptr)
		{
			::memcpy(_array, copyMe._array, arrayCells * sizeof(T));
			_rows = copyMe._rows;
			_cols = copyMe._cols;
		}
	}

	/*!
		\fn Matrix(unsigned short rows, unsigned short cols, T initialValue = T(0))
		\relates Matrix

		Constructs a Matrix with the number of \a rows and the number of \a cols
		optional the constructor can initialize the matrix with an initial value
	*/
	Matrix(unsigned short rows, unsigned short cols, T initialValue = T(0)) :
		_rows(0),
		_cols(0),
		_array(nullptr)
	{
		unsigned long arrayCells(rows * cols); // large enough to hold USHRT_MAX * USHRT_MAX

		if (arrayCells > 0) // make sure there is dimension, if either is zero, it's not valid
		{
			_array = new T[arrayCells];
			if (_array != nullptr) // if this fails, the matrix will be empty
			{
				std::fill(_array, _array + arrayCells, initialValue);
				_rows = rows;
				_cols = cols;
			}
		}
	}

	/*!
		\fn ~Matrix
		\relates Matrix

		returns the number of rows in the matrix, 0 if invalid
	*/
	~Matrix()
	{
		if (_array != nullptr)
		{
			 delete _array;
			_array = nullptr;
		}
	}

	/*!
		\fn unsigned short rows()
		\relates Matrix

		returns the number of rows in the matrix, 0 if invalid
	*/
	unsigned short rows(void) const
	{
		return _rows;
	}

	/*!
		\fn unsigned short cols()
		\relates Matrix

		returns the number of columns in the matrix, 0 if invalid
	*/
	unsigned short cols(void) const
	{
		return _cols;
	}

	/*!
		\fn bool isEmpty()
		\relates Matrix

		returns true if the matrix is empty and invalid
	*/
	bool isEmpty(void) const
	{
		return (_array == nullptr);
	}

	/*!
		\fn T getValue(unsigned short row, unsigned short col)
		\relates Matrix

		one based accessor, throws std::exception on boundary conditions

		Returns the T value at \a row, \a col intersection.

		\sa setValue()
	*/
	T getValue(unsigned short row, unsigned short col) const
	{
		if (isEmpty())
			throw std::runtime_error("Matrix is invalid");

		if (row == 0)
			throw std::runtime_error("getValue row == 0");

		if (col == 0)
			throw std::runtime_error("getValue col == 0");

		if (row > _rows)
			throw std::range_error("row: " + to_string(row) + " out of bounds: " + to_string(_rows));

		if (col > _cols)
			throw std::range_error("col: " + to_string(row) + " out of bounds: " + to_string(_cols));

		return at(row - 1, col - 1); // Good to go!
	}

	/*!
		\fn T setValue(T& value, unsigned short row, unsigned short col)
		\relates Matrix

		one based setter
		sets the value at one based row/column

		Returns true if the value was set, false if not.

		\sa getValue()
	*/
	// This is a ones based accessor to match the math of matrixes
	bool setValue(T& value, unsigned short row, unsigned short col)
	{
		bool result(false);

		if (isEmpty() == false && row > 0 && col > 0 && row <= _rows && col <= _cols)
		{
			setAt(value, row - 1, col - 1);
			result = true;
		}

		return result;
	}

	/*!
		\fn Matrix<T> operator*(const Matrix<T>& multiplyByMe)
		\relates Matrix

		Multiplies this matrix by multiplyByMe
		If the operation fails, it returns an empty Matrix

		\sa isEmpty()
	*/
	Matrix<T> operator*(const Matrix<T>& multiplyByMe) const
	{
		Matrix<T> result;

		// verify we have two viable matrixes
		if (multiplyByMe.isEmpty() == false && isEmpty() == false)
		{
			// verify we can undertake the operation
			if (_cols == multiplyByMe._rows)
			{
				// looks good, create a destination Matrix
				result = Matrix(_rows, multiplyByMe._cols);
				for (unsigned short row = 0; row < _rows; row++)
				{
					for (unsigned short column(0); column < multiplyByMe._cols; column++)
					{
						T sum = (T) 0;
						for (unsigned short r(0); r < _cols; r++)
						{
							sum += at(row, r) * multiplyByMe.at(r, column);
						}
						result.setAt(sum, row, column);
					}
				}
			}
		}

		return result;
	}

	/*!
		\fn Matrix<T> transpose(void)
		\relates Matrix

		Transposes this matrix and returns the result
		If the operation fails, it returns an empty Matrix

		\sa isEmpty()
	*/
	Matrix<T> transpose(void) const
	{
		Matrix<T> result;

		return result;
	}

	/*!
		\fn print(ostream& outputStrm)
		\relates Matrix

		Prints the Matrix to an output stream
	*/
	void print(std::ostream& outputStrm)
	{
		if (isEmpty())
		{
			outputStrm << "Empty Matrix" << std::endl;
			return;
		}

		for (auto row = 0; row < _rows; row++)
		{
			bool first(true);
			for (auto col = 0; col < _cols; col++)
			{
				if (first == false)
					outputStrm << ", ";

				first = false;

				outputStrm << std::setw(5) << at(row, col);
			}

			outputStrm << std::endl;
		}

		outputStrm << std::endl << std::endl;
	}

private:
	/*!
		\internal
		\fn T at(unsigned short row, unsigned short col)
		\relates Matrix

		zero based accessor, validity must be checked before invoking

		Returns the value at \a row, \a col intersection.

		\sa setAt()
	*/

	T at(unsigned short row, unsigned short col) const
	{
		return _array[row * _cols + col];
	}

	/*!
		\internal
		\fn T setAt(T& value, unsigned short row, unsigned short col)
		\relates Matrix

		zero based setter, validity must be checked before invoking

		sets the \s value at the \a row, \a col intersection.

		\sa at()
	*/
	void setAt(T& value, unsigned short row, unsigned short col)
	{
		_array[row * _cols + col] = value;
	}

	unsigned short				_rows;
	unsigned short				_cols;
	T*							_array;
};

#endif // MATRIX_H

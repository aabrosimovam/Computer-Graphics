#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <initializer_list>
using namespace std;

typedef vector<double> row;

class Figura;

class Matrix : public std::vector<row>
{
public:
    Matrix(initializer_list<row> matrix);

    Matrix(int rows, int columns);

    const Matrix operator * (const Matrix &matrix) const;

private:
    int rowCount;
    int columnCount;
};

#endif // MATRIX_H

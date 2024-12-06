#include "Matrices.h"
using namespace std;
namespace Matrices
{
    Matrix::Matrix(int _rows, int _cols)
    {
        rows = _rows;
        cols = _cols;
        a.resize(rows, vector<double>(cols, 0)); // Initialize the matrix with 0s
    }

    Matrix operator+(const Matrix &a, const Matrix &b){
        if(a.getRows() != b.getRows() || a.getCols() != b.getCols()){
            throw runtime_error("Error: dimensions must agree");
        }
        else{
            Matrix c(a.getRows(), a.getCols());
            for (int i = 0; i < a.getRows(); i++)
            {
                for (int j = 0; j < a.getCols(); j++){
                    c(i, j) = a(i, j) + b(i, j);
                }
            }
            return c;
        }
    }

    Matrix operator*(const Matrix &a, const Matrix &b)
    {
        if (a.getCols() != b.getRows())
        {
            throw runtime_error("Error: dimensions must agree");
        }
        else
        {
            Matrix c(a.getRows(), b.getCols());

            for (int i = 0; i < a.getRows(); ++i)
            {
                for (int j = 0; j < b.getCols(); ++j)
                {
                    double sum = 0;
                    for (int k = 0; k < a.getCols(); ++k)
                    {
                        sum += a(i, k) * b(k, j);
                    }
                    c(i, j) = sum;
                }
            }
            return c;
        }
    }
    bool operator==(const Matrix &a, const Matrix &b){
        if(a.getRows() !=b.getRows() || a.getCols() != b.getCols())
            return false;

        for (int i = 0; i < a.getRows(); i++){
            for (int j = 0; j < b.getCols(); j++){
                if(abs(a(i,j) - b(i,j)) >= 0.001){
                    return false;
                }
            }
            return true;
        }
    }

    bool operator!=(const Matrix &a, const Matrix &b){
        return !(a == b);
    }

    ostream &operator<<(ostream &out, const Matrix &a)
    {
        out << "\n";
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                out << setw(10) << a(i, j);
            }
            out << endl;
        }
        return out;
    }

    ScalingMatrix::ScalingMatrix(double scale)
    Matrix(2, 2);
    {
        a[0][0] = scale;
        a[1][1] = scale;
    }

    RotationMatrix::RotationMatrix(double theta) : Matrix(2,2){
        (0,0) = cos(theta);
        (0,1) = -sin(theta);
        (1,0) = sin(theta);
        (1,1) = cos(theta);
    }
}



//
// Created by pierr on 10-May-23.
//

#ifndef RTX_MATRIX_H
#define RTX_MATRIX_H
#include "iostream"
#include "HPoint.h"
#include "HVector.h"

class Matrix{
private:
    int m_rows;
    int m_cols;
    int* m_tab;

public:
    Matrix(int rows, int cols, int val = 1);
    Matrix(const Matrix& m);
    Matrix& operator=(Matrix m);
    ~Matrix();
    void swap(Matrix& m);
    int getCols() const;
    int getRows() const;
    void set(int i, int j, int val);
    int get(int i, int j)const;
    int& operator[](int index);
    int& operator()(int i,int j);
    int operator[](int index) const;
    int operator()(int i,int j) const;
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

    //Inversion part
    static void getCfactor(const Matrix& M, Matrix& t, int p, int q, int n);

    static int DET(const Matrix& M, int n);

    static void ADJ(const Matrix& M, Matrix& adj);

    static bool INV(const Matrix& M, Matrix& inv);

    Matrix operator*(const Matrix& other) const;
    Matrix operator*(const HPoint& point) const;
    Matrix operator*(const HVector& point) const;

};

#endif //RTX_MATRIX_H

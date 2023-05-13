//
// Created by pierr on 10-May-23.
//

#ifndef RTX_MATRIX_H
#define RTX_MATRIX_H

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
};

#endif //RTX_MATRIX_H

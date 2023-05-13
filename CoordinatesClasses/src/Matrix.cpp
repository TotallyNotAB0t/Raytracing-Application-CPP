//
// Created by pierr on 10-May-23.
//

#include "../include/Matrix.h"
#include <utility>

Matrix::Matrix(int rows, int cols, int val){
    this->m_rows = rows;
    this->m_cols = cols;
    int s = rows*cols;
    this->m_tab = new int[s];
    for(int i = 0; i < s; ++i){
        this->m_tab[i] = val;
    }
}

Matrix::Matrix(const Matrix& m){
    this->m_cols = m.m_cols;
    this->m_rows = m.m_rows;
    int s = m_rows*m_cols;
    this->m_tab = new int[s];
    for(int i = 0; i < s; ++i){
        this->m_tab[i] = m.m_tab[i];
    }
}

Matrix &Matrix::operator=(Matrix m) {
    swap(m);
    return *this;
}

Matrix::~Matrix() {
    if(m_tab){
        delete[] m_tab;
    }
}

void Matrix::swap(Matrix& m){
    std::swap(m_cols, m.m_cols);
    std::swap(m_rows, m.m_rows);
    std::swap(m_tab, m.m_tab);
}

int Matrix::getCols() const {
    return this->m_cols;
}

int Matrix::getRows() const {
    return this->m_rows;
}

void Matrix::set(int i, int j, int val) {
    m_tab[j+i*m_cols] = val;
}

int Matrix::get(int i, int j) const {
    return m_tab[j+i*m_cols];
}

int &Matrix::operator[](int index) {
    return m_tab[index];
}

int &Matrix::operator()(int i, int j) {
    return m_tab[j+i*m_cols];
}

int Matrix::operator[](int index) const {
    return m_tab[index];
}

int Matrix::operator()(int i, int j) const {
    return m_tab[j+i*m_cols];
}

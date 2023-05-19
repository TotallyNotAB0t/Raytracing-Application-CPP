//
// Created by pierr on 10-May-23.
//

#include "../include/Matrix.h"
#include "../include/HPoint.h"
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

std::ostream &operator<<(std::ostream &os, const Matrix &m) {
    for (int i = 0; i < m.getRows(); ++i) {
        os << "| ";
        for (int j = 0; j < m.getCols(); ++j) {
            if (m.get(i,j) < 0){
                os << m.get(i, j) << ' ';
            } else {
                os << ' ' << m.get(i, j) << ' ';
            }
        }
        os << '|' << std::endl;
    }
    os << std::endl;
    return os;
}

void Matrix::getCfactor(const Matrix &M, Matrix &t, int p, int q, int n)  {
    int i = 0, j = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (r != p && c != q) {
                t.set(i, j++, M.get(r, c));
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int Matrix::DET(const Matrix &M, int n)  {
    int D = 0;
    if (n == 1)
        return M.get(0, 0);
    Matrix t(n, n); // store cofactors
    int s = 1; // store sign multiplier

    // Iterate each element of first row
    for (int f = 0; f < n; f++) {
        getCfactor(M, t, 0, f, n);
        D += s * M.get(0, f) * DET(t, n - 1);
        s = -s;
    }
    return D;
}

void Matrix::ADJ(const Matrix &M, Matrix &adj) {
    if (M.getCols() == 1) {
        adj.set(0, 0, 1);
        return;
    }
    int s = 1;
    Matrix t(M.getCols(), M.getCols());

    for (int i = 0; i < M.getCols(); i++) {
        for (int j = 0; j < M.getCols(); j++) {
            getCfactor(M, t, i, j, M.getCols());
            s = ((i + j) % 2 == 0) ? 1 : -1;
            adj.set(j, i, s * DET(t, M.getCols() - 1));
        }
    }
}

bool Matrix::INV(const Matrix &M, Matrix &inv)  {
    int det = DET(M, M.getCols());
    if (det == 0) {
        std::cout << "can't find its inverse";
        return false;
    }
    Matrix adj(M.getCols(), M.getCols());
    ADJ(M, adj);

    for (int i = 0; i < M.getCols(); i++) {
        for (int j = 0; j < M.getCols(); j++) {
            inv.set(i, j, adj.get(i, j) / static_cast<float>(det));
        }
    }
    return true;
}

Matrix Matrix::operator*(const Matrix& other) const {
    Matrix result(m_rows, other.m_cols);

    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < other.m_cols; ++j) {
            float sum = 0.0;
            for (int k = 0; k < m_cols; ++k) {
                sum += m_tab[i * m_cols + k] * other.m_tab[k * other.m_cols + j];
            }
            result.m_tab[i * result.m_cols + j] = sum;
        }
    }

    return result;
}

Matrix Matrix::operator*(const HPoint& point) const {
    Matrix result(1, 4);

    result.set(0, 0, m_tab[0] * point.getX() + m_tab[1] * point.getY() + m_tab[2] * point.getZ() + m_tab[3] * point.getW());
    result.set(0, 1, m_tab[4] * point.getX() + m_tab[5] * point.getY() + m_tab[6] * point.getZ() + m_tab[7] * point.getW());
    result.set(0, 2, m_tab[8] * point.getX() + m_tab[9] * point.getY() + m_tab[10] * point.getZ() + m_tab[11] * point.getW());
    result.set(0, 3, m_tab[12] * point.getX() + m_tab[13] * point.getY() + m_tab[14] * point.getZ() + m_tab[15] * point.getW());

    return result;
}

Matrix Matrix::operator*(const HVector& vector) const {
    Matrix result(1, 4);

    result.set(0, 0, m_tab[0] * vector.getX() + m_tab[1] * vector.getY() + m_tab[2] * vector.getZ() + m_tab[3] * vector.getW());
    result.set(0, 1, m_tab[4] * vector.getX() + m_tab[5] * vector.getY() + m_tab[6] * vector.getZ() + m_tab[7] * vector.getW());
    result.set(0, 2, m_tab[8] * vector.getX() + m_tab[9] * vector.getY() + m_tab[10] * vector.getZ() + m_tab[11] * vector.getW());
    result.set(0, 3, m_tab[12] * vector.getX() + m_tab[13] * vector.getY() + m_tab[14] * vector.getZ() + m_tab[15] * vector.getW());

    return result;
}

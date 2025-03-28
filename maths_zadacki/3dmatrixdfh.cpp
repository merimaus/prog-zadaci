#include <iostream>
#include <vector>
#include <cmath>

#define PI 3.1415926535f

using namespace std;

struct Point {
    double e[4] = {0};
    
    Point(double x = 0, double y = 0, double z = 0, double w = 0) {
        e[0] = x;
        e[1] = y;
        e[2] = z;
        e[3] = w;
    };
};

struct Matrix {
    double m[4][4] = {0};
    Matrix() { for (int i = 0; i < 4; i++) m[i][i] = 1; }
    Matrix(int v) { for (int i = 0; i < 4; i++) m[i][i] = v; }
    
    static Matrix rotate(int x, int y, int z) {
        Matrix result;
        float x_rad = x * PI / 180;
        float y_rad = y * PI / 180;
        float z_rad = z * PI / 180;
        result.m[0][0] = cos(z_rad) * cos(y_rad);
        result.m[0][1] = cos(z_rad) * sin(y_rad) * sin(x_rad) - sin(z_rad) * cos(x_rad);
        result.m[0][2] = cos(z_rad) * sin(y_rad) * cos(x_rad) + sin(z_rad) * sin(x_rad);
        result.m[1][0] = sin(z_rad) * cos(y_rad);
        result.m[1][1] = sin(z_rad) * sin(y_rad) * sin(x_rad) + cos(z_rad) * cos(x_rad);
        result.m[1][2] = sin(z_rad) * sin(y_rad) * cos(x_rad) - cos(z_rad) * sin(x_rad);
        result.m[2][0] = -sin(y_rad);
        result.m[2][1] = cos(y_rad) * sin(x_rad);
        result.m[2][2] = cos(y_rad) * cos(x_rad);
        return result;
    }
    
    Matrix operator*(const Matrix &second) {
        Matrix result(0);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    result.m[i][j] += m[i][k] * second.m[k][j];
                }
            }
        }
        return result;
    }
    
    Point operator*(const Point &second) {
        Point result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.e[i] += m[i][j] * second.e[j];
            }
        }
        return result;
    }
};

ostream &operator<<(ostream &os, const Matrix &matrix) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            os << matrix.m[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

ostream &operator<<(ostream &os, const Point &p) {
    os << "[ " << p.e[0] << ' ' << p.e[1] << ' ' << p.e[2] << ' ' << p.e[3] << " ]" << endl;
    return os;
}

int main() {
    Matrix first;
    Matrix second;
    Point p1(3, 1, 1, 1);
    
    first.m[0][2] = 3;
    second.m[0][0] = .5;
    
    Matrix rot = Matrix::rotate(30, 30, 30);
    
    //second.m[0][0] = 3;
    
    Matrix result = first * second;
    Point p2 = rot * p1;
    cout << p2 << endl;
    
    return 0;
}
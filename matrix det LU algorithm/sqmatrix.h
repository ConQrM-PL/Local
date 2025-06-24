#pragma once

#include<iostream>
#include<vector>

class sqmatrix{
private:
    int n;
    std::vector<std::vector<double>> M;
public:
    sqmatrix(int k);
    sqmatrix(std::vector<std::vector<double>> data);
    int get_n();
    std::vector<std::vector<double>> get_M();
    void print_matrix();
    void scalar_row(int k, double a);
    void add_rows(int target, int source);
    std::vector<double> get_row(int k);
    void add_to_row(int k, std::vector<double> data);
    void set_value(int row, int col, double val);
    double get_value(int row, int col);
    double diag_product();
};

void scale_vector(std::vector<double> & source, double scalar);
void LUdecomp(sqmatrix source, sqmatrix & L, sqmatrix & U);
double matrix_det(sqmatrix source);
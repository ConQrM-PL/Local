#pragma once

#include<iostream>
#include<vector>


class lineq{
private:
    std::vector<std::vector<double>> matrix;
    int row;
    int col;
    std::vector<double> solution;
public:
    lineq(int m,int n);
    void modify_cell(int m, int n, double value);
    void modify_row(int m, std::vector<double> value);
    void swap_rows(int row1, int row2);
    void scalar_row(int m, double value);
    void add_row(int target, int reference);
    void subtract_row(int target, int reference);
    void triangulate();
    void diagonalize();
    void beautify();
    void set_solution();
    std::vector<double> get_solution();
    void print_matrix();
};
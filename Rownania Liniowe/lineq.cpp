#include "lineq.h"
#include <iomanip>
#include <cmath>

#define EPSILON 1e-12

//m row, n col
lineq::lineq(int m,int n){
    matrix.clear();
    std::vector<double> temp;
    for (int i = 0; i < m; i++){
        temp.clear();
        for (int j = 0; j < n; j++){
            temp.push_back(0.0);
        }
        matrix.push_back(temp);
    }
    row = m;
    col = n;
}

void lineq::modify_cell(int m, int n, double value){
    matrix[m][n] = value;
}

void lineq::modify_row(int m, std::vector<double> value){
    matrix[m] = value;
}

void lineq::swap_rows(int row1, int row2){
    if (row1 != row2){
        std::vector<double> temp;
        temp = matrix[row1];
        matrix[row1] = matrix[row2];
        matrix[row2] = temp;
    }
}

void lineq::scalar_row(int m, double value){
    for (int i = 0; i < col; i++){
        matrix[m][i] *= value;
    }
}

void lineq::add_row(int target, int reference){
    for (int i = 0; i < col; i++){
        matrix[target][i] += matrix[reference][i];
    }
}

void lineq::subtract_row(int target, int reference){
    for (int i = 0; i < col; i++){
        matrix[target][i] -= matrix[reference][i];
    }
}

// zaklada ze da sie jednoznacznie rozwiazac uklad rownan metoda Gaussa Jordana
void lineq::triangulate(){
    for (int i = 0; i < row; i++){
        double currentlead = matrix[i][i];
        scalar_row(i, 1/currentlead);
        for (int j = i+1; j < row; j++){
            currentlead = matrix[j][i];
            if (currentlead){
                scalar_row(j, 1/currentlead);
                subtract_row(j, i);
            }
        }
    }
    std::cout << "trig done:\n";
    print_matrix();
}

//zakalda ze trojkatna
void lineq::diagonalize(){
    std::vector<double> tempstore;
    double currentlead;
    for (int i = 0; i < row-1; i++){
        for (int j = i+1; j < col-1; j++){
            tempstore = matrix[j];
            currentlead = matrix[i][j];
            if (currentlead){
                scalar_row(j, currentlead);
                subtract_row(i,j);
            }
            modify_row(j, tempstore);
        }
    }
    std::cout << "diag done:\n";
    print_matrix();
}

void lineq::beautify(){
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            if (matrix[i][j] == -0){
                double temp = matrix[i][j];
                modify_cell(i,j, 0.0);
            } else if (fabs(matrix[i][j]) < EPSILON){
                double temp = matrix[i][j];
                modify_cell(i,j, 0.0);
            }
        }
    }
    std::cout << "beutified:\n";
    print_matrix();
}

void lineq::print_matrix(){
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            std::cout << std::setprecision(2) << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "___\n"; 
}

void lineq::set_solution(){
    solution.clear();
    for (int i = 0; i < row; i++){
        solution.push_back(matrix[i][col-1]);
    }
}

std::vector<double> lineq::get_solution(){
    return solution;
}
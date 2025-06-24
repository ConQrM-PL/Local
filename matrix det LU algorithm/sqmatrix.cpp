#include"sqmatrix.h"


sqmatrix::sqmatrix(int k){
    n = k;
    std::vector<double> temp1;
    for (int i = 0; i < n; i++){
        temp1.push_back(0.0);
    }
    std::vector<std::vector<double>> temp2;
    for (int i = 0; i < n; i++){
        temp2.push_back(temp1);
    }
    M = temp2;
}

sqmatrix::sqmatrix(std::vector<std::vector<double>> data){
    M = data;
    n = M.size();
}

void sqmatrix::print_matrix(){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            std::cout << M[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void sqmatrix::scalar_row(int k, double a){
    for (int i = 0; i < n; i++){
        M[k][i] *= a;
    }
}

void sqmatrix::add_rows(int target, int source){
    for (int i = 0; i < n; i++){
        M[target][i] += M[source][i];
    }
}

std::vector<double> sqmatrix::get_row(int k){
    return M[k];
}

void sqmatrix::add_to_row(int k, std::vector<double> data){
    for (int i = 0; i < n; i++){
        M[k][i] += data[i];
    }
}

int sqmatrix::get_n(){
    return n;
}

std::vector<std::vector<double>> sqmatrix::get_M(){
    return M;
}

void sqmatrix::set_value(int row, int col, double val){
    M[row][col] = val;
}

double sqmatrix::get_value(int row, int col){
    return M[row][col];
}

double sqmatrix::diag_product(){
    double temp = 1.0;
    for (int i = 0; i < n; i++){
        temp *= M[i][i];
    }
    return temp;
}

void scale_vector(std::vector<double> & source, double scalar){
    for (int i = 0; i < source.size(); i++){
        source[i] *= scalar;
    }
}

void LUdecomp(sqmatrix source, sqmatrix & L, sqmatrix & U){
    int n = source.get_n();
    U = sqmatrix(source.get_M());
    L = sqmatrix(source.get_n());
    for (int i = 0; i < n; i++){
        L.set_value(i,i, 1.0);
    }
    std::vector<double> row_memo;
    double lead, a;

    for (int i = 1; i < n; i++){
        for (int j = 0; j < i; j++){
            row_memo = U.get_row(j);
            lead = U.get_value(i,j);
            a = lead/row_memo[j];
            L.set_value(i,j, a);
            scale_vector(row_memo, -a);
            U.add_to_row(i, row_memo);
        }
    }

    std::cout << "source:\n";
    source.print_matrix();
    std::cout << "L:\n";
    L.print_matrix();
    std::cout << "U:\n";
    U.print_matrix();
}

double matrix_det(sqmatrix source){
    sqmatrix L(1), U(1);
    LUdecomp(source, L, U);
    return L.diag_product()*U.diag_product();
}
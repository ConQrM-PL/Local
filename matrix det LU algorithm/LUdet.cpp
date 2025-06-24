#include<iostream>
#include"sqmatrix.h"

using namespace std;

int main(){
    vector<vector<double>> data = {{1,2,4},{4,5,8},{5,1,8}};
    sqmatrix macierz(data);
    double det = matrix_det(macierz);
    cout << "det = "<< det << "\n";
    return 0;
}
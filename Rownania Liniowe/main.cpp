//program testowy

#include<iostream>
#include"lineq.h"
#include<vector>

using namespace std;

int main(){
    vector<double> r0 = {1,1,1,3};
    vector<double> r1 = {2,1,0,3};
    vector<double> r2 = {15,-12,3,6};
    lineq uklad34 (3,4);
    uklad34.modify_row(0, r0);
    uklad34.modify_row(1, r1);
    uklad34.modify_row(2, r2);
    uklad34.print_matrix();
    uklad34.triangulate();
    uklad34.diagonalize();
    uklad34.beautify();
    uklad34.set_solution();
    cout << "solution: ";
    r0 = uklad34.get_solution();
    for (int i = 0; i < r0.size(); i++){
        cout << r0[i] << " ";
    }
    cout << endl;
    return 0;
}
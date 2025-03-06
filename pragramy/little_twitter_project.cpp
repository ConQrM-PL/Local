#include<iostream>

using namespace std;

void Init (bool* arr[], int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            arr[i][j]= false;
        }
    }
}

void DrawEdge(bool* arr[], int n, int size){
    for (int i = 0; i < n; i++){
        arr[i][0] = true;
        arr[n+i+1][size-1] = true;
        arr[size-1][i] = true;
        arr[0][n+i+1] = true;
    }
}

void DrawCross(bool* arr[], int n, int size){
    for (int i = 0; i < size; i++){
        arr[n][i] = true;
        arr[i][n] = true;
    }
}

void PrintPic(bool* arr[], int size){
    for (int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if (arr[i][j]) {
                cout << "*";
            } else {
                cout << " ";
            }
        }
        cout << "\n";
    }
}


int main(){
    int n;
    cin >> n;
    const int size = n*2+1;
    bool** picture;
    picture = new bool*[size];
    for (int i = 0; i < size; i++){
        picture[i] = new bool[size];
    }
    Init(picture, size);
    DrawCross(picture, n, size);
    DrawEdge(picture, n, size);
    PrintPic(picture, size);
    delete[] picture;
    return 0;
}
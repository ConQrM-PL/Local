#include<iostream>
#include<vector>
#include<random>

using namespace std;

#define MIN_VAL 1
#define MAX_VAL 100

class RandomGenerator{
public:
    static random_device rd;
    static mt19937 gen;
    static uniform_int_distribution<int> dist;
    
    static float getRandomNumber(){
        return dist(gen);
    }
};

random_device RandomGenerator::rd;
mt19937 RandomGenerator::gen(rd());
uniform_int_distribution<int> RandomGenerator::dist(MIN_VAL, MAX_VAL);

vector<int> generate_data (int n){
    int value;
    vector<int> result;
    for (size_t i = 0; i < n; i++){
        value = RandomGenerator::getRandomNumber();
        result.push_back(value);
    }
    return result;
}

void show_vector(vector<int> data){
    cout << "[";
    for (size_t i = 0; i < data.size() - 1; i++){
        cout << data[i] << ", "; 
    }
    if (data.size() - 1 > 0) cout << data[data.size() - 1];
    cout << "]\n";
}

void swap(int & a, int & b){
    int c = a;
    a = b;
    b = c;
}

bool is_in_order(int a, int b){
    return (a <= b);
}

void bubble_sort(vector<int> & table, int & step_total){
    show_vector(table);
    if (table.size() < 2) return;
    bool was_there_a_swap = false;
    int cleared = 0, steps = 0;
    do {
        was_there_a_swap = false;
        for (size_t i = 0; i < table.size() - 1 - cleared; i++){
            if (!is_in_order(table[i], table[i+1])){
                swap(table[i], table[i+1]);
                steps++;
                cout << steps << ". ";
                show_vector(table);
                was_there_a_swap = true;
            }
        }
        cleared++;
    } while (was_there_a_swap);
    cout << "Bubble sort end. Sorted in "<< steps << " steps\n";
    step_total = steps;
}

void quick_sort(vector<int> & data, int & step_total){
    if (data.size() < 2) return;
    int pivot = data[0];
    vector<int> smaller, greatereq;
    for (size_t i = 1; i < data.size(); i++){
        if (pivot > data[i]){
            smaller.push_back(data[i]);
        } else {
            greatereq.push_back(data[i]);
        }
        step_total++;
    }
    quick_sort(smaller, step_total);
    quick_sort(greatereq, step_total);
    data.clear();
    for (size_t i = 0; i < smaller.size(); i++){
        data.push_back(smaller[i]);
    }
    data.push_back(pivot);
    for (size_t i = 0; i < greatereq.size(); i++){
        data.push_back(greatereq[i]);
    }
    show_vector(data);
    cout << "Steps total: " << step_total << "\n";
}

//is it heap sort tho? I dont remember...
void heap_sort(vector<int> & data, int & step_total){
    if (data.size() < 2) return;

    vector<int> heap_left, heap_right;
    for (size_t i = 0; i < data.size(); i++){
        if (i%2) {
            heap_left.push_back(data[i]);
        } else {
            heap_right.push_back(data[i]);
        }
    }
    heap_sort(heap_left, step_total);
    heap_sort(heap_right, step_total);
    int l_counter = 0, r_counter = 0;
    data.clear();
    while (l_counter < heap_left.size() && r_counter < heap_right.size()){
        if (heap_left[l_counter] < heap_right[r_counter]){
            data.push_back(heap_left[l_counter]);
            l_counter++;
        } else {
            data.push_back(heap_right[r_counter]);
            r_counter++;
        }
        show_vector(data);
        step_total++;
    }
    for (size_t i = l_counter; i < heap_left.size(); i++){
        data.push_back(heap_left[i]);
    }
    for (size_t i = r_counter; i < heap_right.size(); i++){
        data.push_back(heap_right[i]);
    }
}

bool compare_vectors (vector<int> v1, vector<int> v2){
    if (v1.size() != v2.size()) return false;
    for (size_t i = 0; i < v1.size(); i++){
        if (v1[i] != v2[i]) return false;
    }
    return true;
}

int main(){
    int n, qssteps = 0, bssteps, hssteps = 0;
    cin >> n;
    vector<int> data = generate_data(n), copy1 = data, copy2 = data;
    bubble_sort(data, bssteps);
    quick_sort(copy1, qssteps);
    heap_sort(copy2, hssteps);
    cout << "Step comparison:\nBubble sort: " << bssteps << "\nQuick sort: " << qssteps << "\nHeap sort: " << hssteps << "\n";
    bool is_all_tests_the_same = compare_vectors(data, copy1) && compare_vectors(copy1, copy2);
    cout << "All results the same: " << is_all_tests_the_same << "\n";
    return 0;
}
#include <iostream>
#include <vector>
using namespace std;


struct Triple {
    int row;
    int col;
    int value;
};


struct TSMatrix {
    int rows, cols, nums;    
    vector<Triple> data;    

    TSMatrix(int r, int c) : rows(r), cols(c), nums(0) {}
};


void insert(TSMatrix &M, int r, int c, int val) {
    if (val == 0) return;
    M.data.push_back({r, c, val});
    M.nums++;
}


void printMatrix(const TSMatrix &M) {
    int k = 0;
    for (int i = 0; i < M.rows; i++) {
        for (int j = 0; j < M.cols; j++) {
            if (k < M.nums && M.data[k].row == i && M.data[k].col == j) {
                cout << M.data[k].value << " ";
                k++;
            } else {
                cout << "0 ";
            }
        }
        cout << endl;
    }
}


TSMatrix transpose(const TSMatrix &M) {
    TSMatrix T(M.cols, M.rows); 
    for (int c = 0; c < M.cols; c++) {
        for (int i = 0; i < M.nums; i++) {
            if (M.data[i].col == c) {
                T.data.push_back({M.data[i].col, M.data[i].row, M.data[i].value});
                T.nums++;
            }
        }
    }
    return T;
}


TSMatrix fastTranspose(const TSMatrix &M) {
    TSMatrix T(M.cols, M.rows);
    if (M.nums == 0) return T;

    vector<int> colCounts(M.cols, 0);     
    vector<int> colIndex(M.cols, 0);      

    for (int i = 0; i < M.nums; i++)
        colCounts[M.data[i].col]++;
    colIndex[0] = 0;
    for (int i = 1; i < M.cols; i++)
        colIndex[i] = colIndex[i - 1] + colCounts[i - 1];


    T.data.resize(M.nums);
    for (int i = 0; i < M.nums; i++) {
        int c = M.data[i].col;
        int pos = colIndex[c];
        T.data[pos] = {M.data[i].col, M.data[i].row, M.data[i].value};
        colIndex[c]++;
    }
    T.nums = M.nums;
    return T;
}


int main() {
    TSMatrix M(3, 3);

    insert(M, 0, 1, 5);
    insert(M, 1, 2, 3);
    insert(M, 2, 0, 6);

    cout << "原矩阵：" << endl;
    printMatrix(M);

    TSMatrix T1 = transpose(M);
    cout << "\n普通转置矩阵：" << endl;
    printMatrix(T1);

    TSMatrix T2 = fastTranspose(M);
    cout << "\n快速转置矩阵：" << endl;
    printMatrix(T2);

    return 0;
}

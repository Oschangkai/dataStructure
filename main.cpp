//
//  main.cpp
//  dataStructure1
//
//  Created by KaiYi.C on 10/5/16.
//  Copyright © 2016 KaiYi.C. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

void add_matrix(int [20][20], int [20][20]);
void add_sparse(int [20][20], int [20][20]);
void mul_matrix(int [20][20], int [20][20]);
void mul_sparse(int [20][20], int [20][20]);
int main() {
    // Declare two arrays, one char for storing matrix's name
    int matrix_A[20][20];
    int matrix_B[20][20];
    char letter;

    // Read file and catch error
    ifstream file("matrix.txt");
    if (!file) {
        cout << "An error occured when opening the file!\n";
        return 1;
    }
    
    // Store matrix A
    file >> letter;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++)
            file >> matrix_A[i][j];
    }
    // Store matrix B
    file >> letter;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++)
            file >> matrix_B[i][j];
    }
    
    file.close();
    
    add_matrix(matrix_A, matrix_B);
    //mul_matrix(matrix_A, matrix_B);
    add_sparse(matrix_A, matrix_B);
    
    return 0;

}

void add_matrix(int A[20][20], int B[20][20]) {
    cout << "add_martix:\n";
    double START, END;
    int matrix_added[20][20];
    START = clock();
    for(int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            matrix_added[i][j] = A[i][j] + B[i][j];
            cout << matrix_added[i][j] << " ";
        }
        cout << endl;
    }
    END = clock();
    cout << "執行時間：" << (END - START) << endl;
 
}

void mul_matrix(int A[20][20], int B[20][20]) {
    cout << "mul_matrix:\n";
    double START, END;
    int matrix_muled[20][20] = {};
    
    // muled[x, y] += A[x, z] * B[z, y], z = 20
    START = clock();
    for(int x = 0; x < 20; x++) {
        for(int y = 0; y < 20; y++) {
            for(int z = 0; z < 20; z++) {
                matrix_muled[x][y] += A[x][z] * B[z][y];
            }
            cout << matrix_muled[x][y] << " ";
        }
        cout << endl;
    }
    END = clock();
    cout << "執行時間：" << (END - START) << endl;
    
}

void add_sparse(int A[20][20], int B[20][20]) {
    cout << "add_sparse:\n";
    int _3colArr[20][3] = {};
    int added_sparse[20][20] = {};
    int count = 0;
    bool checkPoint = 0;
    double START, END;
    START = clock();
    
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 20; j++) {
            if(A[i][j] != 0) {
                _3colArr[count][0] = i;
                _3colArr[count][1] = j;
                _3colArr[count][2] = A[i][j];
                count++;
                checkPoint = 1;
                added_sparse[i][j] = A[i][j];
            }
            if(B[i][j] != 0) {
                if (checkPoint) {
                    _3colArr[count-1][2] += B[i][j];
                    added_sparse[i][j] = _3colArr[count-1][2];
                } else if (!checkPoint) {
                    _3colArr[count][0] = i;
                    _3colArr[count][1] = j;
                    _3colArr[count][2] = B[i][j];
                    count++;
                    added_sparse[i][j] = B[i][j];
                }
            }
            checkPoint = 0;
        }
    }
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            cout << added_sparse[i][j] << " ";
        }
        cout << endl;
    }
    cout << "3-column array:\n";
    for (int i = 0; i < 20; i++) { // print out
        if(_3colArr[i][0] == 0 && _3colArr[i][1] == 0) break; // if (x, y) == (0, 0) => end
        cout << _3colArr[i][0] << " " << _3colArr[i][1] << " " << _3colArr[i][2] << endl;
    }
    END = clock();
    cout << "執行時間：" << (END - START) << endl;
}

#include <iostream>
#include <fstream>

using namespace std;

void add_matrix(int [20][20], int [20][20]);
void add_sparse(int [20][20], int [20][20]);
void mul_matrix(int [20][20], int [20][20]);
void mul_sparse(int [20][20], int [20][20]);

void init_3colArr(int arr[20][20], int _3colArr[40][3]) {
    int count = 1;
    // init _3colArr
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (arr[i][j] != 0) {
                _3colArr[count][0] = i;
                _3colArr[count][1] = j;
                _3colArr[count][2] = arr[i][j];
                count++;
            }
        }
    }
    _3colArr[0][2] = count - 1; // count elements in array
    
    // print out 3colArr
    for (int i = 0; i < 20; i++) {
        if (_3colArr[i][0] == 0 && _3colArr[i][1] == 0) break; // if (x, y) == (0, 0) => end
        cout << _3colArr[i][0] << " " << _3colArr[i][1] << " " << _3colArr[i][2] << endl;
    }
}

void copy_array(int x[],int y[]) {
    for (int i = 0; i < 3; i++)
        y[i] = x[i];
}

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
    
    int ans = 1;
    while (ans) {
        cout << "1). add_matrix\n" << "2). add_sparse:\n"
             << "3). mul_matrix\n" << "4). mul_sparse\n"
             << "0). Exit\n"<< "Please enter your choise:";
        cin >> ans;
        system("clear");
        switch (ans) {
            case 1:
                cout << "\n\n\nadd_matrix:\n";
                add_matrix(matrix_A, matrix_B);
                break;
            case 2:
                cout << "\n\n\nadd_sparse:\n";
                add_sparse(matrix_A, matrix_B);
            case 3:
                cout << "\n\n\nmul_matrix:\n";
                mul_matrix(matrix_A, matrix_B);
            case 4:
                cout << "\n\n\nmul_sparse:\n";
                mul_sparse(matrix_A, matrix_B);
            default:
                break;
        }
        cout << "\n\n\n";
    }
    
    return 0;

}

void add_matrix(int A[20][20], int B[20][20]) {
    int matrix_added[20][20];
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            matrix_added[i][j] = A[i][j] + B[i][j];
            cout << matrix_added[i][j] << " ";
        }
        cout << endl;
    }
 
}

void mul_matrix(int A[20][20], int B[20][20]) {
    int matrix_muled[20][20] = {};
    
    // muled[x, y] += A[x, z] * B[z, y], z = 20
    for(int x = 0; x < 20; x++) {
        for(int y = 0; y < 20; y++) {
            for(int z = 0; z < 20; z++) {
                matrix_muled[x][y] += A[x][z] * B[z][y];
            }
            cout << matrix_muled[x][y] << " ";
        }
        cout << endl;
    }
    
}

void add_sparse(int A[20][20], int B[20][20]) {
    int a3[40][3] = {{20, 20}}, b3[40][3] = {{20, 20}}; // a, b 3-colArr
    int c3[40][3] = {{20, 20}}; // Merged 3colArr
    int added_sparse[20][20] = {};
    
    cout << "\nA\'s 3-column array:\n";
    init_3colArr(A, a3);
    cout << "\nB\'s 3-column array:\n";
    init_3colArr(B, b3);
    
    // Merge two arrays to c3
    int i, j, k;
    for (i = 1,  j = 1, k = 1; i <= a3[0][2] && j <= b3[0][2];) {
        if (a3[i][0] < b3[j][0])
            copy_array(a3[i++], c3[k++]); // copy_array(a3[i],c3[k]) and then i++, k++
        else if (a3[i][0] > b3[j][0])
            copy_array(b3[j++], c3[k++]);
        else {
            if (a3[i][1] < b3[j][1])
                copy_array(a3[i++], c3[k++]);
            else if (a3[i][1] > b3[j][1])
                copy_array(b3[j++], c3[k++]);
            else {
                copy_array(a3[i], c3[k]);
                c3[k++][2] = a3[i++][2] + b3[j++][2];
            }
        }
    }
    // Storing the remaining obj
    while (i <= a3[i][0])
        copy_array(a3[i++], c3[k++]);
    while (j <= b3[j][0])
        copy_array(b3[j++], c3[k++]);
    c3[0][2] = k - 1;
    
    // print out c3
    cout << "\n(A + B)\'s 3-column array:\n";
    for (i = 0; i < 20; i++) {
        if (c3[i][0] == 0 && c3[i][1] == 0 && c3[i][2] == 0) break; // if (x, y) == (0, 0) => end
        cout << c3[i][0] << " " << c3[i][1] << " " << c3[i][2] << endl;
    }
    
    // replace 0
    for (int i = 1; i < 40; i++)
        if (c3[i][2] != 0)
            added_sparse[c3[i][0]][c3[i][1]] = c3[i][2];
        else
            continue;
    // print out big array
    cout << "\n20*20 array:" << endl;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            cout << added_sparse[i][j] << " ";
        }
        cout << endl;
    }
}

void mul_sparse(int A[20][20], int B[20][20]) {
    int a3[40][3] = {{20, 20}}, b3[40][3] = {{20, 20}}; // a, b 3-colArr
    int c3[40][3] = {{20, 20}}; // Merged 3colArr
    int muled_sparse[20][20] = {};
    int num = 0, index1, index2;
    
    cout << "\nA\'s 3-column array:\n";
    init_3colArr(A, a3);
    cout << "\nB\'s 3-column array:\n";
    init_3colArr(B, b3);
    
    for (int x = 0; x < 40; x++) {
        for (int y = 0; y < 40; y++) {
            index1 = a3[x][0];
            index2 = b3[y][1];
            if ( (a3[x][1] == b3[y][0]) && a3[x][2] != 0 && b3[y][2] != 0) {
                //給定相乘後的結果要放的位置
                c3[num][0] = a3[x][0];
                c3[num][1] = b3[y][1];
                for (int index = 0; index < 20; index++) {
                    //最重要的一行: 因為A的行B的列相同所以他們會互相乘到
                    //然後是整個A的列分別乘以B的整行,說明檔案中有更詳細解釋
                    c3[num][2] += A[index1][index] * B[index][index2];
                    //給定相乘後的結果要放的值
                }
                num++;
            }
        }
    }
    
    c3[0][2] = num - 1;

    // repalce the value of muled_sparse array which is entire 0
    for (int i = 1; i < 40; i++)
        if (c3[i][2] != 0)
            muled_sparse[c3[i][0]][c3[i][1]] = c3[i][2];
        else
            continue;
    // print out c3
    cout << "\n(A * B)\'s 3-column array:\n";
    for (int i = 0; i < 20; i++) {
        if (c3[i][0] == 0 && c3[i][1] == 0 && c3[i][2] == 0) break; // if (x, y) == (0, 0) => end
        cout << c3[i][0] << " " << c3[i][1] << " " << c3[i][2] << endl;
    }
    // print out big array
    cout << "\n20*20 array:" << endl;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            cout << muled_sparse[i][j] << "  ";
        }
        cout << endl;
    }
}

/*void add_sparse_kaiyi(int A[20][20], int B[20][20]) {
 cout << "add_sparse:\n";
 int _3colArr[20][3] = {};
 int added_sparse[20][20] = {};
    int count = 0;
    bool checkPoint = 0;

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
}*/

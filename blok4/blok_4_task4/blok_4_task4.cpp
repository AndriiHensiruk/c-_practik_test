// Task5

#include <iostream>
#include <math.h>
#include <conio.h>

using namespace std;

int main()
 {
   // int i, j, k;
    int n, m, q;
    cout << " Введите размерности матриц: \n";
    cout << " n = ";
    cin >> n;
    cout << " m = ";
    cin >> m;
    
    //----------------- создание динамических массивов
    /* выделение динамической памяти под массивы указателей и инициализация массивов указателей */
    int** C = new int* [n];
    for (int i = 0; i < n; i++)
        C[i] = new int[m];
    int** A = new int* [n];
    for (int i = 0; i < n; i++)
        A[i] = new int[m];
   
    //------------------------------ ввод матриц A[n][m] и B[m][q]
    cout << "\n Ввод матрицы A[n][m] \n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            *(A[i] + j)= rand()%100;
    
    //----------------------- вычисление матрицы C[n][q] = A[n][m]*B[m][q]
    for (int i = 0; i < n; i++)  // перебор строк матрицы A[n][m]
    
       {
            
           for (int j = 0; j < m; j++)
                C[i][j] = A[i][j] ; // определение элемента C[i][k]
        }//-------------------- вывод на экран матрицы С[n][q]
    cout << "\n Матрица C[n][q] = A[n][m] * B[m][q] \n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << *(C[i] + j) << " ";
        cout << endl;
    }
    delete[]A;
    delete[]C;   // освобождение памяти
    //getch();
}
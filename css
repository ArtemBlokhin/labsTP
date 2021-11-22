#include <iostream>
using namespace std;
void createMatrix(int** a,int x) 
{
    for (int i = 0; i < x; i++) 
    {
        a[i] = new int[x];          
    };

    cout << "Введите данные матрицы \n" << endl;
    //цикл в которой перебираем строки матрицы
    for (int i = 0; i < x; i++) 
    {
        //цикл в котором перебираем элементы внутри строки
        for (int j = 0; j < x; j++) 
        {
            cin >> a[i][j];
        };
    };
    cout << "Матрица сгенерирована \n";
    for (int i = 0; i < x; i++)
    {
        // в котором перебираем строки матрицы
        for (int j = 0; j < x; j++) 
        {
            cout << a[i][j] << "\t";
        }
        cout << endl;
    };
}
void createA(int** a, int x, int* arr_A, int num_A) {
    cout << "Массив значений A" << endl;
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < x; j++)
            if (a[i][j] != 0) {
                arr_A[num_A] = a[i][j];
                cout << arr_A[num_A] << "\t";
                num_A += 1;
            };
    };

    cout << endl;
}
void createLJ(int** a, int x, int* arr_LJ, int num_LJ) 
{
    cout << "Массив значений LJ" << endl;
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < x; j++)
            if (a[i][j] != 0) {
                arr_LJ[num_LJ] = j + 1;
                cout << arr_LJ[num_LJ] << "\t";
                num_LJ += 1;
            };
    };

    cout << endl;
}
void createLI(int** a,int x,int* arr_LI,int num_LI,int* arr_A,int num_A) {
    int count = 0, count2 = 0;
    cout << "Массив значений LI" << endl;

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < x; j++) {
            if (a[i][j] == 0) {
                count += 1;
                if (count == x) {
                    count = 0;
                    count2 += 1;
                }
            }
            else {
                for (int k = 0; k < num_A - 1; k++) {
                    if (a[i][j] == arr_A[k]) {
                        if (count2 == 0) {
                            arr_LI[num_LI] = k + 1;
                            cout << arr_LI[num_LI] << "\t";
                            num_LI += 1;
                            count = 0;
                        }
                        else {
                            for (int f = 0; f <= count2; f++) {
                                arr_LI[num_LI] = k + 1;
                                cout << arr_LI[num_LI] << "\t";
                                num_LI += 1;
                            }
                            count = 0;
                            count2 = 0;
                            num_LI += 1;
                        };
                    };
                };
                break;
            };
        };
    };
    arr_LI[num_LI] = num_A + 1;
    cout << arr_LI[num_LI] << endl;
    cout << num_LI << endl;
}
void getMatrixWithoutRowAndCol(int** matrix, int size, int row, int col, int** newMatrix) {
    int offsetRow = 0; //Смещение индекса строки в матрице
    int offsetCol = 0; //Смещение индекса столбца в матрице
    for (int i = 0; i < size - 1; i++) {
        //Пропустить row-ую строку
        if (i == row) {
            offsetRow = 1; //Как только встретили строку, которую надо пропустить, делаем смещение для исходной матрицы
        }

        offsetCol = 0; //Обнулить смещение столбца
        for (int j = 0; j < size - 1; j++) {
            //Пропустить col-ый столбец
            if (j == col) {
                offsetCol = 1; //Встретили нужный столбец, проускаем его смещением
            }

            newMatrix[i][j] = matrix[i + offsetRow][j + offsetCol];
        }
    }
}
int matrixDet(int** matrix, int size) {
    int det = 0;
    int degree = 1; // (-1)^(1+j) из формулы определителя

    //Условие выхода из рекурсии
    if (size == 1) {
        return matrix[0][0];
    }
    //Условие выхода из рекурсии
    else if (size == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    else {
        //Матрица без строки и столбца
        int** newMatrix = new int* [size - 1];
        for (int i = 0; i < size - 1; i++) {
            newMatrix[i] = new int[size - 1];
        }

        //Раскладываем по 0-ой строке, цикл бежит по столбцам
        for (int j = 0; j < size; j++) {
            //Удалить из матрицы i-ю строку и j-ый столбец
            //Результат в newMatrix
            getMatrixWithoutRowAndCol(matrix, size, 0, j, newMatrix);

            //Рекурсивный вызов
            //По формуле: сумма по j, (-1)^(1+j) * matrix[0][j] * minor_j (это и есть сумма из формулы)
            //где minor_j - дополнительный минор элемента matrix[0][j]
            // (напомню, что минор это определитель матрицы без 0-ой строки и j-го столбца)
            det = det + (degree * matrix[0][j] * matrixDet(newMatrix, size - 1));
            //"Накручиваем" степень множителя
            degree = -degree;
        }

        //Чистим память на каждом шаге рекурсии(важно!)
        for (int i = 0; i < size - 1; i++) {
            delete[] newMatrix[i];
        }
        delete[] newMatrix;
    }

    return det;
}
int main()
{
    setlocale(LC_ALL, "RUS");
    int num_A = 0, num_LJ = 0, num_LI = 0, N;
    int* arr_A = new int[num_A];
    int* arr_LJ = new int[num_LJ];
    int* arr_LI = new int[num_LI];
    cout << "Введите размерность матрицы:"; //ввод количества строк
    cin >> N;
    int** a = new int* [N];

    createMatrix(a, N);
    createA(a, N, arr_A, num_A);
    createLJ(a, N, arr_LJ, num_LJ);
    createLI(a, N, arr_LI, num_LI, arr_A, num_A);
    cout<< matrixDet(a, N) << endl;
    for (int i = 0; i < N; i++) {
        delete[] a[i];
    }
    delete[] a;
    //delete[] arr_LI;
    //delete[] arr_A;
    //delete[] arr_LJ;   
    system("pause");
    return 0;
};

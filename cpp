#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("input.txt");

struct Matrix
{
   int* A;
   int* LI;
   int* LJ;
   int N, NZ;
};

int input(int a, int b)
{
   while (true)                                      // цикл продолжается до тех пор, пока пользователь не введет корректное значение
   {
      int n;

      if (a == 0)
         cin >> n;
      else
         fin >> n;

      if(b == 0)
      {
         if (n > 0)
            return n;

         cin.clear();                                   // возвращаем cin в обычный режим работы
         cin.ignore(INT_MAX, '\n');      // и удаляем значения предыдущего ввода из входного буфера
         cout << "Вы ввели символ или число <= 0! Повторите ввод: \n";
      }
      else
      {
         if (cin.fail())
         {
            cin.clear();                                   // возвращаем cin в обычный режим работы
            cin.ignore(INT_MAX, '\n');      // и удаляем значения предыдущего ввода из входного буфера
            cout << "Вы ввели символ или число < 0! Повторите ввод: \n";
         }

         return n;
      }
   }
}

int step(int a, int b)     // функция возвредения числа в степень
{
   if (b == 0)
      return 1;

   if (b == 1)
      return a;

   return a * step(a, b - 1);
}

Matrix* compress(int** arr, int N)     // функция упаковки матрицы
{
   Matrix* matrix = new Matrix;
   matrix->N = N;
   matrix->NZ = 0;

   for (int i = 0; i < N; i++)
   {
      for (int j = 0; j < N; j++)
      {
         if (arr[i][j] != 0)
            matrix->NZ++;             // считаем количество ненулевых элементов
      }
   }

   matrix->A = new int[matrix->NZ];
   matrix->LJ = new int[matrix->NZ];
   matrix->LI = new int[matrix->N + 1];

   int t = -1;                        // число-флаг для заполнения LI

   for (int i = 0, m = 0; i < N; i++)
   {
      for (int j = 0; j < N; j++)
      {

         if (arr[i][j] != 0)
         {
            matrix->A[m] = arr[i][j];  // заполняем массив элементов
            matrix->LJ[m] = j + 1;     // заполняем массив номеров столбцов элементов
            m++;
            if (t < i)                 // если меньше чем i, значит были стооки без ненулевых элементов
            {
               int l = i - 1;
               matrix->LI[i] = m;      // записываем значение первого ненулевого элемента в строке
               while (i > 0 && matrix->LI[l] == 0)
               {
                  matrix->LI[l] = matrix->LI[i];  // заполняем предыдущие, если равны 0
                  l--;
               }
               t = i;
            }
         }
      }
      if (t == i - 1)
         matrix->LI[i] = 0;
   }

   matrix->LI[N] = matrix->NZ + 1;                // заполняем последнее значение LI
   for (int i = N - 1; matrix->LI[i] == 0; i--)   // также предыдущие, если были равны 0
      matrix->LI[i] = matrix->NZ + 1;

   //-------------------------
   for (int i = 0; i < N; i++)         // очистка памяти
      delete[] arr[i];
   delete[] arr;
   arr = nullptr;
   //-------------------------
   return matrix;
}

int** decompress(Matrix* matrix)       // функция распаковки матрицы
{
   int N = matrix->N;

   int** arr = new int* [N];           // двумерный массив, в который будет распаковываться матрица
   int* rows = new int[N];             // массив, который содержит количество ненулевых элементов в строке

   for (int i = 0; i < N; i++)
   {
      rows[i] = matrix->LI[i + 1] - matrix->LI[i] - 1;
      arr[i] = new int[N];
   }

   for (int i = 0, k = 0; i < N; i++)
   {
      for (int j = 0, m = 0; j < N; j++)
      {
         if (matrix->LJ[k] == j + 1)                // если номер столбца совпадает с j
         {
            if (rows[i] > -1 && m <= rows[i])       // смотрим сколько элементов в этой строке
            {
               arr[i][j] = matrix->A[k];            // заполняем элементы
               k++;
               m++;
            }
            else
               arr[i][j] = 0;
         }
         else
            arr[i][j] = 0;
      }
   }

   //-------------------------
   delete[] rows;                   // очищаем память
   rows = nullptr;
   //-------------------------

   return arr;
}

Matrix* read(int N, int k)                    // функция чтения/записи матрицы
{
   int** arr = new int* [N];           // массив для чтения матрицы
   for (int i = 0; i < N; i++)
   {
      arr[i] = new int[N];
      for (int j = 0; j < N; j++)
         arr[i][j] = input(k, 1);
   }
   return compress(arr, N);
}

void print(Matrix* matrix)             // функция вывода матрицы
{
   int N = matrix->N;
   int** arr = decompress(matrix);     // массивы для вывода матрицы

   cout << "\nМатрица: \n";

   for (int i = 0; i < N; i++)
   {
      for (int j = 0; j < N; j++)
         cout << arr[i][j] << " ";
      cout << '\n';
   }

   cout << "\nA: ";
   for (int i = 0; i < matrix->NZ; i++)
      cout << matrix->A[i] << " ";

   cout << "\nLJ: ";
   for (int i = 0; i < matrix->NZ; i++)
      cout << matrix->LJ[i] << " ";

   cout << "\nLI: ";
   for (int i = 0; i < N + 1; i++)
      cout << matrix->LI[i] << " ";

   cout << '\n';

   //-------------------------
   for (int i = 0; i < N; i++)         // очистка памяти
      delete[] arr[i];
   delete[] arr;
   arr = nullptr;
   //-------------------------
}

int recursiveSolution(int** arr, int n)           // функция поиска определителя матрицы
{
   if (n < 2)
      return 0;

   if (n == 2)                                    // если матрица размерности 2
      return arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0];

   int d = 0;

   for(int k = 0; k < n; k++)                     // делаем разложение по строке и столбцу
   {
      int** newArr = new int* [n - 1];            // новый массив меньшего размера
      for(int ii = 0, a = 0; ii < n; ii++)
      {
         newArr[ii] = new int[n - 1];
         for(int jj = 0, b = 0; jj < n; jj++)
         {
            if(ii != k && jj != k)                // если наши счетчики не равны значению k
            {
               newArr[a][b] = arr[ii][jj];        // записываем
               b++;
            }
         }

         if(ii != k)
            a++;
      }
      d = d + step(-1, k) * recursiveSolution(newArr, n - 1);  // считаем определитель, как сумму дальнейших вызовов функции
   }

   return d;
}

int solution(Matrix* matrix)       // функция решения задачи
{
   int** arr = decompress(matrix);             // распаковываем матрицу
   int dM = recursiveSolution(arr, matrix->N); // отправляем на рекурсивный поиск определителя
   return dM;
}

int main()
{
   setlocale(LC_ALL, "Rus");

   int k = 0;
   cout << "Как будем осуществлять ввода матрицы?\n 0. Клавиатура.\n 1. Файл.\n";
   cin >> k;

   cout << "\nВведите размер матрицы: ";
   int N = input(k, 0);
   cout << '\n';

   Matrix* matrix = read(N, k);
   print(matrix);

   cout << "\nОпределитель матрицы = " << solution(matrix) << '\n';


   //-------Очистка памяти------
   delete matrix;
   matrix = nullptr;
   //---------------------------

   return 0;
}

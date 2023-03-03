/*!
\file unit_tests.c
\brief Файл с тестами основной функциональости

Данный файл запускает тестирование функций по работе 
с матрицами из файла matrix.h
*/

#include <stdlib.h>
#include <CUnit/Basic.h>
#include"matrix.c"

/*!
\brief Сравнивает две матрицы между собой
\param[in] matrix_1 первая матрица
\param[in] matrix_2 вторая матрица
\param[in] size_x размер матрици по горизонтали
\param[in] size_y размер матрици по вертикали
\return являются ли элементы матриц идентичными
*/
int CompareMatrix(int** matrix_1, int** matrix_2, int size_x, int size_y)
{
    for(int i = 0; i < size_x; i++)
    {
        for(int j = 0; j < size_y; j++)
        {
            if (matrix_1[i][j] != matrix_2[i][j])
            {
                return 0;
            }
        }
    }
    return 1;
}

/*!
\brief Освобождает выделенную под матрицы память
\param[in] matrix освобождаемая матрица
\param[in] size рпазмер матрицы
*/
void FreeMatrix(int** matrix, int* size)
{
    for(int i = 0; i < size[0]; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

/*!
\brief Тестирует функцию на матрице из одного элемента
*/
void Test1(){
    int size[] = {1, 1};
    int** new_matrix = (int**) malloc(size[0] * sizeof(int*));
    int** matrix = (int**) malloc(size[0] * sizeof(int*));
    matrix[0] = (int*)malloc(size[1] * sizeof(int));
    new_matrix[0] = (int*)malloc(size[1] * sizeof(int));
    matrix[0][0] = 2;
    CreateNewMatrix(matrix, new_matrix, size[0], size[1]);
    CU_ASSERT_EQUAL(CompareMatrix(matrix, new_matrix, size[0], size[1]), 1);
    FreeMatrix(matrix, size);
}

/*!
\brief Тестирует функцию на матрице 2:2
*/
void Test2(){
    int size[] = {2, 2};
    int** new_matrix = (int**) malloc(size[0] * sizeof(int*));
    int** matrix = (int**) malloc(size[0] * sizeof(int*));
    int** correct = (int**) malloc(size[0] * sizeof(int*));
    for(int i = 0; i < size[0]; i++)
    {
        matrix[i] = (int*)malloc(size[1] * sizeof(int));
        new_matrix[i] = (int*)malloc(size[1] * sizeof(int));
        correct[i] = (int*)malloc(size[1] * sizeof(int));
    }
    matrix[0][0] = 2;
    matrix[0][1] = 3;
    matrix[1][0] = 4;
    matrix[1][1] = 5;
    correct[0][0] = 4;
    correct[0][1] = 5;
    correct[1][0] = 2;
    correct[1][1] = 3;
    CreateNewMatrix(matrix, new_matrix, size[0], size[1]);
    CU_ASSERT_EQUAL(CompareMatrix(correct, new_matrix, size[0], size[1]), 1);
    FreeMatrix(matrix, size);
}


/*!
\brief Тестирует функцию на матрице из отрицательных сначений
*/
void Test3(){
    int size[] = {2, 2};
    int** new_matrix = (int**) malloc(size[0] * sizeof(int*));
    int** matrix = (int**) malloc(size[0] * sizeof(int*));
    int** correct = (int**) malloc(size[0] * sizeof(int*));
    for(int i = 0; i < size[0]; i++)
    {
        matrix[i] = (int*)malloc(size[1] * sizeof(int));
        new_matrix[i] = (int*)malloc(size[1] * sizeof(int));
        correct[i] = (int*)malloc(size[1] * sizeof(int));
    }
    matrix[0][0] = -2;
    matrix[0][1] = -3;
    matrix[1][0] = 4;
    matrix[1][1] = -5;
    correct[0][0] = 4;
    correct[0][1] = -5;
    correct[1][0] = -2;
    correct[1][1] = -3;
    CreateNewMatrix(matrix, new_matrix, size[0], size[1]);
    CU_ASSERT_EQUAL(CompareMatrix(correct, new_matrix, size[0], size[1]), 1);
    FreeMatrix(matrix, size);
}

/*!
\brief Тестирует функцию на прямоугольной матрице
*/
void Test4(){
    int size[] = {2, 3};
    int** new_matrix = (int**) malloc(size[0] * sizeof(int*));
    int** matrix = (int**) malloc(size[0] * sizeof(int*));
    int** correct = (int**) malloc(size[0] * sizeof(int*));
    for(int i = 0; i < size[0]; i++)
    {
        matrix[i] = (int*)malloc(size[1] * sizeof(int));
        new_matrix[i] = (int*)malloc(size[1] * sizeof(int));
        correct[i] = (int*)malloc(size[1] * sizeof(int));
    }
    matrix[0][0] = 2;
    matrix[0][1] = 3;
    matrix[0][2] = 0;
    matrix[1][0] = 4;
    matrix[1][1] = 5;
    matrix[1][2] = -9;

    correct[0][0] = 4;
    correct[0][1] = 5;
    correct[0][2] = -9;
    correct[1][0] = 2;
    correct[1][1] = 3;
    correct[1][2] = 0;
    CreateNewMatrix(matrix, new_matrix, size[0], size[1]);
    CU_ASSERT_EQUAL(CompareMatrix(correct, new_matrix, size[0], size[1]), 1);
    FreeMatrix(matrix, size);
}

/*!
\brief Запускает все модульные тесты
\return код завершения программы
*/
int main(){
    CU_pSuite suite;
    CU_initialize_registry();
    suite = CU_add_suite("main_suite", NULL, NULL);
    CU_ADD_TEST(suite, Test1);
    CU_ADD_TEST(suite, Test2);
    CU_ADD_TEST(suite, Test3);
    CU_ADD_TEST(suite, Test4);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
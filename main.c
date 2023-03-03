/*!
\file main.c
\brief Основной файл программы

Данный файл параллельно запускает родительский и дочерний поток
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char* GetString(int *len)
{
    *len = 0; // изначально строка пуста
    int capacity = 1; // ёмкость контейнера динамической строки (1, так как точно будет '\0')
    char *s = (char*) malloc(sizeof(char)); // динамическая пустая строка
    char c = getchar(); // символ для чтения данных
    while (c != '\n') 
    {
        s[(*len)++] = c; // заносим в строку новый символ
        // если реальный размер больше размера контейнера, то увеличим его размер
        if (*len >= capacity) 
        {
            capacity *= 2; // увеличиваем ёмкость строки в два раза
            s = (char*) realloc(s, capacity * sizeof(char)); // создаём новую строку с увеличенной ёмкостью
        }
        c = getchar(); // считываем следующий символ
    }
    s[*len] = '\0'; // завершаем строку символом конца строки
    return s;
}

int InputNumber(int* val)
{
    int len;
    char* str = GetString(&len);
    for(int i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]) && !(i == 0 && str[0] == '-')) return 0;
    }
    *val = atoi(str);
    return 1;
}

/*!
Запускает основной процесс программы
\return код завершения программы
*/
int main()
{
  int islandArea;
  int pirotsQuantity;
  int partsNumber;
  int res = 0;
  while(res == 0){
    printf("Please, enter an island area: ");
    int res = InputNumber(&islandArea);
    printf("%d\n", islandArea);
  }
  res = 0;
  while(res == 0){
    printf("Please, enter a quantity of pirots: ");
    int res = InputNumber(&pirotsQuantity);
  }
  printf("%d\n", pirotsQuantity);
  printf("%d\n", islandArea);
  partsNumber = islandArea / pirotsQuantity;
  printf("%d\n", partsNumber);
  return 0;
}

/*!
\file main.c
\brief Основной файл программы

Данный файл параллельно запускает родительский и дочерний поток
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<semaphore.h>
#include<pthread.h>
#include "part_of_the_island.h"

sem_t island;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct part_of_the_island * Parts ;

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

void* group(void* group_number)
{
  int numb = *((int *)group_number);
  printf("The group number %d of %d pirots is ready\n", numb + 1, 1);
  int pirotsWaiting = 0;
  int pirotsSeaking = 0;
  pthread_mutex_lock(&mutex);
  pirotsWaiting++;
  pthread_mutex_unlock(&mutex);
  return NULL;
}

int getTreasureNumber(int partsNumber)
{
  int treasureNumber = 0;
  int res = 0;
  while(res == 0){
    printf("Please, enter the number of the part where the treasure will be hidden: ");
    res = InputNumber(&treasureNumber);
    if(treasureNumber > partsNumber || treasureNumber < 1){
      printf("This number is incorrect. Please, try again\n");
      res = 0;
    }
  }
  return treasureNumber;
}

int main()
{ 
  int islandArea;
  int pirotsQuantity;
  int partsNumber;
  int res = 0;
  while(res == 0){
    printf("Please, enter an island area: ");
    res = InputNumber(&islandArea);
  }
  res = 0;
  while(res == 0){
    printf("Please, enter a quantity of pirots: ");
    res = InputNumber(&pirotsQuantity);
  }
  
  int minPartArea = 1;
  if(islandArea > pirotsQuantity) {
    minPartArea = islandArea / pirotsQuantity;
  }
  partsNumber = islandArea / minPartArea;
  printf("The island will be divided for %d parts\n", partsNumber);

  sem_init(&island, 0, partsNumber);
  pthread_t groups[partsNumber];
  int groupIds[partsNumber]; ///

  res = 0;
  int treasureNumber = getTreasureNumber(partsNumber);
  Parts = (part_of_the_island *) malloc(sizeof(part_of_the_island) * partsNumber);
  for(int i = 0; i < partsNumber; i++)
  {
    Parts[i].common_area = minPartArea;
    Parts[i].explored_area = 0;
    if(treasureNumber == i + 1)
    {
      Parts[i].has_treasure = 1;
    }
    else
    {
      Parts[i].has_treasure = 0;
    }
    printf("%d\n", i);
    groupIds[i] = i;
    pthread_create(&groups[i], NULL, group, &groupIds[i]);
  }
  for (int i = 0; i < partsNumber; i++) {
    pthread_join(groups[i], NULL);
  }
  sem_destroy(&island);
  free(Parts);
  return 0;
}

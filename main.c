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
struct partOfTheIsland * Parts;
struct timespec ts;

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
  int pirots = Parts[numb].pirotsQuantity;
  printf("The group number %d of %d pirots is ready\n", numb + 1, pirots);
  int pirotsWaiting = 0;
  int pirotsSeaking = 0;
  pthread_mutex_lock(&mutex);
  pirotsWaiting++;
  pthread_mutex_unlock(&mutex);
  sem_wait(&island);
  pthread_mutex_lock(&mutex);
  pirotsWaiting--;
  printf("The group number %d have started seaking\n", numb);
  pthread_mutex_unlock(&mutex);
  ts.tv_sec = rand() % Parts[numb].pirotsQuantity + 3;
  ts.tv_nsec = 0;
  nanosleep(&ts, NULL);
  if(Parts[numb].hasTreasure == 1)
  {
    printf("The group number %d have found a treasure!\n", numb);
  }
  else
  {
    printf("The group number %d have found nothing\n", numb);
  }
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

void hideTreasure(int partsNumber, int minPartArea, int treasureNumber, int groupIds[], int minGroup)
{
  for(int i = 0; i < partsNumber; i++)
  {
    Parts[i].commonArea = minPartArea;
    Parts[i].exploredArea = 0;
    Parts[i].pirotsQuantity = minGroup;
    if(treasureNumber == i + 1)
    {
      Parts[i].hasTreasure = 1;
    }
    else
    {
      Parts[i].hasTreasure = 0;
    }
    printf("%d\n", i);
    groupIds[i] = i;
  }
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
  int minGroup = pirotsQuantity / partsNumber;
  printf("%d\n", minGroup);
  printf("The island will be divided for %d parts\n", partsNumber);

  sem_init(&island, 0, partsNumber);
  pthread_t groups[partsNumber];
  int groupIds[partsNumber]; ///

  res = 0;
  int treasureNumber = getTreasureNumber(partsNumber);
  Parts = (partOfTheIsland *) malloc(sizeof(partOfTheIsland) * partsNumber);
  hideTreasure(partsNumber, minPartArea, treasureNumber, groupIds, minGroup);
  for(int i = 0; i < partsNumber; i++)
  {
    pthread_create(&groups[i], NULL, group, &groupIds[i]);
    ts.tv_sec = rand() % 3;
    ts.tv_nsec = 0;
    nanosleep(&ts, NULL);
  }
  for (int i = 0; i < partsNumber; i++) {
    pthread_join(groups[i], NULL);
  }
  sem_destroy(&island);
  free(Parts);
  return 0;
}

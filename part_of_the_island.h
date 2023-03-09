/*!
 * \file partsOfTheIsland.h
 * \brief Заголовочный файл с описанием стру
 *
 * Данный файл содержит в себе определения основных
 * функций, используемых в программе.
*/

#ifndef PARTS_STRUCTURE
#define PARTS_STRUCTURE

typedef struct partOfTheIsland partOfTheIsland;

/*!
* \brief Структура части острова
*/
struct partOfTheIsland
{
    int commonArea;
    int exploredArea;
    int hasTreasure;
    int pirotsQuantity;
};

#endif
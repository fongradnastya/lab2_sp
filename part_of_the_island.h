/*!
 * \file partsOfTheIsland.h
 * \brief Заголовочный файл с описанием функций
 *
 * Данный файл содержит в себе определения основных
 * функций, используемых в программе.
*/

#ifndef PARTS_STRUCTURE
#define PARTS_STRUCTURE

typedef struct part_of_the_island part_of_the_island;

struct part_of_the_island
{
    int common_area;
    int explored_area;
    int has_treasure;
    int pirotsQuantity;
};

#endif
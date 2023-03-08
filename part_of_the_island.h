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
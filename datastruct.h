#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include "defines.h"

class dataStruct
{
public:
    dataStruct();
    int data[ARRAYH][ARRAYW] = {0};
    void takeData(int tab[ARRAYH][ARRAYW]);

};

#endif // DATASTRUCT_H

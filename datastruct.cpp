#include "datastruct.h"
#include "defines.h"
dataStruct::dataStruct()
{

}
void dataStruct::takeData(int tab[ARRAYH][ARRAYW]){
    for(int i = 0; i < ARRAYH; i++){
        for(int j = 0; j < ARRAYW; j++){
            data[i][j] = tab [i][j];
        }
    }
}


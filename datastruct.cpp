#include "datastruct.h"

dataStruct::dataStruct()
{

}
void dataStruct::takeData(int tab[250][250]){
    for(int i = 0; i < 250; i++){
        for(int j = 0; j < 250; j++){
            data[i][j] = tab [i][j];
        }
    }
}

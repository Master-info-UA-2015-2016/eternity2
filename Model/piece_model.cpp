#include "piece_model.h"

piece_model::piece_model(int _id, int tab[])
{
    id = _id;
    for(int i=0; i<MAX_CARD; ++i){
        color[i] = tab[i];
    }
    return 0;
}

void piece_model::rotate(){
    int tmp[MAX_CARD];

    tmp[0] = color[MAX_CARD-1];

    for(int i=1; i<MAX_CARD;++i){
        tmp[i] = color[i-1];
    }

    for(int j= 0; j < MAX_CARD; ++j){
        color[j] = tmp[j];
    }
}

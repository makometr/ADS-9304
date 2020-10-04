#include "recSearch.h"

bool recSearch(unsigned int from, unsigned int to,unsigned int n,int** arr,bool* watched){
    unsigned int now=from;
    for (int next = 0; next < n; ++next) {
        if((arr[now][next]==1) && next==to){
            return true;
        }
        if((arr[now][next]==1) && !watched[next]){
            watched[now]=true;

            if(recSearch(next, to, n, arr, watched))
                return true;
        }
    }
    return false;
}

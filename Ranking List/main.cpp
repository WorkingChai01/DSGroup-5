#include <iostream>
#include "SequentialList.h"
#include "updateRank.h"
#include "purge_Sq.h"
using namespace std;

int main(){
    LeaderBoard LB;
    InitBoard(&LB, 10);
    Player Alice("Alice", 90, 2);
    Insert(&LB, 0, Alice);
    Player Bob("Bob", 90, 1);
    Insert(&LB, 0, Bob);
    return 0;
}
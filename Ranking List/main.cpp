#include <iostream>
#include <windows.h>
#include "SequentialList.h"
#include "updateRank.h"
#include "purge_Sq.h"
using namespace std;

int main(){
    LeaderBoard LB;
    InitBoard(&LB, 10);
    updateRank(&LB, "Alice", 90, 2);
    updateRank(&LB, "Bob", 90, 1);
    purge_Sq(&LB);
    PrintBoard(&LB);
    system("pause");
    return 0;
}
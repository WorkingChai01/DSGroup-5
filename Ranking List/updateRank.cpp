#include "updateRank.h"
#include <algorithm>  

// 1. 查找(Search)：遍历数组检查玩家是否存在
int Search(LeaderBoard *LB, const string& playerName){
    for(int i = 0; i < LB->size; i++){
        if(LB->elements[i].name == playerName){
            return i;
        }
    }
    return -1;
}

// 2. 更新(Update)：若存在且分数更高，则原地覆盖
void Update(LeaderBoard *LB, int index, int newScore, int newSubs){
    if(index >= 0 && index < LB->size){
        if(newScore > LB->elements[index].score){
            LB->elements[index].score = newScore;
            LB->elements[index].subs = newSubs;
        }
    }
}

// 3. 维护(Maintain)：采用插入排序思想，通过swap确保有序
void Maintain(LeaderBoard *LB, int index){
    // 向前冒泡到正确位置（保持分数降序）
    for(int i = index; i > 0; i--){
        if(LB->elements[i].score > LB->elements[i-1].score){
            std::swap(LB->elements[i], LB->elements[i-1]);
        } else {
            break;
        }
    }
}

// 核心算法：查找-更新-维护
void updateRank(LeaderBoard *LB, const string& playerName, int newScore, int newSubs){
    // 1. 查找(Search)
    int playerIndex = Search(LB, playerName);
    
    if(playerIndex != -1){
        // 玩家存在
        // 2. 更新(Update)
        Update(LB, playerIndex, newScore, newSubs);
        
        // 3. 维护(Maintain)
        Maintain(LB, playerIndex);
    } 
    else {
        // 玩家不存在，插入新玩家
        Player newPlayer(playerName, newScore, newSubs);
        
        // 找到插入位置（保持有序）
        int insertPos = 0;
        while(insertPos < LB->size && LB->elements[insertPos].score > newScore){
            insertPos++;
        }
        
        // 调用已有的Insert函数插入新玩家
        Insert(LB, insertPos, newPlayer);
    }
}

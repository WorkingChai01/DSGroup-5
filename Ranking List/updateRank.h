#ifndef UPDATERANK_H
#define UPDATERANK_H

#include "SequentialList.h"
#include <string>
using namespace std;

// 1. 查找(Search)：遍历数组检查玩家是否存在
int Search(LeaderBoard *LB, const string& playerName);

// 2. 更新(Update)：若存在且分数更高，则原地覆盖
void Update(LeaderBoard *LB, int index, int newScore, int newSubs);

// 3. 维护(Maintain)：采用插入排序思想，通过swap确保有序
void Maintain(LeaderBoard *LB, int index);

// 核心算法：调用三个步骤
void updateRank(LeaderBoard *LB, const string& playerName, int newScore, int newSubs);

#endif

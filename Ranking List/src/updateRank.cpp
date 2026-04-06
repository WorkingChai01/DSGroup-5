#include "updateRank.h"
#include <algorithm>
#include <ctime>

// 查找：遍历数组检查玩家是否存在
int Search(LeaderBoard* LB, const string& playerName) {
    for (int i = 0; i < LB->size; i++) {
        if (LB->elements[i].name == playerName) {
            return i;
        }
    }
    return -1;
}

// 更新：若存在且分数更高，则原地覆盖
void Update(LeaderBoard* LB, int index, int newScore, int newSubs) {
    if (index >= 0 && index < LB->size) {
        if (newScore > LB->elements[index].score) {
            LB->elements[index].score = newScore;
            LB->elements[index].subs = newSubs;
            LB->elements[index].timestamp = time(nullptr);
        }
    }
}

// 维护：采用插入排序思想，通过swap确保有序
void Maintain(LeaderBoard* LB, int index) {
    for (int i = index; i > 0; i--) {
        bool needSwap = false;

        if (LB->elements[i].score > LB->elements[i - 1].score) {
            needSwap = true;
        }
        else if (LB->elements[i].score == LB->elements[i - 1].score) {
            if (LB->elements[i].subs < LB->elements[i - 1].subs) {
                needSwap = true;
            }
            else if (LB->elements[i].subs == LB->elements[i - 1].subs) {
                if (LB->elements[i].timestamp < LB->elements[i - 1].timestamp) {
                    needSwap = true;
                }
            }
        }

        if (needSwap) {
            std::swap(LB->elements[i], LB->elements[i - 1]);
        }
        else {
            break;
        }
    }
}

// 核心算法：查找-更新-维护
void updateRank(LeaderBoard* LB, const string& playerName, int newScore, int newSubs) {
    int playerIndex = Search(LB, playerName);

    if (playerIndex != -1) {
        // 玩家存在且新分数更高
        if (newScore > LB->elements[playerIndex].score) {
            Update(LB, playerIndex, newScore, newSubs);
            Maintain(LB, playerIndex);
        }
    }
    else {
        // 玩家不存在，插入新玩家
        Player newPlayer;
        newPlayer.name = playerName;
        newPlayer.score = newScore;
        newPlayer.subs = newSubs;
        newPlayer.timestamp = time(nullptr);

        // 找到插入位置（保持有序）
        int insertPos = 0;
        while (insertPos < LB->size) {
            if (newScore > LB->elements[insertPos].score) {
                break;  // 新分数更高，插在这里
            }
            else if (newScore < LB->elements[insertPos].score) {
                insertPos++;  // 新分数更低，继续往后
            }
            else {  // 分数相同
                if (newSubs < LB->elements[insertPos].subs) {
                    break;  // 提交数更少，插在这里
                }
                else if (newSubs > LB->elements[insertPos].subs) {
                    insertPos++;  // 提交数更多，继续往后
                }
                else {  // 提交数相同
                    if (newPlayer.timestamp < LB->elements[insertPos].timestamp) {
                        break;  // 时间戳更早，插在这里
                    }
                    else {
                        insertPos++;  // 时间戳更晚，继续往后
                    }
                }
            }
        }

        // 插入新玩家
        Insert(LB, insertPos, newPlayer);
    }
}

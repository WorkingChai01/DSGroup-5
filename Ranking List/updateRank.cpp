#include "updateRank.h"
#include <algorithm>
#include <iostream>
using namespace std;

int Search(LeaderBoard *LB, const string& playerName) {
    for (int i = 0; i < LB->size; i++) {
        if (LB->elements[i].name == playerName) {
            return i;
        }
    }
    return -1;
}

bool Compare(Player a, Player b) {
    if (a.score != b.score) return a.score > b.score;
    if (a.subs != b.subs) return a.subs < b.subs;
    return a.timestamp < b.timestamp;
}

void Update(LeaderBoard *LB, int index, int newScore, int newSubs) {
    static int timeCounter = 0;
    if (index >= 0 && index < LB->size) {
        if (newScore > LB->elements[index].score) {
            LB->elements[index].score = newScore;
            LB->elements[index].subs = newSubs;
            LB->elements[index].timestamp = ++timeCounter;
        } else if (newScore == LB->elements[index].score && newSubs < LB->elements[index].subs) {
            LB->elements[index].subs = newSubs;
            LB->elements[index].timestamp = ++timeCounter;
        }
    }
}

void Maintain(LeaderBoard *LB, int index) {
    for (int i = index; i > 0; i--) {
        if (Compare(LB->elements[i], LB->elements[i - 1])) {
            swap(LB->elements[i], LB->elements[i - 1]);
        } else {
            break;
        }
    }
}

void Insert(LeaderBoard *LB, int pos, const Player& newPlayer) {
    if (LB->size >= 100) {
        cout << "排行榜已满！" << endl;
        return;
    }
    for (int i = LB->size; i > pos; i--) {
        LB->elements[i] = LB->elements[i - 1];
    }
    LB->elements[pos] = newPlayer;
    LB->size++;
}

void updateRank(LeaderBoard *LB, const string& playerName, int newScore, int newSubs) {
    static int timeCounter = 0;
    int playerIndex = Search(LB, playerName);
    if (playerIndex != -1) {
        Update(LB, playerIndex, newScore, newSubs);
        Maintain(LB, playerIndex);
    } else {
        timeCounter++;
        Player newPlayer(playerName, newScore, newSubs, timeCounter);
        int insertPos = 0;
        while (insertPos < LB->size && Compare(LB->elements[insertPos], newPlayer)) {
            insertPos++;
        }
        Insert(LB, insertPos, newPlayer);
    }
}


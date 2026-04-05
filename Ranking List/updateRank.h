#ifndef UPDATERANK_H
#define UPDATERANK_H

#include <string>
using namespace std;

struct Player {
    string name;
    int score;
    int subs;
    int timestamp;
    
    Player() : name(""), score(0), subs(0), timestamp(0) {}
    Player(const string& n, int s, int sub, int t = 0) : name(n), score(s), subs(sub), timestamp(t) {}
};

struct LeaderBoard {
    Player elements[100];
    int size;
    
    LeaderBoard() : size(0) {}
};

int Search(LeaderBoard *LB, const string& playerName);
void Update(LeaderBoard *LB, int index, int newScore, int newSubs);
bool Compare(Player a, Player b);
void Maintain(LeaderBoard *LB, int index);
void Insert(LeaderBoard *LB, int pos, const Player& newPlayer);
void updateRank(LeaderBoard *LB, const string& playerName, int newScore, int newSubs);

#endif

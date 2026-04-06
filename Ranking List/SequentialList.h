#ifndef SEQUENTIALLIST_H
#define SEQUENTIALLIST_H

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Player{
    string name;
    int score, subs;
    Player(string ID = "No data", int sc = 0, int su = 0) : name(ID), score(sc), subs(su) {}
};

struct LeaderBoard{
    Player *elements;
    int size;
    int capacity;
};

void InitBoard(LeaderBoard *LB, int capacity);
void Destroy(LeaderBoard *LB);
//查询大小
int Size(LeaderBoard *LB);
//判断是否为空顺序表
bool IsEmpty(LeaderBoard *LB);
//插入
void Insert(LeaderBoard *LB, int index, Player element);
//输出
void PrintBoard(const LeaderBoard* LB);
#endif
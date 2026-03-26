#ifndef SEQUENTIALLIST_H
#define SEQUENTIALLIST_H

#include <iostream>
#include <string>
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

#endif
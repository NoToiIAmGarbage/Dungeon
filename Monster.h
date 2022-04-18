#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <random>
#include <chrono>
#include <windows.h>
#include <conio.h>
#include <thread>
#include "Player.h"

using namespace std;

class Player;

class Monster {
private:
    vector<pair<int, int> > shots;
    int hp, lvl, curTrack, hit, offenseEnd, defenseEnd, mxHp;
    int hitCnt;
public:
    Monster();
    Monster(int);

    void showMonsterStatus();

    // combat system
    bool combat(Player&);

    // defense phase
    void defensePhase(int, Player&);

    // offense phase
    void offensePhase(Player&);

    // shot dtop
    void shotDrop();

    // hit counter
    void counter();

    void listenForInput();

    void timer();
};


#endif // ENEMY_H_INCLUDED

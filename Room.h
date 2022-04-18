#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <cassert>
#include "Player.h"
#include "Monster.h"

#define sizeX 11
#define sizeY 25
#define roomSize 11

using namespace std;

class Player;
class Monster;

class Room
{
private:
    char facingTable[4] = {'A', 'V', '<', '>'};
    int X, Y;
public:
    virtual void enterRoom(Player&, char(*)[sizeY + 2], int(*obj)[sizeY + 2]) = 0;
    void initializeMap(Player&, char(*)[sizeY + 2], int(*obj)[sizeY + 2]);
    virtual string getRoomType() = 0;
};

class npcRoom : public Room {
public:
    void enterRoom(Player&, char(*)[sizeY + 2], int(*obj)[sizeY + 2]);
    string getRoomType();
};

class monsterRoom : public Room {
private:
    vector<pair<pair<int, int>, Monster>> monster;
public:
    void enterRoom(Player&, char(*)[sizeY + 2], int(*obj)[sizeY + 2]);
    string getRoomType();

    void addMonster(int, int);
};

class chestRoom : public Room {
public:
    void enterRoom(Player&, char(*)[sizeY + 2], int(*obj)[sizeY + 2]);
    string getRoomType();
};

class smithRoom : public Room {
public:
    void enterRoom(Player&, char(*)[sizeY + 2], int(*obj)[sizeY + 2]);
    string getRoomType();
};

class exitRoom : public Room {
public:
    void enterRoom(Player&, char(*)[sizeY + 2], int(*obj)[sizeY + 2]);
    string getRoomType();
};

class startRoom : public Room {
public:
    void enterRoom(Player&, char(*)[sizeY + 2], int(*obj)[sizeY + 2]);
    string getRoomType();
};

#endif // ROOM_H_INCLUDED

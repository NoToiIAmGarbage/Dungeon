#ifndef DUNGEON_H_INCLUDED
#define DUNGEON_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include "Player.h"
#include "Monster.h"
#include "NPC.h"
#include "Room.h"

#define sizeX 11
#define sizeY 25

using namespace std;

class Dungeon {
private:
    int direx[4] = {-1, 1, 0, 0};
    int direy[4] = {0, 0, -1, 1};
    char facingTable[4] = {'A', 'V', '<', '>'};
    int roomX = 100, roomY = 100;
    char curMap[sizeX + 2][sizeY + 2];
    int obj[sizeX + 2][sizeY + 2];
    Player player;
    Room *gm[105][105];
    pair<int, int> gameMap[105][105]; // {roomtype, position in perspective vector}
    vector <smithRoom*> smithRoomVec;
    vector <npcRoom*> npcRoomVec;
    vector <monsterRoom*> monsterRoomVec;
    vector <chestRoom*> chestRoomVec;

public:

    // show the whole room when changing room
    void showRoomChange();

    // show status
    void showStatus();

    // show status pad
    void showStatusPad();

    // show inventory
    void showInventory();

    // show the player position change
    void showPlayerChange(int, int, int, int);

    Dungeon();
    /* Create a new player, and give him/her basic status */
    void createPlayer();

    /* Create a map, which include several different rooms */
    void createMap();


    // check if coordinate valid
    bool checkCoordValid(int, int);

    // handle input action
    void handleMovement(int);

    /* Deal with all game initial setting       */
    /* Including create player, create map etc  */
    void startGame();

    /* Deal with the whole game process */
    void runDungeon();

};


#endif // DUNGEON_H_INCLUDED

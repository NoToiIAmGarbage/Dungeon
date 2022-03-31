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

using namespace std;

class Dungeon{
private:
    int direx[4] = {-1, 1, 0, 0};
    int direy[4] = {0, 0, -1, 1};
    char facingTable[4] = {'A', 'V', '<', '>'};
    int sizeX = 10, sizeY = 25;
    int roomX = 100, roomY = 100;
    Player player;
    vector<Room*> rooms;
    Room gameMap[105][105];
public:
    // show the whole room when changing room
    void showRoomChange();

    // show the player position change
    void showPlayerChange(int, int, int, int);

    Dungeon();
    /* Create a new player, and give him/her basic status */
    void createPlayer();

    /* Create a map, which include several different rooms */
    void createMap();

    /* Deal with player's iteraction with objects in that room */
    void handleEvent(Object*);


    // handle input action
    void handleAction(int);

    /* Deal with all game initial setting       */
    /* Including create player, create map etc  */
    void startGame();

    /* Deal with the player's action     */
    /* including showing the action list */
    /* that player can do at that room   */
    /* and dealing with player's input   */
    void chooseAction(vector<Object*>);

    /* Check whether the game should end or not */
    /* Including player victory, or he/she dead */
    bool checkGameLogic();

    /* Deal with the whole game process */
    void runDungeon();

};


#endif // DUNGEON_H_INCLUDED

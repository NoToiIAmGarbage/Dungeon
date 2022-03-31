#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"

using namespace std;

class Item;

class Player: public GameCharacter
{
private:
    int mapX, mapY, curX, curY, facing;
    // map stands for current room
    // cur stands for position in current room
    // facing ranges in {0, 1, 2, 3} which is {up, down, left, right}
    vector<Item> inventory;
public:
    Player();
    Player(string, int, int);
    void addItem(Item);
    void increaseStates(int,int,int);

    /* Virtual function that you need to complete   */
    /* In Player, this function should show the     */
    /* status of player.                            */
    void triggerEvent(Object*);

    /* Set & Get function*/
    void setCoord(int, int);
    int getCurX();
    int getCurY();
    int getFacing();
    void setFacing(int);
    void setInventory(vector<Item>);
    vector<Item> getInventory();
};

#endif // PLAYER_H_INCLUDED

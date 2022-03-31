#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"

using namespace std;

class Room
{
private:
    vector<Object*> objects; /*contain 1 or multiple objects, including monster, npc, etc*/
public:

    Room();

    /* Set & Get function*/
    void setUpRoom(int);
    void setDownRoom(int);
    void setLeftRoom(int);
    void setRightRoom(int);
    void setObjects(vector<Object*>);
    bool getIsExit();
    int getIndex();
    vector<Object*> getObjects();
    Room* getUpRoom();
    Room* getDownRoom();
    Room* getLeftRoom();
    Room* getRightRoom();
};

#endif // ROOM_H_INCLUDED

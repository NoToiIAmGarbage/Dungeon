#ifndef GAMECHARACTER_H_INCLUDED
#define GAMECHARACTER_H_INCLUDED

#include <iostream>
#include <string>
#include "Object.h"
using namespace std;

class GameCharacter: public Object
{
private:
    string name;
    int maxHealth;
    int currentHealth;
    int attack;
    int defense;
    int exp;
    int lvl;
    int lvlUp;
public:
    GameCharacter();
    GameCharacter(string);
    bool checkIsDead();
    void takeDamage(int);

    /* Set & Get function*/
    void setMaxHealth(int);
    void setCurrentHealth(int);
    void setAttack(int);
    void setDefense(int);
    void setExp(int);
    int getMaxHealth();
    int getCurrentHealth();
    int getAttack();
    int getDefense();
    int getExp();
};
#endif // GAMECHARACTER_H_INCLUDED

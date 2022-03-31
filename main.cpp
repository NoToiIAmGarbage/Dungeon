#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include "Dungeon.h"
#include "Item.h"
#include "Monster.h"
#include "NPC.h"
#include "Player.h"


using namespace std;

int main(){
    system("cls");
    cout << "1. New Game\n";
    cout << "2. Load Game\n";
    char c;
    while(c = getch()) {
        if(c == '1' || c == '2') {
            break;
        }
        else {
            return 0;
        }
    }
    if(c == '1') {
        Dungeon dungeon = Dungeon();
        dungeon.runDungeon();
    }
    else {

    }
    return 0;
}

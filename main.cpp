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

int main() {
    char c;
    bool yes = true;
    while(yes) {
        system("cls");
        cout << "====================================\n";
        cout << "|Press [spacebar] to start the game|\n";
        cout << "====================================\n";
        while(c = getch()) {
            if(c == ' ') {
                break;
            }
        }
        Dungeon dungeon = Dungeon();
        dungeon.runDungeon();
        char c;
        cout << "Press [R] to restart or [Q] to quit\n";
        while(c = getch()) {
            if(c == 'r' || c == 'R') {
                break;
            }
            else if(c == 'q' || c == 'Q') {
                yes = false;
                break;
            }
        }
    }
    return 0;
}

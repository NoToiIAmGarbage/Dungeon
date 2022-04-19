#include "Monster.h"

static int randGen(int left, int right) {

	using clk = chrono::high_resolution_clock;
	using rand_int = uniform_int_distribution<int>;
	using rand_double = uniform_real_distribution<double>;

	mt19937 rng(clk::now().time_since_epoch().count());
    return rand_int(left, right)(rng);
}

Monster::Monster() {};

Monster::Monster(int playerLvl) {
	lvl = randGen(playerLvl - 5, playerLvl + 5);
	lvl = max(1, lvl);
	hp = mxHp = 1000 * lvl;
}

const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

// set output red
static void setOutputRed() {
	SetConsoleTextAttribute(hOut, BACKGROUND_RED);
}

// set output white
static void setOutputWhite() {
	SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);
}

// set output green
static void setOutputGreen() {
	SetConsoleTextAttribute(hOut, BACKGROUND_GREEN);
}

// set output original
static void setOutputOriginal() {
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

// Function supporting printing Room
static void setCursorPosition(int y, int x) {
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void updateShot(int x, int y) {
	setCursorPosition(x - 1, y);
	cout << ' ';
	if(x <= 9) {
		setCursorPosition(x, y);
		cout << '*';
	}
	return;
}

void Monster::shotDrop() {
	vector< pair<int, int> > tmp;
	tmp.clear();
	for(pair<int, int> x : shots) {
		x.first ++;
		if(x.first <= 9) {
			tmp.push_back(x);
		}
		if(x.first == 9 && curTrack == x.second) {
			hit = defenseEnd = true;
			return;
		}
		thread {updateShot, x.first, x.second}.join();
	}
	shots = tmp;
}

void changeTrack(int curTrack) {
	setCursorPosition(9, 12);
	if(curTrack == 12) {
		cout << 'A';
	}
	else {
		cout << ' ';
	}
	setCursorPosition(9, 14);
	if(curTrack == 14) {
		cout << 'A';
	}
	else {
		cout << ' ';
	}
}

void Monster::listenForInput() {
	char c;
	while(c = getch()) {
		if(defenseEnd) {
			return;
		}
		if(c == 'd' || c == 'D') {
			curTrack = 14;
		}
		else if(c == 'a' || c == 'A') {
			curTrack = 12;
		}
	}
}

void Monster::defensePhase(int speed, Player& player) {
	system("cls");
	for(int i = 1; i <= 11; i ++) {
		setCursorPosition(i - 1, 11);
		for(int j = 1; j <= 5; j ++) {
			if(i == 1 || i == 11) {
				cout << '=';
			}
			else if(j == 1 || j == 3 || j == 5) {
				cout << '|';
			}
			else {
				cout << ' ';
			}
		}
		cout << '\n';
	}

	cout << "You : \n";
	player.showStatus();
	cout << "Monster : \n";
	showMonsterStatus();

	cout << "[a] to move to the left track\n";
	cout << "[d] to move to the right track\n";

	char c;
	int time = 5000;

	thread {changeTrack, curTrack}.join();
	thread {listenForInput, this}.detach();
	curTrack = 12;
	thread {changeTrack, std::ref(curTrack)}.join();

	while(time >= 0) {
		if((time / speed) % 3 == 0) {
			int d = randGen(0, 1);
			shots.push_back({1, 12 + d * 2});
		}
		thread {changeTrack, std::ref(curTrack)}.join();
		thread {shotDrop, this}.join();
		if(hit) {
			return;
		}
		Sleep(speed);
		time -= speed;
	}
	defenseEnd = true;
	return;
}
void Monster::counter() {
	char c;
	setCursorPosition(1, 0); 
	while(c = getch()) {
		if(offenseEnd) {
			return;
		}
		if(c != ' ') {
			continue;
		}
		hitCnt ++;
		setCursorPosition(2, 8);
		cout << hitCnt << " hits!!";
	}
}

void Monster::offensePhase(Player& player) {
	system("cls");
	setCursorPosition(3, 0);
	cout << "You : \n";
	player.showStatus();
	cout << "The Monster : \n";
	showMonsterStatus();
	int cnt = 0, time = 5000;
	cout << "Press spacebar to hit the monster\n";
	setCursorPosition(2, 8);
	cout << 0 << " hits!!";
	thread {counter, this}.detach();
	while(time > 0) {
		setCursorPosition(1, 8);
		cout << time / 1000 << " secs remaining\n";
		time -= 1000;
		Sleep(1000);
	}
	offenseEnd = true;
}

void Monster::showMonsterStatus() {
	cout << "LVL : " << lvl << '\n';
	cout << "HP : ";
	int x = mxHp / 5;
	for(int i = 0; i < 5; i ++) {
		if(hp >= x * i) {
			setOutputRed();
			cout << ' ';
			setOutputOriginal();
		}
		else {
			setOutputWhite();
			cout << ' ';
			setOutputOriginal();
		}
	}
	cout << " (" << hp << " / " << mxHp << ")\n";
}

bool Monster::combat(Player& player) {
	system("cls");
	cout << "You've encountered a monster !!\n";
	showMonsterStatus();
	cout << "Press any key to procceed to combat\n";
	Sleep(2000);
	char c;
	c = getch();
	int round = 1;
	while(true) {
		system("cls");
		cout << "Fight or Escape ?\n";
		cout << "[f] for fight, [e] for escape\n";


		cout << "You : \n";
		player.showStatus();
		cout << "Monster : \n";
		showMonsterStatus();
		

		while(c = getch()) {
			if(c == 'f' || c == 'F') {
				break;
			}
			else if(c == 'e' || c == 'E') {
				return false;
			}
		}
		shots.clear();
		defenseEnd = hit = 0;
		defensePhase(300 - 20 * round, player);
		system("cls");
		if(hit) {
			player.setHp(player.getHp() - 1);
		}
		if(player.getHp() == 0) {
			return false;
		}
		cout << "You Survived !!!\n";
		cout << "Press any key to proceed to offense phase\n";
		Sleep(2000);
		c = getch();
		hitCnt = offenseEnd = 0;
		offensePhase(player);
		hp -= hitCnt * player.getAtk();
		if(hp <= 0) {
			system("cls");
			player.gainExp(max(1, lvl - player.getLvl()));
			player.gainMoney(max(1, lvl - player.getLvl()) * randGen(50, 100));
			int t = randGen(0, 9);
			if(t == 6) {
				cout << "You've attained the exit's key!!!\n";
				player.getKey();
			}
			cout << "Congrats !! You've killed the monster !!\n";
			cout << "You've got " << max(1, lvl - player.getLvl()) << " exp!!\n";
			cout << "Press any key to exit the combat system.\n";
			Sleep(2000);
			c = getch();
			return true;
		}
		system("cls");
		cout << "You delt " << hitCnt * player.getAtk() << " damages to the monster!!\n";
		cout << "You didn't kill the monster : (\n";
		cout << "It's OK !!!\n";
		cout << "Press any key to procceed to defensePhase\n";
		Sleep(2000);
		c = getch();
		round ++;
	}
}
#include "Item.h"
#include "subjectives.h"


static int randGen(int left, int right) {

	using clk = chrono::high_resolution_clock;
	using rand_int = uniform_int_distribution<int>;
	using rand_double = uniform_real_distribution<double>;

	mt19937 rng(clk::now().time_since_epoch().count());
    return rand_int(left, right)(rng);
}

// constructor
Item::Item(string tag, int attr, int cost) : tag(tag), cost(cost), attr(attr) {
	int t = randGen(0, 10000) * attr * cost % V.size();
	name = V[t] + ' ' + tag;
	state = false;
}

bool Item::getState() {
	return state;
}

string Item::getName() {
	return name;
}

string Item::getTag() {
	return tag;
}

int Item::getAttr() {
	return attr;
}

int Item::getCost() {
	return cost;
}

string Item::getShopTag() {
	if(tag == "potion") {
		return "REC : ";
	} 
	else if(tag == "weapon") {
		return "ATK : ";
	}
	else {
		return "DEF : ";
	}
}

void Item::equip(Player& player) {
	state = true;
	if(tag == "weapon") {
		player.addAtk(attr);
	}
	else {
		player.addHp(attr);
	}
}

void Item::unEquip(Player& player) {
	state = false;
	if(tag == "weapon") {
		player.downAtk(attr);
	}
	else {
		player.downHp(attr);
	}	
}
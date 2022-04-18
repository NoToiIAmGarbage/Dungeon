#include "Item.h"

// constructor
Item::Item(string tag, int attr, int cost) : tag(tag), cost(cost), attr(attr) {
	name = tag;
}


string Item::getName() {
	return name;
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
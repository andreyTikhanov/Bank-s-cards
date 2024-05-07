#include "Card.h"
Card::Card() {
	srand(time(NULL));
	for (int i = 0; i <= 11; i++) {
		if (i == 4 || i == 8) numberCard += " ";
		numberCard += std::to_string(rand() % 9);
	}
}

Card::Card(int money, std::string numberCard) {
	this->money = money;
	this->numberCard = numberCard;
}

std::string Card::getNumberCard() const {
	return numberCard;
}

int Card::getMoney() const {
	return money;
}
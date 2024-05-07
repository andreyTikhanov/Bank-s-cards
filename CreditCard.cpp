#include "CreditCard.h"

CreditCard::CreditCard() {}
CreditCard::CreditCard(int money, std::string numberCard) {
	this->money = money;
	this->numberCard = numberCard;
}
bool CreditCard::addMoney(int money) {
	return (money > 0) ? (this->money += money, true) : false;
}

bool CreditCard::spendMoney(int money) {
	return (money > 0) ? (this->money -= money, true) : false;
}

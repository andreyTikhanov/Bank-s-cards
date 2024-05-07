#pragma once
#include <iostream>
#include <string>
class Card {
protected:
	std::string numberCard = "5611 ";
	int money = 0;
public:
	Card();
	Card(int money, std::string numberCard);
	virtual bool addMoney(int money) = 0;
	virtual bool spendMoney(int money) = 0;
	std::string getNumberCard() const;
	int getMoney() const;
};


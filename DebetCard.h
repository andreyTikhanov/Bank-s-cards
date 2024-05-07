#pragma once
#include "Card.h"
class DebetCard : public Card {
public:
	DebetCard();
	DebetCard(int money, std::string numberCard);
	bool addMoney(int money) override;
	bool spendMoney(int money) override;
};


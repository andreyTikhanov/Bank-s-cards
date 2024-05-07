#pragma once
#include "Card.h"
class CreditCard : public Card {
public:
	CreditCard();
	CreditCard(int money, std::string numberCard);
	bool addMoney(int money) override;
	bool spendMoney(int money) override;
};


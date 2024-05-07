#include "DebetCard.h"

DebetCard::DebetCard() {}
DebetCard::DebetCard(int money, std::string numberCard) {
    this->money = money;
    this->numberCard = numberCard;
}
bool DebetCard::addMoney(int money) {
    return (money > 0) ? (this->money += money, true) : false;
}

bool DebetCard::spendMoney(int money) {
    return (money > 0 && this->money - money >= 0) ? (this->money -= money, true) : false;
}

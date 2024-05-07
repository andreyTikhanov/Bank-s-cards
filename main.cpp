#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include<iostream>
#include "User.h"
using namespace sf;
const int WS_WIDTH = 900, WS_HEIGHT = 600;
RenderWindow window(VideoMode(WS_WIDTH, WS_HEIGHT), L"wallet", Style::Close);
Text text;
Font font;
Texture background;
Sprite backSprite;
Sprite sprite;

enum Layers {
	registration = 1,
	autoration = 2,
	mainWindow = 3,
};

int main(){
	User user;
	int layers;
	sf::Text userName;
	if (user.loadUser("user.txt") == false) {
		background.loadFromFile("Frame 1.png");
		sprite.setTexture(background);
		layers = Layers::registration;
	}
	else {
		userName.setPosition(sf::Vector2f(430, 128));
		userName.setCharacterSize(42);
		userName.setFont(font);
		userName.setFillColor(sf::Color::Black);
		userName.setString(user.getLogin());
		background.loadFromFile("autorization.png");
		sprite.setTexture(background);
		layers = Layers::autoration;
	}
	font.loadFromFile("arial.ttf");
	sf::Text login;
	login.setFont(font);
	login.setCharacterSize(18);
	login.setFillColor(sf::Color::Black);
	login.setPosition(sf::Vector2f(321, 262));
	sf::Text password;
	password.setFont(font);
	password.setCharacterSize(18);
	password.setFillColor(sf::Color::Black);
	password.setPosition(sf::Vector2f(321, 353));
	text.setFont(font);

	sf::RectangleShape shapes[4];
	shapes[0].setPosition(sf::Vector2f(311, 232));
	shapes[0].setSize(sf::Vector2f(278, 60));

	shapes[1].setPosition(sf::Vector2f(311, 322));
	shapes[1].setSize(sf::Vector2f(278, 60));

	shapes[2].setPosition(sf::Vector2f(311, 411));
	shapes[2].setSize(sf::Vector2f(127, 50));

	shapes[3].setPosition(sf::Vector2f(460, 411));
	shapes[3].setSize(sf::Vector2f(127, 50));
	std::string inputText;
	std::string inputPassword;
	bool isLogin = false;
	bool isPassword = false;
	
	sf::Text numberAndMoney;
	while (window.isOpen()) {
		//выключение повтора при удержании клавиши
		Event event;
		window.clear(Color::Black);
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (layers == Layers::registration) {
			if (event.type == sf::Event::MouseButtonReleased) {
				sf::Vector2i mousePos = Mouse::getPosition(window);
				if (shapes[0].getGlobalBounds().contains(sf::Vector2f(mousePos))) {
					isLogin = true;
					isPassword = false;
				}
				else if (shapes[1].getGlobalBounds().contains(sf::Vector2f(mousePos))) {
					isLogin = false;
					isPassword = true;
				}
				else if (shapes[2].getGlobalBounds().contains(sf::Vector2f(mousePos))) {
					user.setLogin(inputText);
					user.setPassword(inputPassword);
					layers = Layers::mainWindow;
					user.saveUser("user.txt");
				}
				else if (shapes[3].getGlobalBounds().contains(sf::Vector2f(mousePos))) {
					window.close();
				}
				
			}
			else if (event.type == sf::Event::TextEntered) {
				if (isLogin || isPassword) {
					if (event.text.unicode < 128) {
						if (event.text.unicode == 8) { // Backspace
							if (!inputText.empty() && isLogin) {
								inputText.pop_back();
							}
							if (!inputPassword.empty() && isPassword) {
								inputPassword.pop_back();
							}
						}
						else if (event.text.unicode == 13) { // Enter
							inputPassword.clear();
							inputText.clear();
						}
						else {
							if (isLogin) {
								inputText += static_cast<char>(event.text.unicode);
							}
							else if (isPassword) {
								inputPassword += static_cast<char>(event.text.unicode);
							}
						}

					}
					if (isLogin) {
						login.setString(inputText);
					}
					if (isPassword) {
						password.setString(inputPassword);
					}
				}
			}
			
			}
			else if (layers == Layers::autoration) {
				shapes[2].setPosition(sf::Vector2f(311, 291));
				shapes[2].setSize(sf::Vector2f(127, 50));
				shapes[3].setPosition(sf::Vector2f(460, 291));
				shapes[3].setSize(sf::Vector2f(127, 50));
				password.setFillColor(sf::Color::Black);
				password.setPosition(sf::Vector2f(321, 236));
				if (event.type == sf::Event::MouseButtonReleased) {
					sf::Vector2i mousePos = Mouse::getPosition(window);
					if (shapes[2].getGlobalBounds().contains(sf::Vector2f(mousePos))) {
						if (inputPassword == user.getPassword()) layers = Layers::mainWindow;
						else window.setTitle(inputPassword + " " + user.getPassword());
					}
					else if (shapes[3].getGlobalBounds().contains(sf::Vector2f(mousePos))) {
						window.close();
					}

				}
				else if (event.type == sf::Event::TextEntered) {
						if (event.text.unicode < 128) {
							if (event.text.unicode == 8) {
								if (!inputPassword.empty()) inputPassword.pop_back();
							}
							else if (event.text.unicode == 13) inputPassword.clear();
							else inputPassword += static_cast<char>(event.text.unicode);
						}
					 password.setString(inputPassword);
				}
			}
			else if (layers == Layers::mainWindow) {
				shapes[1].setPosition(sf::Vector2f(91, 42));
				shapes[1].setSize(sf::Vector2f(278, 60));
				shapes[2].setPosition(sf::Vector2f(365, 43));
				shapes[2].setSize(sf::Vector2f(127, 50));
				shapes[3].setPosition(sf::Vector2f(639, 43));
				shapes[3].setSize(sf::Vector2f(127, 50));
				if (event.type == sf::Event::MouseButtonReleased) {
					sf::Vector2i mousePos = Mouse::getPosition(window);
					if (shapes[1].getGlobalBounds().contains(sf::Vector2f(mousePos))) {
						user.addDebetCard();
						
					}
					else if (shapes[2].getGlobalBounds().contains(sf::Vector2f(mousePos))) {
						user.spendMoney<DebetCard>(0, 100);
					}
					else if (shapes[3].getGlobalBounds().contains(sf::Vector2f(mousePos))) {
						user.addMoney<DebetCard>(0, 200);
					}
				}
			}
		}
		window.draw(sprite);
		if (layers == Layers::registration) {
			window.draw(login);
			window.draw(password);
		}
		else if (layers == Layers::mainWindow) {
			background.loadFromFile("mainWindow.png");
			sprite.setTexture(background);

			numberAndMoney.setFont(font);
			numberAndMoney.setCharacterSize(18);
			numberAndMoney.setFillColor(sf::Color::Black);
			numberAndMoney.setPosition(sf::Vector2f(321, 262));
			numberAndMoney.setString(user.getNumberAndMoney());
			window.draw(numberAndMoney);
			window.setTitle(user.getNumberAndMoney());
		}
		else if (layers == Layers::autoration) {
			window.draw(userName);
			window.draw(password);
		}
		window.display();
	}
}
#include<iostream>
#include<SFML/Graphics.hpp>

using namespace std;

int main() {
	sf::RenderWindow window(sf::VideoMode(640, 480),"demo");
	window.setFramerateLimit(120);
	int x = 320;
	int y = 240;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.KeyPressed) {
				if (event.key.code == sf::Keyboard::Right) {
					++x;
				}
				if (event.key.code == sf::Keyboard::Left) {
					--x;
				}
				if (event.key.code == sf::Keyboard::Up) {
					--y;
				}
				if (event.key.code == sf::Keyboard::Down) {
					++y;
				}
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
			}

		}

		window.clear();
		sf::RectangleShape shape(sf::Vector2f(20,20));
		shape.setFillColor(sf::Color::Blue);
		shape.setPosition(x, y);
		window.draw(shape);
		window.display();
	}
}
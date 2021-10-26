#include<iostream>
#include<SFML/Graphics.hpp>
#include <chrono>
#include <thread>



using Clock = std::chrono::steady_clock;
using Timestamp = Clock::time_point;
using Duration = Timestamp::duration;

inline Timestamp Now() { return Clock::now(); }

void UpdatePhysics(bool right,bool left, sf::RectangleShape& shape) {
	if (right  == true) {
		shape.move(0.1, 0);
	}
	if (left == true) {
		shape.move(-0.1, 0);
	}

}

int main() {
	sf::RenderWindow window(sf::VideoMode(640, 480),"demo");
	window.setFramerateLimit(60);
	int x = 320;
	int y = 280;
	sf::RectangleShape shape(sf::Vector2f(20, 20));
	shape.setPosition(x, y);
	shape.setFillColor(sf::Color::Blue);

	sf::Texture texture;
	texture.loadFromFile("C:\\Users\\Alexandr\\Desktop\\Projects\\sfml-demo\\sfml-demo\\image.png");
	texture.setSmooth(true);
	sf::Sprite sprite(texture, sf::IntRect(0, 0, 640, 20));
	sprite.setPosition(0, 300);

	const Duration kUpdatePeriod = std::chrono::milliseconds(10);
	auto update_timestamp = Now();
	while (window.isOpen()) {
		bool right = false;
		bool left = false;
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				right = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				left = true;
			}
		}

		if (Now() < update_timestamp) {
			std::this_thread::sleep_until(update_timestamp);
		}

		const auto current_time = Now();

		
		while (current_time >= update_timestamp) {
			update_timestamp += kUpdatePeriod;
			UpdatePhysics(right,left,shape);
		}

		window.clear(sf::Color::White);
		
		
		window.draw(sprite);

		window.draw(shape);

		window.display();
	}
}
#include<iostream>
#include<SFML/Graphics.hpp>
#include <chrono>
#include <thread>

using Clock = std::chrono::steady_clock;
using Timestamp = Clock::time_point;
using Duration = Timestamp::duration;

inline Timestamp Now() { return Clock::now(); }



void UpdatePhysics(int& x, int& y, bool right, bool left,int& space, sf::RectangleShape& shape) { 
	
	
	if (right == true) {
		shape.move(1, 0);
		++x;
	}
	if (left == true) {
		shape.move(-1, 0);
		--x;
	}
	

	if (space == 1 && y != 320) {
		shape.move(0, -1);
		++y;
	}
	if (space == 2) {
		shape.move(0, 1);
		--y;
	}
	if (y == 280)
		space = 0;
	
}


int main() {
	sf::RenderWindow window(sf::VideoMode(640, 480), "demo");

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

	bool right = false;
	bool left = false;
	int  space = 0;
	int x_shape = 320;
	int y_shape = 280;

	const Duration kUpdatePeriod = std::chrono::milliseconds(10);
	auto update_timestamp = Now();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Right) {
					right = true;
				}
				if (event.key.code == sf::Keyboard::Left) {
					left = true;
				}
				if (event.key.code == sf::Keyboard::Space) {
					space = 1;
				}
			}

			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Right) {
					right = false;
				}
				if (event.key.code == sf::Keyboard::Left) {
					left = false;
				}
				
			    if (event.key.code == sf::Keyboard::Space ) {
					space = 2;
				}
				
			}
		}
		if (Now() < update_timestamp) {
			std::this_thread::sleep_until(update_timestamp);
		}

		const auto current_time = Now();


		while (current_time >= update_timestamp) {
			update_timestamp += kUpdatePeriod;
			UpdatePhysics(x_shape,y_shape,right, left, space, shape);
		}
		window.clear(sf::Color::White);


		window.draw(sprite);

		window.draw(shape);

		window.display();
	}
}

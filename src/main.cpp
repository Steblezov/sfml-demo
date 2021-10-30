#include<iostream>
#include<SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "windows.h"


using Clock = std::chrono::steady_clock;
using Timestamp = Clock::time_point;
using Duration = Timestamp::duration;

inline Timestamp Now() { return Clock::now(); }







void UpdatePhysics(int& x, int& y, bool right, bool left, bool up,bool down, sf::RectangleShape& shape, bool& over) {
		
	if (right == true) {
		shape.move(1, 0);
		++x;
	}
	if (left == true) {
		shape.move(-1, 0);
		--x;
	}
	if (up == true) {
		shape.move(0, -1);
		++y;
	}
	if (down == true) {
		shape.move(0, 1);
		--y;
	}
	if (y == 500) {
		over = true;
	}
	if (y == 128) {
		over = true;
	}
	if (x == 64) {
		over = true;
	}
	if (x == 560) {
		over = true;
	}
}


int main() {
	const int map_height = 8;
	const int map_width= 10;
	sf::String map[map_height]{
	"0000000000",
	"0        0",
	"0        0",
	"0        0",
	"0        0",
	"0        0",
	"0        0",
	"0000000000",
	};



	sf::RenderWindow window(sf::VideoMode(640, 480), "demo");

	window.setFramerateLimit(60);

	int x = 320;
	int y = 280;

	sf::RectangleShape shape(sf::Vector2f(20, 20));
	shape.setPosition(x, y);
	shape.setFillColor(sf::Color::Green);

	sf::Image map_image;
	map_image.loadFromFile("C:\\Users\\Alexandr\\Desktop\\Projects\\sfml-demo\\sfml-demo\\image.png");
	sf::Texture texture_map;
	texture_map.loadFromImage(map_image);
	sf::Sprite s_map(texture_map);

	bool right = false;
	bool left = false;
	bool up = false;
	bool down = false;
	int x_shape = 320;
	int y_shape = 280;

	sf::Text gameOver;
	sf::Font font;
	font.loadFromFile("C:\\Users\\Alexandr\\Desktop\\Projects\\sfml-demo\\sfml-demo\\CimeroPro.ttf");
	gameOver.setFont(font);
	gameOver.setString("GameOver");
	gameOver.setCharacterSize(50);
	gameOver.setFillColor(sf::Color::Black);
	gameOver.setStyle(sf::Text::Bold | sf::Text::Underlined);
	gameOver.setPosition(x, y);
	bool over = false;

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
				if (event.key.code == sf::Keyboard::Up) {
					up = true;
				}
				if (event.key.code == sf::Keyboard::Down) {
					down = true;
				}
			}

			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Right) {
					right = false;
				}
				if (event.key.code == sf::Keyboard::Left) {
					left = false;
				}
				if (event.key.code == sf::Keyboard::Up) {
					up = false;
				}
				if (event.key.code == sf::Keyboard::Down) {
					down = false;
				}
				
			}
			
		}
		
		if (Now() < update_timestamp) {
			std::this_thread::sleep_until(update_timestamp);
		}

		const auto current_time = Now();


		while (current_time >= update_timestamp) {
			update_timestamp += kUpdatePeriod;
			UpdatePhysics(x_shape,y_shape,right, left, up, down, shape, over);
		}
		window.clear(sf::Color::White);
		for (int i = 0; i < map_height; i++)
			for (int j = 0; j < map_width; j++)
			{
				if (map[i][j] == ' ')  s_map.setTextureRect(sf::IntRect(64, 0, 64, 64)); 
				if (map[i][j] == '0') s_map.setTextureRect(sf::IntRect(128, 0, 64, 64));


				s_map.setPosition(j * 64, i * 64);
				window.draw(s_map);
			}
		
		
		window.draw(shape);
		if (over == true) {
			window.draw(gameOver);
			sf::Clock clock;
			if (clock.getElapsedTime() >= sf::seconds(1)) {
				window.close();
			}

		}
		
		window.display();
	}
}

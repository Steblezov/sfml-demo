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
		for (int i = 0; i < map_height; i++)
			for (int j = 0; j < map_width; j++)
			{
				if (map[i][j] == ' ')  s_map.setTextureRect(sf::IntRect(64, 0, 64, 64)); 
				if (map[i][j] == '0') s_map.setTextureRect(sf::IntRect(128, 0, 64, 64));


				s_map.setPosition(j * 64, i * 64);
				window.draw(s_map);
			}


		window.draw(shape);
		window.display();
	}
}

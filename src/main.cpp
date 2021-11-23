#include<iostream>
#include<SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "windows.h"


using Clock = std::chrono::steady_clock;
using Timestamp = Clock::time_point;
using Duration = Timestamp::duration;

inline Timestamp Now() { return Clock::now(); }


std::pair<int, int> sneak_pos[200];

int dir ;
int score = 1;
bool over = false;

void UpdatePhysics() {
	for (int i = score; i > 0; --i) {
		sneak_pos[i].first = sneak_pos[i - 1].first;
		sneak_pos[i].second = sneak_pos[i - 1].second;
	}

	if (dir == 1) {
		sneak_pos[0].first += 1;
	}
	if (dir == 2) {
		sneak_pos[0].first -= 1;
	}
	if (dir == 3) {
		sneak_pos[0].second-=1;
	}
	if (dir == 4) {
		sneak_pos[0].second += 1;
	}
	if (sneak_pos[0].first > 27)
		sneak_pos[0].first= 0; 
	if (sneak_pos[0].first < 0) 
		sneak_pos[0].first = 27;
	if (sneak_pos[0].second > 20) 
		sneak_pos[0].second = 0;  
	if (sneak_pos[0].second < 0) 
		sneak_pos[0].second = 20;
	for (int i = 1; i < score; i++) {
		if (sneak_pos[0].first == sneak_pos[i].first && sneak_pos[0].second == sneak_pos[i].second)
			over = true;
	}
}


int main() {
	sf::RenderWindow window(sf::VideoMode(640, 480), "demo");

	window.setFramerateLimit(60);

	const int map_height = 20;
	const int map_width = 27;


	sf::Image map_image;
	map_image.loadFromFile("C:\\Users\\Alexandr\\Desktop\\Projects\\sfml-demo\\sfml-demo\\map.png");
	sf::Texture texture_map;
	texture_map.loadFromImage(map_image);
	sf::Sprite map(texture_map);

	sf::Image image_sneak_head;
	image_sneak_head.loadFromFile("C:\\Users\\Alexandr\\Desktop\\Projects\\sfml-demo\\sfml-demo\\sneak\\Sprite-0002.png");
	sf::Image image_sneak_body;
	image_sneak_body.loadFromFile("C:\\Users\\Alexandr\\Desktop\\Projects\\sfml-demo\\sfml-demo\\sneak\\Sprite-0001.png");
	sf::Texture texture_sneak_body;
	texture_sneak_body.loadFromImage(image_sneak_body);
	sf::Texture texture_sneak_head;
	texture_sneak_head.loadFromImage(image_sneak_head);
	sf::Sprite sneak_head(texture_sneak_head);
	sf::Sprite sneak_body(texture_sneak_body);
	
	


	int time_GameOver = 5;

	sf::Text gameOver;
	sf::Font font;
	font.loadFromFile("C:\\Users\\Alexandr\\Desktop\\Projects\\sfml-demo\\sfml-demo\\CimeroPro.ttf");
	gameOver.setFont(font);
	gameOver.setString("GameOver");
	gameOver.setCharacterSize(50);
	gameOver.setFillColor(sf::Color::Black);
	gameOver.setStyle(sf::Text::Bold | sf::Text::Underlined);
	gameOver.setPosition(320, 280);

	
	sf::Text Score;
	Score.setFont(font);
	Score.setCharacterSize(25);
	Score.setFillColor(sf::Color::Black);
	Score.setStyle(sf::Text::Bold | sf::Text::Underlined);
	Score.setPosition(26, 22);


	int x_food;
	int y_food;
	srand(time(0));
	x_food =  rand() % 27;
	y_food =  rand() % 20;

	sf::Image image_food;
	image_food.loadFromFile("C:\\Users\\Alexandr\\Desktop\\Projects\\sfml-demo\\sfml-demo\\sneak\\Sprite-0003.png");
	sf::Texture texture_food;
	texture_food.loadFromImage(image_food);
	sf::Sprite food(texture_food);
	

	sf::Clock clock;
	float timer = 0, delay = 0.09;

	
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();

			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				if (event.key.code == sf::Keyboard::Right) {
					dir = 1;
					sneak_head.setOrigin(12, 12);
					sneak_head.setRotation(90);
					sneak_head.setOrigin(0, 24);
				}
				if (event.key.code == sf::Keyboard::Left) {
					dir = 2;
					sneak_head.setOrigin(12, 12);
					sneak_head.setRotation(-90);
					sneak_head.setOrigin(24, 0);
				}
				if (event.key.code == sf::Keyboard::Up) {
					dir = 3;
					sneak_head.setOrigin(12, 12);
					sneak_head.setRotation(360);
					sneak_head.setOrigin(0, 0);
				}
				if (event.key.code == sf::Keyboard::Down) {
					dir = 4;
					sneak_head.setOrigin(12, 12);
					sneak_head.setRotation(-180);
					sneak_head.setOrigin(24, 24);
				}
			}



		}
		if (sneak_pos[0].first == x_food && sneak_pos[0].second == y_food) {
			++score;
			x_food =  rand() % 27;
			y_food =  rand() % 20;
			

		}

		food.setPosition(x_food * 24, y_food * 24);
		Score.setString(std::to_string(score));


		if(timer > delay){
			timer = 0;
			UpdatePhysics();
			if (over == true) {
				--time_GameOver;
			}
			if (time_GameOver == 0) {
				window.close();
			}

		}
		window.clear(sf::Color::White);
		for (int i = 0; i < map_height; i++)
			for (int j = 0; j < map_width; j++)
			{
				map.setPosition(j  * 24, i * 24 );
				window.draw(map);
			}

		

		if (over == true) {
			window.draw(gameOver);
		}
		window.draw(food);
		window.draw(Score);
		for (int i = 0; i < score; ++i) {
			if (i == 0) {
				sneak_head.setPosition(sneak_pos[i].first * 24 , sneak_pos[i].second * 24 );
				window.draw(sneak_head);
			}
			else {
				sneak_body.setPosition(sneak_pos[i].first * 24, sneak_pos[i].second  * 24);
				window.draw(sneak_body);
			}
			
		}

		window.display();
	}
}





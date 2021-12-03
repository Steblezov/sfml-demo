#include<iostream>
#include<SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "windows.h"
#include <SFML/Audio.hpp>


using Clock = std::chrono::steady_clock;
using Timestamp = Clock::time_point;
using Duration = Timestamp::duration;

inline Timestamp Now() { return Clock::now(); }


sf::Vector2i sneak_pos[200];

int dir = 4;
int score = 3;
bool over = false;
const int map_H = 20;
const int map_W = 27;
const int sizeS = 24;

void UpdatePhysics(sf::Sprite& sneak_head) {
	for (int i = score; i > 0; --i) {
		sneak_pos[i].x = sneak_pos[i - 1].x;
		sneak_pos[i].y = sneak_pos[i - 1].y;
	}

	switch (dir) {
	case 1:
		sneak_pos[0].x += 1;
		sneak_head.setOrigin(12, 12);
		sneak_head.setRotation(90);
		sneak_head.setOrigin(0, 24);
		break;
	case  2:
		sneak_pos[0].x -= 1;
		sneak_head.setOrigin(12, 12);
		sneak_head.setRotation(-90);
		sneak_head.setOrigin(24, 0);
		break;
	case 3:
		sneak_pos[0].y -= 1;
		sneak_head.setOrigin(12, 12);
		sneak_head.setRotation(360);
		sneak_head.setOrigin(0, 0);
		break;
	case 4:
		sneak_pos[0].y += 1;
		sneak_head.setOrigin(12, 12);
		sneak_head.setRotation(-180);
		sneak_head.setOrigin(24, 24);
		break;
	}
	if (sneak_pos[0].x > map_W - 1)
		sneak_pos[0].x= 0; 
	if (sneak_pos[0].x < 0) 
		sneak_pos[0].x = map_W - 1;
	if (sneak_pos[0].y > map_H - 1) 
		sneak_pos[0].y = 0;  
	if (sneak_pos[0].y < 0) 
		sneak_pos[0].y = map_H - 1;
	for (int i = 1; i < score; i++) {
		if (sneak_pos[0].x == sneak_pos[i].x && sneak_pos[0].y == sneak_pos[i].y)
			over = true;
	}
}


int main() {
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(640, 480), "demo");

	window.setFramerateLimit(60);

	sf::Texture texture_map;
	texture_map.loadFromFile("map.png");
	sf::Sprite map(texture_map);

	sf::Texture texture_sneak_body;
	texture_sneak_body.loadFromFile ("Sprite-0001.png");
	sf::Texture texture_sneak_head;
	texture_sneak_head.loadFromFile("Sprite-0002.png");
	sf::Sprite sneak_head(texture_sneak_head);
	sf::Sprite sneak_body(texture_sneak_body);
	sneak_head.setRotation(-180);
	
	int time_GameOver = 10;

	sf::Text gameOver;
	sf::Font font;
	font.loadFromFile("CimeroPro.ttf");
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

	sf::SoundBuffer rew_buffer;
	rew_buffer.loadFromFile("rew.wav");
	sf::Sound rew(rew_buffer);

	sf::SoundBuffer dead_buffer;
	dead_buffer.loadFromFile("dead.wav");
	sf::Sound dead(dead_buffer);

	

	int x_food;
	int y_food;
	x_food =  rand() % map_W;
	y_food =  rand() % map_H;

	sf::Texture texture_food;
	texture_food.loadFromFile("Sprite-0003.png");
	sf::Sprite food(texture_food);
	

	sf::Clock clock;
	float timer = 0, delay = 0.09;

	bool restart = false;
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
					
				}
				if (event.key.code == sf::Keyboard::Left) {
					dir = 2;
				}
				if (event.key.code == sf::Keyboard::Up) {
					dir = 3;
					
				}
				if (event.key.code == sf::Keyboard::Down) {
					dir = 4;
					
				}
			}



		}
		if (sneak_pos[0].x == x_food && sneak_pos[0].y == y_food) {
			++score;
			x_food =  rand() % map_W;
			y_food =  rand() % map_H;
			rew.play();

		}

		food.setPosition(x_food * 24, y_food * 24);
		Score.setString(std::to_string(score));


		if(timer > delay){
			timer = 0;
			if (over == false)
				UpdatePhysics(sneak_head);
			if (over == true) {
				dead.play();
				--time_GameOver;

			}
			if (time_GameOver == 0) {
				time_GameOver = 10;
				over = false;
				score = 3;
			}

		}
		window.clear(sf::Color::White);
		for (int i = 0; i < map_H; i++)
			for (int j = 0; j < map_W; j++)
			{
				map.setPosition(j  * sizeS, i * sizeS );
				window.draw(map);
			}

		

		if (over == true) {
			if (time_GameOver != 0)
				window.draw(gameOver);
		}
		
		for (int i = 0; i < score; ++i) {
			if (i == 0) {
				sneak_head.setPosition(sneak_pos[i].x* sizeS , sneak_pos[i].y * sizeS );
				window.draw(sneak_head);
			}
			else {
				sneak_body.setPosition(sneak_pos[i].x * sizeS, sneak_pos[i].y * sizeS);
				window.draw(sneak_body);
			}
			
		}

		window.draw(food);
		window.draw(Score);
		window.display();
	}
}





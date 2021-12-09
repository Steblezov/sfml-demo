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

int score = 3;
bool over = false;
const int map_H = 20;
const int map_W = 27;
const int sizeS = 24;

class Sneak {
public:
	Sneak(int length) {
		dir_ = 4;
		length_ = length;
		texture_sneak_body_.loadFromFile("Sprite-0001.png");
		texture_sneak_head_.loadFromFile("Sprite-0002.png");
	}

	void UpdatePhysics() {
		for (int i = length_; i > 0; --i) {
			sneak_pos_[i].x = sneak_pos_[i - 1].x;
			sneak_pos_[i].y = sneak_pos_[i - 1].y;
		}

		switch (dir_) {
		case 1:
			sneak_pos_[0].x += 1;
			break;
		case  2:
			sneak_pos_[0].x -= 1;
			break;
		case 3:
			sneak_pos_[0].y -= 1;
			break;
		case 4:
			sneak_pos_[0].y += 1;
			break;
		}
		if (sneak_pos_[0].x > map_W - 1)
			sneak_pos_[0].x = 0;
		if (sneak_pos_[0].x < 0)
			sneak_pos_[0].x = map_W - 1;
		if (sneak_pos_[0].y > map_H - 1)
			sneak_pos_[0].y = 0;
		if (sneak_pos_[0].y < 0)
			sneak_pos_[0].y = map_H - 1;
		for (int i = 1; i < length_; i++) {
			if (sneak_pos_[0].x == sneak_pos_[i].x && sneak_pos_[0].y == sneak_pos_[i].y)
				over = true;
		}
	}
	void Draw(sf::RenderWindow* window)const {
		sf::Sprite sneak_head(texture_sneak_head_);
		sf::Sprite sneak_body(texture_sneak_body_);
		sneak_head.setRotation(-180);  // TODO: discus
		switch (dir_) {
		case 1:
			sneak_head.setOrigin(12, 12);
			sneak_head.setRotation(90);
			sneak_head.setOrigin(0, 24);
			break;
		case  2:
			sneak_head.setOrigin(12, 12);
			sneak_head.setRotation(-90);
			sneak_head.setOrigin(24, 0);
			break;
		case 3:
			sneak_head.setOrigin(12, 12);
			sneak_head.setRotation(360);
			sneak_head.setOrigin(0, 0);
			break;
		case 4:
			sneak_head.setOrigin(12, 12);
			sneak_head.setRotation(-180);
			sneak_head.setOrigin(24, 24);
			break;
		}
		for (int i = 0; i < length_; ++i) {
			if (i == 0) {
				sneak_head.setPosition(sneak_pos_[i].x * sizeS, sneak_pos_[i].y * sizeS);
				window->draw(sneak_head);
			}
			else {
				sneak_body.setPosition(sneak_pos_[i].x * sizeS, sneak_pos_[i].y * sizeS);
				window->draw(sneak_body);
			}

		}
	}
	const sf::Vector2i& SneakHead()const {
		return sneak_pos_[0];
	}
	void SetLength(int n) {
		length_ = n;
	}
	void SetDir(int dir) {
		dir_ = dir;

	}
private:
	sf::Vector2i sneak_pos_[200];
    int dir_;
	int length_;
	sf::Texture texture_sneak_body_;
	sf::Texture texture_sneak_head_;
};



int main() {
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(640, 480), "demo");

	window.setFramerateLimit(60);

	sf::Texture texture_map;
	texture_map.loadFromFile("map.png");
	sf::Sprite map(texture_map);

	Sneak sneak(score);
	
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


	int x_green_food;
	int y_green_food;
	x_green_food = rand() % map_W;
	y_green_food = rand() % map_H;
	int green_food_time = rand() % 60;
	int green_food_time0 = 0;
	int time_green_food = 25;

	sf::Texture texture_food;
	texture_food.loadFromFile("Sprite-0003.png");
	sf::Sprite food(texture_food);

	sf::Texture texture_green_food;
	texture_green_food.loadFromFile("greenfood.png");
	sf::Sprite green_food(texture_green_food);
	

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
					sneak.SetDir(1);
				}
				if (event.key.code == sf::Keyboard::Left) {
					sneak.SetDir(2);
				}
				if (event.key.code == sf::Keyboard::Up) {
					sneak.SetDir(3);
				}
				if (event.key.code == sf::Keyboard::Down) {
					sneak.SetDir(4);
				}
			}
		}

		if (sneak.SneakHead().x == x_food && sneak.SneakHead().y == y_food) {
			++score;
			sneak.SetLength(score);
			x_food =  rand() % map_W;
			y_food =  rand() % map_H;
			rew.play();
		}
		if (time_green_food == 0) {
			time_green_food = 25;
			green_food_time0 = 0;
		}
		if (sneak.SneakHead().x == x_green_food && sneak.SneakHead().y == y_green_food && green_food_time0 == green_food_time) {
			score += 3;
			sneak.SetLength(score);
			x_green_food = rand() % map_W;
			y_green_food = rand() % map_H;
			green_food_time0 = 0;
			rew.play();

		}
		green_food.setPosition(x_green_food * sizeS, y_green_food * sizeS);
		food.setPosition(x_food * sizeS, y_food * sizeS);
		Score.setString(std::to_string(score));


		if(timer > delay){
			if (green_food_time0 != green_food_time)
				green_food_time0++;
			else {
				--time_green_food;
			}
			timer = 0;
			if (over == false)
				sneak.UpdatePhysics();
			if (over == true) {
				dead.play();
				--time_GameOver;

			}
			if (time_GameOver == 0) {
				time_GameOver = 10;
				over = false;
				score = 3;
				sneak.SetLength(3);
			}

		}
		window.clear(sf::Color::White);
		for (int i = 0; i < map_H; i++)
			for (int j = 0; j < map_W; j++)
			{
				map.setPosition(j  * sizeS, i * sizeS );
				window.draw(map);
			}

		sneak.Draw(&window);

		if (over == true) {
			if (time_GameOver != 0)
				window.draw(gameOver);
		}
		
		if (green_food_time0 == green_food_time) {
			window.draw(green_food);
		}

		window.draw(food);
		window.draw(Score);
		window.display();
	}
}





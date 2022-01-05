#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "windows.h"
#include <SFML/Audio.hpp>
#include "snake.h"
#include "constants.h"
#include "food.h"




using Clock = std::chrono::steady_clock;
using Timestamp = Clock::time_point;
using Duration = Timestamp::duration;

inline Timestamp Now() { return Clock::now(); }

int score = 3;
bool over = false;

int main() {
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(640, 480), "demo");

	window.setFramerateLimit(60);

	sf::Texture texture_map;
	texture_map.loadFromFile("map.png");
	sf::Sprite map(texture_map);

	Snake snake(score);

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

	sf::SoundBuffer dead_buffer;
	dead_buffer.loadFromFile("dead.wav");
	sf::Sound dead(dead_buffer);

	sf::SoundBuffer rew_buffer;
	rew_buffer.loadFromFile("rew.wav");
	sf::Sound rew(rew_buffer);

	Food food(1);
	Food green_food(2);

	int green_food_time0 = rand() % 60;
	int green_food_time1 = 0;
	int green_food_time2 = 25;


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
					snake.SetDir(1);
				}
				if (event.key.code == sf::Keyboard::Left) {
					snake.SetDir(2);
				}
				if (event.key.code == sf::Keyboard::Up) {
					snake.SetDir(3);
				}
				if (event.key.code == sf::Keyboard::Down) {
					snake.SetDir(4);
				}
			}
		}

		if (snake.SnakeHead().x == food.FoodPos().x && snake.SnakeHead().y == food.FoodPos().y) {
			++score;
			snake.SetLength(score);
			food.UpdateFood();
			rew.play();
		}
		if (green_food_time2 == 0) {
			green_food_time2 = 25;
			green_food_time1 = 0;
			green_food_time0 = rand() % 60;
			green_food.UpdateFood();
		}
		if (snake.SnakeHead().x == green_food.FoodPos().x && snake.SnakeHead().y == green_food.FoodPos().y && green_food_time1 == green_food_time0 && green_food_time2 != 0) {
			score += 3;
			snake.SetLength(score);
			green_food_time1 = 0;
			green_food.UpdateFood();
			rew.play();
		}

		Score.setString(std::to_string(score));

		if (timer > delay) {
			if (green_food_time1 != green_food_time0)
				green_food_time1++;
			else {
				--green_food_time2;
			}
			timer = 0;
			if (over == false)
				snake.UpdatePhysics(over);
			if (over == true) {
				dead.play();
				--time_GameOver;

			}
			if (time_GameOver == 0) {
				time_GameOver = 10;
				over = false;
				score = 3;
				snake.SetLength(3);
			}

		}
		window.clear(sf::Color::White);
		for (int i = 0; i < map_H; i++)
			for (int j = 0; j < map_W; j++)
			{
				map.setPosition(j * sizeS, i * sizeS);
				window.draw(map);
			}

		snake.Draw(&window);

		if (over == true) {
			if (time_GameOver != 0)
				window.draw(gameOver);
		}

		if (green_food_time0 == green_food_time1) {
			green_food.DrawFood(&window);
		}

		food.DrawFood(&window);
		window.draw(Score);
		window.display();
	}
}

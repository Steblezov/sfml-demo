#pragma once
#include<SFML/Graphics.hpp>


class Snake {
public:
	Snake(int length);

	void UpdatePhysics(bool& over);

	void Draw(sf::RenderWindow* window)const;

	const sf::Vector2i& SnakeHead()const;

	void SetLength(int n);

	void SetDir(int dir);

private:
	sf::Vector2i snake_pos_[200];
	int dir_;
	int length_;
	sf::Texture texture_snake_body_;
	sf::Texture texture_snake_head_;
	const int map_H = 20;
	const int map_W = 27;
	const int sizeS = 24;
};

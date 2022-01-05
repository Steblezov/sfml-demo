#include "snake.h"
#include <SFML/Graphics.hpp>

Snake::Snake(int length) {
	dir_ = 4;
	length_ = length;
	texture_snake_body_.loadFromFile("Sprite-0001.png");
	texture_snake_head_.loadFromFile("Sprite-0002.png");
}

void Snake::UpdatePhysics(bool& over) {
	for (int i = length_; i > 0; --i) {
		snake_pos_[i].x = snake_pos_[i - 1].x;
		snake_pos_[i].y = snake_pos_[i - 1].y;
	}
	switch (dir_) {
	case 1:
		snake_pos_[0].x += 1;
		break;
	case  2:
		snake_pos_[0].x -= 1;
		break;
	case 3:
		snake_pos_[0].y -= 1;
		break;
	case 4:
		snake_pos_[0].y += 1;
		break;
	}
	if (snake_pos_[0].x > map_W - 1)
		snake_pos_[0].x = 0;
	if (snake_pos_[0].x < 0)
		snake_pos_[0].x = map_W - 1;
	if (snake_pos_[0].y > map_H - 1)
		snake_pos_[0].y = 0;
	if (snake_pos_[0].y < 0)
		snake_pos_[0].y = map_H - 1;
	for (int i = 1; i < length_; i++) {
		if (snake_pos_[0].x == snake_pos_[i].x && snake_pos_[0].y == snake_pos_[i].y)
			over = true;
	}
}
void Snake::Draw(sf::RenderWindow* window)const {
	sf::Sprite snake_head(texture_snake_head_);
	sf::Sprite snake_body(texture_snake_body_);

	snake_head.setOrigin(12, 12);
	switch (dir_) {
	case 1:
		snake_head.setRotation(90);
		snake_head.setOrigin(0, 24);
		break;
	case  2:
		snake_head.setRotation(-90);
		snake_head.setOrigin(24, 0);
		break;
	case 3:
		snake_head.setRotation(360);
		snake_head.setOrigin(0, 0);
		break;
	case 4:
		snake_head.setRotation(-180);
		snake_head.setOrigin(24, 24);
		break;
	}
	for (int i = 0; i < length_; ++i) {
		if (i == 0) {
			snake_head.setPosition(snake_pos_[i].x * sizeS, snake_pos_[i].y * sizeS);
			window->draw(snake_head);
		}
		else {
			snake_body.setPosition(snake_pos_[i].x * sizeS, snake_pos_[i].y * sizeS);
			window->draw(snake_body);
		}
	}
}

const sf::Vector2i& Snake::SnakeHead()const {
	return snake_pos_[0];
}

void Snake::SetLength(int n) {
	length_ = n;
}

void Snake::SetDir(int dir) {
	dir_ = dir;
}

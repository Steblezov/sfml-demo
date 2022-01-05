#include "food.h"


Food::Food() {
	food_.x = rand() % map_W;
	food_.y = rand() % map_H;
	green_food_.x = rand() % map_W;
	green_food_.y = rand() % map_H;
	texture_food_.loadFromFile("Sprite-0003.png");
	texture_green_food_.loadFromFile("greenfood.png");
}

const sf::Vector2i& Food::FoodPos() const {
	return food_;
}
const sf::Vector2i& Food::GreenFoodPos() const {
	return green_food_;
}
void Food::UpdateFood() {
	food_.x = rand() % map_W;
	food_.y = rand() % map_H;
}
void Food::UpdateGheenFood() {
	green_food_.x = rand() % map_W;
	green_food_.y = rand() % map_H;
}

void Food::DrawFood(sf::RenderWindow* window) const {
	sf::Sprite food(texture_food_);
	food.setPosition(food_.x * sizeS, food_.y * sizeS);
	window->draw(food);
}
void Food::DrawGreenFood(sf::RenderWindow* window) const {
	sf::Sprite green_food(texture_green_food_);
	green_food.setPosition(green_food_.x * sizeS, green_food_.y * sizeS);
	window->draw(green_food);
}

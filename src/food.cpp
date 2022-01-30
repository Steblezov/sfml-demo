#include "food.h"


Food::Food(bool reg_food) {
	food_.x = rand() % map_W;
	food_.y = rand() % map_H;
	if (reg_food == true) {
		texture_food_.loadFromFile("Sprite-0003.png");
	}
	if (reg_food == false) {
		texture_food_.loadFromFile("greenfood.png");
	}
}

const sf::Vector2i& Food::FoodPos() const {
	return food_;
}
void Food::UpdateFood() {
	food_.x = rand() % map_W;
	food_.y = rand() % map_H;
}

void Food::DrawFood(sf::RenderWindow* window) const {
	sf::Sprite food(texture_food_);
	food.setPosition(food_.x * sizeS, food_.y * sizeS);
	window->draw(food);
}


#pragma once
#include "constants.h"
#include <SFML/Graphics.hpp>

class Food {
public:
	Food(int a);
	const sf::Vector2i& FoodPos() const;
	void UpdateFood();
	void DrawFood(sf::RenderWindow* window) const;
private:
	sf::Vector2i food_;
	sf::Texture texture_food_;
};


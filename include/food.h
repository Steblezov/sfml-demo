#pragma once
#include "constants.h"
#include <SFML/Graphics.hpp>

class Food {
public:
	Food();
	const sf::Vector2i& FoodPos() const;
	const sf::Vector2i& GreenFoodPos() const;
	void UpdateFood();
	void UpdateGheenFood();
	void DrawFood(sf::RenderWindow* window) const;
	void DrawGreenFood(sf::RenderWindow* window) const;
private:
	sf::Vector2i food_;
	sf::Vector2i green_food_;
	sf::Texture texture_food_;
	sf::Texture texture_green_food_;
};


#pragma once

#include<SFML/Graphics.hpp>

#include<utility>

struct Fruit
{
	Fruit();

	void draw(sf::RenderWindow& window);

	void random_position();
	bool HasBeenEaten();

	void SetHasBeenEaten();

	bool has_been_eaten = false;
	int random_x = 42;
	int random_y = 79;

	sf::Texture texture;
	sf::Sprite sprite;
};
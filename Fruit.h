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

	void Hide();

	bool has_been_eaten = false;
	int random_x = 42;
	int random_y = 79;
	bool should_be_hidden = false;

	sf::Texture texture;
	sf::Sprite sprite;
};
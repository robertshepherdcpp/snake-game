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
	int random_x = 94;
	int random_y = 90;
	bool should_be_hidden = false;

	sf::Vector2u window_size{};

	int window_size_x = 0;
	int window_size_y = 0;

	//sf::Texture texture;
	sf::CircleShape sprite;
};
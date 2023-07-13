#include<SFML/Graphics.hpp>

#include<utility>
#include<random>

#include "Fruit.h"

Fruit::Fruit()
{
	texture.loadFromFile("fruit.png");
	sprite.setTexture(texture);
}

void Fruit::draw(sf::RenderWindow& window)
{
	random_position();
	sprite.setPosition(random_x, random_y);
	window.draw(sprite);
}

void Fruit::random_position()
{
	if (has_been_eaten)
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 170);
		random_x = dist6(rng);

		std::random_device dev_two;
		std::mt19937 rng_two(dev_two());
		std::uniform_int_distribution<std::mt19937::result_type> dist6_two(0, 100);
		random_y = dist6_two(rng_two);
		has_been_eaten = false;
	}
	else
	{
		// do nothing as we already have our random number
	}
}

bool Fruit::HasBeenEaten()
{
	return has_been_eaten;
}

void Fruit::SetHasBeenEaten()
{
	has_been_eaten = true;
}
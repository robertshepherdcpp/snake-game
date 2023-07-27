#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include<utility>
#include<random>
#include<iostream>
#include<thread>

#include "Fruit.h"

Fruit::Fruit()
{
	texture.loadFromFile("fruit.png");
	sprite.setTexture(texture);
}

void Fruit::draw(sf::RenderWindow& window)
{
	window_size = window.getSize();
	window_size_x = window_size.x - sprite.getGlobalBounds().width * 2;
	window_size_y = window_size.y - sprite.getGlobalBounds().height * 2;
	if (should_be_hidden == false)
	{
		random_position();
		sprite.setPosition(random_x, random_y);
		window.draw(sprite);
	}
}

void Fruit::random_position()
{
	if (has_been_eaten)
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(0, window_size_x);
		random_x = dist6(rng);

		std::random_device dev_two;
		std::mt19937 rng_two(dev_two());
		std::uniform_int_distribution<std::mt19937::result_type> dist6_two(0, window_size_y);
		random_y = dist6_two(rng_two);
		has_been_eaten = false;

		std::cout << "(" << random_x << ", " << random_y << ")\n";
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
	std::thread thread([]() {
		sf::SoundBuffer Buffer;
		if (!Buffer.loadFromFile("eat_sound.wav"))
		{
			// Error...
		}
		sf::Sound Sound;
		Sound.setBuffer(Buffer); // Buffer is a sf::SoundBuffer
		Sound.play();
		});
	thread.join();
	has_been_eaten = true;
	std::cout << "Fruit has been eaten\n";
}

void Fruit::Hide()
{
	should_be_hidden = true;
}